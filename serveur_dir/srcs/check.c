/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nschilli <nschilli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/18 12:14:51 by nschilli          #+#    #+#             */
/*   Updated: 2016/01/20 12:20:32 by nschilli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "serveur.h"

int	check_name(t_server *server, char *buff)
{
	int		i;
	char	*tmp;

	tmp = ft_strdup(buff);
	tmp[ft_strlen(tmp) - 1] = 0;
	i = 0;
	while (i < MAX_CLIENTS)
	{
		if (server->clients[i].name != NULL && ft_strcmp(tmp, server->clients[i].name) == 0)
			return (-1);
		i++;
	}
	return (0);
}

int	check_channel(t_client sender, t_client dest)
{
	int		i;

	i = 0;
	while (i < MAX_CHANNEL)
	{
		if (sender.n_channel == dest.n_channel)
			return (1);
		i++;
	}
	return (0);
}