/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkhoudro <nkhoudro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 21:02:31 by nkhoudro          #+#    #+#             */
/*   Updated: 2024/01/25 21:03:37 by nkhoudro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub.h"

int map_wall(double x, double y, t_map *map)
{
    double mapGridIndexX;
    double mapGridIndexY;
    if (x < 0  || x > map->width * TILE_SIZE || y < 0 || y > map->height * TILE_SIZE)
        return (1);
    mapGridIndexX = (int)floor((double)x / (double)TILE_SIZE);
    mapGridIndexY = (int)floor((double)y / (double)TILE_SIZE);
    if (!map->map1[(int)mapGridIndexY] || map->map1[(int)mapGridIndexY][(int)mapGridIndexX] == '1'
    || map->map1[(int)mapGridIndexY][(int)mapGridIndexX] == 'D')
        return (1);
    return (0);
}
void initial_data(t_map *map)
{
    if (!map)
        ft_error();
    if (map->map1[(int)map->player.y /TILE_SIZE][(int)map->player.x /TILE_SIZE] == 'N')
        map->player.rotationAngle = 1.5 * PI;
    else if (map->map1[(int)map->player.y /TILE_SIZE][(int)map->player.x /TILE_SIZE] == 'S')
        map->player.rotationAngle = 0.5 * PI;
    else if (map->map1[(int)map->player.y /TILE_SIZE][(int)map->player.x /TILE_SIZE] == 'E')
        map->player.rotationAngle =PI;
    else if (map->map1[(int)map->player.y /TILE_SIZE][(int)map->player.x /TILE_SIZE] == 'W')
        map->player.rotationAngle = 0;
    map->player.turnDirection = 0;
    map->player.walkDirection = 0;
    map->player.walkleftright = 0;
    map->player.walkSpeed = 8;
    map->player.turnSpeed = 3 * (PI / 180);
    map->player.d = 0;
    map->prev = -1;
}
void key_release(mlx_key_data_t keydata, t_map *map)
{
    if ((keydata.key == MLX_KEY_W) && (keydata.action == MLX_RELEASE)) // w 
        map->player.walkDirection = 0;
    else if (keydata.key == MLX_KEY_S && (keydata.action == MLX_RELEASE))// s
        map->player.walkDirection = 0;
    else if (keydata.key == MLX_KEY_A && (keydata.action == MLX_RELEASE))// A
        map->player.walkleftright = 0;
    else if (keydata.key == MLX_KEY_D && (keydata.action == MLX_RELEASE))// D
        map->player.walkleftright = 0;
    else if (keydata.key == MLX_KEY_LEFT && (keydata.action == MLX_RELEASE)) // left
        map->player.turnDirection = 0;
    else if (keydata.key == MLX_KEY_RIGHT && (keydata.action == MLX_RELEASE)) // right
        map->player.turnDirection = 0;
}

void key_press(mlx_key_data_t keydata, void *mlx)
{
    t_map *map;

    map = mlx;
    if ((keydata.key == MLX_KEY_S) && (keydata.action == MLX_PRESS)) // w 
        map->player.walkDirection = -1;
    else if (keydata.key == MLX_KEY_W && (keydata.action == MLX_PRESS))// s
        map->player.walkDirection = 1;
    else if (keydata.key == MLX_KEY_A && (keydata.action == MLX_PRESS))// A
        map->player.walkleftright = -1;
    else if (keydata.key == MLX_KEY_D && (keydata.action == MLX_PRESS))// D
        map->player.walkleftright = 1;
    else if (keydata.key == MLX_KEY_LEFT && (keydata.action == MLX_PRESS)) // left
        map->player.turnDirection = -1;
    else if (keydata.key == MLX_KEY_RIGHT && (keydata.action == MLX_PRESS)) // right
        map->player.turnDirection = 1;
    else if (keydata.key == MLX_KEY_ESCAPE && (keydata.action == MLX_PRESS))
    {
        mlx_close_window(map->mlx);
        exit(0);
    }
    key_release(keydata, map);
}
void intial_mlx(t_map *map)
{
    map->mlx = mlx_init(WIDTH , HEIGHT, "cub3D", true);
    if (!map->mlx)
    {
        ft_error();
        return ;   
    }
    map->img = mlx_new_image(map->mlx, WIDTH,  HEIGHT);
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
}