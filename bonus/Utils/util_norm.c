/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util_norm.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkhoudro <nkhoudro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/28 18:50:04 by saboulal          #+#    #+#             */
/*   Updated: 2024/02/01 12:57:58 by nkhoudro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub.h"

void	init_part_map(t_map *map)
{
	t_tex	tex;

	init_vaar(&tex);
	map->map1 = (char **) malloc(sizeof(char *) * (map->len - map->start + 1));
	if (map->map1 == NULL)
		ft_error();
	check_line_a(map->str, &tex, map);
	stor_to_map(*map);
	if (check_map(map->map1))
		ft_error();
}

void	init_infos(t_map *map, char **argv)
{
	int	i;

	i = 0;
	map->str = check_before_map(argv[1]);
	if (!map->str)
		ft_error();
	map->map = ft_split(map->str, '\n');
	if (map->map == NULL)
		ft_error();
	map->len = cmp_line(map->map);
	map->width = check_nbr_char(map->map);
	map->start = check_nbr_height(map->map);
	map->height = (map->len - map->start);
	map->player.rays = malloc(sizeof(t_ray) * NB_RAYS);
	if (!map->player.rays)
		ft_error();
}

void	init_parse(t_map *map)
{
	get_map(map);
	check_texture_map(map);
	map_game(map->map1);
	map_game_full(*map);
	if (check_white_space(map))
	{
		write(1, "Error\n", 6);
		write(2, "ERROR NOT VALID\n", 16);
		exit(1);
	}
}

void	check_line_str(char *str, int *i, t_map *map)
{
	(void)map;
	while (str[*i])
	{
		if (str[*i] == '\n' && str[(*i) + 1] && str[(*i) + 1] == '\n')
		{
			(*i)++;
			while (str[*i] == '\n' || str[*i] == ' ')
				(*i)++;
			if (str[*i])
				ft_error();
		}
		(*i)++;
	}
}

void	check_wesfc(t_tex *tex)
{
	if (tex->c > 1 || tex->f > 1 || tex->no > 1 \
			|| tex->so > 1 || tex->we > 1 || tex->ea > 1)
		ft_error();
}
