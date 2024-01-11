/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkhoudro <nkhoudro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/22 13:46:14 by saboulal          #+#    #+#             */
/*   Updated: 2024/01/11 19:49:02 by nkhoudro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"cub.h"

 int	space_waall(char **map, int r, int c)
{
	if (map[r][c] != '1' && ft_is_space(map[r][c]))
		return (1);
	return (0);
}

static int 	space_waall_(char **map, int r, int i)
{
	while (map[r][i])
	{
		if (map[r][i] != '1' && ft_is_space(map[r][i]))
			return (1);
		i++;
	}
	return (0);
}


int	found_wall(char **map, int r)
{
	t_parse par;

	par.lenght_1 = ft_strlen(map[r]);
	par.lenght_2 = 0;
	if (map[r + 1])
		par.lenght_2 = ft_strlen(map[r + 1]);
	if (par.lenght_1 > par.lenght_2 && par.lenght_2 > 0)
	{
		if (space_waall_(map, r, par.lenght_2))
			return (1);
	}
	else if (par.lenght_2 > par.lenght_1)
	{
		if (space_waall_(map, r + 1, par.lenght_1))
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
		ft_error();
	while (map->map[i])
	{ 
		if (map->map[i][0] == '1'
				|| !ft_is_space(map->map[i][0])
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

int ft_is_space(char c)
{
	if(c == ' ')
		return (1);
	return (0);
}