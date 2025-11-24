/* 42 HEADER */

#include "rush02.h"

int	main(int argc, char **argv)
{
	t_dict	*dict;
	char	*dict_path;
	char	*num_to_convert;
	int		dict_size;

	if (argc < 2 || argc > 3)
	{
		ft_putstr("Error\n");
		return (1);
	}
	if (argc == 2)
	{
		dict_path = "numbers.dict";
		num_to_convert = argv[1];
	}
	else
	{
		dict_path = argv[1];
		num_to_convert = argv[2];
	}
	if (!is_valid_number(num_to_convert))
	{
		ft_putstr("Error\n");
		return (1);
	}
	dict = parse_dictionary(dict_path, &dict_size);
	if (!dict)
	{
		ft_putstr("Dict Error\n");
		return (1);
	}
	convert_number(num_to_convert, dict, dict_size);
	ft_putstr("\n");
	free_dictionary(dict, dict_size);
	return (0);
}
