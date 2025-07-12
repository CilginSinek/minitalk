/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iduman <iduman@student.42istanbul.com.tr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 13:14:58 by iduman            #+#    #+#             */
/*   Updated: 2025/07/12 13:14:58 by iduman           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

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
		write(1, &character, 1);
		character = 0;
	}
	else
		character = character << 1;
	kill(info->si_pid, SIGUSR2);
}

int	main(void)
{
	struct sigaction	sa;
	int					pid;

	pid = getpid();
	ft_putnbr(pid);
	ft_putchar('\n');
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_SIGINFO;
	sa.sa_sigaction = string_handler;
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	while (1)
		pause();
	return (0);
}