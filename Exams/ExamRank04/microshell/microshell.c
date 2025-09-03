/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   microshell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 13:24:42 by erazumov          #+#    #+#             */
/*   Updated: 2025/09/03 17:23:10 by erazumov         ###   ########.fr       */
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

/**
 * @brief Logique exécutée UNIQUEMENT par le processus enfant.
 * Ne retourne jamais car elle se termine par execve ou exit.
 */
void	child_execute(char **cmd, char **envp, int fd_in, int *fd_pipe,
		int has_pipe)
{
	/* 1. Rediriger l'entrée si elle ne vient pas de stdin */
	if (fd_in != 0)
	{
		if (dup2(fd_in, STDIN_FILENO) == -1)
			fatal_error();
		close(fd_in);
	}
	/* 2. Rediriger la sortie si la commande est suivie d'un pipe */
	if (has_pipe)
	{
		if (dup2(fd_pipe[1], STDOUT_FILENO) == -1)
			fatal_error();
		close(fd_pipe[0]);
		close(fd_pipe[1]);
	}
	/* 3. Exécuter la commande */
	execve(cmd[0], cmd, envp);
	/* Si execve échoue, le processus enfant doit s'arrêter */
	print_error("error: cannot execute ", cmd[0]);
	exit(1);
}

/**
 * @brief Attend la fin de TOUS les processus enfants en attente.
 */
void wait_for_children(void)
{
	/* La boucle continue tant que waitpid trouve un enfant terminé.
	** Elle s'arrête quand waitpid retourne -1 (car il n'y a plus d'enfants) */
	while (waitpid(-1, NULL, 0) > 0);
}

void	execute_sequence(char **args, char **envp)
{
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
		int	has_pipe = (args[i] && !strcmp(args[i], "|"));
		if (has_pipe)
			args[i] = NULL;
		/* Création du pipe si ce n'est pas la dernière commande */
		if (has_pipe)
		{
			if (pipe(fd_pipe) == -1)
				fatal_error();
		}
		pid = fork();
		if (pid == -1)
			fatal_error();
		if (pid == 0)
			child_execute(&args[cmd_start], envp, fd_in, fd_pipe, has_pipe);
		else
		{
			/* On ferme les descripteurs au fur et à mesure */
			if (fd_in != 0)
				close(fd_in);
			if (has_pipe)
			{
				close(fd_pipe[1]);
				fd_in = fd_pipe[0];
			}
			if (has_pipe)
				i++;
		}
	}
	/* L'appel à la fonction d'attente est maintenant plus simple */
	wait_for_children();
	if (fd_in != 0)
		close(fd_in);
}

//-----------------------------------------------------------------------------
// FONCTION PRINCIPALE
//-----------------------------------------------------------------------------

int	main(int ac, char **av)
{
}
