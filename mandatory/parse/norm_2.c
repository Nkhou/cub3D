/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   norm_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saboulal <saboulal@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 11:14:04 by saboulal          #+#    #+#             */
/*   Updated: 2024/01/26 17:19:12 by saboulal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../../include/cub.h"

int cmp_line(char **str)
{
    int i;
    
    i = 0;
    while(str[i])
        i++;
    return(i);
}

void free_programme(char *str,t_map map)
{
    free(str);
    free(map.ceil);
    ft_free(map.map);
    free(map.floor);
	ft_free(map.map1);
}

void ini_map(t_map *map,int argc)
{
    if (argc  != 2)
    {
        write(2,"ERROR NOT VALID\n",16);
        exit(0);
    }
     map->j = 0;  
     map->i = 0;
     map->k = 0;
    
}

void	map_game_full(t_map map)
{
	int	row;
	int	col;

	row = 0;
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