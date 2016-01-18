/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nschilli <nschilli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/13 11:21:39 by nschilli          #+#    #+#             */
/*   Updated: 2016/01/18 16:36:42 by nschilli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

static void		do_select(int sock, fd_set *groupfd)
{
	FD_ZERO(groupfd);
	FD_SET(STDIN_FILENO, groupfd);
	FD_SET(sock, groupfd);
	if (select(sock, groupfd, NULL, NULL, NULL) == -1)
	{
		ft_putstr("Error: select, do select into client\n");
		exit(-1);
	}
}

static void		client(int sock, char *name)
{
	char		buff[BUFF_SIZE];
	fd_set		groupfd;

	write_to_server(sock, name);
	while (1)
	{
		ft_bzero(buff, BUFF_SIZE);
		do_select(sock, &groupfd);
		if (FD_ISSET(STDIN_FILENO, &groupfd))
		{
			read_message(buff);
			write_to_server(sock, buff);
			ft_putstr("FD_ISSET(STDIN_FILENO, &groupfd)");
		}
		else if (FD_ISSET(sock, &groupfd))
		{
			ft_putstr("FD_ISSET(sock, &groupfd)");
			if (read_to_server(sock, buff) == 0)
			{
				ft_putstr("server disconnect\n");
				break ;
			}
			ft_putendl(buff);
			if (ft_strcmp(buff, "Name is already used !\n") == 0)
				write_to_server(sock, choose_name());
		}
	}
	close(sock);
}

static int		create_client(char *addr, int port)
{
	int					sock;
	struct protoent		*proto;
	struct sockaddr_in	sin;

	proto = getprotobyname("tcp");
	if (proto == 0)
		return (-1);
	if ((sock = socket(AF_INET, SOCK_STREAM, proto->p_proto)) == -1)
	{
		ft_putstr("Error: socket !\n");
		exit(-1);
	}
	sin.sin_family = AF_INET;
	sin.sin_port = htons(port);
	sin.sin_addr.s_addr = inet_addr(addr);
	if (connect(sock, (const struct sockaddr*)&sin, sizeof(sin)) == -1)
	{
		ft_putstr("Error: connect !\n");
		exit(-1);
	}
	return (sock);
}


int		main(int argc, char **argv)
{
	int			port;
	int			sock;

	if (argc != 3)
	{
		ft_putstr("./client [serveur][port]");
		exit(-1);
	}
	port = ft_atoi(argv[2]);
	sock = create_client(argv[1], port);
	client(sock, choose_name());
	close(sock);
	return (0);
}