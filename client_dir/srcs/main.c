/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nschilli <nschilli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/13 11:21:39 by nschilli          #+#    #+#             */
/*   Updated: 2016/01/13 16:44:14 by nschilli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

void	manager(int sock)
{
	// int			r;
	char		buff[BUFF_SIZE];
	

	ft_bzero(buff, BUFF_SIZE);
	ft_putstr_fd(" ", 1);
	// while ((r = read(1, buff, BUFF_SIZE - 1)) > 0)
	// {
	// 	buff[r - 1] = 0;
	// 	if ((write(sock, buff, r)) == -1)
	// 		break ;
	// 	if (ft_strncmp(buff, "quit", 4) == 0)
	// 		break ;
	// 	// get_msg(sock, buff);
	// 	ft_putstr_fd("message : ", 1);
	// 	ft_bzero(buff, BUFF_SIZE);
	// }
}

int		client(sock, char *name)
{

}

int		create_client(char *addr, int port)
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
	client(sock);
	close(sock);
	return (0);
}