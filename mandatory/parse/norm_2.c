/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   norm_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saboulal <saboulal@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 11:14:04 by saboulal          #+#    #+#             */
/*   Updated: 2024/01/26 11:14:36 by saboulal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../../include/cub.h"

int cmp_line(char **str)
{
    int i;
    
    i = 0;
    while(str[i])
        i++;
    return(i);
}

void free_programme(char *str,t_map map)
{
    free(str);
    free(map.ceil);
    ft_free(map.map);
    free(map.floor);
}

void ini_map(t_map *map,int argc)
{
    if (argc  != 2)
    {
        write(2,"ERROR NOT VALID\n",16);
        exit(0);
    }
     map->j = 0;  
     map->i = 0;
     map->k = 0;
    
}