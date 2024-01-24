/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_game_draw.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saboulal <saboulal@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 13:25:55 by nkhoudro          #+#    #+#             */
/*   Updated: 2024/01/24 15:13:40 by saboulal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub.h"

void drow_rays(t_map *map);
void drow_line(t_map *map, double rx, double ry , int color);
void render_rays(t_map *map)
{
    int i;
    double x;
    double y;

    i = 0;
    while (i < NB_RAYS )
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
            if (x + i < WIDTH  && y + j < HEIGHT && x + i > 0 && y + j > 0)
            {
                if (sqrt(pow((x + i) - (x + r), 2) + pow((y + j) - (y + r), 2)) <= r)
                {
                    mlx_put_pixel(map.img, x + i , y + j, cor);
                }
            }
        }
    }
    // drow_line(&map, x + cos(map.player.rotationAngle ) * 40, y + sin(map.player.rotationAngle ) * 40 , 0xF00880);
}

void drow_line(t_map *map, double rx, double ry , int color)
{
    int dx;
    int dy;
    int i;

    dx = rx / 8 - map->player.x / 8;
    dy = ry / 8 - map->player.y / 8;
    int steps;
    if (abs(dx) > abs(dy))
        steps = abs(dx);
    else
        steps = abs(dy);
    double xinc = dx / (double)steps;
    double yinc = dy / (double)steps;
    double x = map->player.x / 8;
    double y = map->player.y / 8;
    i =  0;
    while (i < steps )
    {
        if (x > 0 && x < WIDTH && y > 0 && y < HEIGHT)
            mlx_put_pixel(map->img, x , y, color);
        else
            break;
        x += xinc;
        y += yinc;
        i++;
    }
}

void trace_carre(t_map map, int x, int y, int cor)
{
    for (int i = 0; i < TILE_SIZE  ; ++i)
	{
		for (int j = 0; j <TILE_SIZE ; ++j)
		{
            if ((x / 8) + i < WIDTH / 2 && (y  / 8) + j < HEIGHT && (x / 8) + i > 0 && (y  / 8) + j > 0)
			    mlx_put_pixel(map.img, x / 8 + j , (y  / 8)+ i  , cor);
		}
	}
}


void inisti_window(void *mlx)
{
    int i;
    int j;
    int k;
    t_map *map;

    map = mlx;
    i = 0;
    k = 0;
    while (map->map1[i])
    {
        j = 0;
        while(map->map1[i][j])
        {
            if(map->map1[i][j] == '1')
                trace_carre(*map, j * TILE_SIZE, k *TILE_SIZE , 0xFFFFFFFF);
            else
                trace_carre(*map, j * TILE_SIZE , k * TILE_SIZE , 0x00000F);
            j++;
        }
        k++;
        i++;
    }
    if (map->player.x > 0 && map->player.y > 0 && map->player.x < WIDTH && map->player.y < HEIGHT)
        trace_cercle(*map, map->player.x, map->player.y, 0xF00080);
}


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
                map->player.y = (i) * TILE_SIZE;
                map->player.x = j * TILE_SIZE;
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
// void render_color(t_map *map, unsigned int color)
// {
    
// }
int draw_3d_line(t_map *map, int i)
{
    if (map->player.rays[i].isv && map->player.rays[i].isr)
        return (EAST);
    else if (map->player.rays[i].isv && map->player.rays[i].isl)
        return (WEST);
    else if (!map->player.rays[i].isv && map->player.rays[i].isu)
        return (NORTH);
    else if (!map->player.rays[i].isv && map->player.rays[i].isd)
        return (SOUTH);
    return (-1);
}
// void  my_mlx_put_image_to_image(t_map *map, int walltoppixel, int wallbottompixel, int i, double height)
// {
//     int texture;
//     double tex_x;
//     double tex_y;
//     double title_x;

//     texture = draw_3d_line(map, i);
//     if (texture == -1)
//         return ;
//     if (texture == NORTH || texture == SOUTH)
//         title_x = fmod(map->player.rays[i].wallHX, TILE_SIZE);
//     else
//         title_x = fmod(map->player.rays[i].wallHY, TILE_SIZE);
//     // if (title_x < 0)
//     //     title_x = 0;
//     tex_x = title_x * (map->texture[texture]->width / TILE_SIZE);
//     tex_y = ((wallbottompixel - HEIGHT / 2) + height / 2) * (map->texture[texture]->height / height);
//     while (walltoppixel < wallbottompixel)
//     {
//     if (tex_y < 0)
//         tex_y = 0;
//     printf("pp %d\n" ,pixels_color_rgb(map->texture[texture], tex_x, tex_y));
//     mlx_put_pixel(map->img, i,walltoppixel, pixels_color_rgb(map->texture[texture], tex_x, tex_y));
//         walltoppixel++;
//     }
//     // exit(0);
// }

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

    if (text == NORTH || text == SOUTH)
        xo = (int)fmodf(map->player.rays[i].wallHX, TILE_SIZE);
    else
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
        if (map->player.rays[i].distance == 0) // to avoid the fisheye effect
            map->player.rays[i].distance = 1;
        perpDistance = map->player.rays[i].distance * cos(map->player.rays[i].rayA - map->player.rotationAngle); // correct the fisheye effect 
        distanceprojplane = (WIDTH / 2) / tan(FOV_ANGLE / 2); // distance between the player and the projection plane
        projwallheight = (TILE_SIZE / perpDistance) * distanceprojplane; // projection wall height
        wallstripheight = projwallheight; // wall strip height
        // if (wallstripheight > HEIGHT)
        //     wallstripheight = HEIGHT;
        walltoppixel = (HEIGHT / 2) - (wallstripheight / 2); // wall top pixel
        wallbottompixel = (HEIGHT / 2) + (wallstripheight / 2);
        if (walltoppixel < 0)
            walltoppixel = 0;
        if (wallbottompixel > HEIGHT)
            wallbottompixel = HEIGHT;
        // if (wallbottompixel < 0)
        //     wallbottompixel = 0;
        // printf("walltoppixel = %d\n", walltoppixel);
        draw_c_f(map, i);
        // my_mlx_put_image_to_image(map,walltoppixel, wallbottompixel, i, wallstripheight);
        pp(map, walltoppixel, wallbottompixel, i, wallstripheight);
        i++;
    }
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
    if (mlx_image_to_window(map->mlx, map->img, 0, 0) == -1) //
    {
        mlx_close_window(map->mlx);
        ft_error();
    }
    move_player(map);
    generate_3d_projection(map);
    castRays(map);
    // render_color(map);
    // clear_color(map, 0xFF000000);
    inisti_window(mlx);
}
int map_wall(float x, float y, t_map *map)
{
    double mapGridIndexX;
    double mapGridIndexY;
    // printf("x = %f\n", x / TILE_SIZE);
    // printf("y = %f\n", y /  TILE_SIZE);
    // getchar();
    if (x < 0  || x > map->width * TILE_SIZE || y < 0 || y > map->height * TILE_SIZE)
        return (1);
    mapGridIndexX = floor(x / TILE_SIZE);
    mapGridIndexY = floor(y / TILE_SIZE);
    // if ((map->map1[(int)mapGridIndexY] || map->map1[(int)mapGridIndexY][(int)x / TILE_SIZE] == '1') && (map->map1[(int)y] || map->map1[(int)y / TILE_SIZE][(int)mapGridIndexX] == '1'))
    //     return (1);
    if (!map->map1[(int)mapGridIndexY] || map->map1[(int)mapGridIndexY][(int)mapGridIndexX] == '1')
        return (1);
    return (0);
}
// int map_wall1(float x, float y, t_map *map)
// {
//     int mapGridIndexX;
//     int mapGridIndexY;
//     // printf("x = %f\n", x / TILE_SIZE);
//     // printf("y = %f\n", y /  TILE_SIZE);
//     // getchar();
//     if (x < 0  || x > map->width * TILE_SIZE || y < 0 || y > map->height * TILE_SIZE)
//         return (1);
//     mapGridIndexX = floorf(x / TILE_SIZE);
//     mapGridIndexY = floorf(y / TILE_SIZE);
//     // if ((map->map1[(int)mapGridIndexY] || map->map1[(int)mapGridIndexY][(int)x / TILE_SIZE] == '1') && (map->map1[(int)y] || map->map1[(int)y / TILE_SIZE][(int)mapGridIndexX] == '1'))
//     //     return (1);
//     if (!map->map1[(int)mapGridIndexY] || map->map1[(int)mapGridIndexY][(int)mapGridIndexX] == '1')
//         return (1);
//     return (0);
// }

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
    if (!map_wall(newPlayerX , newPlayerY, map))
    {
        
        if ((!map->map1[(int)newPlayerY / TILE_SIZE] ||map->map1[(int)newPlayerY / TILE_SIZE][(int)map->player.x / TILE_SIZE] == '1') && (!map->map1[(int)map->player.y / TILE_SIZE] || map->map1[(int)map->player.y / TILE_SIZE][(int)newPlayerX / TILE_SIZE] == '1'))
            return ;
        map->player.x = (int)newPlayerX;
        map->player.y = (int)newPlayerY;
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
    map.texture = malloc(sizeof(mlx_image_t *) * 4);
    if (!map.texture)
          ft_error();
   map.texture[NORTH] = mlx_load_png(map.North);
   map.texture[SOUTH] = mlx_load_png(map.South);    
   map.texture[WEST] =  mlx_load_png(map.West);
   map.texture[EAST] =  mlx_load_png(map.East);
   if (!map.texture[NORTH]|| !map.texture[SOUTH] || !map.texture[WEST] || !map.texture[EAST])
        ft_error();
    mlx_cursor_hook(map.mlx, mouse_press, &map); // mouse hook
   // map->adress = mlx_get_data_addr(map.img, &map.bits_per_pixel, &map.line_length, &map.endian);
    mlx_loop_hook(map.mlx,  start_draw, &map);
    mlx_key_hook(map.mlx, key_press, &map);
    // mlx_set_cursor(map.mlx, mlx_create_std_cursor(MLX_CURSOR_ARROW)); // cursor
    mlx_set_cursor_mode(map.mlx, MLX_MOUSE_HIDDEN);
    // mlx_mouse_hook(map.mlx, mouse_press, &map);
	mlx_loop(map.mlx);
    mlx_delete_image(map.mlx, map.img);
    mlx_delete_texture(map.texture[NORTH]);
	mlx_terminate(map.mlx);
} 