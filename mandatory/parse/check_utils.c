/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saboulal <saboulal@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 16:02:47 by saboulal          #+#    #+#             */
/*   Updated: 2024/01/30 18:31:18 by saboulal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub.h"

void	get_map(t_map *map)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	map->r = len_map(map->map1);
	map->tab = malloc(sizeof(char *) * (map->r + 1));
	map->c = 0;
	if (!map->tab)
		ft_error();
	while (map->map1[i])
	{
		if (map->map1[i][0] == '1'
				|| map->map1[i][0] == ' '
				|| map->map1[i][0] == '0')
		{
			map->tab[j++] = ft_strndup(map->map1[i],
					ft_strlen(map->map1[i]) - \
					check_new_line(map->map1[i]));
			if (map->c < ft_strlen(map->tab[j - 1]))
				map->c = ft_strlen(map->tab[j - 1]);
		}
		i++;
	}
	map->tab[j] = 0;
}

int	floor_(t_map *map)
{
	int		i;
	char	**p;
	int		find;
	char *f;

	i = 0;
	find = 0;
	f = NULL;
	while (i < map->start && map->map[i])
	{
		f = ft_skip_1(map->map[i], f);
		if (f && ft_strncmp(f, "F ", 2) == 0)
		{
			if (cmp_comma(f))
				ft_error();
			p = ft_split(f + 1, ',');
			ft_rgb_cor1(p, map);
			ft_free(p);
			free(f);
			f = NULL;
			find++;
		}
		if (find > 1)
			ft_error();
		i++;
	}
	if (f)
		free(f);
	if (find != 1)
		ft_error();
	return (0);
}

int	cmp_comma(char *str)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] == ',')
			j++;
		i++;
	}
	if (j != 2)
		return (1);
	return (0);
}

int	ceilling_(t_map *map)
{
	int		i;
	char	**p;
	int		find;
	char	*c;

	i = 0;
	find = 0;
	c = NULL;
	while (i < map->start && map->map[i])
	{
		c = ft_skip_1(map->map[i], c);
		if (c && ft_strncmp(c, "C ", 2) == 0)
		{
			if (cmp_comma(c))
				ft_error();
			p = ft_split(c + 1, ',');
			ft_rgb_cor(p, map);
			ft_free(p);
			free(c);
			c = NULL;
			find++;
		}
		if (find > 1)
			ft_error();
		i++;
	}
	if (c)
		free(c);
	if (find != 1)
		ft_error();
	return (0);
}

void	ft_extention(char **argv)
{
	if (check_exet(argv[1], ".cub") || ft_strlen(argv[1]) < 5)
	{
		write(2, "Error Not Valid Extention\n", 26);
		exit(0);
	}
}
