/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nschilli <nschilli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/13 11:20:40 by nschilli          #+#    #+#             */
/*   Updated: 2016/01/14 17:10:29 by nschilli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "serveur.h"

static void		init_fds(t_server *server, int actual_client)
{
	int		i;

	i = 0;
	FD_ZERO(&(server->groupfd));
	FD_SET(STDIN_FILENO, &(server->groupfd));
	FD_SET(server->sock, &(server->groupfd));
	while (i < actual_client)
		FD_SET(server->clients[i++].sock, &(server->groupfd));
}

static void		init_server(t_server *server, int sock)
{
	int		i;

	i = 0;
	server->max = sock;
	server->sock = sock;
	while (i < MAX_CLIENTS)
	{
		server->clients[i].name = NULL;
		i++;
	}
}

static void		server(int sock)
{
	t_server	server;
	int			actual_client;

	actual_client = 0;
	init_server(&server, sock);
	while (1)
	{
		init_fds(&server, actual_client);
		if (select(server.max + 1, &server.groupfd, NULL, NULL, NULL) == -1)
			ft_putstr("Error : select serveur \n");
		if (FD_ISSET(STDIN_FILENO, &server.groupfd))
			break ;
		else if (FD_ISSET(server.sock, &server.groupfd)) // nouvelle connexion
		{
			if (new_clients(&server, &actual_client) == 0)
				continue ;
		}
		else //ecriture
			ft_putstr("talking");
	}
	close_clients(server.clients, actual_client);
	close(sock);
}


int		create_server(int port)
{
	int					sock;
	struct protoent		*proto;
	struct sockaddr_in	sin;

	proto = getprotobyname("tcp");
	if (proto == 0)
		return (-1);
	if ((sock = socket(PF_INET, SOCK_STREAM, proto->p_proto)) == -1)
	{
		ft_putstr("Error: socket !\n");
		exit(-1);
	}
	sin.sin_family = AF_INET;
	sin.sin_port = htons(port);
	sin.sin_addr.s_addr = htonl(INADDR_ANY);
	if (bind(sock, (const struct sockaddr*)&sin, sizeof(sin)) == -1)
	{
		ft_putstr("Error: bind !\n");
		exit(-1);
	}
	listen(sock, 42);
	return (sock);
}

int		main(int argc, char **argv)
{
	int					port;
	int					sock;

	signal(SIGCHLD, SIG_IGN);
	if (argc != 2)
	{
		ft_putstr("./serveur [port]\n");
		exit(-1);
	}
	port = ft_atoi(argv[1]);
	sock = create_server(port);
	server(sock);
	close(sock);
	return (0);
}