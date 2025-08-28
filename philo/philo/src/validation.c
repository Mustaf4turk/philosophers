#include "philo.h"

int	ft_isdigit(int c)
{
	if (c >= 48 && c <= 57)
		return (2048);
	return (0);
}

int	is_natural_nbr(char *string)
{
	int	i;

	i = 0;
	while (string[i] != '\0')
	{
		if (!ft_isdigit(string[i]))
			return (0);
		i++;
	}
	return (1);
}

int	is_valid_input(int argc, char **argv)
{
	int	i;

	i = 1;
	if (argc < 5 || argc > 6)
		return (0);
	while (i < argc)
	{
		if (!is_natural_nbr(argv[i]) || *argv[1] == '0' \
			|| *argv[2] == '0' || *argv[3] == '0' || *argv[4] == '0')
			return (0);
		i++;
	}
	return (1);
}

int	to_natural_nbr(char *str)
{
	int	nbr_conv;

	nbr_conv = 0;
	while (*str)
	{
		nbr_conv = (nbr_conv * 10) + (*str - '0');
		str++;
	}
	return (nbr_conv);
}

