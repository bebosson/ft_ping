#include "ft_ping.h"

void send_signal_set_alrm()
{
    send_v4();
 	alarm(pr.iter); 
}

void send_v4()
{
    int len;
    struct icmp *icmp;
    int datalen;
    char sendbuf[64];
    int data_send = 0;

    icmp = (struct icmp *)sendbuf;
    icmp->icmp_type = ICMP_ECHO;
    icmp->icmp_code = 0;
    icmp->icmp_id = pr.pid;
    icmp->icmp_seq = pr.n_sent++;
    datalen = DATALEN; // header_len ? 
    ft_memset(icmp->icmp_data, 0, datalen); /* fill with pattern */
    gettimeofday((struct timeval *)icmp->icmp_data, NULL);
    len = 8 + datalen; /* checksum ICMP header and data */
	icmp->icmp_cksum = 0;
    icmp->icmp_cksum = in_cksum((u_short *)icmp, len);
    if((data_send = sendto(pr.sockfd, sendbuf, len, 0, pr.sasend, pr.salen)) < 0)
        printf("sendto: le reseau n'est pas accessible\n");
}


void set_signal()
{
    signal(SIGALRM, send_signal_set_alrm);
    signal(SIGINT, print_stat_end);
    static_addr_info();
    alarm(pr.iter);
    gettimeofday(&pr.first, NULL);
}

void send_loop()
{
    struct msghdr msg;
    struct iovec iov;
    char recvbuf[BUFSIZE];
    char controlbuf[BUFSIZE];
    struct timeval tval;
    ssize_t n;

    ft_bzero(recvbuf, sizeof(recvbuf));
    iov.iov_base = recvbuf;
    iov.iov_len = sizeof(recvbuf);
    msg.msg_name = pr.sarecv;
    msg.msg_iov = &iov;
    msg.msg_iovlen = 1;
    msg.msg_control = controlbuf;
    set_signal();
    while (1)
    {
        msg.msg_namelen = pr.salen;
        msg.msg_controllen = sizeof(controlbuf);
        if ((n = recvmsg(pr.sockfd, &msg, 0)) > 0)
        {
            ft_bzero(&tval, sizeof(tval));
            gettimeofday(&tval, NULL);
            proc_v4(recvbuf, n, &tval) > 0 ? pr.n_recv++ : pr.err++;
		}
    }
}
