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

# define BUFF_SIZE 256
# define MAX_CLIENTS 42
# define MAX_CHANNEL 10
# define NAME_LENGTH 20

typedef struct		s_client
{
	int				sock;
	char			*name;
	int				n_channel;
	char			*channel[MAX_CHANNEL];
}					t_client;

typedef struct		s_server
{
	int				sock;
	int				max;
	fd_set			groupfd;
	t_client		clients[MAX_CLIENTS];
}					t_server;

typedef struct		s_cmd
{
	char			*name;
	void			(*f)(char *, t_client *, t_server *);
	int				length;
}					t_cmd;

int					listen_clients(int stock);
int					create_server(int port);

void				close_clients(t_client *clients, int actual);
int					new_clients(t_server *server, int *actual_client,
					char *buff);
void				define_client(t_server *server, int *actual_client,
					char *buff, int cs);
void				error_client_connect(t_server *server, int *actual_client,
					char *buff, int i);
void				client_talking(t_server *server, int *actual_client,
					char *buff);

int					read_to_client(int sock, char *buff);
void				write_to_client(int sock, char *buff);
void				remove_client(t_server *server, int i,
					int *actual_client);
void				send_to_by_channel(t_server *server, t_client client,
					int *actual_client, char *buff);
void				send_to_all(t_server *server, t_client client,
					int *actual_client, char *buff);

int					check_name(t_server *server, char *buff);
int					check_channel(t_client sender, t_client dest);

void				ft_nick(char *buff, t_client *client, t_server *server);
void				ft_who(char *buff, t_client *client, t_server *server);
void				ft_join(char *buff, t_client *client, t_server *server);
void				ft_leave(char *buff, t_client *client, t_server *server);
void				ft_msg(char *buff, t_client *client, t_server *server);

void				delete_channel(char *buff, t_client *client);
void				add_channel(char *name, t_client *client);
void				command(t_server *server, t_client *client, char *buff);

#endif
