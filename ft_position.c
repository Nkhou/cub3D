/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_position.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saboulal <saboulal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 19:34:51 by saboulal          #+#    #+#             */
/*   Updated: 2024/01/18 14:46:28 by saboulal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void ft_north(t_map *map)
{
    char **tab;
     int i = 0;
    int k = 0;
     while( map->map[i] && i < map->start )
      {
      
        k = 0;
        if(ft_strncmp(map->map[i],"NO ",3) == 0 )
        {
          printf("map->map[i] = %s\n",map->map[i]);
          while (map->map[i][k] && map->map[i][k] != '.' && map->map[i][k] != '/')
                (k)++;
            if (map->map[i][k])
            {
                map->North = ft_strdup(map->map[i] + k);
                tab = ft_split(map->North,' ');
                map->North = tab[0];
                ft_free(tab);
            }
        }
        i++;
    }
}

void ft_south(t_map *map)
{
    char **tab;
     int i = 0;
    int k = 0;
     while( i < map->start && map->map[i])
      {
        k = 0;
        if(ft_strncmp(map->map[i],"SO ",3) == 0 )
        {
          while (map->map[i][k] && map->map[i][k] != '.' && map->map[i][k] != '/')
                (k)++;
            if (map->map[i][k])
            {
                map->South = ft_strdup(map->map[i] + k);
                tab = ft_split(map->South,' ');
                map->South = tab[0];
                ft_free(tab);
            }
        }
        i++;
    }
}


void ft_west(t_map *map)
{
    char **tab; 
     int i = 0;
    int k = 0;
    while(i < map->start && map->map[i])
    {
        if (ft_strncmp(map->map[i],"WE ",3) == 0)
        { 
            while (map->map[i][k] && map->map[i][k] != '.' && map->map[i][k] != '/')
                k++;
            if (map->map[i][k])
            {
                map->West = ft_strdup(map->map[i] + k);
                tab = ft_split(map->West,' ');
                map->West = tab[0];
                ft_free(tab);
            }
        }
        i++;
    }
}

void ft_east(t_map *map)
{
    char **tab; 
     int i = 0;
    int k = 0;
    while(i < map->start && map->map[i])
    {
       
        if (ft_strncmp(map->map[i],"EA ",3) == 0)
        { 
            while (map->map[i][k] && map->map[i][k] != '.' && map->map[i][k] != '/')
                k++;
            if (map->map[i][k])
            {
                map->East = ft_strdup(map->map[i] + k);
                tab = ft_split(map->East,' ');
                map->East = tab[0];
                ft_free(tab);
            }
        }
        i++;
    }
}
