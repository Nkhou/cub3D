/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_position.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saboulal <saboulal@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 19:34:51 by saboulal          #+#    #+#             */
/*   Updated: 2024/01/24 20:45:43 by saboulal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub.h"

int  ft_north(t_map *map)
{
    char **tab;
     int i = 0;
    int k = 0;
     while( map->map[i] && i < map->start )
      {
      
        k = 0;
        if(ft_strncmp(map->map[i],"NO ",3) == 0 )
        {
          while (map->map[i][k] && map->map[i][k + 1] && map->map[i][k] != '.' && map->map[i][k + 1] != '/')
                (k)++;
            if (map->map[i][k] && map->map[i][k + 1])
            {
                map->North = ft_strdup(map->map[i] + k);
                tab = ft_split(map->North,' ');
                free(map->North);
                map->North = ft_strdup(tab[0]);
                ft_free(tab);
                return(1);
            }
            
        }
        i++;
    }
    return(0);
}

int  ft_south(t_map *map)
{
    char **tab;
     int i = 0;
    int k = 0;
     while( map->map[i] && i < map->start )
      {
      
        k = 0;
        if(ft_strncmp(map->map[i],"SO ",3) == 0 )
        {
          while (map->map[i][k] && map->map[i][k + 1] && map->map[i][k] != '.' && map->map[i][k + 1] != '/')
                (k)++;
            if (map->map[i][k] && map->map[i][k + 1])
            {
                map->South = ft_strdup(map->map[i] + k);
                tab = ft_split(map->South,' ');
                free(map->South);
                map->South = ft_strdup(tab[0]);
                ft_free(tab);
                return(1);
            }
        }
        i++;
    }
    return(0);
}


int ft_west(t_map *map)
{
     char **tab;
     int i = 0;
    int k = 0;
     while( map->map[i] && i < map->start )
      {
      
        k = 0;
        if(ft_strncmp(map->map[i],"WE ",3) == 0 )
        {
          while (map->map[i][k] && map->map[i][k + 1] && map->map[i][k] != '.' && map->map[i][k + 1] != '/')
                (k)++;
            if (map->map[i][k] && map->map[i][k + 1])
            {
                map->West = ft_strdup(map->map[i] + k);
                tab = ft_split(map->West,' ');
                free(map->West);
                map->West = ft_strdup(tab[0]);
                ft_free(tab);
                return(1);
            }
        }
        i++;
    }
    return(0);
}

int ft_east(t_map *map)
{
    char **tab;
     int i = 0;
    int k = 0;
     while( map->map[i] && i < map->start )
      {
      
        k = 0;
        if(ft_strncmp(map->map[i],"EA ",3) == 0 )
        {
          while (map->map[i][k] && map->map[i][k + 1] && map->map[i][k] != '.' && map->map[i][k + 1] != '/')
                (k)++;
            if (map->map[i][k] && map->map[i][k + 1])
            {
                map->East = ft_strdup(map->map[i] + k);
                tab = ft_split(map->East,' ');
                free(map->East);
                map->East = ft_strdup(tab[0]);
                ft_free(tab);
                return(1);
            }
        }
        i++;
    }
    return(0);
}


int floor_(t_map *map)
{
    int i;
  
    char **p;
    i = 0;
    
    while(i < map->start && map->map[i])
        {
             if(map->map[i] && ft_strncmp(map->map[i],"F ",2) == 0)
             {  
                 p = ft_split(map->map[i] + 1,',');            
                 ft_rgb_cor1(p,map);
                 ft_free(p);
                 return(1);
            }
             i++;
        }
    return(0);
}
int ceilling_(t_map *map)
{
    int i;
    char **p;
    i = 0;
    while(i < map->start && map->map[i])
        {
            if(ft_strncmp(map->map[i],"C ",2) == 0)
             {
                 p = ft_split(map->map[i] + 1,',');            
                 ft_rgb_cor(p,map);
                 ft_free(p);
                return(1);
              }
            i++;
        }
    return(0);
}