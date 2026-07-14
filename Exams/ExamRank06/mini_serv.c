#include <stdbool.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>
#include <sys/select.h>
#include <sys/socket.h>
#include <unistd.h>
#include <stdio.h>

// Global tracking variables
int		max_fd = 0, next_id = 0;
fd_set	master_fds, read_fds;

// Global buffers to save stack memory and prevent allocation failures
char	buff_write[65536], buff_read[65536];

typedef struct s_client
{
	int		id;
	char	*msg;
}	t_client;

t_client	clients[65536];

// Standard exam error handling: outputs message to stderr and exits with 1
static void
fatal_error()
{
	write(2, "Fatal error\n", 12);
	exit(1);
}

// Sends a text packet to every connected client except the sender and server
void
broadcast(int sender_fd, int server_fd, char *msg)
{
	for (int fd = 0; fd <= max_fd; fd++)
		if (FD_ISSET(fd, &master_fds) && fd != server_fd && fd != sender_fd)
			send(fd, msg, strlen(msg), 0);
}

// Exam-provided function: slices the message buffer cleanly at every '\n' character
int
extract_message(char **buf, char **msg)
{
	char	*newbuf;
	int		i = 0;

	*msg = 0;
	if (*buf == 0)
		return (0);

	while ((*buf)[i])
	{
		if ((*buf)[i] == '\n')
		{
			newbuf = (char *)calloc(1, sizeof(*newbuf) * (strlen(*buf + i + 1) + 1));
			if (newbuf == 0)
				return (-1);
			strcpy(newbuf, *buf + i + 1);
			*msg = *buf;
			(*msg)[i + 1] = 0;
			*buf = newbuf;
			return (1);
		}
		i++;
	}
	return (0);
}

// Exam-provided function: safely appends raw received data to the client's internal string
char
*str_join(char *buf, char *add)
{
	char	*newbuf;
	int		len = buf ? strlen(buf) : 0;

	newbuf = (char *)malloc(sizeof(*newbuf) * (len + strlen(add) + 1));
	if (newbuf == 0)
		return (0);
	newbuf[0] = 0;
	if (buf != 0)
		strcat(newbuf, buf);
	free(buf);
	strcat(newbuf, add);
	return (newbuf);
}

int
main(int ac, char **av)
{
	// 1. Initial verification of execution parameters
	if (ac != 2)
	{
		write(2, "Wrong number of arguments\n", 26);
		exit(1);
	}

	// 2. Master server socket allocation
	int	server_fd = socket(AF_INET, SOCK_STREAM, 0);
	if (server_fd < 0)
		fatal_error();

	// 3. Strict local address binding layout configuration (127.0.0.1)
	struct sockaddr_in	server_addr;
	memset(&server_addr, 0, sizeof(server_addr));
	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
	server_addr.sin_port = htons(atoi(av[1]));

	// 4. Combined socket association and connection backlog initialisation
	if (bind(server_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0 ||
		listen(server_fd, 128) < 0)
	{
		close(server_fd);
		fatal_error();
	}

	// 5. Initial client array clearing and root tracking registration
	memset(clients, 0, sizeof(clients));
	FD_ZERO(&master_fds);
	FD_SET(server_fd, &master_fds);
	max_fd = server_fd;

	// 6. Infinite operational network monitoring pool loop
	while (true)
	{
		// Always mirror the master registry into the working copy
		read_fds = master_fds;

		// Block process and save resources until network activity occurs
		if (select(max_fd + 1, &read_fds, NULL, NULL, NULL) < 0)
			fatal_error();

		// Scan all tracked slots within active boundary limits
		for (int fd = 0; fd <= max_fd; fd++)
		{
			if (!FD_ISSET(fd, &read_fds))
				continue;

			// SCENARIO A: Main gate activity signifies a new arrival
			if (fd == server_fd)
			{
				struct sockaddr_in	client_addr;
				socklen_t			addr_len = sizeof(client_addr);

				// Accept
				int	client_fd = accept(server_fd, (struct sockaddr *)&client_addr, &addr_len);
				if (client_fd < 0)
					continue;

				// Assign client metadata and securely register the socket
				clients[client_fd].id = next_id++;
				clients[client_fd].msg = NULL;
				FD_SET(client_fd, &master_fds);
				if (client_fd > max_fd)
					max_fd = client_fd;

				// Broadcast introduction packet to the network mesh
				sprintf(buff_write, "server: client %d just arrived\n", clients[client_fd].id);
				broadcast(client_fd, server_fd, buff_write);
			}
			// SCENARIO B: Active node transaction (Message or Disconnection)
			else
			{
				ssize_t	bytes_read = recv(fd, buff_read, 65535, 0);

				// Connection broken or node cleanly disconnected
				if (bytes_read <= 0)
				{
					sprintf(buff_write, "server: client %d just left\n", clients[fd].id);
					broadcast(fd, server_fd, buff_write);

					// Safe resource disposal to guarantee zero leaks
					free(clients[fd].msg);
					clients[fd].msg = NULL;
					FD_CLR(fd, &master_fds);
					close(fd);
				}
				// Raw string payload processing block
				else
				{
					buff_read[bytes_read] = '\0';
					clients[fd].msg = str_join(clients[fd].msg, buff_read);
					if (!clients[fd].msg)
						fatal_error();

					// Sequentially dissect buffer text and forward line fragments
					char	*msg_to_send = NULL;
					int		res;
					while ((res = extract_message(&clients[fd].msg, &msg_to_send)) > 0)
					{
						sprintf(buff_write, "client %d: %s", clients[fd].id, msg_to_send);
						broadcast(fd, server_fd, buff_write);

						// Critical point: clear the extracted slice string instantly
						free(msg_to_send);
						msg_to_send = NULL;
					}
					if (res == -1)
						fatal_error();
				}
			}
		}
	}
	return 0;
}
