/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/09 15:07:21 by erazumov          #+#    #+#             */
/*   Updated: 2026/03/28 15:22:32 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"
#include "Config.hpp"
#include "Request.hpp"
#include "Response.hpp"
#include "Utils.hpp"

volatile sig_atomic_t	g_stop = 0;

// Function to handle system signals (like Ctrl+C)
void	handle_signal(int sig)
{
	(void)sig;
	g_stop = 1; // Signal the server to stop gracefully
	std::cout << "\nShutdown signal received. Closing server..." << std::endl;
}

int	main(int ac, char **av)
{
	Config	config;

	if (ac == 2)
		config.parse(av[1]);
	else
		config.parse("default.conf");

	// Initialise the server
	Server	myServ(config);
	myServ.setup();

	// Set up Ctrl+C handling
	signal(SIGINT, handle_signal);

	// Start the server's main loop
	myServ.run();

	// This message will appear ONLY after you press Ctrl+C
	std::cout << "Server shut down successfully." << std::endl;

	return 0;
}
