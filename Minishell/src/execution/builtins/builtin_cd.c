/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 15:00:00 by preltien          #+#    #+#             */
/*   Updated: 2025/08/19 15:49:45 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* The core logic for changing to a specified path. */
static int	cd_to_path(char *path)
{
	if (chdir(path) != 0)
	{
		ft_putstr_fd("minishell: cd: ", 2);
		ft_putstr_fd(path, 2);
		ft_putstr_fd(": ", 2);
		ft_putstr_fd(strerror(errno), 2);
		ft_putstr_fd("\n", 2);
		return (1);
	}
	return (0);
}

/* Handles the 'cd' command with no arguments by changing to HOME dir. */
static int	handle_cd_to_home(t_shell *state)
{
	char	*home_dir;

	home_dir = get_env_value("HOME", state->envp);
	if (!home_dir || *home_dir == '\0')
	{
		ft_putstr_fd("minishell: cd: HOME not set\n", 2);
		free(home_dir);
		return (1);
	}
	if (cd_to_path(home_dir) != 0)
	{
		free(home_dir);
		return (1);
	}
	free(home_dir);
	return (0);
}

/* Updates the PWD and OLDPWD environment variables after a successful cd. */
static void	update_pwd_vars(t_shell *state)
{
	char	cwd[4096];
	char	*old_pwd;

	old_pwd = get_env_value("PWD", state->envp);
	if (old_pwd)
	{
		set_env_var(state, "OLDPWD", old_pwd);
		free(old_pwd);
	}
	if (getcwd(cwd, sizeof(cwd)) != NULL)
		set_env_var(state, "PWD", cwd);
}

/* Built-in command: change directory.
 * This is the main dispatcher for the cd command. */
int	builtin_cd(char **argv, t_shell *state)
{
	int	ret_code;

	if (argv[1] && argv[2])
	{
		ft_putstr_fd("minishell: cd: too many arguments\n", 2);
		return (1);
	}
	if (!argv[1])
		ret_code = handle_cd_to_home(state);
	else
		ret_code = cd_to_path(argv[1]);
	if (ret_code == 0)
		update_pwd_vars(state);
	return (ret_code);
}
