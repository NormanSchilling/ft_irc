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

int				check_char_name(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (ft_isprint(line[i]) && line[i] != ' ')
			i++;
		else
			return (0);
	}
	return (1);
}

char	*choose_name(void)
{
	char	name[NAME_LENGTH + 1];

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
