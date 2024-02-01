/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util_lines.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saboulal <saboulal@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/28 19:58:13 by saboulal          #+#    #+#             */
/*   Updated: 2024/02/01 12:28:35 by saboulal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub.h"

void	check_pos_line_c(char *str, int i, t_tex *tex)
{
	if (str[i] == 'C' && str[i + 1] == ' ')
	{
		while (str[i] != '\n')
			i++;
		tex->c++;
	}
}

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

void	get_floor(char *f, t_map *map, int *find)
{
	char	**p;

	check(f + 1);
	if (cmp_comma(f))
		ft_error();
	p = ft_split(f + 1, ',');
	ft_rgb_cor1(p, map);
	ft_free(p);
	(*find)++;
}

int	floor_(t_map *map)
{
	int		i;
	int		find;
	char	*f;

	i = 0;
	find = 0;
	f = NULL;
	while (i < map->start && map->map[i])
	{
		f = ft_skip_1(map->map[i], f);
		if (f && ft_strncmp(f, "F ", 2) == 0)
		{
			get_floor(f, map, &find);
			free(f);
			f = NULL;
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
