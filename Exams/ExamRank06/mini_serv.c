#include <stdbool.h>
#include <fcntl.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>
#include <sys/select.h>
#include <sys/socket.h>
#include <unistd.h>

int		max_fd = 0;
int		next_id = 0;
fd_set	master_set;
fd_set	read_set;
bool	g_server_running = true;

char	buff_write[65536];
char	buff_read[65536];

typedef struct s_client
{
	int		id;
	char	*msg;
}	t_client;

t_client	clients[65536];

static void
fatal_error()
{
	char	*err = "Fatal error\n";
	write(STDERR_FILENO, err, strlen(err));
	exit(EXIT_FAILURE);
}

void
broadcast(int sender_fd, int server_fd, char *msg)
{
	for (int fd = 0; fd <= max_fd; fd++)
		if (FD_ISSET(fd, &master_set) && fd != server_fd && fd != sender_fd)
			send(fd, msg, strlen(msg), 0);
}

int
main(int ac, char **av)
{
	if (ac != 2)
	{
		write(2, "Wrong number of arguments\n", 26);
		exit(1);
	}

	// Socket Creation
	int	server_fd = socket(AF_INET, SOCK_STREAM, 0);
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

	memset((t_client *)clients, 0, sizeof(clients));
	FD_ZERO(&master_set);
	FD_SET(server_fd, &master_set);
	max_fd = server_fd;

	// select()
	while (g_server_running)
	{
		read_set = master_set;

		if (select(max_fd + 1, &read_set, NULL, NULL, NULL) < 0)
			fatal_error();

		for (int fd = 0; fd <= max_fd; fd++)
		{
			if (!FD_ISSET(fd, &read_set))
				continue;

			int	client_fd;
			if (fd == server_fd)
			{
				struct sockaddr_in	client_addr;
				socklen_t			addr_len = sizeof(client_addr);

				// Accept
				client_fd = accept(server_fd, (struct sockaddr *)&client_addr, &addr_len);
				if (client_fd < 0)
					continue;

				clients[client_fd].id = next_id++;
				clients[client_fd].msg = NULL;
				FD_SET(client_fd, &master_set);
				if (client_fd > max_fd)
					max_fd = client_fd;

				sprintf(buff_write, "server: client %d just arrived\n", clients[client_fd].id);
				broadcast(client_fd, server_fd, buff_write);
			}
			else
			{
				ssize_t	bytes_read = recv(client_fd, buff_read, buff_read - 1, 0);
				if (bytes_read <= 0)
				{
					sprintf(buff_write, "server: client %d just left\n", clients[client_fd].msg);
					broadcast(client_fd, server_fd, buff_write);
					free(clients[fd].msg);
					FD_CLR(fd, &master_set);
					close(client_fd);
				}
			}
		}
	}



	return 0;
}
