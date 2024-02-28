#include "ft_ping.h"


void	icmp_type(int type)
{
	switch (type)
	{
		case(ICMP_DEST_UNREACH):
			printf("ICMP_DEST_UNREACH");
			break;           
		case(ICMP_SOURCE_QUENCH):           /* Source Quench                */
			printf("ICMP_SOURCE_QUENCH");           
			break;           
		case(ICMP_REDIRECT):          /* Redirect (change route)      */
			printf("ICMP_REDIRECT");           
			break;           
		case(ICMP_ECHO):                    /* Echo Request                 */
			printf("ICMP_ECHO");           
			break;           
		case(ICMP_TIME_EXCEEDED):           /* Time Exceeded                */
			printf("time to live excedeed");           
			break;           
		case(ICMP_PARAMETERPROB):           /* Parameter Problem            */
			printf("ICMP_PARAMETERPROB");           
			break;           
		case(ICMP_TIMESTAMP):               /* Timestamp Request            */
			printf("ICMP_TIMESTAMP");           
			break;           
		case(ICMP_TIMESTAMPREPLY):          /* Timestamp Reply              */
			printf("ICMP_TIMESTAMPREPLY");           
			break;           
		case(ICMP_INFO_REQUEST):            /* Information Request          */
			printf("ICMP_INFO_REQUEST");           
			break;           
		case(ICMP_INFO_REPLY):              /* Information Reply            */
			printf("ICMP_INFO_REPLY");           
			break;           
		case(ICMP_ADDRESS):                 /* Address Mask Request         */
			printf("ICMP_ADDRESS");           
			break;           
		case(ICMP_ADDRESSREPLY):            /* Address Mask Reply           */
			printf("ICMP_ADDRESSREPLY");           
			break;                   
	}
}

void	icmp_code(int code)
{
	switch (code) {
		case ICMP_NET_UNREACH:
			printf("Destination Net Unreachable\n");
			break;
		case ICMP_HOST_UNREACH:
			printf("Destination Host Unreachable\n");
			break;
		case ICMP_PROT_UNREACH:
			printf("Destination Protocol Unreachable\n");
			break;
		case ICMP_PORT_UNREACH:
			printf("Destination Port Unreachable\n");
			break;
		case ICMP_FRAG_NEEDED:
			printf("Frag needed and DF set");
			break;
		case ICMP_SR_FAILED:
			printf("Source Route Failed\n");
			break;
		case ICMP_NET_UNKNOWN:
			printf("Destination Net Unknown\n");
			break;
		case ICMP_HOST_UNKNOWN:
			printf("Destination Host Unknown\n");
			break;
		case ICMP_HOST_ISOLATED:
			printf("Source Host Isolated\n");
			break;
		case ICMP_NET_ANO:
			printf("Destination Net Prohibited\n");
			break;
		case ICMP_HOST_ANO:
			printf("Destination Host Prohibited\n");
			break;
		case ICMP_NET_UNR_TOS:
			printf("Destination Net Unreachable for Type of Service\n");
			break;
		case ICMP_HOST_UNR_TOS:
			printf("Destination Host Unreachable for Type of Service\n");
			break;
		case ICMP_PKT_FILTERED:
			printf("Packet filtered\n");
			break;
		case ICMP_PREC_VIOLATION:
			printf("Precedence Violation\n");
			break;
		case ICMP_PREC_CUTOFF:
			printf("Precedence Cutoff\n");
			break;
		default:
			printf("Dest Unreachable, Bad Code: %d\n", code);
			break;
		}
}

void	print_stat_exceed(char *ptr)
{
	struct iphdr *iphdr;
	char addr[150];

	iphdr = (struct iphdr *) ptr;
	printf("From ");
    ft_name_addr(iphdr->saddr, addr);
	!pr.opt_num ? printf("(%s)", addr) : printf("%s", addr);
    printf(" icmp_seq=%u ", pr.n_sent);
	printf("Time to live excedeed \n");
}

void icmp_error(struct icmp *icmp, struct timeval *tvrecv, int icmplen, int code, char *ptr)
{
	struct icmp *icmphdr;
	icmphdr = (struct icmp *) (ptr + sizeof(struct ip));
	

	if (id_error_icmp(ptr) != pr.pid)
		return ;
	else
	{
		if (icmphdr->icmp_type == ICMP_TIME_EXCEEDED)
			print_stat_exceed(ptr);
		else
		{
			print_stat(icmp, tvrecv, icmplen, 0);
			icmp_code(code);
		}
	}
	return ;
}
