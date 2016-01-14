/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   name.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nschilli <nschilli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/13 16:23:41 by nschilli          #+#    #+#             */
/*   Updated: 2016/01/13 16:43:47 by nschilli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

int				check_char_name(char *name)
{
	int	i;

	i = 0;
	while (name[i])
	{
		if (ft_isprint(name[i]) && name[i] != ' ')
			i++;
		else
			return (0);
	}
	return (1);
}

char	*choose_name(void)
{
	int		r;
	char	*name;

	name = (char *)malloc(sizeof(char) * NAME_LENGTH + 1);
	write(1, "What's your name ?: ", 20);
	while ((r = read(0, name, NAME_LENGTH - 1)) > 0)
	{
		if (ft_strlen(name) <= 2 && check_char_name(name) >= 0)
			write(1, "What's your name ?: ", 20);
		else
			return (name);
	}
	return (NULL);
}
