/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saboulal <saboulal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 16:19:04 by saboulal          #+#    #+#             */
/*   Updated: 2024/01/21 10:51:40 by saboulal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"cub.h"

int check_nbr_char(char **map)
{     
    int i;
    int j;
    int max;
    int len;

    i = 0;
    j = 0;
    max = 0;
    while(map[i])
    {
        len = ft_strlen(map[i]);
        if(len > max)
            max = len;
        i++;
    }
    return(max);
}

int check_nbr_height(char **map)
{
    int i;
    int j;
    
    i = 0;
    while (map[i] && !(ft_strncmp(map[i], "NO ", 3) && ft_strncmp(map[i], "SO ", 3) && ft_strncmp(map[i], "WE ", 3) && ft_strncmp(map[i], "EA ", 3)  && ft_strncmp(map[i], "F ", 2) && ft_strncmp(map[i], "C ", 2)))
        i++;
    while (map[i])
    {
        j = 0;
        while(map[i][j])
        {
            if(map[i][j] == '1')
            {
                return(i);
            }
            j++;
        }
        i++;
    }
    return(i);
}
int cmp_line(char **str)
{
    int i;
    
    i = 0;
    while(str[i])
    {
        i++;
    }
    return(i);
}

void free_programme(char *str,t_map map)
{
    free(str);
    free(map.ceil);
    ft_free(map.map);
    free(map.floor);
}
void ft_exit(void)
{
   system("leaks Cub");
}
int main(int argc, char **argv)
{
    (void)argc;
    (void)argv;
    // atexit(ft_exit);
    // puts("inisti_window");
   
    t_map map;
    
    ini_map(&map);
    if (argc  != 2)
    {
        write(2,"ERROR NOT VALID\n",16);
        exit(0);
    }
    ft_extention(argv);
    map.str = check_before_map(argv[1]);
    if(retir_space(&map,open(argv[1],O_RDONLY)) == 1)
    {
        write(2,"ERROR NOT VALID\n",16);
        exit(0);
    }
    map.map = ft_split(map.str,'\n');
    map.len = cmp_line(map.map);
    map.width = check_nbr_char(map.map);
    map.start = check_nbr_height(map.map);
    map.height = (map.len - map.start);
    map.width = map.width * map.size;
    map.NB_RAYS = map.width ;
    // printf("NB_RAYS = %d\n",map.NB_RAYS);
    // printf("width = %d\n",map.width /);
    map.player.rays = malloc(sizeof(ray_t) * map.NB_RAYS);
    if (map.player.rays == NULL)
        ft_error();
    map.height = map.height * map.size;
    if(map.map == NULL)
        ft_error();
    get_map(&map);
    check_texture_map(&map);
    map_games(&map);
    map_game_full(map); 
    check_position_players(map);
    // get_south(&map);
    map_draw(map);
    // ft_texture(&map);
  
    free_programme(map.str,map);
    return(0);
 }

void ini_map(t_map *map)
{
     map->j = 0;   
     map->i = 0;
     map->k = 0;
     map->size = 64;
    
}

void ft_extention(char **argv)
{
    if (check_exet(argv[1],".cub") || ft_strlen(argv[1]) < 5)
    {
        write(2,"Error Not Valid Extention\n",26);
        exit(0);
    }
}
