/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   serveur.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nschilli <nschilli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/13 11:23:25 by nschilli          #+#    #+#             */
/*   Updated: 2016/01/13 16:01:54 by nschilli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVEUR_H
# define SERVEUR_H
# include <stdio.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/socket.h>
# include <unistd.h>
# include <netdb.h>
# include <netinet/in.h>
# include <arpa/inet.h>
# include <signal.h>
# include <sys/select.h>
# include "../../libft/libft.h"

# define BUFF_SIZE 1024
# define MAX_CLIENTS 42
# define MAX_CHANNEL 10

typedef struct					s_client
{
	int							sock;
	char						*name;
	int							n_channel;
	char						*channel[MAX_CHANNEL];
}								t_client;

typedef struct					s_server
{
	int							sock;
	int							max;
	fd_set						rdfs;
	t_client					clients[MAX_CLIENTS];
}								t_server;

int		listen_clients(int stock);
int		create_server(int port);

int		new_clients(t_server *server, int *actual_client);

#endif