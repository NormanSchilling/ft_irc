/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manager_clients.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nschilli <nschilli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/13 14:44:38 by nschilli          #+#    #+#             */
/*   Updated: 2016/01/18 16:20:00 by nschilli         ###   ########.fr       */
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

int		new_clients(t_server *server, int *actual_client, char *buff)
{
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
		write_to_client(cs, "Name is already used !\n");
		if (read_to_client(cs, buff) == -1)
			return (-1);
	}
	FD_SET(cs, &(server->groupfd));
	server->max = cs > server->max ? cs : server->max;
	define_client(server, actual_client, buff, cs);
	(*actual_client)++;
	return (cs);
}

void	define_client(t_server *server, int *actual_client, char *buff, int cs)
{	
	int		i;

	i = 0;
	server->clients[(*actual_client)].sock = cs;
	server->clients[(*actual_client)].name = ft_strdup(buff);
	server->clients[(*actual_client)].name[
		ft_strlen(server->clients[(*actual_client)].name) - 1] = 0;
	server->clients[(*actual_client)].n_channel = 0;
	while (i < MAX_CHANNEL)
	{
		server->clients[(*actual_client)].channel[i] = NULL;
		i++;
	}
	ft_putstr("Welcome #");
	ft_putendl(server->clients[(*actual_client)].name);
}

void	error_client_connect(t_server *server, int *actual_client, char *buff, int i)
{
	t_client	client;

	client = server->clients[i];
	close(server->clients[i].sock);
	remove_client(server, i, actual_client);
	ft_strncpy(buff, client.name, NAME_LENGTH);
	ft_strncat(buff, " disconnected !", BUFF_SIZE - ft_strlen(buff));
	send_to_all(server, client, actual_client, buff);
	ft_bzero(client.name, NAME_LENGTH);
}

void		client_talking(t_server *server, int *actual_client, char *buff)
{
	int			i;
	t_client	client;

	i = 0;
	while (i < *actual_client)
	{
		if (FD_ISSET(server->clients[i].sock, &(server->groupfd)))
		{
			client = server->clients[i];
			if (read_to_client(server->clients[i].sock, buff) == 0)
			{
				error_client_connect(server, actual_client, buff, i);
			}
			else
			{
				send_to_by_channel(server, client, actual_client, buff);
			}
			break ;
		}
		i++;
	}
}

// else if (buff[0] == '/')
// {
// 	if ((tmp = cmd(buff, &(server->clients[i]), server)))
// 		write_client(server->clients[i].sock, tmp);
// }
