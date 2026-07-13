#include <stdbool.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>
#include <sys/select.h>
#include <sys/socket.h>
#include <unistd.h>
#include <stdio.h>

int		max_fd = 0, next_id = 0;
fd_set	master_fds, read_fds;
char	buff_write[65536], buff_read[65536];

typedef struct s_client
{
	int		id;
	char	*msg;
}	t_client;

t_client	clients[65536];

static void
fatal_error()
{
	write(2, "Fatal error\n", 12);
	exit(1);
}

void
broadcast(int sender_fd, int server_fd, char *msg)
{
	for (int fd = 0; fd <= max_fd; fd++)
		if (FD_ISSET(fd, &master_fds) && fd != server_fd && fd != sender_fd)
			send(fd, msg, strlen(msg), 0);
}

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
	server_addr.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
	server_addr.sin_port = htons(atoi(av[1]));

	// Bind & Listen
	if (bind(server_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0 ||
		listen(server_fd, 128) < 0)
	{
		close(server_fd);
		fatal_error();
	}

	memset(clients, 0, sizeof(clients));
	FD_ZERO(&master_fds);
	FD_SET(server_fd, &master_fds);
	max_fd = server_fd;

	// select()
	while (true)
	{
		read_fds = master_fds;

		if (select(max_fd + 1, &read_fds, NULL, NULL, NULL) < 0)
			fatal_error();

		for (int fd = 0; fd <= max_fd; fd++)
		{
			if (!FD_ISSET(fd, &read_fds))
				continue;

			if (fd == server_fd)
			{
				struct sockaddr_in	client_addr;
				socklen_t			addr_len = sizeof(client_addr);

				// Accept
				int	client_fd = accept(server_fd, (struct sockaddr *)&client_addr, &addr_len);
				if (client_fd < 0)
					continue;

				clients[client_fd].id = next_id++;
				clients[client_fd].msg = NULL;
				FD_SET(client_fd, &master_fds);
				if (client_fd > max_fd)
					max_fd = client_fd;

				sprintf(buff_write, "server: client %d just arrived\n", clients[client_fd].id);
				broadcast(client_fd, server_fd, buff_write);
			}
			else
			{
				ssize_t	bytes_read = recv(fd, buff_read, 65535, 0);
				if (bytes_read <= 0)
				{
					sprintf(buff_write, "server: client %d just left\n", clients[fd].id);
					broadcast(fd, server_fd, buff_write);

					free(clients[fd].msg);
					clients[fd].msg = NULL;
					FD_CLR(fd, &master_fds);
					close(fd);
				}
				else
				{
					buff_read[bytes_read] = '\0';
					clients[fd].msg = str_join(clients[fd].msg, buff_read);
					if (!clients[fd].msg)
						fatal_error();

					char	*msg_to_send = NULL;
					int		res;
					while ((res = extract_message(&clients[fd].msg, &msg_to_send)) > 0)
					{
						sprintf(buff_write, "client %d: %s", clients[fd].id, msg_to_send);
						broadcast(fd, server_fd, buff_write);
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
