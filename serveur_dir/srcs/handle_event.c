/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_event.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nschilli <nschilli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/14 14:11:48 by nschilli          #+#    #+#             */
/*   Updated: 2016/01/14 16:59:27 by nschilli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "serveur.h"

int		read_to_client(int sock, char *buff)
{
	int		r;

	r = 0;
	if ((r = recv(sock, buff, BUFF_SIZE, 0)) < 0)
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
	ft_putstr("write_to_client\n");
}