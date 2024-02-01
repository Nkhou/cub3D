/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_rgb.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkhoudro <nkhoudro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 21:36:33 by saboulal          #+#    #+#             */
/*   Updated: 2024/02/01 11:19:07 by nkhoudro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub.h"

void	ft_rgb_cor(char **p, t_map *map)
{
	char	*c;
	char	*c1;
	char	*c2;

	map->ceil = (t_rgb *) malloc(sizeof(t_rgb));
	if (!map->ceil)
		ft_error();
	c = ft_strtrim(p[0], " ");
	map->ceil->r = ft_atoi(c);
	c1 = ft_strtrim(p[1], " ");
	map->ceil->g = ft_atoi(c1);
	c2 = ft_strtrim(p[2], " ");
	map->ceil->b = ft_atoi(c2);
	free(c);
	free(c1);
	free(c2);
	check_rgb_ceil(map);
}

void	ft_rgb_cor1(char **p, t_map *map)
{
	char	*c;
	char	*c1;
	char	*c2;

	map->floor = (t_rgb *) malloc(sizeof(t_rgb));
	if (!map->floor)
		ft_error();
	c = ft_strtrim(p[0], " ");
	map->floor->r = ft_atoi(c);
	c1 = ft_strtrim(p[1], " ");
	map->floor->g = ft_atoi(c1);
	c2 = ft_strtrim(p[2], " ");
	map->floor->b = ft_atoi(c2);
	free(c);
	free(c1);
	free(c2);
	check_rgb_floor(map);
}

void	check_rgb_floor(t_map *map)
{
	int	i;

	i = 0;
	while (i < 3)
	{
		if ((map->floor->r >= 0 && map->floor->r <= 255)
			&& (map->floor->g >= 0 && map->floor->g <= 255)
			&& (map->floor->b >= 0 && map->floor->b <= 255))
			i++;
		else
			ft_error();
	}
}

int	check_path(t_map *map)
{
	int	i;
	int	j;

	i = 0;
	while (map->map[i])
	{
		j = 0;
		while (map->map[i][j]
		&& map->map[i][j] == 'N'
		&& map->map[i][j + 1] == 'O'
		&& map->map[i][j + 2] == ' ')
			j++;
		i++;
	}
	return (0);
}
