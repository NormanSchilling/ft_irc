/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manager_clients.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nschilli <nschilli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/13 14:44:38 by nschilli          #+#    #+#             */
/*   Updated: 2016/01/13 16:20:42 by nschilli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "serveur.h"

int		new_clients(t_server *server, int *actual_client)
{
	int					cs;
	unsigned int		cslen;
	struct sockaddr_in	csin;

	cs = accept(server->sock, (struct sockaddr *)&csin, &cslen);
	if (cs > 0)
	{
		ft_putstr("new client \n");
	}

	(*actual_client)++;
	close(cs);
	return (0);
}
