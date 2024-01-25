/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_game_draw.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkhoudro <nkhoudro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 13:25:55 by nkhoudro          #+#    #+#             */
/*   Updated: 2024/01/25 19:03:49 by nkhoudro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub.h"

double fix_angle(double angle)
{
    angle = remainder(angle, 2 *PI);
    if (angle < 0)
        angle = (2 *PI) + angle;
    return (angle);
}


void find_player(t_map *map)
{
    int i;
    int j;
    

    i = 0;
    if (!map)
        return ;
    while (map->map1[i])
    {
        j = 0;
        while(map->map1[i][j])
        {
            if(map->map1[i][j] && ( map->map1[i][j] == 'N' || map->map1[i][j] == 'S' || map->map1[i][j] == 'W' || map->map1[i][j] == 'E'))
            {
                map->player.y = i * TILE_SIZE + TILE_SIZE / 2;
                map->player.x = j * TILE_SIZE + TILE_SIZE / 2;
                map->dr = map->map1[i][j];
                map->map1[i][j] = '0';
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

void clear_color(t_map *map, uint32_t color)
{
    int x;
    int y;
    x = 0;
    while (x < WIDTH)
    {
        y = 0;
        while (y < HEIGHT)
        {
            map->map3D.color[y * WIDTH + x] = color;
            y++;
        }
        x++;
    }
}

int draw_3d_line(t_map *map, int i)
{
    if (map->player.rays[i].content == 'D')
        return (DOOR);
    else if (map->player.rays[i].isv && map->player.rays[i].isr)
        return (EAST);
    else if (map->player.rays[i].isv && map->player.rays[i].isl)
        return (WEST);
    else if (!map->player.rays[i].isv && map->player.rays[i].isu)
        return (NORTH);
    else if (!map->player.rays[i].isv && map->player.rays[i].isd)
        return (SOUTH);
    return (-1);
}

void draw_c_f(t_map *map, int i)
{
    int j = 0;
    while (j < HEIGHT / 2)
    {
        mlx_put_pixel(map->img, i, j, rgb_to_int(map->ceil->r, map->ceil->g, map->ceil->b, 255));
        j++;
    }
    j = HEIGHT / 2;
    while (j < HEIGHT)
    {
        mlx_put_pixel(map->img, i, j, rgb_to_int(map->floor->r, map->floor->g, map->floor->b, 255));
        j++;
    }
}

void pp(t_map *map, int walltoppixel, int wallbottompixel, int i, double height)
{
    int text = draw_3d_line(map,i);

    if (text == -1)
        return ;
    double factor = (double)map->texture[text]->height / height;
    uint32_t	*arr = (u_int32_t *)map->texture[text]->pixels;
    double			xo = 0;

    if (text == NORTH || text == SOUTH || (text == DOOR && !map->player.rays[i].isv))
        xo = (int)fmodf(map->player.rays[i].wallHX, TILE_SIZE);
    else if ((text == DOOR && map->player.rays[i].isv))
        xo = (int)fmodf(map->player.rays[i].wallHY, TILE_SIZE);
    else if (text == EAST || text == WEST)
        xo = (int)fmodf(map->player.rays[i].wallHY, TILE_SIZE);
    double tex_x = xo * (map->texture[text]->width / TILE_SIZE);
    
    if (tex_x < 0)
        tex_x = 0;
	double			yo = (walltoppixel - (HEIGHT/2) + (height/2)) * factor;

    if (yo < 0)
        yo = 0;
    while (walltoppixel < wallbottompixel)
    {
        if (yo >= map->texture[text]->height)
            yo = map->texture[text]->height - 1;
        mlx_put_pixel(map->img, i, walltoppixel, arr[(int)yo * map->texture[text]->width + (int)tex_x]);
        yo += factor;
        walltoppixel++;
    }
    
}
void generate_3d_projection(t_map *map)
{
    int i;
    double wallstripheight;
    double distanceprojplane;
    double projwallheight;
    int walltoppixel;
    int wallbottompixel;
    double perpDistance;
    (void)map;
    i = 0;
    while (i < WIDTH)
    {
        if (map->player.rays[i].distance == 0) 
            map->player.rays[i].distance = 1;
        perpDistance = map->player.rays[i].distance * cos(map->player.rays[i].rayA - map->player.rotationAngle);
        distanceprojplane = (WIDTH / 2) / tan(FOV_ANGLE / 2);
        projwallheight = (TILE_SIZE / perpDistance) * distanceprojplane;
        wallstripheight = projwallheight;
        walltoppixel = (HEIGHT / 2) - (wallstripheight / 2);
        wallbottompixel = (HEIGHT / 2) + (wallstripheight / 2);
        if (walltoppixel < 0)
            walltoppixel = 0;
        if (wallbottompixel > HEIGHT)
            wallbottompixel = HEIGHT;
        draw_c_f(map, i);
        pp(map, walltoppixel, wallbottompixel, i, wallstripheight);
        i++;
    }
}
void draw_player(t_map *map)
{
    int px;
    int py;
    py = 140;
    while (py < 160)
    {
        px = 140;
        while (px < 160)
        {
            if (distance_between_points(px, py, 150, 150) <= 5)
                mlx_put_pixel(map->img, px, py, 0xF8E559);
            px++;
        }
        py++;
    }
}
void    minimap(t_map *map)
{
    int i = 0;
    int j = 0;
    double x;
    double y;
    
    y = map->player.y - 150;
    while (i < 300)
    {
        j = 0;
        x = map->player.x - 150;
        while (j < 300)
        {
            if ((int)(x / TILE_SIZE) < 0 || (int)(x / TILE_SIZE) > map->width || (int)(y / TILE_SIZE) < 0 || (int)(y / TILE_SIZE) > map->height)
            {
                j++;
                x++;
                continue;
            }
            if (map->map1[(int)(y / TILE_SIZE)] && map->map1[(int)(y / TILE_SIZE)][(int)(x / TILE_SIZE)] == '1')
                mlx_put_pixel(map->img, j ,i, 0xFFFFFFFF);
            else if (map->map1[(int)(y / TILE_SIZE)] && map->map1[(int)(y / TILE_SIZE)][(int)(x / TILE_SIZE)] == '0')
                mlx_put_pixel(map->img, j, i, 0x00000000);
            else if (map->map1[(int)(y / TILE_SIZE)] && map->map1[(int)(y / TILE_SIZE)][(int)(x / TILE_SIZE)] == 'D')
                mlx_put_pixel(map->img, j, i, 0xFFFFFF);
            else
                mlx_put_pixel(map->img, j, i, 0x00000000);
           j++;
           x++;
        }
        i++;
        y++;
        
    }
    draw_player(map);
}
void start_draw(void *mlx)
{
    t_map *map;
    
    map = mlx;
    mlx_delete_image(map->mlx, map->img);
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
    generate_3d_projection(map);
    castRays(map);
    move_player(map);
    minimap(map);
}
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
         if ((!map->map1[(int)newPlayerY / TILE_SIZE]
         || map->map1[(int)newPlayerY / TILE_SIZE][(int)map->player.x / TILE_SIZE] == '1')
         && (!map->map1[(int)map->player.y / TILE_SIZE]
         || map->map1[(int)map->player.y / TILE_SIZE][(int)newPlayerX / TILE_SIZE] == '1'))
            return ;
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
void open_dor(t_map *map)
{
    int x;
    int y;

    x = floor(map->player.x / TILE_SIZE);
    y = floor(map->player.y / TILE_SIZE);
    if (map->map1[y] && map->map1[y][x + 1] == 'D')
        map->map1[y][x + 1] = 'd';
    else if (map->map1[y] && map->map1[y][x - 1] == 'D')
        map->map1[y][x - 1] = 'd';
    else if (map->map1[y + 1] && map->map1[y + 1][x] == 'D')
        map->map1[y + 1][x] = 'd';
    else if (map->map1[y - 1] && map->map1[y - 1][x] == 'D')
        map->map1[y - 1][x] = 'd';
}
void close_dor(t_map *map)
{
    int x;
    int y;

    x = floor(map->player.x / TILE_SIZE);
    y = floor(map->player.y / TILE_SIZE);
    if (map->map1[y] && map->map1[y][x + 1] == 'd')
        map->map1[y][x + 1] = 'D';
    else if (map->map1[y] && map->map1[y][x - 1] == 'd')
        map->map1[y][x - 1] = 'D';
    else if (map->map1[y + 1] && map->map1[y + 1][x] == 'd')
        map->map1[y + 1][x] = 'D';
    else if (map->map1[y - 1] && map->map1[y - 1][x] == 'd')
        map->map1[y - 1][x] = 'D';
}
void key_press(mlx_key_data_t keydata, void *mlx)
{
    t_map *map;

    map = mlx;
    if ((keydata.key == MLX_KEY_S) && (keydata.action == MLX_PRESS))
        map->player.walkDirection = -1;
    else if (keydata.key == MLX_KEY_W && (keydata.action == MLX_PRESS))
        map->player.walkDirection = 1;
    else if (keydata.key == MLX_KEY_A && (keydata.action == MLX_PRESS))
        map->player.walkleftright = -1;
    else if (keydata.key == MLX_KEY_D && (keydata.action == MLX_PRESS))
        map->player.walkleftright = 1;
    else if (keydata.key == MLX_KEY_LEFT && (keydata.action == MLX_PRESS))
        map->player.turnDirection = -1;
    else if (keydata.key == MLX_KEY_RIGHT && (keydata.action == MLX_PRESS))
        map->player.turnDirection = 1;
    else if (keydata.key == MLX_KEY_O)
        open_dor(map);
    else if (keydata.key == MLX_KEY_C)
        close_dor(map);
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
    if (map->dr == 'N')
        map->player.rotationAngle = 1.5 * PI;
    else if (map->dr == 'S')
        map->player.rotationAngle = 0.5 * PI;
    else if (map->dr == 'E')
        map->player.rotationAngle =PI;
    else if (map->dr == 'W')
        map->player.rotationAngle = 0;
    map->player.turnDirection = 0;
    map->player.walkDirection = 0;
    map->player.walkleftright = 0;
    map->player.walkSpeed = 8;
    map->player.turnSpeed = 3 * (PI / 180);
    map->player.direction = 0;
    map->player.d = 0;
    map->player.height = 8;
    map->player.width = 8;
    map->prev = -1;
}
void mouse_press(double x, double y, void *mlx)
{
    t_map *map;

    map = mlx;
    if (x > 0 && x < WIDTH && y > 0 && y < HEIGHT)
    {
        if (map->prev != -1)
        {
            map->player.rotationAngle += (x - map->prev) * 0.00008;
        }
        else
            map->prev = x;
    }
    else
        map->prev = -1;
}
void map_draw(t_map map)
{
  
    mlx_image_t *img;

  
    find_player(&map);
    initial_data(&map);
    map.mlx = mlx_init(WIDTH , HEIGHT, "cub3D", true);
    if (!map.mlx)
    {
        ft_error();
        return ;   
    }
    img = mlx_new_image(map.mlx, WIDTH,  HEIGHT);
    if (!img)
    {
        mlx_close_window(map.mlx);
        ft_error();
    }
    if (mlx_image_to_window(map.mlx, img, 0, 0) == -1) 
    {
        mlx_close_window(map.mlx);
        ft_error();
    }
    map.img = img;
    map.texture = malloc(sizeof(mlx_image_t *) * 5);
    if (!map.texture)
          ft_error();
    map.texture[NORTH] = mlx_load_png(map.North);
   map.texture[SOUTH] = mlx_load_png(map.South);    
   map.texture[WEST] =  mlx_load_png(map.West);
   map.texture[EAST] =  mlx_load_png(map.East);
   map.texture[DOOR] =  mlx_load_png("./Textures/Door.png");
   if (!map.texture[NORTH]|| !map.texture[SOUTH] || !map.texture[WEST] || !map.texture[EAST] || !map.texture[DOOR])
        ft_error();
    mlx_cursor_hook(map.mlx, mouse_press, &map);
    mlx_loop_hook(map.mlx,  start_draw, &map);
    mlx_key_hook(map.mlx, key_press, &map);
    mlx_set_cursor_mode(map.mlx, MLX_MOUSE_HIDDEN);
	mlx_loop(map.mlx);
    mlx_delete_image(map.mlx, map.img);
    mlx_delete_texture(map.texture[NORTH]);
	mlx_terminate(map.mlx);
} 
