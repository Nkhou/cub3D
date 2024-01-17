/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_draw.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkhoudro <nkhoudro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 13:25:55 by nkhoudro          #+#    #+#             */
/*   Updated: 2024/01/17 15:05:58 by nkhoudro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void drow_rays(t_map *map);
void drow_line(t_map *map, double rx, double ry , int color);
void render_rays(t_map *map)
{
    int i;
    double x;
    double y;

    i = 0;
    while (i < map->NB_RAYS )
    {
        x = map->player.rays[i].wallHX;
        y = map->player.rays[i].wallHY;
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

    dx = rx / 4 - map->player.x / 4;
    dy = ry / 4 - map->player.y / 4;
    int steps;
    if (abs(dx) > abs(dy))
        steps = abs(dx);
    else
        steps = abs(dy);
    double xinc = dx / (double)steps;
    double yinc = dy / (double)steps;
    double x = map->player.x  / 4;
    double y = map->player.y / 4;
    i =  0;
    while (i < steps )
    {
        if (x > 0 && x < map->width && y > 0 && y < map->height)
            mlx_put_pixel(map->img, x , y, color);
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

void trace_carre(t_map map, int x, int y, int cor)
{
    for (int i = 0; i < map.size  ; ++i)
	{
		for (int j = 0; j <map.size ; ++j)
		{
            if ((x / 4) + i < map.width  && (y  / 4) + j < map.height && (x / 4) + i > 0 && (y  / 4) + j > 0)
			    mlx_put_pixel(map.img, x / 4 + j , (y  / 4)+ i  , cor);
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
// t_hv findwallv(double nextvertTouchX, double nextvertTouchY, t_map *map, t_direction direction, t_step step)
// {
//     double xtocheck;
//     double ytocheck;
//     t_hv vert;

//     while (nextvertTouchX >= 0 && nextvertTouchX <= map->width && nextvertTouchY >= 0 && nextvertTouchY <= map->height)
//     {
//         xtocheck = nextvertTouchX + (direction.left ? -1 : 0);
//         ytocheck = nextvertTouchY;
//         if (map_wall(xtocheck, ytocheck, map))
//         {
//             vert.fhwv = 1;
//             vert.wallhitx = nextvertTouchX;
//             vert.wallhity = nextvertTouchY;
//             vert.content = (int)map->map[(int)((ytocheck /map->size) + map->start)][(int)(xtocheck /map->size)];
//             break;
//         }
//         else
//         {
//             nextvertTouchX += step.xstep;
//             nextvertTouchY += step.ystep;
//         }
//     }
//     return (vert);
// }
t_hv incrver(double x, double y, t_map *map, t_direction direction, double ra)
{
    double nextvertTouchX;
    double nextvertTouchY;
    double xtocheck;
    double ytocheck;
    t_step step;
    t_hv vert;

    vert.fhwv= 0;
    vert.wallhitx = 0;
    vert.wallhity = 0;
    vert.content = 0;
    step.xstep = map->size;
    if (direction.left) 
        step.xstep *= -1;
    step.ystep = map->size * tan(ra);
    if (direction.up && step.ystep > 0)
        step.ystep *= -1;
    if (direction.down && step.ystep < 0)
        step.ystep *= -1;
    nextvertTouchX = x;
    nextvertTouchY = y;
    // findwallv(x, y, map, direction, step);
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
            nextvertTouchX += step.xstep;
            nextvertTouchY += step.ystep;
        }
    }
    return (vert);
}
t_hv vert_(t_map *map, double ra, t_direction direction)
{
    double xintercept; // x and y intercept of the wall
    double yintercept;
    t_hv vert;

    xintercept = floor(map->player.x / map->size) * map->size;
    if (direction.right) // looking right
        xintercept += map->size;
    yintercept = map->player.y + (xintercept - map->player.x) * tan(ra);
    vert = incrver(xintercept, yintercept, map, direction, ra);
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
    while (map->map[i])
    {
        j = 0;
        while(map->map[i][j])
        {
            if(map->map[i][j] == '1')
                trace_carre(*map, j * map->size, k *map->size , 0xFFFFFF);
            else
                trace_carre(*map, j * map->size , k * map->size , 0x00000F);
            j++;
        }
        k++;
        i++;
    }
    if (map->player.x > 0 && map->player.y > 0 && map->player.x < map->width && map->player.y < map->height)
        trace_cercle(*map, map->player.x, map->player.y, 0xF00080);
}
void clear_color(t_map *map, uint32_t color)
{
    int x;
    int y;
    x = 0;
    while (x < map->width)
    {
        y = 0;
        while (y < map->height)
        {
            map->map3D.color[y * map->width + x] = color;
            y++;
        }
        x++;
    }
}
// void render_color(t_map *map, unsigned int color)
// {
    
// }
void  my_mlx_put_image_to_image(t_map *map, int walltoppixel, int wallbottompixel, int i)
{
    int j;

    j = 0;
    while (i < map->width)
    {
        while (j < walltoppixel && j < map->height)
        {
            mlx_put_pixel(map->img, i, j,0xFFFFFFFF);
            j++;
        }
        while (j < wallbottompixel && j < map->height)
        {
            if (map->player.rays[i].isv)
                mlx_put_pixel(map->img, i, j, 0x786d6d);
            else
                mlx_put_pixel(map->img, i, j, 0x625454);
            j++;
        }
        while (j < map->height)
        {
            mlx_put_pixel(map->img, i, j,0x3f2c18);
            j++;
        }
        
        i++;
    }
    // printf("walltoppixel = %d\n", walltoppixel);
}
void generate_3d_projection(t_map *map)
{
    int i;
    int wallstripheight;
    double distanceprojplane;
    double projwallheight;
    int walltoppixel;
    int wallbottompixel;
    double perpDistance;

    i = 0;
    while (i < map->width)
    {
        if (map->player.rays[i].distance == 0)
            map->player.rays[i].distance = 1;
        perpDistance = map->player.rays[i].distance * cos(map->player.rays[i].rayA - map->player.rotationAngle);
        distanceprojplane = (map->width / 2) / tan(FOV_ANGLE / 2);
        projwallheight = (map->size / perpDistance) * distanceprojplane;
        wallstripheight = (int)projwallheight;
        walltoppixel = (map->height / 2) - (wallstripheight / 2);
        if (walltoppixel < 0)
            walltoppixel = 0;
        wallbottompixel = (map->height / 2) + (wallstripheight / 2);
        if (wallbottompixel > map->height)
            wallbottompixel = map->height;
        if (wallbottompixel < 0)
            wallbottompixel = 0;
        my_mlx_put_image_to_image(map,walltoppixel, wallbottompixel, i);
        i++;
    }
}
void start_draw(void *mlx)
{
    t_map *map;
    
    map = mlx;

    mlx_delete_image(map->mlx, map->img);
    map->img = mlx_new_image(map->mlx, map->width,  map->height);
    if (!map->img)
    {
        mlx_close_window(map->mlx);
        ft_error();
    }
    if (mlx_image_to_window(map->mlx, map->img, 0, 0) == -1) //
    {
        mlx_close_window(map->mlx);
        ft_error();
    }
    generate_3d_projection(map);
    castRays(map);
    move_player(map);
    // render_color(map);
    // clear_color(map, 0xFF000000);
    // inisti_window(mlx);
}
int map_wall(double x, double y, t_map *map)
{
   if (x < 0 || x> map->width || y < 0 || y > map->height)
        return (1);
    int mapGridIndexX;
    int mapGridIndexY;
    mapGridIndexX = floor(x / map->size);
    mapGridIndexY = floor(y / map->size);
    if (map->map[mapGridIndexY + map->start][mapGridIndexX] && (int)map->map[mapGridIndexY + map->start][mapGridIndexX] == '1')
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
        ft_error();
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
    map->map3D.color = ( uint32_t *) malloc(sizeof(uint32_t ) * (uint32_t)map->width * (uint32_t)map->height);
    if (!map->map3D.color)
        ft_error();
    // map->color_texture = malloc(sizeof(mlx_texture_t));
    // map->img 
}

void map_draw(t_map map)
{
    find_player(&map);
    initial_data(&map);
    map.mlx = mlx_init(map.width , map.height, "cub3D", true);
    if (!map.mlx)
    {
        ft_error();
        return ;   
    }
    map.img = mlx_new_image(map.mlx, map.width,  map.height);
    if (!map.img)
    {
        mlx_close_window(map.mlx);
        ft_error();
    }
    if (mlx_image_to_window(map.mlx, map.img, 0, 0) == -1) 
    {
        mlx_close_window(map.mlx);
        ft_error();
    }
    map.texture = malloc(sizeof(mlx_texture_t) * 4);
    if (!map.texture)
        ft_error();
    // map.texture[NORTH] = mlx_load_png(map.North);
    // map.texture[SOUTH] = mlx_load_png(map.South);    
    // map.texture[WEST] =  mlx_load_png(map.West);
    // map.texture[EAST] =  mlx_load_png(map.East);
    // if(map.texture[NORTH]  || map.texture[SOUTH]  || map.texture[WEST]  || map.texture[EAST] )
    //     ft_error();
    // map.adress = mlx_get_data_addr(map.img, &map.bits_per_pixel, &map.line_length, &map.endian);
    mlx_loop_hook(map.mlx,  start_draw, &map);
    mlx_key_hook(map.mlx, key_press, &map);
	mlx_loop(map.mlx);
    mlx_delete_image(map.mlx, map.img);
	mlx_terminate(map.mlx);
} 