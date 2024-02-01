/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_space_.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saboulal <saboulal@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 11:09:09 by saboulal          #+#    #+#             */
/*   Updated: 2024/02/01 11:35:28 by saboulal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub.h"

int	invalid_white_space(t_map *map, int i, int j)
{
	if (!map->map1)
		return (1);
	if (map->map1[i][j] == ' ' || map->map1[i][j] == '\t')
	{
		if (i != 0 && map->map1[i - 1][j] != '1' && map->map1[i - 1][j] != ' ')
			return (1);
		if (i != map->r - 1 && map->map1[i + 1][j] != '1' && map->map1[i
			+ 1][j] != ' ' )
			return (1);
		if (j != 0 && map->map1[i][j - 1] != '1' && map->map1[i][j - 1] != ' '
			)
			return (1);
		if (j != map->c - 1 && map->map1[i][j + 1] != '1' \
			&& map->map1[i][j + 1] != ' ' )
			return (1);
	}
	return (0);
}

int	waall(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] != '1' && str[i] != ' ' && str[i] != '\t')
			return (1);
		i++;
	}
	return (0);
}

char	*ft_str(const char *s, int c)
{
	if (!s)
		return (NULL);
	while (*s)
	{
		if (*(char *)s == (char)c)
		{
			return ((char *)s);
		}
		s++;
	}
	if (*(char *)s == (char)c)
	{
		return ((char *)s);
	}
	return (NULL);
}

int	check_white_space(t_map *map)
{
	int	i;
	int	j;

	i = 0;
	while (i < map->r)
	{
		if (map->map1[i] && (ft_str(map->map1[i], ' ')
				|| ft_str(map->map1[i], '\t')))
		{
			j = 0;
			while (map->map1[i] && map->map1[i][j])
			{
				if (invalid_white_space(map, i, j))
					return (1);
				j++;
			}
		}
		i++;
	}
	return (0);
}

void	get_space_wall(t_map map)
{
	int	i;
	int	j;

	i = 0;
	if (!map.map1)
		return ;
	while (map.map1[i])
	{
		j = 0;
		while (map.map1[i][j])
		{
			if (map.map1[i][j] == ' ')
				map.map1[i][j] = '1';
			j++;
		}
		i++;
	}
}
