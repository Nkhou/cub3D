/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saboulal <saboulal@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 17:14:15 by saboulal          #+#    #+#             */
/*   Updated: 2024/01/24 20:45:35 by saboulal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include"../include/cub.h"


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

void check_texture_map(t_map *map)
{
   
    if(ft_north(map) != 1)
        ft_error();
    if (ft_south(map) != 1)
        ft_error();
    if(ft_west(map) != 1)
        ft_error();
    if(ft_east(map) != 1)
        ft_error();
    if(floor_(map) != 1)
        ft_error();
    if (ceilling_(map) != 1)
        ft_error();
}
int ft_identifier(char c)
{
    if(c != 'N' && c != 'S' && c != 'W' && c != 'E' )
    {

        return(1);
    }
    return(0);
}

int map_games(t_map *map)
{
    int a;
  
   a = 0;
    // k = 0;
   map->i = 0;

  while (map->map1[map->i])
  { 
    map->j = 0;
    while (map->map1[map->i][map->j])
    {
      if (!(map->map1[map->i][map->j] == '1' || map->map1[map->i][map->j] == ' ' || ft_identifier(map->map1[map->i][map->j])  || map->map1[map->i][map->j] == '0'))
        {
            printf("avvc\n");
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
   
//    int a;

//    a = 0;
//    ini_map(&map);
//   int i = 0;
//    while (map.map1[i])
//    {   
//         printf("%s\n",map.map1[i]);
//         map.j = 0;
//         while(map.map1[i][map.j])
//        { 
//               if(a > 1)
//                 ft_error();
//               if(ft_identifier(map.map1[i][map.j]))
//               {
              
//                   map.player.x = map.j;
//                   map.player.y = i;
//                   a++;
//               }
//             map.j++;
//        }
//      i++;
//    }
//    exit(0);
int i;
int j;
 i = 0;
 j = 0;
  printf("%d\n",ft_identifier(map.map1[i][j]));
 while(map.map1[i])
 {
    j = 0;
    while(map.map1[i][j])
    {
        if(ft_identifier(map.map1[i][j]) != 0)
           ft_error();
        j++;
    }
    i++;
 }
    
}

void check_RGB_ceil(t_map *map)
{
    int i;

    i = 0;
    while(i < 3)
    {
        if((map->ceil->r >= 0 && map->ceil->r<= 255) && (map->ceil->g >= 0 && map->ceil->g<= 255) &&(map->ceil->b >= 0 && map->ceil->b<= 255))
            i++;
        else
          ft_error();
    }
}

void check_RGB_floor(t_map *map)
{
    int i;

    i = 0;
    while(i < 3)
    {
        if((map->floor->r >= 0 && map->floor->r<= 255) && (map->floor->g >= 0 && map->floor->g<= 255) &&(map->floor->b >= 0 && map->floor->b<= 255))
            i++;
        else
          ft_error();
    }
}

void ft_rgb_cor(char **p,t_map *map)
{
   map->ceil = (t_rgb *)malloc(sizeof(t_rgb) * 3);
    if(!map->ceil)
        ft_error();
    map->ceil->r = ft_atoi(p[0]);
    map->ceil->g = ft_atoi(p[1]);
    map->ceil->b = ft_atoi(p[2]);
    check_RGB_ceil(map);
}
void ft_rgb_cor1(char **p,t_map *map)
{
    map->floor = (t_rgb *)malloc(sizeof(t_rgb) * 3);
    if(!map->floor)
        ft_error();
    map->floor->r = ft_atoi(p[0]);
    map->floor->g = ft_atoi(p[1]);
    map->floor->b = ft_atoi(p[2]);
    check_RGB_floor(map);
}

int check_path(t_map *map)
{
    int i;
    int j;

    i = 0;
    while(map->map[i])
    {
        j = 0;
       while(map->map[i][j] && map->map[i][j] == 'N' && map->map[i][j + 1] == 'O' && map->map[i][j + 2] == ' ')
           j++;
        i++;
    } 
    return(0);
} 