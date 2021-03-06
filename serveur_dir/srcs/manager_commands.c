/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manager_commands.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nschilli <nschilli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/20 15:16:17 by nschilli          #+#    #+#             */
/*   Updated: 2016/01/21 13:56:09 by nschilli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "serveur.h"

void		delete_channel(char *buff, t_client *client)
{
	int		i;
	char	**tmp;

	tmp = ft_strsplit(buff, ' ');
	i = 0;
	while (i < MAX_CHANNEL)
	{
		if (client->channel[i] && tmp[1])
		{
			if (ft_strcmp(client->channel[i], tmp[1]) == 0)
			{
				client->channel[i] = NULL;
				client->n_channel--;
				write_to_client(client->sock, "leave with success !");
				return ;
			}
		}
		i++;
	}
}

void		add_channel(char *name, t_client *client)
{
	int		i;

	i = 0;
	while (client->channel[i])
		i++;
	if (client->n_channel + 1 == MAX_CHANNEL)
	{
		write_to_client(client->sock, "/join => limit of channel !");
		return ;
	}
	client->channel[i] = ft_strdup(name);
	client->n_channel++;
	write_to_client(client->sock, "channel join !");
}

void		command(t_server *server, t_client *client, char *buff)
{
	int				i;
	static	t_cmd	array_cmd[6] = {
		{"/nick", &ft_nick, 5},
		{"/who", &ft_who, 4},
		{"/join", &ft_join, 5},
		{"/leave", &ft_leave, 6},
		{"/msg", &ft_msg, 4},
		{NULL, NULL, 0}
	};

	i = 0;
	while (array_cmd[i].name != NULL)
	{
		if (ft_strncmp(buff, array_cmd[i].name, array_cmd[i].length) == 0)
			array_cmd[i].f(buff, client, server);
		i++;
	}
}
