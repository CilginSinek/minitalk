/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iduman <iduman@student.42istanbul.com.tr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 14:35:10 by iduman            #+#    #+#             */
/*   Updated: 2025/07/10 14:35:10 by iduman           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	signal_handler(int sig)
{
	static int	i;

	if (sig == SIGUSR1)
	{
		ft_putnbr(i);
		i = 0;
		exit(0);
	}
	else if (sig == SIGUSR2)
		i++;
}

void	send_char(int pid, char c)
{
	int	bit;
	int	i;

	i = 0;
	while (i < 8)
	{
		bit = (c >> (7 - i)) & 1;
		if (bit == 0)
			kill(pid, SIGUSR1);
		else
			kill(pid, SIGUSR2);
		usleep(300);
		i++;
	}
}

int	main(int argc, char const *argv[])
{
	int					pid;
	char				*str;
	struct sigaction	sa;

	if (argc == 3)
	{
		sa.sa_handler = signal_handler;
		sigaction(SIGUSR1, &sa, NULL);
		sigaction(SIGUSR2, &sa, NULL);
		pid = ft_atoi(argv[1]);
		str = (char *)(argv[2]);
		while (*str)
			send_char(pid, *str++);
		send_char(pid, '\0');
		sleep(1000);
	}
	return (0);
}
