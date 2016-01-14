/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nschilli <nschilli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/13 11:21:39 by nschilli          #+#    #+#             */
/*   Updated: 2016/01/14 13:59:33 by nschilli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

static void		do_select(int sock, fd_set *rdfs)
{
	FD_ZERO(rdfs);
	FD_SET(STDIN_FILENO, rdfs);
	FD_SET(sock, rdfs);
	if (select(sock, rdfs, NULL, NULL, NULL) == -1)
	{
		ft_putstr("Error: select, do select into client\n");
		exit(-1);
	}
}

static void		client(int sock, char *name)
{
	char		buff[BUFF_SIZE + 1];
	fd_set		rdfs;

	write_to_server(sock, name);
	while(1)
	{
		do_select(sock, &rdfs);
		if (FD_ISSET(STDIN_FILENO, &rdfs))
		{
			read_message(buff);
			write_to_server(sock, buff);
		}
		else if (FD_ISSET(sock, &rdfs))
		{
			if (read_to_server(sock, buff) == 0)
			{
				ft_putstr("server disconnect\n");
				break ;
			}
			ft_putendl(buff);
			// if (ft_strcmp(buff, "Pseudo already used\n") == 0)
			// 	write_to_server(sock, choose_name());
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
	if ((sock = socket(PF_INET, SOCK_STREAM, proto->p_proto)) == -1)
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