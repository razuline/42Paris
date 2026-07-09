#include <stdbool.h>
#include <fcntl.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>
#include <sys/select.h>
#include <sys/socket.h>
#include <unistd.h>

bool	g_server_running = true;

static void
fatal_error()
{
	ft_putstr_fd("Fatal error\n", 2);
	exit(1);
}

void
setup_server()
{

}

int
main(int ac, char **av)
{
	if (ac != 2)
	{
		ft_putstr_fd("Wrong number of arguments\n", 2);
		exit(1);
	}

	// Socket Creation
	int	server_fd;
	server_fd = socket(AF_INET, SOCK_STREAM, 0);
	if (server_fd < 0)
		fatal_error();

	// Address Configuration
	struct sockaddr_in	server_addr;
	memset(&server_addr, 0, sizeof(server_addr));
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(atoi(av[1]));
	server_addr.sin_addr.s_addr = htonl(INADDR_LOOPBACK);

	// Bind & Listen
	if (bind(server_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0)
	{
		close(server_fd);
		fatal_error();
	}
	if (listen(server_fd, 128) < 0)
	{
		close(server_fd);
		fatal_error();
	}

	// FDs
	fd_set	master_set;
	fd_set	read_set;

	// Client
	int		client_ids[4096];
	char	*client_buffs[4096];
	int		next_id = 0;

	memset(client_buffs, 0, sizeof(client_buffs));
	FD_ZERO(&master_set);
	FD_SET(server_fd, &master_set);
	int	max_fd = server_fd;

	// select()
	while (g_server_running)
	{
		read_set = master_set;

		if (select(max_fd + 1, &read_set, NULL, NULL, NULL) < 0)
			fatal_error();
	}



	return (0);
}
