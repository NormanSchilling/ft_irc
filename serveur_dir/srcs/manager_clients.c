/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manager_clients.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nschilli <nschilli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/13 14:44:38 by nschilli          #+#    #+#             */
/*   Updated: 2016/01/14 17:09:58 by nschilli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "serveur.h"

void		close_clients(t_client *clients, int actual_client)
{
	int		i;

	i = 0;
	while (i < actual_client)
	{
		close(clients[i].sock);
		i++;
	}
}

int		new_clients(t_server *server, int *actual_client)
{
	char				buff[BUFF_SIZE + 1];
	int					cs;
	unsigned int		cslen;
	struct sockaddr_in	csin;

	cs = accept(server->sock, (struct sockaddr *)&csin, &cslen);
	if (cs == -1)
	{
		ft_putstr("Error: accept, new_clients\n");
		exit(-1);
	}
	if (read_to_client(cs, buff) == -1)
		return (-1);
	if (check_name(server, buff) == -1)
	{
		ft_putstr("check_name\n");
		write_to_client(cs, "Name is already used !\n");
		if (read_to_client(cs, buff) == -1)
		{
			ft_putstr("after if read_to_client\n");
			return (-1);
		}
	}
	FD_SET(cs, &(server->groupfd));
	define_client(server, actual_client, buff, cs);
	write_to_client(cs, "Hello, welcome to the futur !\n");
	(*actual_client)++;
	printf("%d\n", (*actual_client));
	close(cs);
	return (0);
}

void	define_client(t_server *server, int *actual_client, char *buff, int cs)
{	
	int		i;

	i = 0;
	server->clients[(*actual_client)].sock = cs;
	server->clients[(*actual_client)].name = ft_strdup(buff);
	server->clients[(*actual_client)].n_channel = 0;
	while (i < MAX_CHANNEL)
	{
		server->clients[(*actual_client)].channel[i] = NULL;
		i++;
	}
}

int	check_name(t_server *server, char *buff)
{
	int		i;

	i = 0;
	while (i < MAX_CLIENTS)
	{
		if (server->clients[i].name != NULL && ft_strcmp(buff, server->clients[i].name) == 0)
			return (-1);
		i++;
	}
	return (0);
}