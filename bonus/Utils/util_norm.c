/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util_norm.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saboulal <saboulal@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/28 18:50:04 by saboulal          #+#    #+#             */
/*   Updated: 2024/01/28 20:29:19 by saboulal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub.h"

void	init_part_map(t_map *map)
{
	t_tex	*tex;

	tex = (t_tex *)malloc(sizeof(t_tex));
	if (tex == NULL)
		ft_error();
	map->map1 = (char **) malloc(sizeof(char *) * (map->len - map->start + 1));
	if (map->map1 == NULL)
		ft_error();
	check_line_a(map->str, tex);
	stor_to_map(*map);
	if (check_map(map->map1))
		ft_error();
}

void	init_infos(t_map *map, char **argv)
{
	map->str = check_before_map(argv[1]);
	map->map = ft_split(map->str, '\n');
	map->len = cmp_line(map->map);
	map->width = check_nbr_char(map->map);
	map->start = check_nbr_height(map->map);
	map->height = (map->len - map->start);
	map->player.rays = malloc(sizeof(t_ray) * NB_RAYS);
	if (!map->player.rays)
		ft_error();
	if (map->map == NULL)
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
		write(2, "ERROR NOT VALID\n", 16);
		exit(0);
	}
}

void	check_line_str(char *str, int i)
{
	while (str[i])
	{
		if (str[i] == '\n' && str[i + 1] && str[i + 1] == '\n')
			ft_error();
		i++;
	}
}

void	check_wesfc(t_tex *tex)
{
	if (tex->c > 1 || tex->f > 1 || tex->no > 1 \
			|| tex->so > 1 || tex->we > 1 || tex->ea > 1)
		ft_error();
}
