/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   norm.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saboulal <saboulal@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 11:10:49 by saboulal          #+#    #+#             */
/*   Updated: 2024/01/26 17:51:27 by saboulal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub.h"

void    stor_to_map(t_map map)
{
    int i;
    int k;

    i = map.start;
    k = 0;
    while(i < map.len)
    {
        map.map1[k] = (char *)malloc(sizeof(char) * (map.width + 1));
        if (map.map1[k] == NULL)
            ft_error();
        if (ft_strlen(map.map[i]) < map.width)
        {
            int j = 0;
            while(map.map[i][j])
            {
                map.map1[k][j] = map.map[i][j];
                j++;
            }
            while(j < map.width)
            {
                map.map1[k][j] = ' ';
                j++;
            }
            map.map1[k][j] = '\0';
        }
        else
        {
            free(map.map1[k]);
            map.map1[k] = ft_strdup(map.map[i]);
        }
        k++;
        i++;
    }
    map.map1[k] = NULL;
}


void init_part_map(t_map *map)
{
    map->map1 = (char **)malloc(sizeof(char *) * (map->len - map->start + 1));
    if (map->map1 == NULL)
        ft_error();
    stor_to_map(*map);
}

void init_infos(t_map *map,char **argv)
{
    map->str = check_before_map(argv[1]);
    map->map = ft_split(map->str,'\n');
    map->len = cmp_line(map->map);
    map->width = check_nbr_char(map->map);
    map->start = check_nbr_height(map->map);
    map->height = (map->len - map->start);
    map->player.rays = malloc(sizeof(ray_t) * NB_RAYS);
    if (!map->player.rays)
        ft_error();
    if (map->map == NULL)
        ft_error();
}

void init_parse(t_map *map)
{
    get_map(map);
    check_texture_map(map);
    map_game(map->map1);
    map_game_full(*map);
    if(check_white_space(map))
    {
        write(2,"ERROR NOT VALID\n",16);
        exit(0);
    }
}

void ft_extention(char **argv)
{
    if (check_exet(argv[1],".cub") || ft_strlen(argv[1]) < 5)
    {
        write(2,"Error Not Valid Extention\n",26);
        exit(0);
    }
}