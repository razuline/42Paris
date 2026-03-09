/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/09 15:07:21 by erazumov          #+#    #+#             */
/*   Updated: 2026/03/09 17:37:18 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

volatile sig_atomic_t	g_stop = 0;

// Function to handle system signals (like Ctrl+C)
void	handle_signal(int sig)
{
	(void)sig;
	g_stop = 1; // Signal the server to stop gracefully
	std::cout << "\nShutdown signal received. Closing server..." << std::endl;
}

int	main()
{
	Server	myServ(8080);

	// Initialise the server
	myServ.setup();

	// Set up Ctrl+C handling
	signal(SIGINT, handle_signal);

	// Start the server's main loop
	myServ.run();

	// This message will appear ONLY after you press Ctrl+C
	std::cout << "Server shut down successfully." << std::endl;

	return 0;
}
