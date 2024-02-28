#ifndef FT_PING_H
# define FT_PING_H

#include <signal.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdio.h>
#include <limits.h>
#include <arpa/inet.h>
#include <netinet/ip_icmp.h>
#include "libft.h"
#include <sys/time.h>
#include <unistd.h>
#include <errno.h>

# define BUFSIZE 1500
# define DATALEN 56
# define TR 100000
# define PING_SLEEP_RATE 1000000
# define TTL_MAX 255
# define NORMAL_SIZE 56
# define TTLDEF 64

typedef struct s_pr
{
	int opt_num;
	int opt_count;  
	int opt_verb;
	int opt_iter;
    int opt_ttl;
    int opt_tmstp;
    int sockfd;
    pid_t pid;
    struct sockaddr *sasend;
    struct sockaddr *sarecv;
    socklen_t salen;
    struct timeval first;
    int n_sent;
    char *buf_name;
    uint32_t iaddr;
    int n_recv;
    int n_loss;
    double rtt_min;
    double rtt_max;
    double rtt_avg;
    double rtt_sum;
    double rtt_sum2;
	int iter;
	u_int8_t ttl;
    int err;
	int count;
}               t_pr;

extern t_pr pr;

/*              tool.c                      */
void        e_printf(char *msg, int e);
double      ft_min(double a, double b);
double      ft_max(double a, double b);
long        llsqrt(long long a);
void	    print_help_exit();
/*             parse_option.c               */
int		    try_opt_addr(int ac, char **av);
int	        ft_getopt(char **av, int ac, int nbr_add);
/*             set_option.c                  */
void	    default_option();
void     	save_opt_num(char opt, int num);
void    	save_opt(char opt);
/*             code_icmp.c                  */
void	    icmp_code(int code);
void        print_stat(struct icmp *icmp, struct timeval *tvrecv, int icmplen, int ip_ttl);
void	    icmp_type(int type);
void        icmp_error(struct icmp *icmp, struct timeval *tvrecv, int icmplen, int code, char *ptr);
/*             debug.c                       */
int         id_error_icmp(char *pkt);
/*              send.c                       */
void        send_v4();
void        send_loop();
/*              addr.c                          */
void        dns_lookup(char *addr, t_pr *pr);
void        ft_name_addr(u_int32_t addr, char *str);
void        static_addr_info();
/*              main.c                       */
uint16_t    in_cksum(uint16_t *addr, int len);
int         proc_v4(char *ptr, ssize_t len, struct timeval *tvrecv);
void        print_stat_end();

# endif