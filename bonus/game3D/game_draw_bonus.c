/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_draw_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkhoudro <nkhoudro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 13:25:55 by nkhoudro          #+#    #+#             */
/*   Updated: 2024/02/01 13:23:06 by nkhoudro         ###   ########.fr       */
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
		error_in_draw();
	}
	if (mlx_image_to_window(map->mlx, map->img, 0, 0) == -1)
	{
		mlx_close_window(map->mlx);
		error_in_draw();
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

void	mouse_press(void *mlx)
{
	t_map	*map;
	int		x;
	int		y;

	map = (t_map *)mlx;
	mlx_get_mouse_pos(map->mlx, &x, &y);
	map->player.ra += (float)(x - (WIDTH / 2)) / (HEIGHT / 2);
	mlx_set_mouse_pos(map->mlx, (WIDTH / 2), (HEIGHT / 2));
}

void	map_draw(t_map map)
{
	find_player(&map);
	initial_data(&map);
	intial_mlx(&map);
	map.texture = malloc(sizeof(mlx_image_t *) * 5);
	if (!map.texture)
		error_in_draw();
	map.texture[NORTH] = mlx_load_png(map.north);
	map.texture[SOUTH] = mlx_load_png(map.south);
	map.texture[WEST] = mlx_load_png(map.west);
	map.texture[EAST] = mlx_load_png(map.east);
	map.texture[DOOR] = mlx_load_png("./Textures/Door.png");
	if (!map.texture[NORTH] || !map.texture[SOUTH]
		|| !map.texture[WEST] || !map.texture[EAST] || !map.texture[DOOR])
	{
		error_in_draw();
	}
	mlx_cursor_hook(map.mlx, (void *)mouse_press, &map);
	mlx_loop_hook(map.mlx, start_draw, &map);
	mlx_key_hook(map.mlx, key_press, &map);
	mlx_set_cursor_mode(map.mlx, MLX_MOUSE_HIDDEN);
	mlx_loop(map.mlx);
	mlx_terminate(map.mlx);
}
