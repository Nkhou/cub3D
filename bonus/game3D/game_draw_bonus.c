/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_draw_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkhoudro <nkhoudro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 13:25:55 by nkhoudro          #+#    #+#             */
/*   Updated: 2024/01/26 15:33:01 by nkhoudro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub.h"

// void	find_player(t_map *map)
// {
// 	int	i;
// 	int	j;

// 	i = 0;
// 	if (!map)
// 		return ;
// 	while (map->map1[i])
// 	{
// 		j = 0;
// 		while (map->map1[i][j])
// 		{
// 			if (map->map1[i][j] && (map->map1[i][j] == 'N'
// 			|| map->map1[i][j] == 'S'
// 			|| map->map1[i][j] == 'W' || map->map1[i][j] == 'E'))
// 			{
// 				map->player.y = (i) * TILE_SIZE + TILE_SIZE / 2;
// 				map->player.x = j * TILE_SIZE + TILE_SIZE / 2;
// 				map->dr = map->map1[i][j];
// 				map->map1[i][j] = '0';
// 			}
// 			j++;
// 		}
// 		i++;
// 	}
// }

// void	draw_player(t_map *map)
// {
// 	int	px;
// 	int	py;

// 	py = 140;
// 	while (py < 160)
// 	{
// 		px = 140;
// 		while (px < 160)
// 		{
// 			if (distance_between_points(px, py, 150, 150) <= 5)
// 				mlx_put_pixel(map->img, px, py, 0xF8E559);
// 			px++;
// 		}
// 		py++;
// 	}
// }

// void	draw_minmap(t_map *map, t_min *min)
// {
// 	if (map->map1[(int)(min->y / TILE_SIZE)]
// 		&& map->map1[(int)(min->y / TILE_SIZE)] \
// 		[(int)(min->x / TILE_SIZE)] == '1')
// 		mlx_put_pixel(map->img, min->j, min->i, 0xFFFFFFFF);
// 	else if (map->map1[(int)(min->y / TILE_SIZE)]
// 	&& map->map1[(int)(min->y / TILE_SIZE)] \
// 	[(int)(min->x / TILE_SIZE)] == '0')
// 		mlx_put_pixel(map->img, min->j, min->i, 0x00000000);
// 	else if (map->map1[(int)(min->y / TILE_SIZE)]
// 	&& map->map1[(int)(min->y / TILE_SIZE)] \
// 	[(int)(min->x / TILE_SIZE)] == 'D')
// 		mlx_put_pixel(map->img, min->j, min->i, 0xFFFFFF);
// 	else
// 		mlx_put_pixel(map->img, min->j, min->i, 0x00000000);
// 	min->j++;
// 	min->x++;
// }

// void	minimap(t_map *map)
// {
// 	t_min	min;

// 	min.y = map->player.y - 150;
// 	min.i = 0;
// 	while (min.i < 300)
// 	{
// 		min.j = 0;
// 		min.x = map->player.x - 150;
// 		while (min.j < 300)
// 		{
// 			if ((int)(min.x / TILE_SIZE) < 0
// 				|| (int)(min.x / TILE_SIZE) > map->width
// 				|| (int)(min.y / TILE_SIZE) < 0
// 				|| (int)(min.y / TILE_SIZE) > map->height)
// 			{
// 				min.j++;
// 				min.x++;
// 				continue ;
// 			}
// 			draw_minmap(map, &min);
// 		}
// 		min.i++;
// 		min.y++;
// 	}
// 	draw_player(map);
// }

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

void	mouse_press(double x, double y, void *mlx)
{
	t_map	*map;

	map = mlx;
	if (x > 0 && x < WIDTH && y > 0 && y < HEIGHT)
	{
		if (map->prev != -1)
		{
			map->player.rA += (x - map->prev) * 0.00008;
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
	map.texture = malloc(sizeof(mlx_image_t *) * 4);
	if (!map.texture)
		ft_error();
	map.texture[NORTH] = mlx_load_png(map.North);
	map.texture[SOUTH] = mlx_load_png(map.South);
	map.texture[WEST] = mlx_load_png(map.West);
	map.texture[EAST] = mlx_load_png(map.East);
	if (!map.texture[NORTH] || !map.texture[SOUTH]
		|| !map.texture[WEST] || !map.texture[EAST])
		ft_error();
	mlx_cursor_hook(map.mlx, mouse_press, &map);
	mlx_loop_hook(map.mlx, start_draw, &map);
	mlx_key_hook(map.mlx, key_press, &map);
	mlx_set_cursor_mode(map.mlx, MLX_MOUSE_HIDDEN);
	mlx_loop(map.mlx);
	mlx_delete_image(map.mlx, map.img);
	mlx_delete_texture(map.texture[NORTH]);
	mlx_terminate(map.mlx);
}
