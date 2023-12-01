/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saboulal <saboulal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 17:14:15 by saboulal          #+#    #+#             */
/*   Updated: 2023/12/01 21:27:34 by saboulal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include"cub.h"

//check extention

int check_exet(char *str,char *exe)
{
    int len_all;
    int len_exe;
    
    len_all = ft_strlen(str);
    len_exe = ft_strlen(exe);

    while(len_all > len_exe)
    {
        str++;
        len_all--;
        
    }
    return(ft_strncmp(str,exe,len_all));
}

char *check_before_map(char *path)
{
    int fd;
   static char *str;
   char *line ;
   
   fd = open(path,O_RDONLY);
   line = get_next_line(fd);
   while(line)
   {
     line = get_next_line(fd);
     str = ft_strjoin(str,line);
     free(line);
   }
   close(fd);
   return(str);
}

int map_texture(t_map map)
{
    int i;
    int j;

    while (map.map[i])
    {
       while(map.map[i][j])
       {
          if(map.map[i][j] == 'N' && map.map[i][j + 1] == 'o')
            j++;
          if(map.map[i][j] == )
       }
       i++;
    }
    return(0);
}