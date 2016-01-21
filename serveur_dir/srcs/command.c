/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nschilli <nschilli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/20 11:54:35 by nschilli          #+#    #+#             */
/*   Updated: 2016/01/21 13:28:16 by nschilli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "serveur.h"

void		ft_nick(char *buff, t_client *client, t_server *server)
{
	char		**tmp;

	tmp = ft_strsplit(buff, ' ');
	if (check_name(server, tmp[1]) == -1)
	{
		write_to_client(client->sock, "/nick => name is already used !\n");
		return ;
	}
	free(client->name);
	client->name = ft_strdup(tmp[1]);
}

void		ft_who(char *buff, t_client *client, t_server *server)
{
	int		i;

	(void)buff;
	i = 0;
	while (i < MAX_CLIENTS)
	{
		if (server->clients[i].name != NULL
			&& server->clients[i].n_channel == client->n_channel
			&& ft_strcmp(client->name, server->clients[i].name) != 0)
		{
			ft_putendl(server->clients[i].name);
			write_to_client(client->sock, server->clients[i].name);
		}
		i++;
	}
}

void		ft_join(char *buff, t_client *client, t_server *server)
{
	int		i;
	char	**tmp;

	(void)server;
	tmp = ft_strsplit(buff, ' ');
	i = 0;
	while (i < MAX_CHANNEL)
	{
		if (client->channel[i] && tmp[1])
		{
			if (ft_strcmp(client->channel[i], tmp[1]) == 0)
			{
				write_to_client(client->sock, "/join => channel already joined !");
				return ;
			}
		}
		i++;
	}
	add_channel(tmp[1], client);
}

void		ft_leave(char *buff, t_client *client, t_server *server)
{
	int		i;

	(void)server;
	i = 0;
	if (ft_strlen(buff) > 6)
	{
		delete_channel(buff, client);
	}
	else
	{

		while (i < MAX_CHANNEL)
			client->channel[i++] = NULL;
		client->n_channel = 0;
		write_to_client(client->sock, "leave with success !");
	}
}

void		ft_msg(char *buff, t_client *client, t_server *server)
{
	int		i;
	char	**tmp;
	char	*message;

	tmp = ft_strsplit(buff, ' ');
	i = 0;
	if (tmp[3])
	{
		write_to_client(client->sock, "Usage : /msg <name> <message>");
		return ;
	}
	while (i < MAX_CLIENTS)
	{
		if (server->clients[i].name != NULL
			&& ft_strcmp(tmp[1], server->clients[i].name) == 0)
		{
			message = ft_strdup(tmp[2]);
			message = ft_strjoin(client->name, " : ");
			message = ft_strjoin(message, tmp[2]);
			write_to_client(server->clients[i].sock, message);
			free(message);
		}
		i++;
	}
}

