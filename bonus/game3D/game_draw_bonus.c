/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_draw_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saboulal <saboulal@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 13:25:55 by nkhoudro          #+#    #+#             */
/*   Updated: 2024/01/27 18:19:24 by saboulal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub.h"

void	start_draw(void *mlx)
{
	t_map	*map;

	map = mlx;
	mlx_delete_image(map->mlx, map->img);
	map->img = mlx_new_image(map->mlx, WIDTH, HEIGHT);
	if (!map->img)
	{
		mlx_close_window(map->mlx);
		ft_error();
	}
	if (mlx_image_to_window(map->mlx, map->img, 0, 0) == -1)
	{
		mlx_close_window(map->mlx);
		ft_error();
	}
	generate_3d_projection(map);
	castrays(map);
	moveplayer(map);
	minimap(map);
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

	map->player.ra += map->player.td * map->player.ts;
	movestep = map->player.wd * map->player.ws;
	if (map->player.wlr)
		movestep = map->player.wlr * map->player.ws;
	newplayerx = map->player.x + cos(map->player.ra) * movestep;
	newplayery = map->player.y + sin(map->player.ra) * movestep;
	if (map->player.wlr)
	{
		newplayerx = map->player.x + cos(map->player.ra + M_PI_2) * movestep;
		newplayery = map->player.y + sin(map->player.ra + M_PI_2) * movestep;
	}
	if (!map_wall(newplayerx, newplayery, map))
	{
		if (wall_collision(map, newplayerx, newplayery))
			return ;
		map->player.x = newplayerx;
		map->player.y = newplayery;
	}
}

void	mouse_press(double x, double y, void *mlx)
{
	t_map	*map;

	map = mlx;
	if (x > 0 && x < WIDTH && y > 0 && y < HEIGHT)
	{
		if (map->prev != -1)
		{
			map->player.ra += (x - map->prev) * 0.00008;
		}
		else
			map->prev = x;
	}
	else
		map->prev = -1;
}

void	map_draw(t_map map)
{
	find_player(&map);
	initial_data(&map);
	intial_mlx(&map);
	map.texture = malloc(sizeof(mlx_image_t *) * 5);
	if (!map.texture)
		ft_error();
	map.texture[NORTH] = mlx_load_png(map.north);
	map.texture[SOUTH] = mlx_load_png(map.south);
	map.texture[WEST] = mlx_load_png(map.west);
	map.texture[EAST] = mlx_load_png(map.east);
	map.texture[DOOR] = mlx_load_png("./Textures/Door.png");
	if (!map.texture[NORTH] || !map.texture[SOUTH]
		|| !map.texture[WEST] || !map.texture[EAST] || !map.texture[DOOR])
	{
		for_leak_mlx(&map);
		ft_error();
	}
	mlx_cursor_hook(map.mlx, mouse_press, &map);
	mlx_loop_hook(map.mlx, start_draw, &map);
	mlx_key_hook(map.mlx, key_press, &map);
	mlx_set_cursor_mode(map.mlx, MLX_MOUSE_NORMAL);
	mlx_loop(map.mlx);
	for_leak_mlx(&map);
}
