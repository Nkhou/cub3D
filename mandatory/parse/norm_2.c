/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   norm_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkhoudro <nkhoudro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 11:14:04 by saboulal          #+#    #+#             */
/*   Updated: 2024/02/01 12:57:58 by nkhoudro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub.h"

int	cmp_line(char **str)
{
	int	i;

	i = 0;
	if (!str)
		return (i);
	while (str[i])
		i++;
	return (i);
}

void	free_programme(t_map *map)
{
	free(map->str);
	ft_free(map->map);
	ft_free(map->map1);
	free(map->player.rays);
	free(map->ceil);
	free(map->floor);
	free(map->north);
	free(map->south);
	free(map->west);
	free(map->east);
}

void	ini_map(t_map *map, int argc)
{
	(void)map;
	if (argc != 2)
	{
		write(2, "ERROR NOT VALID\n", 16);
		exit(1);
	}
}

void	map_game_full(t_map map)
{
	int	row;
	int	col;

	row = 0;
	if (!map.map1)
		return ;
	while (map.map1[row])
	{
		col = 0;
		if (found_wall(map.map1, row) == 1)
			ft_error_wall();
		while (map.map1[row][col])
		{
			map_checks_(map, row, col);
			col++;
		}
		row++;
	}
}

void	map_checks_(t_map map, int r, int c)
{
	if ((r == 0 && space_waall(map.map1, r, c))
		|| (r == map.r - 1 && space_waall(map.map1, r, c)))
		ft_error_wall();
	else if (c == 0 && space_waall(map.map1, r, c))
		ft_error_wall();
	else if (c == ft_strlen(map.map1[r]) - 1
		&& space_waall(map.map1, r, c))
		ft_error_wall();
	else if ((r > 0 && r < map.r - 1)
		&& (c > 0 && c < ft_strlen(map.map1[r]) - 1))
	{
		if (map.map1[r][c] == '0'
			&& (map.map1[r + 1][c] == ' ' || map.map1[r - 1][c] == ' '
			|| map.map1[r][c + 1] == ' ' || map.map1[r][c - 1] == ' '))
			ft_error_wall();
	}
}
