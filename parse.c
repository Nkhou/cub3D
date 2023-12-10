/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: salmakali <salmakali@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 17:14:15 by saboulal          #+#    #+#             */
/*   Updated: 2023/12/09 19:02:14 by salmakali        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include"cub.h"

int check_nub_line(char *path)
{
    
    int i;
    int fd;
   static char *str;
   char *line ;
   
   i = 0;
   fd = open(path,O_RDONLY);
   if(fd == -1)
   {
      write(1,"Error\n",6);
      exit(0);
   }
   line = get_next_line(fd);
   while(line)
   {
     line = get_next_line(fd);
     str = ft_strjoin(str,line);
     i++;
     free(line);
   }
   close(fd);
   return(i);
}
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

int check_texture_map(char **map)
{
    int i;
    int j;

    i = 0;
  
    while (map[i])
    {
        j = 0;
        while(map.map[i][j])
        {
          if (map.map[i][j] == 'N' && map.map[i][j + 1] == 'O')
            j++;
         if (map.map[i][j] == 'S' && map.map[i][j + 1] == 'O')
            j++;
         if (map.map[i][j] == 'W' && map.map[i][j + 1] == 'E')
            j++;
         if (map.map[i][j] == 'E' && map.map[i][j + 1] == 'A')
            j++;
         if (map.map[i][j] == 'F')
            j++;
         if (map.map[i][j] == 'C')
            j++;
        }
        i++;
   }
    return(0);
}

int check_walls(t_map map)
{
   int i;
   int j;
   
   i = 0;
   while(map.map[i])
   {
      j = 0;
      while(map.map[i][j])
      {
         if ((map.map[i][j] == ' ' || map.map[i][j] != '\t') && map.map[i][j] == '1' && map[i][j] != '\n')
            j++;
         else if(map.map[i + 1][j] != '\n' && map[i + 1][j] == '1')
            j++;
          else 
            write(1,"Error not Valid\n",16);
      }
      i++;
   }          
   return(0);                                                                                                                                                                                                                                                                                                                                 
}