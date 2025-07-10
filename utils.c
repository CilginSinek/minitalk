/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iduman <iduman@student.42istanbul.com.tr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 14:35:13 by iduman            #+#    #+#             */
/*   Updated: 2025/07/10 14:35:13 by iduman           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static int	strlenspc(const char *str)
{
	int	len;

	len = 0;
	while (str[len] == ' ' || (str[len] >= 9 && str[len] <= 13))
		len++;
	return (len);
}

int	ft_atoi(const char *str)
{
	int			result;
	int			i;
	signed char	a;

	result = 0;
	i = 0 + strlenspc(str);
	a = 1;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			a = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + (str[i] - '0');
		i++;
	}
	return (result * a);
}

void	ft_putchar(char c)
{
	write(1, &c, 1);
}

void	ft_putnbr(int n)
{
	long	nbr;

	nbr = n;
	if (nbr < 0)
	{
		nbr *= -1;
		ft_putchar('-');
	}
	if (nbr >= 10)
	{
		ft_putnbr(nbr / 10);
		ft_putchar((nbr % 10) + '0');
		nbr /= 10;
	}
	else
	{
		ft_putchar(nbr + '0');
	}
}