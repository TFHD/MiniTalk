/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabartho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 16:12:21 by sabartho          #+#    #+#             */
/*   Updated: 2024/11/02 20:02:47 by sabartho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minitalk.h"

char	*ft_charjoin(char const *s, char c)
{
	char			*join;
	unsigned long	len_tot;
	int				i;
	int				j;

	i = 0;
	j = 0;
	if (!s || !c)
		return (0);
	len_tot = ft_strlen(s) + 1;
	join = malloc(sizeof(char) * len_tot + 1);
	if (!join)
		return (0);
	if (s)
		while (s[i])
			join[j++] = (char)s[i++];
	join[j++] = c;
	join[j] = '\0';
	free((char *)s);
	return (join);
}

char	*init_str(char *str)
{
	if (!str)
	{
		str = malloc(1);
		if (!str)
			return (0);
		*str = 0;
	}
	return (str);
}

void	handle_signal(int signal, siginfo_t *siginfo, void *s)
{
	static char				*str;
	static unsigned char	c;
	static int				i;

	s = 0;
	str = init_str(str);
	c |= (signal == SIGUSR1);
	if ((++i) == 8)
	{
		if (c == 0)
		{
			ft_printf("%s", str);
			free(str);
			str = 0;
			kill(siginfo->si_pid, SIGUSR1);
		}
		else
			str = ft_charjoin(str, c);
		i = 0;
		c = 0;
	}
	else
		c <<= 1;
}

int	main(void)
{
	struct sigaction	sig;

	ft_printf("┌───────────────────────────────────────────┐\n");
	ft_printf("│___  ___ _         _   _____       _  _    │\n");
	ft_printf("│|  \\/  |(_)       (_) |_   _|     | || |   │\n");
	ft_printf("│| .  . | _  _ __   _    | |  __ _ | || | __│\n");
	ft_printf("│| |\\/| || || '_ \\ | |   | | / _` || || |/ /│\n");
	ft_printf("│| |  | || || | | || |   | || (_| || ||   < │\n");
	ft_printf("│\\_|  |_/|_||_| |_||_|   \\_/ \\__,_||_||_|\\_\\│\n");
	ft_printf("└───────────────────────────────────────────┘\n");
	ft_printf("Server PID : %d\n", getpid());
	sig.sa_sigaction = handle_signal;
	sigemptyset(&sig.sa_mask);
	sig.sa_flags = SA_SIGINFO;
	sigaction(SIGUSR1, &sig, NULL);
	sigaction(SIGUSR2, &sig, NULL);
	while (1)
		pause();
	return (0);
}
