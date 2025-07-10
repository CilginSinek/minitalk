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
#include <stdio.h>
volatile sig_atomic_t ack_received;

void	signal_counter(int sig)
{
	static int	i;
    ack_received = 1;
	if (sig == SIGUSR1)
	{
		ft_putnbr(((i + 1) / 8) - 1);
		i = 0;
		exit(0);
	}
	else if (sig == SIGUSR2)
		i++;
}

void send_bit(int pid, int bit) {
	int timeout_ms;
    int interval_ms;
    int elapsed;

	timeout_ms = 1000;
	interval_ms = 10;
	elapsed = 0;
    ack_received = 0;
    if (bit)
        kill(pid, SIGUSR2);
    else
        kill(pid, SIGUSR1);
    while (elapsed < timeout_ms) {
        if (ack_received)
            return;
        usleep(interval_ms * 1000);
        elapsed += interval_ms;
    }
	if(!ack_received)
		exit(EXIT_FAILURE);
}

void	send_char(int pid, unsigned char c)
{
	int	bit;
	int	i;

	i = 0;
	while (i < 8)
	{
		bit = (c >> (7 - i)) & 1;
        send_bit(pid, bit);
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
        sigemptyset(&sa.sa_mask);
		sa.sa_handler = signal_counter;
		sigaction(SIGUSR1, &sa, NULL);
		sigaction(SIGUSR2, &sa, NULL);
		pid = ft_atoi(argv[1]);
		str = (char *)(argv[2]);
		while (*str)
			send_char(pid, *str++);
		send_char(pid, '\0');
	}
	return (0);
}
