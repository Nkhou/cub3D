/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkhoudro <nkhoudro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 16:19:04 by saboulal          #+#    #+#             */
/*   Updated: 2024/01/13 20:17:42 by nkhoudro         ###   ########.fr       */
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
 
char *ft_open_texture(char *tex)
{
    int fd;
   
    char **tab;
     
    tab = ft_split(tex, ' ');
    fd = open(tab[1],O_RDONLY);
    if(fd == -1)
    {
      ft_error();
    }
    tabfree(tab);
    close(fd);
    return(tex);
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
    free(map.rgb);
    tabfree(map.map);
    free(map.rgb1);
}
void ft_exit(void)
{
   system("leaks Cub");
}
int main(int argc, char **argv)
{
    // atexit(ft_exit);
    char *str;
    t_map map;
    ini_map(&map);
    if (argc  != 2)
    {
        write(2,"ERROR NOT VALID\n",16);
        exit(0);
    }
    ft_extention(argv);
    str = check_before_map(argv[1]);
    map.map = ft_split(str,'\n');
    map.len = cmp_line(map.map);
    map.width = check_nbr_char(map.map);
    map.start = check_nbr_height(map.map);
    map.height = (map.len - map.start);
    map.width = map.width * map.size;
    map.NB_RAYS = map.width / map.size;
    // printf("NB_RAYS = %d\n",map.NB_RAYS);
    // printf("width = %d\n",map.width /);
    map.player.rays = malloc(sizeof(t_ray) * map.NB_RAYS);
    if (map.player.rays == NULL)
        ft_error();
    map.height = map.height * map.size;
    if(map.map == NULL)
        ft_error();
    get_map(&map);
    check_texture_map(&map,&map.i,&map.k);
    map_games(&map);
    map_game_full(map);
    check_position_players(map);
    // get_south(&map);
    map_draw(map);
    ft_texture(&map);
    mlx_delete_texture(map.texture);
    free_programme(str,map);
    return(0);
 }

void ini_map(t_map *map)
{
     map->j = 0;   
     map->i = 0;
     map->k = 0;
     map->size = 32;
    
}

void ft_extention(char **argv)
{
    if (check_exet(argv[1],".cub") || ft_strlen(argv[1]) < 5)
    {
        write(2,"Error Not Valid Extention\n",26);
        exit(0);
    }
}
