/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   microshell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 14:09:16 by erazumov          #+#    #+#             */
/*   Updated: 2025/10/22 14:26:11 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <stdlib.h>

/**
 * Fonction d’affichage d’erreur
 */
void	ft_putstr_fd2(char *str, char *arg)
{
	while (*str)
		write(2, str++, 1);
	if (arg)
		while(*arg)
			write(2, arg++, 1);
	write(2, "\n", 1);
}

/*
 * Fonction d’exécution d’une commande
 */
void ft_exec(char **av, int i, int tmp_fd, char **env)
{
	av[i] = NULL;
	dup2(tmp_fd, STDIN_FILENO);
	close(tmp_fd);
	execve(av[0], av, env);
	ft_putstr_fd2("error: cannot execute ", av[0]);
	exit(1);
}

int	main(int ac, char **av, char **env)
{
	(void)ac;
	int		i = 1; // On commence à l'index 1, après le nom du programme
	int		fd[2];
	int		tmp_fd = dup(STDIN_FILENO); // On sauvegarde l'entrée standard

	if (ac > 1) // On vérifie qu'il y a bien des commandes à exécuter
	{
		while (av[i]) // On boucle tant qu'il y a des arguments
		{
			char	**cmd_start = &av[i]; // cmd_start pointe sur le début de la commande actuelle
			int		j = 0;

			// On cherche la fin de la commande (un séparateur ou la fin du tableau)
			while (cmd_start[j] && strcmp(cmd_start[j], ";") && strcmp(cmd_start[j], "|"))
				j++;

			if (j > 0) // On vérifie que la commande n'est pas vide (ex: ";;")
			{
				if (strcmp(cmd_start[0], "cd") == 0)
				{
					if (j != 2)
						ft_putstr_fd2("error: cd: bad arguments", NULL);
					else if (chdir(cmd_start[1]) != 0)
						ft_putstr_fd2("error: cd: cannot change directory to ", cmd_start[1]);
				}
				// Si c'est une commande simple (terminée par ; ou la fin)
				else if (cmd_start[j] == NULL || strcmp(cmd_start[j], ";") == 0)
				{
					if (fork() == 0)
						ft_exec(cmd_start, j, tmp_fd, env);
					else
					{
						close(tmp_fd);
						while (waitpid(-1, NULL, WUNTRACED) != -1)
							;
						tmp_fd = dup(STDIN_FILENO);
					}
				}
				// Si c'est une commande pipée
				else if (strcmp(cmd_start[j], "|") == 0)
				{
					pipe(fd);
					if (fork() == 0)
					{
						dup2(fd[1], STDOUT_FILENO);
						close(fd[0]);
						close(fd[1]);
						ft_exec(cmd_start, j, tmp_fd, env);
					}
					else
					{
						close(fd[1]);
						close(tmp_fd);
						tmp_fd = fd[0];
					}
				}
			}
			i += j; // On avance notre index principal `i` à la commande suivante
			if (av[i])
				i++;
		}
		close(tmp_fd); // Fermer le dernier descripteur
	}
	// On ferme le dernier descripteur de fichier avant de quitter
	return (0);
}
