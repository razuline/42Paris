#include <stdlib.h>
#include <stdio.h>
# define WD_NUM 1000
# define WD_LEN 1000

char	**ft_split(char *str)
{
	int	i;
	int	j;
	int	k;
	char **tab;

	i = 0;
	j = 0;
	tab = (char**)malloc(sizeof(**tab) * WD_NUM);
	while (str[i] == ' ' || str[i] == '\t' || str[i] == '\n')
		i++;
	while (str[i] != '\0')
	{
		if (str[i] > 32)
		{
			k = 0;
			tab[j] = (char*)malloc(sizeof(char) * WD_LEN);
			while (str[i] > 32)
			{
				tab[j][k] = str[i];
				i++;
				k++;
			}
			tab[j][k] = '\0';
			j++;
		}
		else
			i++;
	}
	tab[j] = 0;
	return (tab);
}

int	main(void)
{
	char	*str;
	char	**res;

	str = "Hello, how are you?";
	res = ft_split(str);
	while (*res)
	{
		printf("%s\n", *res);
		res++;
	}
	return (0);
}
