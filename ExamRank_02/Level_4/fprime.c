#include <unistd.h>

void	ft_putchar(char c)
{
	write(1, &c, 1);
}

void	ft_putstr(char *str)
{
	int i;

	i = 0;
	while (str[i])
		i++;
	write(1, str, i);
}

void	ft_putnbr(int n)
{
	if (n < 0)
	{
		n = -n;
		ft_putchar('-');
	}
	if (n >= 10)
		ft_putnbr(n / 10);
	ft_putchar((n % 10) + '0');
}

int		ft_atoi(char *s)
{
	int		num;
	int		sign;

	sign = 1;
	num = 0;
	while (*s == '\t' || *s == '\n' || *s == '\v' || \
			*s == '\f' || *s == '\r' || *s == ' ')
		s++;
	if (*s == '-')
		sign = -1;
	while ((*s == '-') || (*s == '+'))
		s++;
	while (*s && *s >= '0' && *s <= '9')
		num = (num * 10) + ((int)(*(s++)) - '0');
	return (num * sign);
}

void	fprime(int nbr)
{
	int		i;

	i = 2;
	if (nbr == 1)
		ft_putchar('1');
	while (nbr >= i)
	{
		if (nbr % i == 0)
		{
			ft_putnbr(i);
			if (nbr == i)
				break ;
			else
				ft_putchar('*');
			nbr /= i;
			i = 2;
		}
		i++;
	}
}

int		main(int argc, char *argv[])
{
	if (argc == 2)
		fprime(ft_atoi(argv[1]));
	ft_putchar('\n');
	return (0);
}


