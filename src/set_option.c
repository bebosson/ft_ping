#include "ft_ping.h"

void	default_option()
{
	pr.ttl = TTLDEF;
	pr.iter = 1;
}

int		save_ttl(int num)
{
	if (num < 1 || num > TTL_MAX || pr.opt_ttl == 1)
	{
		if (num < 1)
			printf("ping: can't set unicast time-to-live: Argument invalide");
		else if (num > 255)
			printf("ping: ttl %d out of range", num);
		else if (pr.opt_ttl == 1)
			printf("option already set");
		exit(EXIT_FAILURE);
	}
	pr.ttl = num;
	return (1);
}

int 	save_count(int num)
{
	if (num < 1 || num > INT_MAX)
		e_printf("ping: bad number of packets to transmit", 0);
	if (pr.opt_count == 1)
		e_printf("option already set", 0);
	pr.count = num;
	return (1);
}

int		save_iter(int num)
{
	if (num < 1 || num > INT_MAX / 1000)
		e_printf("ping: bad timing interval", 0);
	if (pr.opt_iter == 1)
		e_printf("option already set", 0);
	pr.iter = num;
	return (1);
}


int		already_set(int opt)
{
	
	if (opt == 1)
		e_printf("option already set", 0);
	else
		return 1;
	return 0;
}

void 	save_opt_num(char opt, int num)
{
	switch (opt)
	{
		case 'i':
			pr.opt_iter = save_iter(num);
			break;
		case 't':
			pr.opt_ttl = save_ttl(num);
			break;
		case 'c':
			pr.opt_count = save_count(num);
			break;
	}
}

void 	save_opt(char opt)
{
	switch (opt)
	{
		case 'n':
			pr.opt_num = already_set((int)pr.opt_num); // 
			break;
		case 'v':
			pr.opt_verb = already_set((int)pr.opt_verb);
			break;
		case 'h':
			print_help_exit();
			break;
		case 'D':
			pr.opt_tmstp = already_set((int)pr.opt_tmstp);
			break;
	}
}