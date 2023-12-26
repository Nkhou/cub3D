/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saboulal <saboulal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/22 13:46:14 by saboulal          #+#    #+#             */
/*   Updated: 2023/12/26 10:20:07 by saboulal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"cub.h"

 int	check_wall(char **map, int row, int col)
{
	if (map[row][col] != '1' && map[row][col] != ' ')
		return (1);
	return (0);
}

static int 	check_wall_(char **map, int row, int i)
{
	while (map[row][i])
	{
		if (map[row][i] != '1' && map[row][i] != ' ')
			return (1);
		i++;
	}
	return (0);
}

int	check_extended_wall(char **map, int row)
{
	int	l1;
	int	l2;

	l1 = ft_strlen(map[row]);
	l2 = 0;
	if (map[row + 1])
		l2 = ft_strlen(map[row + 1]);
	if (l1 > l2 && l2 > 0)
	{
		if (check_wall_(map, row, l2))
			return (1);
	}
	else if (l2 > l1)
	{
		if (check_wall_(map, row + 1, l1))
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
	map->row = len_map(map->map);
	tab = malloc(sizeof(char *) * (map->row + 1));
	map->col = 0;
	if (!tab)
		write(2,"Malloc Error: parser->c: 201\n", 29);
	
	while (map->map[i])
	{
		if (map->map[i][0] == '1'
				|| map->map[i][0] == ' '
				|| map->map[i][0] == '0')
		{
			tab[j++] = ft_strdup(map->map[i]);
			if (map->col < ft_strlen(map->map[j - 1]))
				map->col = ft_strlen(map->map[j - 1]);
		}
		i++;
	}
	tab[j] = 0;
}