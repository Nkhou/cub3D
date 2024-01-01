/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drow_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkhoudro <nkhoudro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 15:10:35 by nkhoudro          #+#    #+#             */
/*   Updated: 2024/01/01 19:01:36 by nkhoudro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"


void trace_carre(t_map map, int x, int y, int color)
{
    for (int i = 0; i < 31; ++i)
	{
		for (int j = 0; j <31; ++j)
		{
            // if ((x + i) > 0 && (x + i) < map.height && (y + j) > 0 && (y + j) < map.width)
            //     return ;
			    mlx_put_pixel(map.img, x + i , y + j  , color);
		}
	}
}
void trace_cercle(t_map map, int x, int y, int color)
{
    int r;

    r = 8;
    // k == ((int)map->player.x - map->start) && j == (int)map->player.y
    for (int i = 0; i < 31; ++i)
	{
		for (int j = 0; j <31; ++j)
		{
            if (sqrt(pow((x + i) - (x + r), 2) + pow((y + j) - (y + r), 2)) <= r)
            {
                // if ((x + i) + 8 > 0 && (x + i)  + 8< map.height && (y + j) + 8 > 0 && (y + j) + 8< map.width)
                //     return ;
                mlx_put_pixel(map.img, x + i + 8, y + j + 8, color);
            }
        }
        // i++;
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
            while (x1 > x2)
            {
                y1 = (m * x1) + c;
                mlx_put_pixel(map.img,  x1 + 16 * 2 + 8, y1 + 16 /2 + 8, color);
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
               mlx_put_pixel(map.img, x1 + 8, y1 + 8, color);
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
           mlx_put_pixel(map.img, x1 + 8, y1 + 8, color);
            i++;
            y1--;
        }
    }
    else if (map.player.direction == 270)
    {
        y2 = y2 + 16 * 2;
        y1 = y1 + 16;
        x1 = x1 + 16 / 2;
        while (y1 < y2 )
        {
           mlx_put_pixel(map.img,  x1 + 8, y1 + 8, color);
            i++;
            y1++;
        }
    }
}
void key_press(void *mlx)
{
    int i;
    t_map *map;
    int j;
    map = mlx;
    j = map->player.x / 32;
    i = map->player.y / 32 + map->start;

    mlx_delete_image(map->mlx, map->img);

    // printf("map->map[i][j] = '%c'%d,%d\n", map->map[i][j],i,j);
    // exit(0);
    if (mlx_is_key_down(map->mlx, MLX_KEY_UP)|| mlx_is_key_down(map->mlx, MLX_KEY_W)) // w 
    {
        if (map->map[i - 1][j] == '1')
            return ;
        // exit(0);
        map->map[i][j] = '0';
        map->map[i - 1][j] = 'N';
        map->player.direction = 90;
        map->player.x -= 1;
        map->player.walkDirection = 1;
        map->player.turnDirection = -1;
    }
    else if (mlx_is_key_down(map->mlx, MLX_KEY_DOWN) || mlx_is_key_down(map->mlx, MLX_KEY_S)) // s
    {
        printf("key S\n");
        if (map->map[i + 1][j] == '1')
            return ;
        map->map[i][j] = '0';
        map->map[i + 1][j] = 'S';
        map->player.direction = 270;
        map->player.walkDirection = -1;
        map->player.turnDirection = 1;
        map->player.x += 1;
    }
    else if (mlx_is_key_down(map->mlx, MLX_KEY_LEFT)|| mlx_is_key_down(map->mlx, MLX_KEY_A)) // a
    {
        printf("key A\n");
        
        if (map->map[i][j - 1] == '1')
            return ;
        map->map[i][j] = '0';
        map->map[i][j - 1] = 'W';
        map->player.direction = 180;
        map->player.walkDirection = 0;
        map->player.y -= 1;
        map->player.turnDirection = -1;
    }
    else if (mlx_is_key_down(map->mlx, MLX_KEY_RIGHT)|| mlx_is_key_down(map->mlx, MLX_KEY_D)) // d
    {
        printf("key d\n");
        if (map->map[i][j + 1] == '1')
            return ;
        map->map[i][j] = '0';
        map->map[i][j + 1] = 'E';
        map->player.direction = 0;
        map->player.walkDirection = 0;
        map->player.y += 1;
        map->player.turnDirection = 1;
    }
    else if (mlx_is_key_down(map->mlx, MLX_KEY_ESCAPE))
    {
        mlx_close_window(map->mlx);
        return  ;
    }
    else
    {
        map->player.walkDirection = 0;
        map->player.turnDirection = 0;
    }
    map->img = mlx_new_image(map->mlx, map->width,  map->height);
    if (!map->img)
        return ;
    if (mlx_image_to_window(map->mlx, map->img, 0, 0) == -1) //
    {
        mlx_close_window(map->mlx);
        puts("error");
        return ;
    }
    inisti_window(map);
    return ;
}
int key_release(int keycode, t_map *map)
{
    if (keycode == 13) // w
        map->player.walkDirection = 0;
    else if (keycode == 1) // s
        map->player.walkDirection = 0;
    else if (keycode == 0) // a
        map->player.turnDirection = 0;
    else if (keycode == 2) // d
        map->player.turnDirection = 0;
    return(0);
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
            printf("map->player.x = %d\n", ((int)map->player.x) - map->start);
            printf("map->player.y = %d\n", (int)map->player.y);
            printf("i = %d\n", i);
            printf("j = %d\n", j);
            if(map->map[i][j] == '1')
            {
                trace_carre(*map, j *32 , k *32, 0xFFFFFF);
            }
            else if (map->map[i][j] == '0') 
            {
                trace_carre(*map, j * 32, k * 32, 0x00000F);
            }
            else if (k == ((int)map->player.x - map->start) && j == (int)map->player.y)
            {
                printf("player\n");
                // map->player.x = j * 32;
                // map->player.y = k * 32;
                trace_cercle(*map, j * 32, k * 32, 0xF00080);
                // exit(0);
            }
            j++;
        }
        k++;
        i++;
    }
    int x;
    int y;
    x = map->player.x;
    y = map->player.y;
    if (map->player.direction == 0) // 0 is east
    {
        x -= cos(map->player.direction) * map->player.walkSpeed;
        y -= sin(map->player.direction) * map->player.walkSpeed;
    }
    else if (map->player.direction == 180) // 180 is west
    {
        printf("W\n");
        x += cos(map->player.direction) * map->player.walkSpeed;
        y += sin(map->player.direction) * map->player.walkSpeed;
    }
    else if (map->player.direction == 90) // 90 is north
    {
        printf("N\n");
        x -= cos(map->player.direction) * map->player.walkSpeed;
        y -= sin(90) * map->player.walkSpeed;
    }
    else if (map->player.direction == 270) // 270 is south
    {
        printf("S\n");
        x += cos(map->player.direction) * map->player.walkSpeed;
        y += sin(map->player.direction) * map->player.walkSpeed;
    }
    // trace_line(*map, x, y, 0xF00080);
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
    int x = map->player.x;
    int y = map->player.y;
    if (map->map[x][y] == 'S')
    {
        // printf("S\n");
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
    map->player.turnDirection = 0; // -1 for left, +1 for right
    map->player.walkDirection = 0; // -1 for back, +1 for front
    map->player.walkSpeed = 2.5; // 100 pixel per second
    map->player.turnSpeed = 2.5 * (M_PI / 180); // 100 pixel per second
}

void map_draw(t_map map)
{
    mlx_image_t *img;
    ini_data(&map);
    map.mlx = mlx_init(map.width - 32, map.height, "cub3D", true);
    if (!map.mlx)
        return ;
    // printf("map.width = %d\n", map.width);
    // printf("map.height = %d\n", map.height);
    // exit(0);
    img = mlx_new_image(map.mlx, map.width,  map.height);
    if (!img)
        return ;
    map.img = img;
    if (mlx_image_to_window(map.mlx, map.img, 0, 0) == -1) //
    {
        mlx_close_window(map.mlx);
        puts("error");
        return ;
    }
    mlx_loop_hook(map.mlx,  inisti_window, &map);
    mlx_loop_hook(map.mlx, &key_press, &map);
	mlx_loop(map.mlx);
	mlx_terminate(map.mlx);
} 