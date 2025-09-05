/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   title.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 19:07:39 by erazumov          #+#    #+#             */
/*   Updated: 2025/08/15 14:43:29 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Color codes for users  */
#define GRAY "\001\033[1;90m\002"
#define RED "\001\033[1;91m\002"
#define GREEN "\001\033[1;92m\002"
#define YELLOW "\001\033[0;93m\002"
#define BLUE "\001\033[1;94m\002"
#define MAGENTA "\001\033[1;95m\002"
#define CYAN "\001\033[1;96m\002"
#define WHITE "\001\033[0;97m\002"
#define RESET "\033[0m"
#define BOLD "\033[1m"

/* Displays the stylized "Minihell" title banner. */
void	display_title(void)
{
	ft_putstr_fd(RED, 1);
	ft_putstr_fd(BOLD, 1);
	ft_putstr_fd("                                           \n", 1);
	ft_putstr_fd("   *    (       ) (       )     (    (     \n", 1);
	ft_putstr_fd(" (  `   )\\ ) ( /( )\\ ) ( /(     )\\ ) )\\ )  \n", 1);
	ft_putstr_fd(" )\\))( (()/( )\\()|()/( )\\())(  (()/((()/(  \n", 1);
	ft_putstr_fd("((_)()\\ /(_)|(_)\\ /(_)|(_)\\ )\\  /(_))/(_)) \n", 1);
	ft_putstr_fd("(_()((_|_))  _((_|_))  _((_|(_)(_)) (_))   \n", 1);
	ft_putstr_fd("|  \\/  |_ _|| \\| |_ _|| || | __| |  | |    \n", 1);
	ft_putstr_fd("| |\\/| || | | .` || | | __ | _|| |__| |__  \n", 1);
	ft_putstr_fd("|_|  |_|___||_|\\_|___||_||_|___|____|____|\n", 1);
	ft_putstr_fd("                                           \n", 1);
	ft_putstr_fd(YELLOW, 1);
	printf("Abandon all hope, ye who enter here...\n");
	ft_putstr_fd("                                           \n", 1);
	printf("Welcome, %s!\n", getenv("USER"));
	ft_putstr_fd(RESET, 1);
	ft_putstr_fd("\n", 1);
}
