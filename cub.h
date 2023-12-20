/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saboulal <saboulal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 13:23:54 by saboulal          #+#    #+#             */
/*   Updated: 2023/12/20 13:45:17 by saboulal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB_H
#define CUB_H

#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<fcntl.h>
#include<math.h>
# include <mlx.h>
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif
typedef struct s_player
{
    double x;
    double y;
    int    turnDirection;
    int    walkDirection;
    double rotationAngle;
    double walkSpeed;
    double turnSpeed;
}t_player;
typedef struct s_map
{
    t_player player;
    char **map;
    char *North;
    char *South;
    char *West;
    char *East;
    char *Floor;
    char *Ceiling;
    int  *rgb;
    int width;
    int height;
    int size;
    void *mlx;
    void *win;
    int  i;
    int  j;
    int  k;
    int len;
    int start;
    int row; 
    int col;
}t_map;

void map_draw(t_map map);
char	*ft_strjoin(char *left_str, char *buff);
int	    ft_strlen(char *str);
void	*tabfree(char **tab);
int	    ft_strchr(char *str);
char	*ft_strdup(char *str);
char	*ft_read(int fd, char *str);
char	*ft_get_line(char **str);
char	*ft_next_right(char *str);
char	*get_next_line(int fd);
char	**ft_split(char *s, char c);
size_t	ft_strlcpy(char *dest, char *src, size_t size);
char	*ft_strdup_1( char	*str);
char	*ft_substr(char *s, unsigned int start, size_t len);
int	    ft_strncmp(const char *f, const char *s, int len);
int     check_exet(char *str,char *exe);
char    *check_before_map(char *path);
int     check_nub_line(char *path); 
int	    ft_isalpha(int c);
void    check_texture_map(t_map *map,int *i,int *k);
int	    ft_strcmp(char *s1, char *s2);
int	    ft_atoi(const char *str);
void     check_RGB(int *rgb);
char    *ft_open_texture(char *tex);
void    ft_is_identifier(char *str);
void    inisti_window(t_map map);
 char	*ft_strchr_1(const char *s, int c);
 void   init_map(t_map *map);
void    ft_rgb_color(t_map *map,char **p);
void    ft_extention(char **argv);
int     check_maps(t_map *map);
int     len_map(char **map);
void    check_walls(t_map map);
void    check_position_players(t_map map);
#endif