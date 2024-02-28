#include "ft_ping.h"

t_pr pr;

uint16_t in_cksum(uint16_t *addr, int len)
{
    int nleft = len;
    uint32_t sum = 0;
    uint16_t *w = addr;
    uint16_t answer = 0;
    
    while (nleft > 1)
    {
        sum += *w++;
        nleft -= 2;
    }
    if (nleft == 1)
    {
        *(unsigned char *)(&answer) = *(unsigned char *)w;
        sum += answer;
    }
    sum = (sum >> 16) + (sum & 0xffff); 
    sum += (sum >> 16);                 
    answer = ~sum;                      
    return (answer);
}

void tv_sub(struct timeval *out, struct timeval *in)
{
    if ((out->tv_usec -= in->tv_usec) < 0)
    { /* out -= in */
        --out->tv_sec;
        out->tv_usec += 1000000;
    }
    out->tv_sec -= in->tv_sec;
}

void 	print_stat(struct icmp *icmp, struct timeval *tvrecv, int icmplen, int ip_ttl)
{
    struct timeval *tvsend;
    double rtt;
    char addr[150];
	double tmvar;
	long long tmdev;
	long triptime;

    tvsend = (struct timeval *)icmp->icmp_data;
    tv_sub(tvrecv, tvsend);
    rtt = tvrecv->tv_sec * 1000.0 + tvrecv->tv_usec / 1000.0;
    if(pr.opt_tmstp)
    {
        printf("[%ld.", tvsend->tv_sec);
        printf("%ld]", tvsend->tv_usec);
    }
	triptime = tvrecv->tv_sec * 1000000 + tvrecv->tv_usec;
    printf("%d bytes from ", icmplen);
    ft_name_addr(pr.iaddr, addr);
	!pr.opt_num ? printf("(%s)", addr) : printf("%s", addr);
    printf(" icmp_seq=%u ", pr.n_sent);
    if (ip_ttl != 0)
        printf("ttl=%d ", ip_ttl);
    if (icmp->icmp_code == 0)
        printf("time = %.3f ms\n", rtt);
	pr.rtt_min = (pr.rtt_min == 0) ? rtt : ft_min(rtt, pr.rtt_min); 
	pr.rtt_max = (pr.rtt_max == 0) ? rtt : ft_max(rtt, pr.rtt_max);
   	pr.rtt_sum += triptime;	
	pr.rtt_sum2 += triptime * triptime;
	if (pr.opt_count == 1 && pr.count == pr.n_sent)
 	{
		pr.n_recv++;
		print_stat_end();
	}
}

int proc_v4(char *ptr, ssize_t len, struct timeval *tvrecv)
{
    int hlenl;
    int icmplen;
    struct ip *ip;
    struct icmp *icmp;

    ip = (struct ip *)ptr;  /* start of IP header */
    hlenl = ip->ip_hl << 2; /* length of IP header */
    if (ip->ip_p != IPPROTO_ICMP)
        return -1;                          /* not ICMP */
    icmp = (struct icmp *)(ptr + hlenl); /* start of ICMP header */
    if ((icmplen = len - hlenl) < 8)
        return -1; /* malformed packet */
    if (icmp->icmp_type == ICMP_ECHOREPLY)
    {
        if (icmp->icmp_id != pr.pid)
            return -1; /* not a response to our ECHO_REQUEST */
        if (icmplen < 16)
            return -1;
        print_stat(icmp, tvrecv, icmplen, ip->ip_ttl);

		return 1;
    }
    else
		icmp_error(icmp, tvrecv, icmplen, icmp->icmp_code, ptr);
    
        
	return -1;
}

void print_stat_end()
{
    int time;
    struct timeval last;
    int pourcent;
	long long tmvar;
	long tmdev;

    gettimeofday(&last, NULL);
    time = (int) (last.tv_sec - pr.first.tv_sec) * 1000 + (last.tv_usec - pr.first.tv_usec) / 1000.0;
    pr.n_loss = pr.n_sent - pr.n_recv;
	pourcent = (pr.n_sent != 0) ? (pr.n_loss / pr.n_sent) * 100 : 0; 
    printf("\n-- %s ping statistics--\n", pr.buf_name);
	printf("%d packets transmitted, ",pr.n_sent);
	if (pr.err != 0)
		printf("+%d errors,", pr.err);
	printf("%d received, ",pr.n_recv);
	printf("%d%% packet loss, ",pourcent);
	printf("time %d ms\n", time);
	pr.rtt_avg = pr.rtt_sum / ((double) pr.n_recv * 1000);
	if (!pr.n_loss && !pr.err && pr.n_recv > 0)	
	{
		printf("rtt min/avg/max/mdev %.3f/%.3f/%.3f", pr.rtt_min, pr.rtt_avg, pr.rtt_max);
    	tmvar = (pr.rtt_sum2 - ((pr.rtt_sum * pr.rtt_sum ) / (double) pr.n_recv ) / (double) pr.n_recv);
    	tmdev = llsqrt(tmvar);
		printf("/%ld.%03ld ms", (long)(tmdev / TR), (long)(tmdev % TR));
	}
	exit(EXIT_SUCCESS);
}

int main(int ac, char **av)
{
    int size;
    struct timeval timeout;
    int nb_addr;

	ft_memset(&pr, 0, sizeof(t_pr));
    default_option();
	nb_addr = try_opt_addr(ac, av);
    if (ac > 2) 
        ft_getopt(av, ac, nb_addr);
	dns_lookup(av[nb_addr], &pr);
    if ((pr.sockfd = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP)) < 0)
        e_printf("erreur socket (sudo ?)", 0);
    timeout.tv_sec = 1;
    timeout.tv_usec = 0;
    if (setsockopt(pr.sockfd, SOL_SOCKET, SO_RCVTIMEO, &timeout, sizeof (timeout)) < 0)
        e_printf("setsockopt failed", 0);
    if (pr.opt_verb == 1)
        printf("ping: socket: Permission denied, attempting raw socket...\n");
    pr.pid = getpid() & 0xffff; /* ICMP ID field is 16 bits */
    pr.rtt_max = 0;
    pr.rtt_min = 0;
	setsockopt(pr.sockfd, IPPROTO_IP, IP_TTL, &(pr.ttl), sizeof(u_int8_t));
	send_loop();
}
