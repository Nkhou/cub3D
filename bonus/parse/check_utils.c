/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saboulal <saboulal@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 16:02:47 by saboulal          #+#    #+#             */
/*   Updated: 2024/01/26 13:46:37 by saboulal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub.h"

void	get_map(t_map *map)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	map->r = len_map(map->map1);
	map->tab = malloc(sizeof(char *) * (map->r + 1));
	map->c = 0;
	if (!map->tab)
		ft_error();
	while (map->map1[i])
	{
		if (map->map1[i][0] == '1'
				|| map->map1[i][0] == ' '
				|| map->map1[i][0] == '0')
		{
			map->tab[j++] = ft_strndup(map->map1[i],
					ft_strlen(map->map1[i]) - \
					check_new_line(map->map1[i]));
			if (map->c < ft_strlen(map->tab[j - 1]))
				map->c = ft_strlen(map->tab[j - 1]);
		}
		i++;
	}
	map->tab[j] = 0;
}