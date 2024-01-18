/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saboulal <saboulal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 13:23:54 by saboulal          #+#    #+#             */
/*   Updated: 2024/01/18 11:01:42 by saboulal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB_H
#define CUB_H
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <math.h>
#include <OpenGL/gl.h>
#include   <string.h>


#include "MLX42/include/MLX42/MLX42.h"
#ifndef BUFFER_SIZE
#define BUFFER_SIZE 42
// #define NB_RAYS 20
#define FOV_ANGLE (60 * (M_PI / 180))
#define PI 3.14159265
#define TWO_PI 6.28318530
#define false 0
#define true 1
#define FPS 20
#define FRAME_TIME_LENGTH (1000 /FPS)
#define MINIMAP_SCALE_FACTOR 0.3
#define NORTH 0
#define SOUTH 1
#define WEST 2
#define EAST 3
#include <limits.h>

#endif
typedef struct s_hv
{
    double wallhitx;
    double wallhity;
    double distance;
    int content;
    int fhwh;
    int fhwv;
}t_hv;
typedef struct s_step
{
    double xstep;
    double ystep;
}t_step;
typedef struct direction
{
    int up;
    int down;
    int left;
    int right;
}t_direction;

typedef struct ray
{
    double rayA;
    double wallHX; // wall hit x
    double wallHY; // wall hit y
    double distance;
    int isv; // is vertical
    int ish; // is horizontal
    int isu; // is up
    int isd; // is down
    int isl; // is left
    int isr; // is right
    int wallHitContent; // wall hit content texture
}
ray_t;
typedef struct s_player
{
    ray_t *rays;
    double x;
    double y;
    double width;
    double height;
    double pa;
    double pdx;
    double pdy;
    int d;
    int turnDirection;
    int walkDirection;
    int walkleftright;
    double rotationAngle;
    double walkSpeed;
    double turnSpeed;
    int direction;
    // unsigned long long start_time;
    double delta;
} t_player;

typedef struct s_map3D
{
    uint32_t *color;
    // mlx_texture_t *color_texture;;
} t_map3D;

typedef struct s_map
{
    t_map3D map3D;
    t_player player;
    char *adress;
    char **map;
    char *str;
    char *North;
    char *South;
    char *West;
    char *East;
    char *Floor;
    char *Ceiling;
    int *rgb;
    int *rgb1;
    int width;
    int height;
    int size;
    void *mlx;
    void *win;
    mlx_image_t   *img;
    mlx_texture_t **texture;
    int i;
    int j;
    int k;
    int x;
    int y;
    int len;
    int start;
    int r; // row
    int c; // column
    int NB_RAYS;
} t_map;

typedef struct s_texture
{
    t_map *map;
    
}t_tex;

typedef struct s_parse
{
    int lenght_1;
    int lenght_2;
}t_parse;

 typedef struct s_ray
 {
    int up;
    int down;
    int left;
    int right;
    double rayAngle;
    double wallHitX;
    double wallHitY;
    double distance;
    int wasHitVertical;
    int isRayFacingUp;
    int isRayFacingDown;
    int isRayFacingLeft;
    int isRayFacingRight;
    int wallHitContent;
    int foundWallHit;
 }t_ray;
 
void map_draw(t_map map);
char *ft_strjoin(char *left_str, char *buff);
int ft_strlen(char *str);
void	ft_free(char **p);
int ft_strchr(char *str);
char *ft_strdup(char *str);
char *ft_read(int fd, char *str);
char *ft_get_line(char **str);
char *ft_next_right(char *str);
char *get_next_line(int fd);
char	**ft_split(char const *s, char c);
size_t ft_strlcpy(char *dest, char *src, size_t size);
char *ft_strdup_1(char *str);
char *ft_substr(char *s, unsigned int start, size_t len);
int ft_strncmp(const char *f, const char *s, int len);
int check_exet(char *str, char *exe);
char *check_before_map(char *path);
int check_nub_line(char *path);
int ft_isalpha(int c);
void check_texture_map(t_map *map);
int ft_strcmp(char *s1, char *s2);
int ft_atoi(const char *str);
void check_RGB(int *rgb);
char *ft_open_texture(char *tex);
void ft_is_identifier(char *str);
void inisti_window(void *map);
char *ft_strchr_1(const char *s, int c);
void ini_map(t_map *map);
void ft_rgb_cor(t_map *map, char **p);
void ft_extention(char **argv);
int map_games(t_map *map);
int len_map(char **map);
void space_waalls(t_map map);
int rgb_to_int(int r, int g, int b,int a);
void ft_rgb_cor1(t_map *map,char **p);
/*testing*/
void map_game_full(t_map map);
void map_checks_(t_map map, int r, int c);
void map_game(char **map);
int check_player_surroundings(char **map, int r, int c);
int space_waall(char **map, int r, int c);
int found_wall(char **map, int r);
int found_char(char c, char *set);
void check_position_players(t_map map);
void get_map(t_map *map);
int  check_space(char *str);
int ft_texture(t_map *map);
void ft_error(void);
int ft_is_space(char *str);
void free_programme(char *str,t_map map);
int     get_south(t_map *map);
void move_player(t_map *map);
int map_wall(double x, double y, t_map *map);
int retir_space(t_map *map,int fd);
int check_readd(t_map *map,char *str,int fd);
//  bool mlx_is_key_down(void *map);
int check_path(t_map *map);
void ft_north(t_map *map);
void ft_south(t_map *map);
void ft_west(t_map *map);
void ft_east(t_map *map);
#endif