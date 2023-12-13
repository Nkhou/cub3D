/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drow_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkhoudro <nkhoudro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 15:10:35 by nkhoudro          #+#    #+#             */
/*   Updated: 2023/12/13 20:46:33 by nkhoudro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"
void trace_carre(t_map map, int x, int y, int color)
{
    int i;
    int j;

    i = 0;
    j = 0;
    while (i < 32)
    {
        while (j < 32)
        {
            mlx_pixel_put(map.mlx, map.win, x + i, y + j, color);
            j++;
        }
        j = 0;
        i++;
    }
}
void trace_cercle(t_map map, int x, int y, int color)
{
    int i;
    int j;
    int r;

    i = 0;
    j = 0;
    r = 8;
    
    while (i < 32)
    {
        while (j < 32)
        {
            if (sqrt(pow((x + i) - (x + r), 2) + pow((y + j) - (y + r), 2)) <= r)
                mlx_pixel_put(map.mlx, map.win, x + i, y + j, color);
            j++;
        }
        j = 0;
        i++;
    }
}
void key_press(int keycode, t_map *map)
{
    if (keycode == 13) // w
        map->player.walkDirection = 1;
    else if (keycode == 1) // s
        map->player.walkDirection = -1;
    else if (keycode == 0) // a
        map->player.turnDirection = -1;
    else if (keycode == 2) // d
        map->player.turnDirection = 1;
}
void key_release(int keycode, t_map *map)
{
    if (keycode == 13) // w
        map->player.walkDirection = 0;
    else if (keycode == 1) // s
        map->player.walkDirection = 0;
    else if (keycode == 0) // a
        map->player.turnDirection = 0;
    else if (keycode == 2) // d
        map->player.turnDirection = 0;
}

void inisti_window(t_map map)
{
    int i;
    int j;
    int k;

    i = map.start;
    j = 0;
    k = 0;
    map.mlx = mlx_init();
    map.win = mlx_new_window(map.mlx, map.width, map.height, "cub3D");
    while (map.map[i])
    {
        while(map.map[i][j])
        {
            if(map.map[i][j] == '1')
            {
                trace_carre(map, j * 32, k * 32, 0xFFFFFF);
            }
            else if (map.map[i][j] == '0') 
            {
                trace_carre(map, j * 32, k * 32, 0x000000);
            }
            else if (map.map[i][j] == 'N' || map.map[i][j] == 'S' || map.map[i][j] == 'W' || map.map[i][j] == 'E')
            {
                trace_cercle(map, j * 32, k * 32, 0xFF0000);
                // trace_carre(map, j * 32, k * 32, 0x00FF00);
            }
            j++;
        }
        k++;
        j = 0;
        i++;
    }
    mlx_loop(map.mlx);
}
void inisti_player(t_map *map)
{
    int i;
    int j;
    int k;

    i = map->start;
    j = 0;
    k = 0;
    while (map->map[i])
    {
        while(map->map[i][j])
        {
            if(map->map[i][j] == 'N' || map->map[i][j] == 'S' || map->map[i][j] == 'W' || map->map[i][j] == 'E')
            {
                map->player.x = j * 32;
                map->player.y = k * 32;
                if (map->map[i][j] == 'N')
                    map->player.rotationAngle = 270 * (M_PI / 180);
                else if (map->map[i][j] == 'S')
                    map->player.rotationAngle = 90 * (M_PI / 180);
                else if (map->map[i][j] == 'W')
                    map->player.rotationAngle = 180 * (M_PI / 180);
                else if (map->map[i][j] == 'E')
                    map->player.rotationAngle = 0 * (M_PI / 180);
            }
            j++;
        }
        k++;
        j = 0;
        i++;
    }
}
int find_player_x(char **map)
{
    int i;
    int j;
    
    i = 0;
    if (!map)
        return(0);
    while (map[i] && !(ft_strncmp(map[i], "NO ", 3) && ft_strncmp(map[i], "SO ", 3) && ft_strncmp(map[i], "WE ", 3) && ft_strncmp(map[i], "EA ", 3)  && ft_strncmp(map[i], "F ", 2) && ft_strncmp(map[i], "C ", 2)))
        i++;
    while (map[i] && i > 6 )
    {
        j = 0;
        while(map[i][j])
        {
            if(map[i][j] == 'N' || map[i][j] == 'S' || map[i][j] == 'W' || map[i][j] == 'E')
            {
                return(j);
            }
            j++;
        }
        i++;
    }
    return(0);
}
int find_player_y(char **map)
{
    int i;
    int j;
    
    i = 0;
    while (map[i] && !(ft_strncmp(map[i], "NO ", 3) && ft_strncmp(map[i], "SO ", 3) && ft_strncmp(map[i], "WE ", 3) && ft_strncmp(map[i], "EA ", 3)  && ft_strncmp(map[i], "F ", 2) && ft_strncmp(map[i], "C ", 2)))
        i++;
    while (map[i] && i > 6 )
    {
        j = 0;
        while(map[i][j])
        {
            if(map[i][j] == 'N' || map[i][j] == 'S' || map[i][j] == 'W' || map[i][j] == 'E')
            {
                return(i);
            }
            j++;
        }
        i++;
    }
    return(0);
}
void ini_data(t_map *map)
{
    map->player.x = find_player_x(map->map);
    map->player.y = find_player_y(map->map);
    map->player.turnDirection = 0; // -1 for left, +1 for right
    map->player.walkDirection = 0; // -1 for back, +1 for front
    map->player.rotationAngle = M_PI / 2; // 90 degree
    map->player.walkSpeed = 5; // 100 pixel per second
    map->player.turnSpeed = 5 * (M_PI / 180); // 100 pixel per second
}
void map_draw(t_map map)
{
    ini_data(&map);
    // inisti_player(&map);
    inisti_window(map);
    // mlx_hook(map.win, 2, 1L<<0, key_press, &map);
    // mlx_hook(map.win, 3, 1L<<1, key_release, &map);
}