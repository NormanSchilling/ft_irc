/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nschilli <nschilli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/13 11:20:40 by nschilli          #+#    #+#             */
/*   Updated: 2016/01/13 13:58:12 by nschilli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "serveur.h"

// int		manager(int cs)
// {
// 	int			r;
// 	char		buff[BUFF_SIZE];

// 	ft_bzero(buff, BUFF_SIZE);
// 	while ((r = read(cs, buff, BUFF_SIZE - 1)) > 0)
// 	{
// 		buff[r] = 0;
// 		if (ft_strncmp("pwd", buff, 3) == 0)
// 			cmd_pwd(cs);
// 		else if (ft_strncmp("ls", buff, 2) == 0)
// 			cmd_ls(cs, buff);
// 		else if (ft_strncmp(buff, "quit", 4) == 0)
// 			break ;
// 		else
// 		{
// 			send_msg(cs, "Error: command not exist", 0);
// 			ft_putendl("Error !");
// 		}
// 		ft_bzero(buff, BUFF_SIZE);
// 	}
// 	return (0);
// }

int		listen_clients(int sock)
{
	// int					pid;
	int					cs;
	unsigned int		cslen;
	struct sockaddr_in	csin;

	while ((cs = accept(sock, (struct sockaddr *)&csin, &cslen)) > 0)
	{
		ft_putstr("new client\n");
	}
	close(cs);
	return (0);
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
	listen_clients(sock);
	close(sock);
	return (0);
}