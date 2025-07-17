/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   n_queens.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 13:25:45 by erazumov          #+#    #+#             */
/*   Updated: 2025/07/17 13:24:06 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "n_queens.h"

#define MAX_N 20

// Affiche une solution
void	print_solution(int *board, int n)
{
	for (int i = 0; i < n; i++)
	{
		fprintf(stdout, "%d", board[i]);
		if (i != n - 1)
			fprintf(stdout, " ");
	}
	fprintf(stdout, "\n");
}

// Vérifie si une position est sûre
int	is_safe(int *board, int row, int col)
{
	for (int i = 0; i < col; i++)
	{
		// Vérification des menaces (ligne et diagonale) est inchangée
		if (board[i] == row
			|| (board[i] - row == i - col)
			|| (board[i] - row == col - i))
			return (0); // Position non sûre
	}
	return (1); // Position sûre
}

// Fonction récursive pour résoudre le problème
void	solve_nqueens(int *board, int col, int n)
{
	if (col == n)
	{
		print_solution(board, n);
		return ;
	}
	for (int row = 0; row < n; row++)
	{
		if (is_safe(board, row, col))
		{
			board[col] = row;
			// On passe le 'board' à l'appel récursif
			solve_nqueens(board, col + 1, n);
		}
	}
}

int	main(int ac, char **av)
{
	if (ac != 2)
	{
		write(1, "\n", 1);
		return (0);
	}

	int	n = atoi(av[1]);
	if (n < 1 || n > MAX_N)
	{
		write(1, "\n", 1);
		return (0);
	}

	int	board[MAX_N]; // Le tableau est créé localement dans main
	solve_nqueens(board, 0, n);

	return (0);
}
