/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   n_queens.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 13:25:45 by erazumov          #+#    #+#             */
/*   Updated: 2025/07/15 13:54:19 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @brief Vérifie si une position est sûre.
 * @param board Le tableau représentant l'échiquier.
 */
int	is_safe(int row, int col, int *board)
{
	int	i;

	i = 0;
	while (i < col)
	{
		// Vérification des menaces (ligne et diagonale) est inchangée
		if (board[i] == row || abs(board[i] - row) == abs(i - col))
			return (0); // Position non sûre
		i++;
	}
	return (1); // Position sûre
}

/**
 * @brief Affiche une solution.
 * @param board Le tableau représentant l'échiquier.
 */
void	print_solution(int n, int *board)
{
	int		i;
	char	c;

	i = 0;
	while (i < n)
	{
		c = board[i] + '0';
		write(1, &c, 1);
		if (i < n - 1)
			write(1, " ", 1);
		i++;
	}
	write(1, "\n", 1);
}

/**
 * @brief Fonction récursive pour résoudre le problème.
 * @param board Le tableau représentant l'échiquier.
 */
void	solve_n_queens(int col, int n, int *board)
{
	int	row;

	if (col == n)
	{
		print_solution(n, board);
		return ;
	}
	row = 0;
	while (row < n)
	{
		if (is_safe(row, col, board))
		{
			board[col] = row;
			// On passe le 'board' à l'appel récursif
			solve_n_queens(col + 1, n, board);
		}
		row++;
	}
}

int	main(int ac, char **av)
{
	int	n;
	int	board[15]; // Le tableau est créé localement dans main

	if (ac != 2)
		return (1);

	n = atoi(av[1]);
	if (n <= 0 || n > 15)
		return (0);
	// On lance la récursion en passant le tableau 'board'
	solve_n_queens(0, n, board);
	return (0);
}
