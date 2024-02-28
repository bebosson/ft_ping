#include "ft_ping.h"

int		ft_getopt(char **av, int ac, int nbr_add)
{
	const char *list_opt = "-hvitncD";  
	const char *list_opt_num = "itc";  
	int i;
	int j;

	i = 0;
	while (++i < ac)
	{
		j = 0;
		if (av[i][j] == list_opt[j] && ft_strlen(av[i]) < 3 && i != nbr_add) //  && i != nbr_add
		{
			if (!ft_strchr(list_opt + 1, av[i][j + 1]))
				print_help_exit();
			else if (ft_strchr(list_opt_num, av[i][j + 1]))
			{
				if (i + 1 < ac && ft_str_is_numeric(av[i + 1]) && i + 1 != nbr_add) //i + 1 != nbr_add
				{
					save_opt_num(av[i][j + 1], ft_atoi(av[i + 1]));
					i+=1;
				}
				else
					print_help_exit();
			}
			else
				save_opt(av[i][j + 1]);
		}
		else if (i != nbr_add)
			print_help_exit();

	}
	return (0);
}

int		try_opt_addr(int ac, char **av)
{
	int i;
	int j; 
	struct addrinfo ai_addr;
    struct addrinfo *p_adr;
    struct sockaddr_in *sock_addr;


    i = 0;
	j = 0;
	ft_memset(&ai_addr, 0, sizeof(ai_addr));
    while (++i < ac)
	{
		if (getaddrinfo(av[i], NULL, &ai_addr, &p_adr) >= 0)
		{
			if (i - 1 > 0 && av[i - 1][0] == '-' && ft_strchr("itc", av[i - 1][1]))
				continue;
			else if (j == 0)
				j = i;
			else
				print_help_exit();
		}			
	}
	return (j);
}