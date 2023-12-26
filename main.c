/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkhoudro <nkhoudro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 16:19:04 by saboulal          #+#    #+#             */
/*   Updated: 2023/12/26 16:19:44 by nkhoudro         ###   ########.fr       */
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
      
        write(1,"AError\n",6);
        exit(0);
    }
    free(tab[1]);
    free(tab);
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
int main(int argc, char **argv)
{
    char *str;

  
    t_map map;
    
    init_map(&map);
    if (argc  != 2)
    {
        write(2,"ERROR NOT VALID\n",16);
        exit(0);
    }
    ft_extention(argv);
    // map.len = check_nub_line(argv[1]) ;
    str = check_before_map(argv[1]);
    map.map = ft_split(str,'\n');
    map.len = cmp_line(map.map);
    map.width = check_nbr_char(map.map);
    map.start = check_nbr_height(map.map);
    map.height = (map.len - map.start);
    map.width = map.width * map.size;
    map.height = map.height * map.size;
    if(map.map == NULL)
    {
        write(2,"BError\n",6);
        exit(0);
    }
    get_map(&map);
    check_texture_map(&map,&map.i,&map.k);
    check_maps(&map);
    check_map_full(map);
    check_position_players(map);
    map_draw(map);
    return(0);
}

void init_map(t_map *map)
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


