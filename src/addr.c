#include "ft_ping.h"


void dns_lookup(char *addr, t_pr *pr)
{
    struct addrinfo ai_addr;
    struct addrinfo *p_adr;
    struct sockaddr_in *sock_addr;
    char buf[100];

    ft_memset(&ai_addr, 0, sizeof(ai_addr));
    ai_addr.ai_family = AF_INET;
    ai_addr.ai_socktype = SOCK_STREAM;
    ai_addr.ai_flags = AI_CANONNAME;
    if (getaddrinfo(addr, NULL, &ai_addr, &p_adr) < 0)
    {
        printf("ping : %s : Name or service not known",addr);
        exit(EXIT_FAILURE);
    }
    if (p_adr->ai_addr->sa_family == AF_INET)
        sock_addr = (struct sockaddr_in *)p_adr->ai_addr;
    inet_ntop(AF_INET, &sock_addr->sin_addr.s_addr, buf, sizeof(buf));
    pr->iaddr = sock_addr->sin_addr.s_addr;
    pr->sasend = p_adr->ai_addr;
    pr->salen = p_adr->ai_addrlen;
	pr->buf_name = addr;
}


void ft_name_addr(u_int32_t addr, char *str)
{
    struct sockaddr_in sa;    /* input */
    socklen_t len;         /* input */
    char hbuf[1500];
    
    ft_memset(&sa, 0, sizeof(struct sockaddr_in));
    inet_ntop(AF_INET, &addr, str, 150);
    sa.sin_family = AF_INET;
    sa.sin_addr.s_addr = inet_addr(str);
    len = sizeof(struct sockaddr_in);
    if (getnameinfo((struct sockaddr *) &sa, len, hbuf, sizeof(hbuf), 
        NULL, 0, NI_NAMEREQD)) 
        printf("%s", str);
    else if (pr.opt_num == 0)
        printf("%s", hbuf);
}

void static_addr_info()
{
    char addr[150];
    printf("PING to ");
    ft_name_addr(pr.iaddr, addr);
    printf("(%s) ", addr);
	printf("%d(%d) bytes of data\n", NORMAL_SIZE, NORMAL_SIZE + 28);
}