/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   microshell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 13:24:42 by erazumov          #+#    #+#             */
/*   Updated: 2025/09/03 14:00:36 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "microshell.h"

//-----------------------------------------------------------------------------
// FONCTIONS UTILITAIRES DÉDIÉES
//-----------------------------------------------------------------------------

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
 * @brief Affiche un message d'erreur sur STDERR.
 */
void	print_error(char *msg, char *arg)
{
	write(STDERR_FILENO, msg, ft_strlen(msg));
	if (arg)
		write(STDERR_FILENO, arg, ft_strlen(arg));
	write(STDERR_FILENO, "\n", 1);
}

/**
 * @brief Affiche "error: fatal" et quitte.
 */
void	fatal_error(void)
{
	print_error("error: fatal", NULL);
		exit(1);
}

/**
 * @brief Gère la commande intégrée 'cd'.
 */
int	handle_cd(char **args)
{
	int	i = 0;

	while (args[i])
		i++;

	if (i != 2)
	{
		print_error("error: cd: bad arguments", NULL);
		return (1);
	}
	if (chdir(args[1]) == -1)
	{
		print_error("error: cd: cannot change directory to ", args[1]);
		return (1);
	}
	return (0);
}

//-----------------------------------------------------------------------------
// GESTION D'UNE SÉQUENCE (avec les pipes)
//-----------------------------------------------------------------------------

void	execute_sequence(char **args, char **envp)
{
	int		num_cmds = 0;
	int		fd_pipe[2];
	int		fd_in = 0;
	pid_t	pid;

	/* Cas spécial pour 'cd' qui ne doit pas être forké */
	if (args[0] && !strcmp(args[0], "cd"))
	{
		handle_cd(args);
		return ;
	}

	/* On parcourt la séquence pour lancer chaque commande */
	int	i = 0;
	while (args[i])
	{
		/* On isole la commande actuelle en remplaçant '|' par NULL */
		int	cmd_start = i;
		while (args[i] && strcmp(args[i], "|"))
			i++;

		int	next_is_pipe = 0;
		if (args[i] && !strcmp(args[i], "|"))
		{
			next_is_pipe = 1;
			args[i] = NULL;
		}

		/* Création du pipe si ce n'est pas la dernière commande */
		if (next_is_pipe)
		{
			if (pipe(fd_pipe) == -1)
				fatal_error();
		}

		pid = fork();
		if (pid == -1)
			fatal_error();

		/* --- Processus Enfant --- */
		
	}
}

//-----------------------------------------------------------------------------
// FONCTION PRINCIPALE
//-----------------------------------------------------------------------------

int	main(int ac, char **av)
{
	
}
