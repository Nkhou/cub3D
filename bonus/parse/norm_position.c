/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   norm_position.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saboulal <saboulal@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 14:34:14 by saboulal          #+#    #+#             */
/*   Updated: 2024/02/01 12:23:34 by saboulal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub.h"

void	get_north(t_map *map, char *p, int k)
{
	char	**tab;

	map->north = ft_strdup(p + k);
	tab = ft_split(map->north, ' ');
	free(map->north);
	free(p);
	p = NULL;
	map->north = ft_strdup(tab[0]);
	ft_free(tab);
}

void	get_south(t_map *map, char *s, int k)
{
	char	**tab;

	map->south = ft_strdup(s + k);
	tab = ft_split(map->south, ' ');
	free(map->south);
	map->south = ft_strdup(tab[0]);
	ft_free(tab);
}

void	get_west(t_map *map, int k, char *w)
{
	char	**tab;

	map->west = ft_strdup(w + k);
	tab = ft_split(map->west, ' ');
	free(map->west);
	map->west = ft_strdup(tab[0]);
	ft_free(tab);
}

void	get_east(t_map *map, char *e, int k)
{
	char	**tab;

	map->east = ft_strdup(e + k);
	tab = ft_split(map->east, ' ');
	free(map->east);
	map->east = ft_strdup(tab[0]);
	ft_free(tab);
}
