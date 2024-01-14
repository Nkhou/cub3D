/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saboulal <saboulal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 17:14:15 by saboulal          #+#    #+#             */
/*   Updated: 2024/01/14 13:30:15 by saboulal         ###   ########.fr       */
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
      ft_error();
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
   char *str;
   char *line ;
   fd = open(path,O_RDONLY);
    str = NULL;
   if (fd == -1)
   {
       ft_error();
   }
  line = get_next_line(fd);
   while(line)
   {
     str = ft_strjoin(str,line);
     free(line);
     line = NULL;
     line = get_next_line(fd);
   }
    close(fd);
   return(str);
}

void check_texture_map(t_map *map,int *i,int *k)
{
     char **p;
    (void)k;
     while(*i < map->start && map->map[*i])
      {
        if(ft_strncmp(map->map[*i],"NO ",3) == 0)
        {
            map->North = ft_open_texture(map->map[*i]);
            (*k)++;
        }
        else if(ft_strncmp(map->map[*i],"SO ",3) == 0)
        {
            map->South = ft_open_texture(map->map[*i]);
            (*k)++;
        }
        else if(ft_strncmp(map->map[*i],"WE ",3) == 0)
        {
            map->West = ft_open_texture(map->map[*i]);
            (*k)++;
        }
        else if(ft_strncmp(map->map[*i],"EA ",3) == 0)
        {
            map->East = ft_open_texture(map->map[*i]);
            (*k)++;
        }
       else if(map->map[*i] && ft_strncmp(map->map[*i],"F ",2) == 0)
        {
            p = ft_split(map->map[*i] + 1,',');            
            ft_rgb_cor(map,p);
            tabfree(p);
            (*k)++;
        }
        else if(ft_strncmp(map->map[*i],"C ",2) == 0)
        {
            p = ft_split(map->map[*i] + 1,',');            
            ft_rgb_cor1(map,p);
            tabfree(p);
            (*k)++;
        }
        else
            ft_error();
        
        (*i)++;
    }
  
}
int ft_identifier(char c)
{
    if(c == 'N' || c == 'S' || c == 'W' || c == 'E' )
        return(1);
    return(0);
}

int map_games(t_map *map)
{
    int a;
    int k;
   a = 0;
    k = 0;
   map->i = map->start;

  while (map->map[map->i])
  { 
    map->j = 0;
    while (map->map[map->i][map->j])
    {
      if (!(map->map[map->i][map->j] == '1' || map->map[map->i][map->j] == ' ' || ft_identifier(map->map[map->i][map->j])  || map->map[map->i][map->j] == '0'))
        {
          ft_error();
          
        }
        map->j++;
    }

        map->i++;
   }
    return(0);                                                                                                                                                                                                                                                                                                                               
}

void check_position_players(t_map map)
{
   
   int a;

   a = 0;
   ini_map(&map);
   map.i = map.start;
   while (map.map[map.i])
   {
        map.j = 0;
        while(map.map[map.i][map.j])
       { 
              if(a > 1)
                ft_error();
              if(ft_identifier(map.map[map.i][map.j]))
              {
              
                  map.player.x = map.j;
                  map.player.y = map.i;
                  a++;
              }
            map.j++;
       }
     map.i++;
   }
    
}

void check_RGB(int *rgb)
{
    int i;

    i = 0;
    while(i < 3)
    {
        if(rgb[i] >= 0 && rgb[i]<= 255)
            i++;
        else
        {
            ft_error();
          
        }
    }
}

void ft_rgb_cor(t_map *map,char **p)
{
    map->rgb = (int *)malloc(sizeof(int) * 3);
    printf("%p\n", map->rgb);
    if(!map->rgb)
        ft_error();
    map->rgb[0] = ft_atoi(p[0]);
    map->rgb[1] = ft_atoi(p[1]);
    map->rgb[2] = ft_atoi(p[2]);
    check_RGB(map->rgb);
}
void ft_rgb_cor1(t_map *map,char **p)
{
    map->rgb1 = (int *)malloc(sizeof(int) * 3);
    printf("%p\n", map->rgb1);
    if(!map->rgb1)
        ft_error();
    map->rgb1[0] = ft_atoi(p[0]);
    map->rgb1[1] = ft_atoi(p[1]);
    map->rgb1[2] = ft_atoi(p[2]);
    check_RGB(map->rgb1);
}

