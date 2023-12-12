/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saboulal <saboulal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 16:19:04 by saboulal          #+#    #+#             */
/*   Updated: 2023/12/12 20:23:46 by saboulal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"cub.h"
void inisti_window(t_map map)
{
    int i;
    int j;

    i = map.start;
    j = 0;
    map.mlx = mlx_init();
    map.win = mlx_new_window(map.mlx, map.width, map.height, "cub3D");
    while (map.map[i])
    {
        while(map.map[i][j])
        {
            if(map.map[i][j] == '1')
            {
                mlx_pixel_put(map.mlx, map.win, j * 32, i * 32,  0xFFFFFF);
            }
            else if (map.map[i][j] == '0')
            {
                mlx_pixel_put(map.mlx, map.win, j * 32, i * 32, 0x00000);
            }
            j++;
        }
        j = 0;
        i++;
    }
    mlx_loop(map.mlx);
}
void map_draw(t_map map)
{
    inisti_window(map);
    // mlx_hook(map.win, 2, 1L<<0, key_press, &map);
    // mlx_hook(map.win, 3, 1L<<1, key_release, &map);
}
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
      
        write(1,"Error\n",6);
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
    while (map[i] && i > 6 )
    {
        printf("%s\n",map[i]);
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
int main(int argc, char **argv)
{
    char *str;
    t_map map;
    int len;
    int j;
    int i;
    int k;
    
    j = 0;
    i = 0;
    k = 0;
    if(argc  != 2)
    {
        write(1,"ERROR NOT VALID\n",16);
        exit(0);
    }
    if(check_exet(argv[1],".cub") || ft_strlen(argv[1]) < 5)
    {
        write(1,"Error Not Valid Extention\n",26);
        exit(0);
    }
    len = check_nub_line(argv[1]) ;
    str = check_before_map(argv[1]);
    map.map = ft_split(str,'\n');
    // free(str);
    map.width = check_nbr_char(map.map) * 32;
    check_texture_map(&map,&i,&k);
    map.start = check_nbr_height(map.map);
    map.height = (len - map.start) * 32;
    map_draw(map);
    return(0);
}


