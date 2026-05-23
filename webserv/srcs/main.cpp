/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/09 15:07:21 by erazumov          #+#    #+#             */
/*   Updated: 2026/05/23 17:06:34 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cluster.hpp"
#include <csignal>
#include <iostream>

// Global flag to control the server's main loop
volatile sig_atomic_t	g_stop = 0;

// Function to handle system signals (like Ctrl+C)
void	handle_signal(int sig)
{
	(void)sig;
	g_stop = 1; // Signal the server to stop gracefully
	std::cout << "\n[Signal received] Stopping the webserv..." << std::endl;
}

int	main(int ac, char **av)
{
	// 1. ARGUMENT CHECK: Ensure the user provides at most one config file
	if (ac > 2)
	{
		std::cerr << "Usage: ./webserv [configuration_file]" << std::endl;
		return 1;
	}

	// 2. CONFIGURATION: Load the rules from the .conf file
	// If no file is provided, use a default path
	std::string			configPath = (ac == 2) ? av[1] : "configs/default.conf";
	std::vector<Config>	configs = configParser.getConfigs();

	std::cout << "Loading configuration: " << configPath << std::endl;
	config.parse(configPath);

	// 3. SERVER INITIALISATION: Create the server instance with the loaded rules
	Server server(config);

	// 4. SIGNAL SETUP: Bind the SIGINT (Ctrl+C) to the handler
	// This is mandatory for a clean 42 project
	signal(SIGINT, handle_signal);
	signal(SIGQUIT, handle_signal);

	// 5. LAUNCH: Setup the sockets and start the polling loop
	Cluster.setup(configs);
	server.run();

	// 6. EXIT: Once run() finishes (when g_stop == 1), the program ends here
	std::cout << "Webserv closed successfully. See you later!" << std::endl;

	return 0;
}
