/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_draw.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saboulal <saboulal@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 13:25:55 by nkhoudro          #+#    #+#             */
/*   Updated: 2024/01/26 17:49:41 by saboulal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub.h"

void	find_player(t_map *map)
{
	int	i;
	int	j;

	i = 0;
	if (!map)
		ft_error();
	while (map->map1[i])
	{
		j = 0;
		while (map->map1[i][j])
		{
			if (map->map1[i][j] && (map->map1[i][j] == 'N'
			|| map->map1[i][j] == 'S'
			|| map->map1[i][j] == 'W' || map->map1[i][j] == 'E'))
			{
				map->player.y = (i) * TILE_SIZE + TILE_SIZE / 2;
				map->player.x = j * TILE_SIZE + TILE_SIZE / 2;
			}
			j++;
		}
		i++;
	}
}

void	start_draw(void *mlx)
{
	t_map	*map;

	if (!mlx)
	{
		mlx_close_window(mlx);
		ft_error();
	}
	map = mlx;
	mlx_delete_image(map->mlx, map->img);
	map->img = mlx_new_image(map->mlx, WIDTH, HEIGHT);
	if (!map->img)
	{
		mlx_close_window(map->mlx);
		free_programme(map);
		ft_error();
	}
	if (mlx_image_to_window(map->mlx, map->img, 0, 0) == -1)
	{
		mlx_close_window(map->mlx);
		free_programme(map);
		ft_error();
	}
	generate_3d_projection(map);
	castrays(map);
	moveplayer(map);
}

int	wall_collision(t_map *map, double x, double y)
{
	if (((!map->map1[(int)y / TILE_SIZE]
				|| map->map1[(int)y / TILE_SIZE] \
				[(int)map->player.x / TILE_SIZE] == '1')
			&& ((!map->map1[(int)map->player.y / TILE_SIZE]
					|| map->map1[(int)map->player.y / TILE_SIZE] \
					[(int)x / TILE_SIZE] == '1'))))
		return (1);
	return (0);
}

void	moveplayer(t_map *map)
{
	double	movestep;
	double	newplayerx;
	double	newplayery;

	map->player.rA += map->player.tD * map->player.tS;
	movestep = map->player.wD * map->player.ws;
	if (map->player.wlr)
		movestep = map->player.wlr * map->player.ws;
	newplayerx = map->player.x + cos(map->player.rA) * movestep;
	newplayery = map->player.y + sin(map->player.rA) * movestep;
	if (map->player.wlr)
	{
		newplayerx = map->player.x + cos(map->player.rA + M_PI_2) * movestep;
		newplayery = map->player.y + sin(map->player.rA + M_PI_2) * movestep;
	}
	if (!map_wall(newplayerx, newplayery, map))
	{
		if (wall_collision(map, newplayerx, newplayery))
			return ;
		map->player.x = newplayerx;
		map->player.y = newplayery;
	}
}

void	map_draw(t_map map)
{
	find_player(&map);
	initial_data(&map);
	intial_mlx(&map);
	map.texture = malloc(sizeof(mlx_image_t *) * 4);
	if (!map.texture)
		ft_error();
	map.texture[NORTH] = mlx_load_png(map.North);
	map.texture[SOUTH] = mlx_load_png(map.South);
	map.texture[WEST] = mlx_load_png(map.West);
	map.texture[EAST] = mlx_load_png(map.East);
	if (!map.texture[NORTH] || !map.texture[SOUTH]
		|| !map.texture[WEST] || !map.texture[EAST])
		{
			mlx_close_window(map.mlx);
			free_programme(&map);
			ft_error();
		}
	mlx_loop_hook(map.mlx, start_draw, &map);
	mlx_key_hook(map.mlx, key_press, &map);
	mlx_loop(map.mlx);
	mlx_delete_image(map.mlx, map.img);
	mlx_delete_texture(map.texture[0]);
	mlx_delete_texture(map.texture[1]);
	mlx_delete_texture(map.texture[2]);
	mlx_delete_texture(map.texture[3]);
	mlx_terminate(map.mlx);
}
