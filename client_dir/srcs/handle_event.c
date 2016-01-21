/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_event.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nschilli <nschilli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/14 11:42:29 by nschilli          #+#    #+#             */
/*   Updated: 2016/01/21 12:04:59 by nschilli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

void		read_message(char *buff)
{
	char	*p;

	read(0, buff, BUFF_SIZE - 1);
	if ((p = ft_strstr(buff, "\n")) != NULL)
		*p = 0;
	else
		buff[BUFF_SIZE] = 0;
}

int			read_to_server(int sock, char *buff)
{
	int		r;

	r = 0;
	if ((r = recv(sock, buff, BUFF_SIZE - 1, 0)) < 0)
	{
		ft_putstr("Error : recv, read to server\n");
		exit(-1);
	}
	buff[r] = 0;
	return (r);
}

void		write_to_server(int sock, char *buff)
{
	char	*tmp;

	tmp = ft_strdup(buff);
	if (tmp[ft_strlen(tmp) - 1] == '\n')
		tmp[ft_strlen(tmp) - 1] = 0;
	if (send(sock, tmp, ft_strlen(tmp), 0) < 0)
	{
		ft_putstr("Error : send, write to server");
		exit(-1);
	}
}
