/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/09 15:07:21 by erazumov          #+#    #+#             */
/*   Updated: 2026/06/09 16:44:54 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cluster.hpp"

#include <signal.h>
#include <iostream>

volatile sig_atomic_t	g_stop = 0;

// Function to handle system signals (like Ctrl+C)
void	handle_signal(int sig)
{
	(void)sig;
	g_stop = 1; // Signal the server to stop gracefully
	std::cout << "\n[Signal received] Stopping the webserv..." << std::endl;
}

int		main(int ac, char **av)
{
	signal(SIGPIPE, SIG_IGN);

	if (ac > 2)
	{
		std::cerr << "Usage: ./webserv [configuration_file]" << std::endl;
		return 1;
	}

	std::string	configPath = (ac == 2) ? av[1] : "configs/default.conf";
	std::cout << "Loading configuration: " << configPath << std::endl;

	// 1. Single config instance for now (will receive vector after location parser)
	Config	config;
	config.parse(configPath);

	std::vector<Config>	configs;
	configs.push_back(config);

	// 2. Setup system signal handlers for graceful shutdown
	signal(SIGINT, handle_signal);
	signal(SIGQUIT, handle_signal);
	signal(SIGPIPE, SIG_IGN);

	// 3. Launch Cluster multiplexer loop
	Cluster	cluster;
	cluster.setup(configs);
	cluster.run();

	std::cout << "Webserv closed successfully" << std::endl;
	return 0;
}
