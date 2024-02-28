#include "ft_ping.h"

void read_icmp(struct icmp *icmp, char *debug)
{
    printf("-------READ ICMP PACKET %s----------\n", debug);
	icmp_type(icmp->icmp_type);
    icmp_code(icmp->icmp_code);
    printf("code = %d\n", icmp->icmp_code);
    printf("id = %d\n", icmp->icmp_id);
    printf("seq = %d\n", icmp->icmp_seq);
    printf("checksum = %x\n", icmp->icmp_cksum);
}

int id_error_icmp(char *pkt)
{
	struct icmp *icmp;
	icmp = (struct icmp *) (pkt + sizeof(struct icmp) + sizeof(struct ip));

    return  (icmp->icmp_id);
}
