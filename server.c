/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iduman <iduman@student.42istanbul.com.tr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 14:34:53 by iduman            #+#    #+#             */
/*   Updated: 2025/07/10 14:34:53 by iduman           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"
#include <stdio.h>

void	string_handler(int sig, siginfo_t *info, void *context)
{
	static int	bit_index;
	static char	character;

	if (!character)
		character = 0;
	(void)context;
	character |= (sig == SIGUSR2);
	bit_index++;
	if (bit_index == 8)
	{
		bit_index = 0;
		if (character == '\0')
		{
			kill(info->si_pid, SIGUSR1);
			character = 0;
			return ;
		}
		else
			write(1, &character, 1);
		character = 0;
		kill(info->si_pid, SIGUSR2);
		usleep(100);
	}
	else
		character = character << 1;
}

int	main(void)
{
	struct sigaction	sa;
	int					pid;

	pid = getpid();
	ft_putnbr(pid);
	ft_putchar('\n');
	sa.sa_flags = SA_SIGINFO;
	sa.sa_sigaction = string_handler;
	sigemptyset(&sa.sa_mask);
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	while (1)
		pause();
	return (0);
}
