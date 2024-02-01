/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_position.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saboulal <saboulal@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 19:34:51 by saboulal          #+#    #+#             */
/*   Updated: 2024/02/01 13:26:41 by saboulal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub.h"

int	ft_north(t_map *map, int i, int k)
{
	char	*p;

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
				get_north(map, p, k);
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
	char	*s;

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
				get_south(map, s, k);
				return (free(s), s = NULL, 1);
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
				get_west(map, k, w);
				return (free(w), w = NULL, 1);
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
				get_east(map, e, k);
				return (free(e), e = NULL, 1);
			}
		}
		i++;
	}
	if (e)
		free(e);
	return (0);
}
