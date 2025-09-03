/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   microshell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 13:24:42 by erazumov          #+#    #+#             */
/*   Updated: 2025/09/03 13:32:22 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "microshell.h"

/**
 * @brief Calcule la longueur d'une chaîne.
 */
int	ft_strlen(char *str)
{
	int	i = 0;

	while (str && str[i])
		i++;
	return (i);
}

/**
 * @brief Affiche "error: fatal" et quitte.
 */
void	fatal_error(void)
{
	print_error("error: fatal", NULL);
		exit(1);
}
