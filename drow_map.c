/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drow_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkhoudro <nkhoudro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 15:10:35 by nkhoudro          #+#    #+#             */
/*   Updated: 2023/12/26 14:16:41 by nkhoudro         ###   ########.fr       */
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
void trace_line(t_map map, int x2, int y2, int color)
{
   int m;
    int x1;
    int y1;
    int c;
    int center_x;
    int center_y;
    int i;
    i = 0;

    m = (y2 - map.player.y) / (x2 - map.player.x);
    c = map.player.y - (m * map.player.x);
    x1 = map.player.x;
    y1 = map.player.y;
    center_x = map.player.x + 16;
    center_y = map.player.y + 16;
    if (map.player.direction == 0)
    {
            printf("----E\n");
            while (x1 > x2)
            {
                printf("------E\n");
                y1 = (m * x1) + c;
                mlx_pixel_put(map.mlx, map.win, x1 + 16 * 2, y1 + 16 /2, color);
                i++;
                x1--;
            }

    }
    else if (map.player.direction == 180)
    {
       printf("----W\n");
            while (x1 > x2)
            {
                printf("------w\n");
                y1 = (m * x1) + c + (16/2 + i );
                mlx_pixel_put(map.mlx, map.win, x1, y1 , color);
                i++;
                x1--;
            }
    }
    else if (map.player.direction == 90)
    {
        printf("-----N\n");
        while (y1 > y2)
        {
            x1 = (y1 - c) / m + (16/2 - i / 2);
            mlx_pixel_put(map.mlx, map.win, x1 , y1, color);
            i++;
            y1--;
        }
    }
    else if (map.player.direction == 270)
    {
        // if (m == 0)
        // {
        //     x1  = 
        // }
        y2 = y2 + 16 * 2;
        y1 = y1 + 16;
        x1 = x1 + 16 / 2;
        while (y1 < y2)
        {
        printf("-----S\n");
            // x1 = (y1 - c) / m;
            mlx_pixel_put(map.mlx, map.win, x1 , y1, color);
            i++;
            y1++;
        }
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
// void renderplayer(t_map *map)
// {
    
// }
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
                map.player.x = j * 32;
                map.player.y = k * 32;
                trace_cercle(map, j * 32, k * 32, 0xFF0000);
                // trace_carre(map, j * 32, k * 32, 0x00FF00);
            }
            j++;
        }
        k++;
        j = 0;
        i++;
    }
    int x;
    int y;
    x = map.player.x;
    y = map.player.y;
    if (map.player.direction == 0) // 0 is east
    {
        printf("E\n");
        printf("%d\n", map.player.direction);
        x -= cos(map.player.direction) * map.player.walkSpeed;
        y -= sin(map.player.direction) * map.player.walkSpeed;
    }
    else if (map.player.direction == 180) // 180 is west
    {
        printf("W\n");
        x += cos(map.player.direction) * map.player.walkSpeed;
        y += sin(map.player.direction) * map.player.walkSpeed;
    }
    else if (map.player.direction == 90) // 90 is north
    {
        printf("N\n");
        x -= cos(map.player.direction) * map.player.walkSpeed;
        y -= sin(90) * map.player.walkSpeed;
    }
    else if (map.player.direction == 270) // 270 is south
    {
        printf("S\n");
        x += cos(map.player.direction) * map.player.walkSpeed;
        y += sin(map.player.direction) * map.player.walkSpeed;
    }
    // if (map.player.direction == 0)
    // {
    //     x += cos(map.player.direction) * map.player.walkSpeed;
    //     y += sin(map.player.direction) * map.player.walkSpeed;
    // }
    // else if (map.player.direction == 180)
    // {
    //     x -= cos(map.player.direction) * map.player.walkSpeed;
    //     y -= sin(map.player.direction) * map.player.walkSpeed;
    // }
    // else if (map.player.direction == 90)
    // {
    //     x += cos(map.player.direction) * map.player.walkSpeed;
    //     y += sin(map.player.direction) * map.player.walkSpeed;
    // }
    // else if (map.player.direction == 270)
    // {
    //     x -= cos(map.player.direction) * map.player.walkSpeed;
    //     y -= sin(map.player.direction) * map.player.walkSpeed;
    // }
    trace_line(map, x, y, 0x00FF00);
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
int find_player_x(t_map *map)
{
    int i;
    int j;
    

    i = map->start;
    if (!map)
        return(0);
    // while (map[i] && !(ft_strncmp(map[i], "NO ", 3) && ft_strncmp(map[i], "SO ", 3) && ft_strncmp(map[i], "WE ", 3) && ft_strncmp(map[i], "EA ", 3)  && ft_strncmp(map[i], "F ", 2) && ft_strncmp(map[i], "C ", 2)))
    //     i++;
    while (map->map[i] && i >= 6 )
    {
        j = 0;
        while(map->map[i][j])
        {
            if(map->map[i][j] && ( map->map[i][j] == 'N' || map->map[i][j] == 'S' || map->map[i][j] == 'W' || map->map[i][j] == 'E'))
            {
                map->player.y = j;
                map->player.x = i;
                return(j);
            }
            j++;
        }
        i++;
    }
    return(0);
}

void ini_data(t_map *map)
{
    find_player_x( map);
    // map->player.y = find_player_y(map->map, map->start);
    int x = map->player.x;
    int y = map->player.y;
    // int i = 0;
    if (map->map[x][y] == 'S')
    {
        printf("S\n");
        map->player.rotationAngle = 270 * (M_PI / 180);
        map->player.direction = 270;
    }
    else if (map->map[x][y] == 'N')
    {
        printf("*****N\n");
        map->player.rotationAngle = 90 * (M_PI / 180);
        map->player.direction = 90;
       
    }
    else if (map->map[x][y] == 'W')
    {
        printf("W\n");
        map->player.rotationAngle = 180 * (M_PI / 180);
        map->player.direction = 180;
    }
    else if (map->map[x][y] == 'E')
    {
        printf("E\n");
        map->player.rotationAngle = 0 * (M_PI / 180);
        map->player.direction = 0;
    }
    // if (map->map[x][y] == 'S')
    // {
    //     map->player.rotationAngle = 270 * (M_PI / 180);
    //     map->player.direction = 270;
    // }
    // else if (map->map[x][y] == 'N')
    // {
    //     map->player.rotationAngle = 90 * (M_PI / 180);
    //     map->player.direction = 90;
       
    // }
    // else if (map->map[x][y] == 'W')
    // {
    //     map->player.rotationAngle = 180 * (M_PI / 180);
    //     map->player.direction = 180;
    // }
    // else if (map->map[x][y] == 'E')
    // {
    //     map->player.rotationAngle = 0 * (M_PI / 180);
    //     map->player.direction = 0;
    // }
    map->player.turnDirection = 0; // -1 for left, +1 for right
    map->player.walkDirection = 0; // -1 for back, +1 for front
    // map->player.rotationAngle = M_PI / 2; // 90 degree
    map->player.walkSpeed = 16; // 100 pixel per second
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