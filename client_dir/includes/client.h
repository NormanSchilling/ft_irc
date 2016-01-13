/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nschilli <nschilli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/13 11:23:14 by nschilli          #+#    #+#             */
/*   Updated: 2016/01/13 13:55:20 by nschilli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENT_H
# define CLIENT_H
# include <stdio.h>
# include <stdlib.h>
# include <sys/socket.h>
# include <unistd.h>
# include <netdb.h>
# include <netinet/in.h>
# include <arpa/inet.h>
# include <stdlib.h>
# include "../../libft/libft.h"

# define BUFF_SIZE 1024

void	manager(int sock);
int		create_client(char *addr, int port);
#endif