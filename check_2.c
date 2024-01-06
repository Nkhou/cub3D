/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saboulal <saboulal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/22 13:46:14 by saboulal          #+#    #+#             */
/*   Updated: 2024/01/06 19:42:49 by saboulal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"cub.h"

 int	space_waall(char **map, int r, int c)
{
	if (map[r][c] != '1' && map[r][c] != ' ')
		return (1);
	return (0);
}

static int 	space_waall_(char **map, int r, int i)
{
	while (map[r][i])
	{
		if (map[r][i] != '1' && map[r][i] != ' ')
			return (1);
		i++;
	}
	return (0);
}

int	found_wall(char **map, int r)
{
	int	l1;
	int	l2;

	l1 = ft_strlen(map[r]);
	l2 = 0;
	if (map[r + 1])
		l2 = ft_strlen(map[r + 1]);
	if (l1 > l2 && l2 > 0)
	{
		if (space_waall_(map, r, l2))
			return (1);
	}
	else if (l2 > l1)
	{
		if (space_waall_(map, r + 1, l1))
			return (1);
	}
	return (0);
}

void	get_map(t_map *map)
{
	int		i;
	int		j;
    char **tab;
	i = 0;
	j = 0;
	map->r = len_map(map->map);
	tab = malloc(sizeof(char *) * (map->r + 1));
	map->c = 0;
	if (!tab)
		write(2,"Error\n", 6);
	while (map->map[i])
	{
		if (map->map[i][0] == '1'
				|| map->map[i][0] == ' '
				|| map->map[i][0] == '0')
		{
			tab[j++] = ft_strdup(map->map[i]);
			if (map->c < ft_strlen(map->map[j - 1]))
				map->c = ft_strlen(map->map[j - 1]);
		}
		i++;
	}
	tab[j] = 0;
	tabfree(tab);
	
}