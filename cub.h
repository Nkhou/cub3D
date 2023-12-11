/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkhoudro <nkhoudro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 13:23:54 by saboulal          #+#    #+#             */
/*   Updated: 2023/12/11 21:07:13 by nkhoudro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB_H
#define CUB_H

#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<fcntl.h>
# include <mlx.h>
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif
typedef struct s_map
{
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
    void *mlx;
    void *win;
}t_map;
typedef struct s_map2
{
    
}t_map2;
char	*ft_strjoin(char *left_str, char *buff);
int	    ft_strlen(char *str);
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
int     check_texture_map(t_map map);
int	    ft_strcmp(char *s1, char *s2);
int	    ft_atoi(const char *str);
int     check_RGB(t_map map);
#endif