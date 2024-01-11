/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_draw.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkhoudro <nkhoudro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 13:25:55 by nkhoudro          #+#    #+#             */
/*   Updated: 2024/01/11 18:34:21 by nkhoudro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void drow_rays(t_map *map);
void drow_line(t_map *map, double rx, double ry , int color);
void trace_cercle(t_map map, int x, int y, int cor)
{
    int r;

    r = 0;
    for (int i = 0; i < 31; ++i)
	{
		for (int j = 0; j <31; ++j)
		{
            if (x + i < map.width  && y + j < map.height && x + i > 0 && y + j > 0)
            {
                if (sqrt(pow((x + i) - (x + r), 2) + pow((y + j) - (y + r), 2)) <= r)
                {
                    mlx_put_pixel(map.img, x + i , y + j, cor);
                }
            }
        }
    }
    drow_line(&map, x + cos(map.player.rotationAngle ) * 40, y + sin(map.player.rotationAngle ) * 40 , 0xF00080);
}
void drow_line(t_map *map, double rx, double ry , int color)
{
    int dx;
    int dy;
    int i;

    dx = map->player.x - rx;
    dy = map->player.y - ry;
    int steps;
    if (abs(dx) > abs(dy))
        steps = abs(dx);
    else
        steps = abs(dy);
    double xinc = dx / (double)steps;
    double yinc = dy / (double)steps;
    double x = map->player.x;
    double y = map->player.y;
    i =  0;
    while (i <= steps)
    {
        if (x > 0 && x < map->width && y > 0 && y < map->height)
            mlx_put_pixel(map->img, x, y , color);
        else
            break;
        x += xinc;
        y += yinc;
        i++;
    }
}
int fix_angle(int angle)
{
    if (angle > 360)
        angle = angle % 360;
    if (angle < 0)
        angle = ((int)angle + 360 ) % 360;
    return (angle);
}

void drow_rays(t_map *map)
{
    int r;
    int mx;
    int my;
    int mp;
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
        atan =  -1 / tan(ra);
        if (ra > M_PI) // looking up
        {
            ry = (((int)map->player.y >> 6) << 6) - 0.0001;
            rx = (map->player.y - ry) * atan + map->player.x;
            yo = -map->size;
            xo = -yo * atan;
        }
        else if (ra < M_PI) // looking down
        {
            ry = (((int)(map->player.y) >> 6) << 6) + map->size;
            rx = ((map->player.y) - ry) * atan + map->player.x;
            yo = map->size;
            xo = -yo * atan;
        }
        else // looking straight left or right
        {
            rx = map->player.x;
            ry = map->player.y ;
            dof = 8;
        }
        while (dof < 8)
        {
            mx = (int)(rx) >> 6;
            my = (int)(ry) >> 6;
            mp =   my* (map->width) + mx; // map position in map array
            if (mp  + map->start > 0 && mp  + map->start < (map->width /map->size) * (map->height /map->size) && (int)map->map[mp + map->start] && (int)map->map[mp + map->start] == 1)
                dof = 8;
            else
            {
                rx += xo;
                ry += yo;
                dof += 1;
            }
        }
       r++;
    }
    drow_line(map, rx, ry, 0xF00080);
    
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
                map->player.y = (i - map->start) * map->size;
                map->player.x = j * map->size;
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
    mlx_delete_image(map->mlx, map->img);
    move_player(map);
    map->img = mlx_new_image(map->mlx, map->width,  map->height);
    if (!map->img)
    {
        mlx_close_window(map->mlx);
        puts("error");
        return ;
    }
    if (mlx_image_to_window(map->mlx, map->img, 0, 0) == -1) //
    {
        mlx_close_window(map->mlx);
        puts("error");
        return ;
    }
    while (map->map[i])
    {
        j = 0;
        while(map->map[i][j])
        {
            if(map->map[i][j] == '1')
                trace_carre(*map, j *map->size , k *map->size, 0xFFFFFF);
            else
                trace_carre(*map, j * map->size, k * map->size, 0x00000F);
            j++;
        }
        k++;
        i++;
    }
    
    if (map->player.x > 0 && map->player.y > 0 && map->player.x < map->width && map->player.y < map->height)
        trace_cercle(*map, map->player.x, map->player.y, 0xF00080);
}
void move_player(t_map *map)
{
    double moveStep;
    double newPlayerX;
    double newPlayerY;
    map->player.rotationAngle += map->player.turnDirection * map->player.turnSpeed;
    moveStep = map->player.walkDirection * map->player.walkSpeed;
    newPlayerX = map->player.x + cos(map->player.rotationAngle) * moveStep;
    newPlayerY = map->player.y + sin(map->player.rotationAngle) * moveStep;
    if (map->map[(int)newPlayerY /map->size + map->start][(int)newPlayerX /map->size] != '1')
    {
        map->player.x = newPlayerX;
        map->player.y = newPlayerY;
    }
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
    if ((keydata.key == MLX_KEY_W) && (keydata.action == MLX_PRESS)) // w 
        map->player.walkDirection = 1;
    else if (keydata.key == MLX_KEY_S && (keydata.action == MLX_PRESS))// s
        map->player.walkDirection = -1;
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
// int ang(int angle)
// {
//     if (angle > 360)
//         angle = angle % 360;
//     if (angle < 0)
//         angle = ((int)angle + 360 ) % 360;
//     return (angle);
// }
// void key_press(mlx_key_data_t keydata, void* mlx)
// {
//     t_map *map;

//     map = mlx;
//     double x;
//     double y;
//     int i;
//     x= map->player.x;
//     y= map->player.y;
//     i = 0;
//     if ((keydata.key == MLX_KEY_UP) || (keydata.key ==  MLX_KEY_W)) // w 
//     {
//         y += map->player.pdy;
//         x += map->player.pdx;
//         if (map->map[(int)y /map->size + map->start][(int)x /map->size] == '1')
//             return ;
//         map->player.x += map->player.pdx;
//         map->player.y += map->player.pdy;
//     }
//     else if (keydata.key == MLX_KEY_DOWN || keydata.key == MLX_KEY_S) // s
//     {
//         y -= map->player.pdy;
//         x -= map->player.pdx;
//         if (map->map[(int)y /map->size + map->start][(int)x /map->size] == '1')
//             return ;
//         map->player.x -= map->player.pdx;
//         map->player.y -= map->player.pdy;
//     }
//     else if (keydata.key == MLX_KEY_LEFT || keydata.key == MLX_KEY_A) // a
//     {
//         map->player.pa -= 0.1;
//         if (map->player.pa < 0)
//         {
//             map->player.pa += 2 * M_PI;
//         }
//         map->player.pdx = cos(map->player.pa) * 5;
//         map->player.pdy = sin(map->player.pa)  * 5;
//     }
//     else if (keydata.key == MLX_KEY_RIGHT || keydata.key == MLX_KEY_D) // d
//     {
//         map->player.pa += 0.1;
//         if (map->player.pa < 2* M_PI)
//         {
//             map->player.pa -= 2 * M_PI;
//         }
//         map->player.pdx = cos(map->player.pa) * 5;
//         map->player.pdy = sin(map->player.pa) * 5;
//     }
//     else if (keydata.key == MLX_KEY_ESCAPE)
//     {
//         mlx_close_window(map->mlx);
//         exit(0);
//     }
// }

void initial_data(t_map *map)
{
    if (!map)
        return ;
    if (map->map[(int)map->player.y /map->size + map->start][(int)map->player.x /map->size] == 'N')
        map->player.rotationAngle = 1.5 * M_PI;
    else if (map->map[(int)map->player.y /map->size + map->start][(int)map->player.x /map->size] == 'S')
        map->player.rotationAngle = 0.5 * M_PI;
    else if (map->map[(int)map->player.y /map->size + map->start][(int)map->player.x /map->size] == 'W')
        map->player.rotationAngle = M_PI;
    else if (map->map[(int)map->player.y /map->size + map->start][(int)map->player.x /map->size] == 'E')
        map->player.rotationAngle = 0;
    map->player.turnDirection = 0;
    map->player.walkDirection = 0;
    map->player.walkleftright = 0;
    map->player.walkSpeed = 3;
    map->player.turnSpeed = 3 * (PI / 180);
    map->player.direction = 0;
    map->player.d = 0;
    map->player.height = 8;
    map->player.width = 8;
}

void map_draw(t_map map)
{
    find_player(&map);
    initial_data(&map);
    map.mlx = mlx_init(map.width - map.size, map.height, "cub3D", true);
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
    mlx_loop_hook(map.mlx,  inisti_window, &map);
    mlx_key_hook(map.mlx, key_press, &map);
	mlx_loop(map.mlx);
    mlx_delete_image(map.mlx, map.img);
	mlx_terminate(map.mlx);
} 