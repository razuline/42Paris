/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_color.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 16:28:52 by erazumov          #+#    #+#             */
/*   Updated: 2026/01/09 19:30:29 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
** Parses a single RGB value and validates the 0-255 range.
*/
static int	parse_color_value(char *str)
{
	int	value;
	int	i;

	i = 0;
	while (str[i] && ft_isspace(str[i]))
		i++;
	if (!str[i] || !ft_isdigit(str[i]))
		return (-1);
	value = ft_atoi(&str[i]);
	if (value < 0 || value > 255)
		return (-1);
	return (value);
}

/*
** Validates the "ID R,G,B" format.
*/
static int	is_valid_color_format(char **words)
{
	if (count_elem(words) != 2)
	{
		ft_putstr_fd("Error\nInvalid color line format\n", 2);
		return (0);
	}
	return (1);
}

/*
** Parses the comma-separated string into three RGB integers.
*/
static int	parse_rgb_values(char *rgb_str, t_color *color)
{
	char	**rgb;

	rgb = ft_split(rgb_str, ',');
	if (!rgb || count_elem(rgb) != 3)
	{
		free_tab(rgb);
		ft_putstr_fd("Error\nColor must have 3 values (R,G,B)\n", 2);
		return (0);
	}
	color->r = parse_color_value(rgb[0]);
	color->g = parse_color_value(rgb[1]);
	color->b = parse_color_value(rgb[2]);
	free_tab(rgb);
	if (color->r < 0 || color->g < 0 || color->b < 0)
	{
		ft_putstr_fd("Error\nColor values must be 0-255\n", 2);
		return (0);
	}
	return (1);
}

/*
** Main function to parse a color configuration line.
*/
int	parse_color(t_color *color, char *line)
{
	char	**words;
	int		ret;

	replace_tabs(line);
	words = ft_split(line, ' ');
	if (!words)
		return (0);
	if (!is_valid_color_format(words))
	{
		free_tab(words);
		return (0);
	}
	if (color->r != -1)
	{
		ft_putstr_fd("Error\nDuplicate color definition\n", 2);
		free_tab(words);
		return (0);
	}
	ret = parse_rgb_values(words[1], color);
	free_tab(words);
	return (ret);
}
