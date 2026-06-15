/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/09 15:07:21 by erazumov          #+#    #+#             */
/*   Updated: 2026/06/15 18:58:09 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cluster.hpp"

#include <iostream>
#include <signal.h>

volatile sig_atomic_t	g_stop = 0;

void	handle_signal(int sig)
{
	(void)sig;
	g_stop = 1;
	std::cout << "\n[Signal received] Stopping the webserv..." << std::endl;
}

int	main(int ac, char **av)
{
	signal(SIGPIPE, SIG_IGN);

	if (ac > 2)
	{
		std::cerr << "Usage: ./webserv [config_file]" << std::endl;
		return 1;
	}

	std::string	configPath = (ac == 2) ? av[1] : "configs/default.conf";
	std::cout << "Loading configuration: " << configPath << std::endl;

	std::vector<Config>	configs = Config::parseFile(configPath);
	if (configs.empty())
	{
		std::cerr << "Fatal: No valid server blocks parsed." << std::endl;
		return 1;
	}

	// Setup system signal handlers for graceful shutdown
	signal(SIGINT, handle_signal);
	signal(SIGQUIT, handle_signal);
	signal(SIGPIPE, SIG_IGN);

	// Launch Cluster multiplexer loop
	Cluster	cluster;
	cluster.setup(configs);
	cluster.run();

	std::cout << "Webserv closed successfully" << std::endl;
	return 0;
}
