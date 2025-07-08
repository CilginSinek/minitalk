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