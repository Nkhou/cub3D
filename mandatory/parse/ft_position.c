/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_position.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkhoudro <nkhoudro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 19:34:51 by saboulal          #+#    #+#             */
/*   Updated: 2024/02/01 10:52:13 by nkhoudro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub.h"

int	ft_north(t_map *map, int i, int k)
{
	char	**tab;
	char *p;

	p = NULL;
	while (map->map[i] && i < map->start)
	{
		k = 0;
		p = ft_skip_1(map->map[i], p);
		if (ft_strncmp(p, "NO ", 3) == 0)
		{
			while (p[k] && p[k + 1] \
				&& p[k] != '.' && p[k + 1] != '/')
				(k)++;
			if (p[k] && p[k + 1])
			{
				map->north = ft_strdup(p + k);
				tab = ft_split(map->north, ' ');
				free(map->north);
				free(p);
				p = NULL;
				map->north = ft_strdup(tab[0]);
				ft_free(tab);
				return (1);
			}
		}
		i++;
	}
	if (p)
		free(p);
	return (0);
}

int	ft_south(t_map *map, int i, int k)
{
	char	**tab;
	char *s;

	i = 0;
	s = NULL;
	while (map->map[i] && i < map->start)
	{
		k = 0;
		s = ft_skip_1(map->map[i], s);
		if (s && ft_strncmp(s, "SO ", 3) == 0)
		{
			while (s[k] && s[k + 1] \
				&& s[k] != '.' && s[k + 1] != '/')
				(k)++;
			if (s[k] && s[k + 1])
			{
				map->south = ft_strdup(s + k);
				tab = ft_split(map->south, ' ');
				free(map->south);
				free(s);
				s = NULL;
				map->south = ft_strdup(tab[0]);
				ft_free(tab);
				return (1);
			}
		}
		i++;
	}
	if (s)
		free(s);
	return (0);
}

int	ft_west(t_map *map, int i, int k)
{
	char	**tab;
	char	*w;

	i = 0;
	w = NULL;
	while (map->map[i] && i < map->start)
	{
		k = 0;
		w = ft_skip_1(map->map[i], w);
		if (w && ft_strncmp(w, "WE ", 3) == 0)
		{
			while (w[k] && w[k + 1] \
				&& w[k] != '.' && w[k + 1] != '/')
				(k)++;
			if (w[k] && w[k + 1])
			{
				map->west = ft_strdup(w + k);
				tab = ft_split(map->west, ' ');
				free(map->west);
				free(w);
				w = NULL;
				map->west = ft_strdup(tab[0]);
				ft_free(tab);
				return (1);
			}
		}
		i++;
	}
	if (w)
		free(w);
	return (0);
}

int	ft_east(t_map *map, int i, int k)
{
	char	**tab;
	char	*e;

	i = 0;
	e = NULL;
	while (map->map[i] && i < map->start)
	{
		k = 0;
		e = ft_skip_1(map->map[i], e);
		if (e && ft_strncmp(e, "EA ", 3) == 0)
		{
			while (e[k] && e[k + 1] \
				&& e[k] != '.' && e[k + 1] != '/')
				(k)++;
			if (e[k] && e[k + 1])
			{
				map->east = ft_strdup(e + k);
				tab = ft_split(map->east, ' ');
				free(map->east);
				free(e);
				e = NULL;
				map->east = ft_strdup(tab[0]);
				ft_free(tab);
				return (1);
			}
		}
		i++;
	}
	if (e)
		free(e);
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
