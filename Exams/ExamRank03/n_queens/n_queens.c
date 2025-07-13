/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   n_queens.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 13:25:45 by erazumov          #+#    #+#             */
/*   Updated: 2025/07/13 14:02:03 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>

// Le tableau pour stocker les positions des reines reste le même
int	g_board[15];

/**
 * @brief Vérifie si il est sûr de placer une reine à la position (row, col)
 * @param row La ligne où on veut placer la reine
 * @param col La colonne où on veut placer la reine
 * @return int 1 si la position est sûre, 0 sinon
 * @abs La fonction qui calcule la valeur absolue d'un nombre entier (int).
 * 		La valeur absolue d'un nombre est sa distance par rapport à zéro,
 * 		sans tenir compte de son signe.
 */
int	is_safe(int row, int col)
{
	int	i;

	i = 0;
	while (i < col)
	{
		// Vérification des menaces (ligne et diagonale) est inchangée
		if (g_board[i] == row || abs(g_board[i] - row) == abs(i - col))
			return (0); // Position non sûre
		i++;
	}
	return (1); // Position sûre
}

/**
 * @brief Affiche une solution trouvée au format requis
 * @param n La taille de l'échiquier
 */
void	print_solution(int n)
{
	int		i;
	char	c;

	i = 0;
	while (i < n)
	{
		c = g_board[i] + '0';
		write(1, &c, 1);
		if (i < n - 1)
			write(1, " ", 1);
		i++;
	}
	write(1, "\n", 1);
}

void	solve_n_queens(int col, int n)
{
	int	row;

	if (col == n)
	{
		print_solution(n);
		return ;
	}
	row = 0;
	while (row < n)
	{
		if (is_safe(row, col))
		{
			g_board[col] = row;
			solve_n_queens(col + 1, n);
		}
		row++;
	}
}

int	main(int ac, char **av)
{
	int	n;

	// Verifier, si le programme a l'autres arguments que son nom
	if (ac != 2)
		return (1);

	n = atoi(av[1]);

	if (n <= 0)
		return (0);

	solve_n_queens(0, n);
	return (0);
}
