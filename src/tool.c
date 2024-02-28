#include "ft_ping.h"

void	print_help_exit()
{
	const char *help = "Usage: ping [-hvcitD] [-h help] [-v verbose] [-c count] \n \
[-i interval] [-t ttl] [-D timestamp]\n";

	printf("%s",help);
	exit(EXIT_SUCCESS);
}


void    e_printf(char *msg, int e)
{
    printf("%s \n", msg);
    (e > 0) ? exit(EXIT_SUCCESS) : exit(EXIT_FAILURE);
}

double	ft_min(double a, double b)
{
   double ret;
   
   ret = (a > b) ? b : a;
   return (ret);
}

double ft_max(double a, double b)
{
   double ret;

   ret = (a > b) ? a : b;
   return (ret);
}

long llsqrt(long long a)
{
	long long prev = LLONG_MAX;
	long long x = a;

	if (x > 0) {
		while (x < prev) {
			prev = x;
			x = (x + (a / x)) / 2;
		}
	}

	return (long)x;
}
