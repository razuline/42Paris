#include <stdlib.h>
#include <stdio.h>

int		nbr_len(int nbr)
{
	int i;

	i = 1;
	if (nbr < 0)
	{
		i++;
		nbr *= -1;
	}
	while (nbr > 9)
	{
		nbr /= 10;
		i++;
	}
	return (i);
}

int		ft_div(int len)
{
	int i;

	i = 1;
	if (len == 1)
		return (1);
	while (len > 1)
	{
		i *= 10;
		len--;
	}
	return (i);
}

char	*ft_itoa(int nbr)
{
	int i;
	int len;
	int len2;
	char *result;

	i = 0;
	len = nbr_len(nbr);
	len2 = len;
	if ((result = (char*)malloc(sizeof(char) * (len + 1))) == NULL)
		return (NULL);
	if (nbr == -2147483648)
		return ("-2147483648\0");
	if (nbr < 0)
	{
		nbr *= -1;
		result[0] = '-';
		i++;
		len--;
	}
	while (i < len2)
	{
		result[i] = ((nbr / ft_div(len)) % 10) + 48;
		len--;
		i++;
	}
	result[i] = '\0';
	return (result);
}

int	main(void)
{
	printf("0 -> %s\n", ft_itoa(0));
	printf("1 -> %s\n", ft_itoa(1));
	printf("42 -> %s\n", ft_itoa(42));
	printf("1001 -> %s\n", ft_itoa(1001));
	printf("0-> %s\n", ft_itoa(-0));
	printf("-2-> %s\n", ft_itoa(-2));
	printf("-24-> %s\n", ft_itoa(-24));
	printf("-2147483648-> %s\n", ft_itoa(-2147483648));
	printf("2147483647-> %s\n", ft_itoa(2147483647));
}
