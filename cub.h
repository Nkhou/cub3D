/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saboulal <saboulal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 13:23:54 by saboulal          #+#    #+#             */
/*   Updated: 2023/12/01 18:01:07 by saboulal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB_H
#define CUB_H

#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
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
    
    
}t_map;
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
int check_exet(char *str,char *exe);
#endif