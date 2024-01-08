/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_draw.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkhoudro <nkhoudro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 13:25:55 by nkhoudro          #+#    #+#             */
/*   Updated: 2024/01/08 21:39:30 by nkhoudro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void trace_cercle(t_map map, int x, int y, int cor)
{
    int r;

    r = 8;
    for (int i = 0; i < 31; ++i)
	{
		for (int j = 0; j <31; ++j)
		{
            if (x + i < map.width  && y + j < map.height && x + i > 0 && y + j > 0)
            {
                if (sqrt(pow((x + i) - (x + r), 2) + pow((y + j) - (y + r), 2)) <= r)
                {
                    mlx_put_pixel(map.img, x + i + 6 , y + j + 6, cor);
                }
            }
        }
    }
}
void drow_line(t_map *map, double rx, double ry , int color)
{
    int dx;
    int dy;
    double err;
    // double der;
    int x0;
    int y0;
    
    dx = rx - map->player.x;
    dy = ry - map->player.y;
    x0 = map->player.x;
    y0 = map->player.y;
    err = 0; 
    while (x0 < rx)
    {
        mlx_put_pixel(map->img, x0 * 32, y0 *32, color);
        err += dy;
        if (err >= 0.5)
        {
            y0 += 1;
            err -= 1;
        }
        x0 += 1;
    }
    // der = (double)dy / (double)dx;
    // while (x0 < rx)
    // {
    //     mlx_put_pixel(map->img, x0, y0, color);
    //     err += der;
    //     if (err >= 0.5)
    //     {
    //         y0 += 1;
    //         err -= 1;
    //     }
    //     x0 += 1;
    // }
}
void drow_rays(t_map *map)
{
    int r;
    // int mx;
    // int my;
    // int mp;
    int dof;
    double rx;
    double ry;
    double ra;
    double xo;
    double yo;
    double atan;
    ra = map->player.pa;
    r = 0;
    while (r < 1)
    {
        dof = 0;
        atan = -1 / tan(ra);
        if (ra > M_PI) //looking up
        {
            ry = (((int)map->player.y >> 6) << 6) - 0.0001;
            rx = (map->player.y - ry) * atan + map->player.x;
            yo = -32;
            xo = -yo * atan;
        }
        if (ra < M_PI) //looking down
        {
            ry = (((int)map->player.y >> 6) << 6) + 32;
            rx = (map->player.y - ry) * atan + map->player.x;
            yo = 32;
            xo = -yo * atan;
        }
        if (ra == 0 || ra == M_PI) //looking straight left or right
        {
            rx = map->player.x;
            ry = map->player.y;
            dof = 8;
        }
        // while (dof < 8)
        // {
        //     mx = (int)(rx) >> 6;
        //     my = (int)(ry) >> 6;
        //     mp = my * map->width + mx; // map position in map array
        //     // printf("mp = %d\n", mp);
        //     // printf("map->map[mp] = %s\n", map->map[mp]);
        //     // printf("mp = %d\n", mp);
        //     // if (mp > 0 && mp < map->width * map->height && map->map[mp] && ft_strncmp(map->map[mp], "1", 1) == 0)
        //     // {
        //     //     dof = 8;
        //     // }
        //     // else
        //     // {
        //     //     rx += xo;
        //     //     ry += yo;
        //     //     dof += 1;
        //     // }
        // }
        // drow_line(map, rx, ry, 0xF00080);
       r++;
    }
    
}
void trace_carre(t_map map, int x, int y, int cor)
{
    for (int i = 0; i < 31; ++i)
	{
		for (int j = 0; j <31; ++j)
		{
			    mlx_put_pixel(map.img, x + j , y + i  , cor);
		}
	}
}

void find_player(t_map *map)
{
    int i;
    int j;
    

    i = map->start;
    if (!map)
        return ;
    while (map->map[i] && i >= 6 )
    {
        j = 0;
        while(map->map[i][j])
        {
            if(map->map[i][j] && ( map->map[i][j] == 'N' || map->map[i][j] == 'S' || map->map[i][j] == 'W' || map->map[i][j] == 'E'))
            {
                map->player.y = (i - map->start) * 32;
                map->player.x = j * 32;
            }
            j++;
        }
        i++;
    }
}
void inisti_window(void *mlx)
{
    int i;
    int j;
    int k;
    t_map *map;

    map = mlx;
    i = map->start;    

    k = 0;
    while (map->map[i])
    {
        j = 0;
        while(map->map[i][j])
        {
            if(map->map[i][j] == '1')
                trace_carre(*map, j *32 , k *32, 0xFFFFFF);
            else
                trace_carre(*map, j * 32, k * 32, 0x00000F);
            // if (k == ((int)map->player.y / 32 - map->start) && j == (int)map->player.x / 32)
            // {
            //     // if (map->player.d == 0)
            //     // {
            //     // }
                
            //     drow_rays(map);
            //     trace_cercle(*map, j, k, 0xF00080);
            //     // draw_line(*map, j * 32, k * 32, 0xF00080);
            // }
            j++;
        }
        k++;
        i++;
    }
    drow_rays(map);
    trace_cercle(*map, map->player.x, map->player.y, 0xF00080);
}
// int ang(int angle)
// {
//     if (angle > 360)
//         angle = angle % 360;
//     if (angle < 0)
//         angle = ((int)angle + 360 ) % 360;
//     return (angle);
// }
void key_press(mlx_key_data_t keydata, void* mlx)
{
    t_map *map;

    map = mlx;
    double x;
    double y;
    int i;
    x= map->player.x;
    y= map->player.y;
    i = 0;
    if (keydata.key == MLX_KEY_UP || keydata.key == MLX_KEY_W) // w 
    {
        y += map->player.pdy;
        x += map->player.pdx;
        // if (map->map[(int)y /32][(int)x /32] == '1')
        //     return ;
        map->player.x += map->player.pdx;
        map->player.y += map->player.pdy;
    }
    else if (keydata.key == MLX_KEY_DOWN || keydata.key == MLX_KEY_S) // s
    {
        y -= map->player.pdy;
        x -= map->player.pdx;
        // if (map->map[(int)y /32][(int)x /32] == '1')
        //     return ;
        map->player.x -= map->player.pdx;
        map->player.y -= map->player.pdy;
    }
    else if (keydata.key == MLX_KEY_LEFT || keydata.key == MLX_KEY_A) // a
    {
        map->player.pa -= 0.1;
        if (map->player.pa < 0)
        {
            map->player.pa += 2 * M_PI;
        }
        map->player.pdx = cos(map->player.pa) * 5;
        map->player.pdy = sin(map->player.pa)  * 5;
    }
    else if (keydata.key == MLX_KEY_RIGHT || keydata.key == MLX_KEY_D) // d
    {
        map->player.pa += 0.1;
        if (map->player.pa < 2* M_PI)
        {
            map->player.pa -= 2 * M_PI;
        }
        map->player.pdx = cos(map->player.pa) * 5;
        map->player.pdy = sin(map->player.pa) * 5;
    }
    else if (keydata.key == MLX_KEY_ESCAPE)
    {
        mlx_close_window(map->mlx);
        exit(0);
    }
}

void initial_data(t_map *map)
{
    map->player.pa = 0; // pa is the angle of the player
    map->player.pdx = cos(map->player.pa) * 5;
    map->player.pdy = sin(map->player.pa) * 5;
    map->player.turnDirection = 0;
    map->player.walkDirection = 0;
    map->player.rotationAngle = 0;
    map->player.walkSpeed = 5;
    map->player.turnSpeed = 5;
    map->player.direction = 0;
    map->player.d = 0;
}
void map_draw(t_map map)
{
    // printf("map.width = %d\n", map.width);
    // mlx_image_t *img;
    find_player(&map);
    initial_data(&map);
    map.mlx = mlx_init(map.width - 32, map.height, "cub3D", true);
    if (!map.mlx)
    {
        puts("error");
        return ;   
    }
    map.img = mlx_new_image(map.mlx, map.width,  map.height);
    if (!map.img)
    {
        mlx_close_window(map.mlx);
        puts("error");
        return ;
    }
    if (mlx_image_to_window(map.mlx, map.img, 0, 0) == -1) //
    {
        mlx_close_window(map.mlx);
        puts("error");
        return ;
    }
    // mlx_loop_hook(map.mlx, key_press, &map);
    mlx_loop_hook(map.mlx,  inisti_window, &map);
    mlx_key_hook(map.mlx, key_press, &map);
	mlx_loop(map.mlx);
    mlx_delete_image(map.mlx, map.img);
	mlx_terminate(map.mlx);
} 