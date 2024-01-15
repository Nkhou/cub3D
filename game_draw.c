/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_draw.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkhoudro <nkhoudro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 13:25:55 by nkhoudro          #+#    #+#             */
/*   Updated: 2024/01/15 11:02:43 by nkhoudro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void drow_rays(t_map *map);
void drow_line(t_map *map, double rx, double ry , int color);
void render_rays(t_map *map)
{
    int i;

    i = 0;
    while (i < map->NB_RAYS )
    {
        drow_line(map, map->player.rays[i].wallHX, map->player.rays[i].wallHY, 0x0FFFFF);
        i++;
    }
}


void trace_cercle(t_map map, int x, int y, int cor)
{
    int r;

    r = 0;
    render_rays(&map);
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
    drow_line(&map, x + cos(map.player.rotationAngle ) * 40, y + sin(map.player.rotationAngle ) * 40 , 0xF00880);
}

void drow_line(t_map *map, double rx, double ry , int color)
{
    int dx;
    int dy;
    int i;

    // dx = map->player.x - rx;
    // dy = map->player.y - ry;
    dx = rx - map->player.x;
    dy = ry - map->player.y;
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
    while (i < steps)
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
double fix_angle(double angle)
{
    angle = remainder(angle, 2 *PI);
    if (angle < 0)
        angle = (2 *PI) + angle;
    return (angle);
}

// void drow_rays(t_map *map)
// {
//     int r;
//     int mx;
//     int my;
//     int mp;
//     int dof;
//     double rx;
//     double ry;
//     double ra;
//     double xo;
//     double yo;
//     double atan;
//     ra = map->player.pa;
//     r = 0;
//     while (r < 1)
//     {
//         dof = 0;
//         atan =  -1 / tan(ra);
//         if (ra >PI) // looking up
//         {
//             ry = (((int)map->player.y >> 6) << 6) - 0.0001;
//             rx = (map->player.y - ry) * atan + map->player.x;
//             yo = -map->size;
//             xo = -yo * atan;
//         }
//         else if (ra <PI) // looking down
//         {
//             ry = (((int)(map->player.y) >> 6) << 6) + map->size;
//             rx = ((map->player.y) - ry) * atan + map->player.x;
//             yo = map->size;
//             xo = -yo * atan;
//         }
//         else // looking straight left or right
//         {
//             rx = map->player.x;
//             ry = map->player.y ;
//             dof = 8;
//         }
//         while (dof < 8)
//         {
//             mx = (int)(rx) >> 6;
//             my = (int)(ry) >> 6;
//             mp =   my* (map->width) + mx; // map position in map array
//             if (mp  + map->start > 0 && mp  + map->start < (map->width /map->size) * (map->height /map->size) && (int)map->map[mp + map->start] && (int)map->map[mp + map->start] == 1)
//                 dof = 8;
//             else
//             {
//                 rx += xo;
//                 ry += yo;
//                 dof += 1;
//             }
//         }
//        r++;
//     }
//     drow_line(map, rx, ry, 0xF00080);    
// }

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
int distance_between_points(double x1, double y1, double x2, double y2)
{
    return (sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2)));
}
int israyfacingdown(double rayangle)
{
    return (sin(rayangle) > 0);
}
int israyfacingup(double rayangle)
{
    return (!israyfacingdown(rayangle));
}
int israyfacingright(double rayangle)
{
    return (cos(rayangle) > 0);
}
int israyfacingleft(double rayangle)
{
    return (!israyfacingright(rayangle));
}
// int israyfacingdown(double rayangle)
// {
//     return (rayangle > 0 && rayangle <PI);
// }
// int israyfacingup(double rayangle)
// {
//     return (!israyfacingdown(rayangle));
// }
// int israyfacingright(double rayangle)
// {
//     return (rayangle <PI_2 && rayangle > 1.5 *PI);
// }
// int israyfacingleft(double rayangle)
// {
//     return (!israyfacingright(rayangle));
// }
t_hv horz_(t_map *map, double ra, t_direction direction)
{
    double xintercept; // x and y intercept of the wall
    double yintercept;
    double xstep;
    double ystep;
    int foundhorzwallhit;
    double horzwallhitx;
    double horzwallhity;
    double horzWllcontent;
    double nextHorzTouchX;
    double nextHorzTouchY;
    double xtocheck;
    double ytocheck;
    t_hv horz;
 //need to check if ray is up or down*****
    ra = fix_angle(ra);
    direction.up = israyfacingup(ra);
    direction.down = !direction.up;
    direction.right = israyfacingright(ra);
    direction.left = !direction.right;
    horzwallhitx = 0;
    horzwallhity = 0;
    foundhorzwallhit = 0;
    horzWllcontent = 0;
    yintercept = floor(map->player.y / map->size) * map->size;
    if (direction.down) // looking down
    {
        yintercept += map->size;
    }
    xintercept = map->player.x + (yintercept - map->player.y) / tan(ra);
    ystep = map->size;
    if (direction.up) // looking up
        ystep *= -1;
    xstep = map->size / tan(ra);
    if (direction.left && xstep > 0) // looking left
        xstep *= -1;
    if (direction.right && xstep < 0) // looking right
        xstep *= -1;
    nextHorzTouchX = xintercept;
    nextHorzTouchY = yintercept;
    while (nextHorzTouchX >= 0 && nextHorzTouchX <= map->width && nextHorzTouchY >= 0 && nextHorzTouchY <= map->height)
    {
        xtocheck = nextHorzTouchX;
        ytocheck = nextHorzTouchY + (direction.up ? -1 : 0);
        if (map_wall(xtocheck, ytocheck, map))
        {
            foundhorzwallhit = 1;
            horzwallhitx = nextHorzTouchX;
            horzwallhity = nextHorzTouchY;
            horzWllcontent = (int)map->map[(int)floor(ytocheck /map->size + map->start)][(int)floor(xtocheck /map->size)];
            break;
        }
        else
        {
            nextHorzTouchX += xstep;
            nextHorzTouchY += ystep;
        }
    }
    // printf("%d\n", map->player.y < horzwallhity ? 1 : 0);
    horz.wallhitx = horzwallhitx;
    horz.wallhity = horzwallhity;
    horz.content = horzWllcontent;
    horz.fhwh = foundhorzwallhit;
    return (horz);
}
t_hv incrver(double x, double y, t_map *map, t_direction direction, double ra)
{
    double nextvertTouchX;
    double nextvertTouchY;
    double xtocheck;
    double ytocheck;
    double xstep;
    double ystep;
    t_hv vert;
    vert.fhwv= 0;
    vert.wallhitx = 0;
    vert.wallhity = 0;
    vert.content = 0;
    xstep = map->size;
    if (direction.left) 
        xstep *= -1;
    ystep = map->size * tan(ra);
    if (direction.up && ystep > 0)
        ystep *= -1;
    if (direction.down && ystep < 0)
        ystep *= -1;
    nextvertTouchX = x;
    nextvertTouchY = y;
    while (nextvertTouchX >= 0 && nextvertTouchX <= map->width && nextvertTouchY >= 0 && nextvertTouchY <= map->height)
    {
        xtocheck = nextvertTouchX + (direction.left ? -1 : 0);
        ytocheck = nextvertTouchY;
        if (map_wall(xtocheck, ytocheck, map))
        {
            vert.fhwv = 1;
            vert.wallhitx = nextvertTouchX;
            vert.wallhity = nextvertTouchY;
            vert.content = (int)map->map[(int)((ytocheck /map->size) + map->start)][(int)(xtocheck /map->size)];
            break;
        }
        else
        {
            nextvertTouchX += xstep;
            nextvertTouchY += ystep;
        }
    }
    return (vert);
}
t_hv vert_(t_map *map, double ra, t_direction direction)
{
    double xintercept; // x and y intercept of the wall
    double yintercept;

    t_hv vert;
 //need to check if ray is up or down*****
    ra = fix_angle(ra);
    direction.up = israyfacingup(ra);
    direction.down = !direction.up;
    direction.right = israyfacingright(ra);
    direction.left = !direction.right;

    xintercept = floor(map->player.x / map->size) * map->size;
    if (direction.right) // looking right
        xintercept += map->size;
    yintercept = map->player.y + (xintercept - map->player.x) * tan(ra);
    vert = incrver(xintercept, yintercept, map, direction, ra);
    // printf("%d\n", map->player.y < vert.fhwv ? 1 : 0);
    return (vert);
}
void castr(t_map *map, double ra, int i)
{
    t_direction direction;
    t_hv horz;
    double horzhitdistance;
    double verthitdistance;
    t_hv vert;
    direction.up = israyfacingup(ra);
    ra = fix_angle(ra);
    direction.down = !direction.up;
    direction.right = israyfacingright(ra);
    direction.left = !direction.right;
    horz = horz_(map, ra, direction);
    vert = vert_(map, ra, direction);
    horzhitdistance = (horz.fhwh) ? distance_between_points(map->player.x, map->player.y, horz.wallhitx, horz.wallhity) : LONG_MAX;
    verthitdistance = (vert.fhwv) ? distance_between_points(map->player.x, map->player.y, vert.wallhitx, vert.wallhity) : LONG_MAX;
    if (verthitdistance < horzhitdistance)
    {
        map->player.rays[i].distance = verthitdistance;
        map->player.rays[i].wallHX = vert.wallhitx;
        map->player.rays[i].wallHY = vert.wallhity;
        map->player.rays[i].wallHitContent = vert.content;
        map->player.rays[i].isv = 1;
    }
    else
    {
        map->player.rays[i].distance = horzhitdistance;
        map->player.rays[i].wallHX = horz.wallhitx;
        map->player.rays[i].wallHY = horz.wallhity;
        map->player.rays[i].wallHitContent = horz.content;
        map->player.rays[i].isv = 0;
    }
    map->player.rays[i].rayA = ra;
    map->player.rays[i].isu = direction.up;
    map->player.rays[i].isd = direction.down;
    map->player.rays[i].isl = direction.left;
    map->player.rays[i].isr = direction.right;
    
}
void castRays(t_map *map)
{
    int i;
    //start first ray
    double ra;
    i = 0;
    if (!map)
        return ;
    ra = map->player.rotationAngle - (FOV_ANGLE / 2);
    while (i < map->NB_RAYS)
    {
        castr(map, ra, i);
        ra += FOV_ANGLE / map->NB_RAYS;
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
    move_player(map);
    castRays(map);
    mlx_delete_image(map->mlx, map->img);
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
    {
        trace_cercle(*map, map->player.x, map->player.y, 0xF00080);
    }
}
int map_wall(double x, double y, t_map *map)
{
   if (x < 0 || x> map->width || y < 0 || y > map->height)
        return (1);
    int mapGridIndexX;
    int mapGridIndexY;
    mapGridIndexX = floor(x / map->size);
    mapGridIndexY = floor(y / map->size);
    if ((int)map->map[mapGridIndexY + map->start][mapGridIndexX] == '1')
        return (1);
    return (0);
}

void move_player(t_map *map)
{
    double moveStep;
    double newPlayerX;
    double newPlayerY;
    map->player.rotationAngle += map->player.turnDirection * map->player.turnSpeed;
    moveStep = map->player.walkDirection * map->player.walkSpeed;
    if (map->player.walkleftright)
        moveStep = map->player.walkleftright * map->player.walkSpeed;
    newPlayerX = map->player.x + cos(map->player.rotationAngle) * moveStep;
    newPlayerY = map->player.y + sin(map->player.rotationAngle) * moveStep;
    if (map->player.walkleftright)
    {
        newPlayerX = map->player.x + cos(map->player.rotationAngle + M_PI_2) * moveStep;
        newPlayerY = map->player.y + sin(map->player.rotationAngle + M_PI_2) * moveStep;
    }
    // if (map->player.rotationAngle < 0)
    //     map->player.rotationAngle += 2 * PI;
    // if (map->player.rotationAngle > 2 * PI)
    //     map->player.rotationAngle -= 2 * PI;
    if (!map_wall(newPlayerX, newPlayerY, map))
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
    if ((keydata.key == MLX_KEY_S) && (keydata.action == MLX_PRESS)) // w 
        map->player.walkDirection = -1;
    else if (keydata.key == MLX_KEY_W && (keydata.action == MLX_PRESS))// s
        map->player.walkDirection = 1;
    else if (keydata.key == MLX_KEY_A && (keydata.action == MLX_PRESS))// A
        map->player.walkleftright = 1;
    else if (keydata.key == MLX_KEY_D && (keydata.action == MLX_PRESS))// D
        map->player.walkleftright = -1;
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

void initial_data(t_map *map)
{
    if (!map)
        return ;
    if (map->map[(int)map->player.y /map->size + map->start][(int)map->player.x /map->size] == 'N')
        map->player.rotationAngle = 1.5 * PI;
    else if (map->map[(int)map->player.y /map->size + map->start][(int)map->player.x /map->size] == 'S')
        map->player.rotationAngle = 0.5 * PI;
    else if (map->map[(int)map->player.y /map->size + map->start][(int)map->player.x /map->size] == 'E')
        map->player.rotationAngle =PI;
    else if (map->map[(int)map->player.y /map->size + map->start][(int)map->player.x /map->size] == 'W')
        map->player.rotationAngle = 0;
    map->player.turnDirection = 0;
    map->player.walkDirection = 0;
    map->player.walkleftright = 0;
    map->player.walkSpeed = 2;
    map->player.turnSpeed = 2 * (PI / 180);
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
    if (mlx_image_to_window(map.mlx, map.img, 0, 0) == -1) 
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