/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_position.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saboulal <saboulal@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 19:34:51 by saboulal          #+#    #+#             */
/*   Updated: 2024/01/27 16:49:05 by saboulal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub.h"

int	ft_north(t_map *map, int i, int k)
{
	char	**tab;

	i = 0;
	while (map->map[i] && i < map->start)
	{
		k = 0;
		if (ft_strncmp(map->map[i], "NO ", 3) == 0)
		{
			while (map->map[i][k] && map->map[i][k + 1] \
				&& map->map[i][k] != '.' && map->map[i][k + 1] != '/')
				(k)++;
			if (map->map[i][k] && map->map[i][k + 1])
			{
				map->north = ft_strdup(map->map[i] + k);
				tab = ft_split(map->north, ' ');
				free(map->north);
				map->north = ft_strdup(tab[0]);
				ft_free(tab);
				return (1);
			}
		}
		i++;
	}
	return (0);
}

int	ft_south(t_map *map, int i, int k)
{
	char	**tab;

	i = 0;
	while (map->map[i] && i < map->start)
	{
		k = 0;
		if (ft_strncmp(map->map[i], "SO ", 3) == 0)
		{
			while (map->map[i][k] && map->map[i][k + 1] \
				&& map->map[i][k] != '.' && map->map[i][k + 1] != '/')
				(k)++;
			if (map->map[i][k] && map->map[i][k + 1])
			{
				map->south = ft_strdup(map->map[i] + k);
				tab = ft_split(map->south, ' ');
				free(map->south);
				map->south = ft_strdup(tab[0]);
				ft_free(tab);
				return (1);
			}
		}
		i++;
	}
	return (0);
}

int	ft_west(t_map *map, int i, int k)
{
	char	**tab;

	i = 0;
	while (map->map[i] && i < map->start)
	{
		k = 0;
		if (ft_strncmp(map->map[i], "WE ", 3) == 0)
		{
			while (map->map[i][k] && map->map[i][k + 1] \
				&& map->map[i][k] != '.' && map->map[i][k + 1] != '/')
				(k)++;
			if (map->map[i][k] && map->map[i][k + 1])
			{
				map->west = ft_strdup(map->map[i] + k);
				tab = ft_split(map->west, ' ');
				free(map->west);
				map->west = ft_strdup(tab[0]);
				ft_free(tab);
				return (1);
			}
		}
		i++;
	}
	return (0);
}

int	ft_east(t_map *map, int i, int k)
{
	char	**tab;

	i = 0;
	while (map->map[i] && i < map->start)
	{
		k = 0;
		if (ft_strncmp(map->map[i], "EA ", 3) == 0)
		{
			while (map->map[i][k] && map->map[i][k + 1] \
				&& map->map[i][k] != '.' && map->map[i][k + 1] != '/')
				(k)++;
			if (map->map[i][k] && map->map[i][k + 1])
			{
				map->east = ft_strdup(map->map[i] + k);
				tab = ft_split(map->east, ' ');
				free(map->east);
				map->east = ft_strdup(tab[0]);
				ft_free(tab);
				return (1);
			}
		}
		i++;
	}
	return (0);
}

void	for_leak_mlx(t_map *map)
{
	mlx_delete_image(map->mlx, map->img);
	mlx_close_window(map->mlx);
	free_programme(map);
	mlx_terminate(map->mlx);
	exit(0);
}
