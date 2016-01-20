/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_event.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nschilli <nschilli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/14 14:11:48 by nschilli          #+#    #+#             */
/*   Updated: 2016/01/20 11:23:28 by nschilli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "serveur.h"

int		read_to_client(int sock, char *buff)
{
	int		r;

	r = 0;
	if ((r = recv(sock, buff, BUFF_SIZE - 1, 0)) < 0)
	{
		ft_putstr("Error : recv, read to client\n");
		exit(-1);
	}
	buff[r] = 0;
	return (r);
}

void	write_to_client(int sock, char *buff)
{
	if (send(sock, buff, ft_strlen(buff), 0) < 0)
	{
		ft_putstr("Error : send, write to client");
		exit(-1);
	}
}

void		remove_client(t_server *server, int i, int *actual_client)
{
	t_client	*client;

	client = server->clients;
	ft_memmove(client + i, client + i + 1, (*actual_client - i - 1) * sizeof(t_client));
	(*actual_client)--;
}

void	send_to_by_channel(t_server *server, t_client client, int *actual_client, char *buff)
{
	int		i;
	char	*message;

	i = 0;
	message = ft_strdup(buff);
	message = ft_strjoin(client.name, " : ");
	message = ft_strjoin(message, buff);
	while (i < *actual_client)
	{
		if (client.sock != server->clients[i].sock
			&& client.n_channel == server->clients[i].n_channel)
		{
			write_to_client(server->clients[i].sock, message);
		}
		i++;
	}
}

void	send_to_all(t_server *server, t_client client, int *actual_client, char *buff)
{
	int		i;

	i = 0;
	while (i < *actual_client)
	{
		if (client.sock != server->clients[i].sock)
			write_to_client(server->clients[i].sock, buff);
		i++;
	}
}
