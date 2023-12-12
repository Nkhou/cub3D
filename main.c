/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saboulal <saboulal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 16:19:04 by saboulal          #+#    #+#             */
/*   Updated: 2023/12/12 14:21:32 by saboulal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"cub.h"
void inisti_window(t_map map)
{
    map.mlx = mlx_init();
    map.win = mlx_new_window(map.mlx, map.width, map.height, "cub3D");
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
int main(int argc, char **argv)
{
    int len;
    int j;
    int i;
    int k;
    
    // char *p = NULL;
    t_map map;
    char *str;
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
    map.height = len * 32;
    map.map = (char **)malloc(sizeof(char *) * (len + 1));
    if(!map.map)
    {
        write(1,"Error\n",6);
        exit(0);
    }
    str = check_before_map(argv[1]);
    map.map = ft_split(str,'\n');
    map.width = check_nbr_char(map.map) * 32;
    j = 0;
    i = 0;
    k = 0;
    while(i < 6 && map.map[i])
    {
        if(ft_strncmp(map.map[i],"NO ",3) == 0)
        {
            map.North = ft_open_texture(map.map[i]);
            k++;
        }
        if(ft_strncmp(map.map[i],"SO ",3) == 0)
        {
            map.South = ft_open_texture(map.map[i]);
            k++;
        }
        if(ft_strncmp(map.map[i],"WE ",3) == 0)
        {
            map.West = ft_open_texture(map.map[i]);
            k++;
        }
        if(ft_strncmp(map.map[i],"EA ",3) == 0)
        {
            map.East = ft_open_texture(map.map[i]);
            k++;
        }
       
        printf("map.map[i] = %s\n",map.map[i]);
        // if(ft_strncmp(map.map[i],"F ",2) == 0)
        // {
        //     while(j < 3)
        //     {
        //         map.rgb[j] = ft_atoi(map.map[i]);
        //         map.rgb[j] = ft_atoi(map.map[i]);
        //         map.rgb[j] = ft_atoi(map.map[i]);
        //         j++;
        //     }
        //     check_RGB(map);
        //     k++;
        // }
        //  if(ft_strncmp(map.map[i],"C ",3) == 0)
        // {
        //     printf("map.map[i] = %s\n",map.map[i]);
        //     map.map = ft_split(map.map[i],',');
        //     map.rgb = (int *)malloc(sizeof(int) * 3);
        //     if(!map.rgb)
        //     {
        //         write(1,"2Error\n",6);
        //         break;
        //     }
        //     map.rgb[0] = ft_atoi(str);
        //     map.rgb[1] = ft_atoi(str);
        //     map.rgb[2] = ft_atoi(str);
        //     check_RGB(map);
        //     k++;
        // }
        i++;
    }
     map_draw(map);
    return(0);
}

void check_RGB(t_map map)
{
    int i;

    i = 0;
    while(map.rgb[i])
    {
        if(map.rgb[i] >= 0 && map.rgb[i]<= 255)
            i++;
        else
        {
            write(1,"HORS Range Try Again\n",21);
            break;
        }
    }
}
