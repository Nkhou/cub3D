/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkhoudro <nkhoudro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 16:19:04 by saboulal          #+#    #+#             */
/*   Updated: 2023/12/11 21:11:50 by nkhoudro         ###   ########.fr       */
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
     printf("%s\n",str);
    map.map = ft_split(str,'\n');
    map.width = check_nbr_char(map.map) * 32;
    
    j = 0;
    i = 0;
    k =0;
    while(i <= 4)
    {
        if((map.map[i]))
        {
            write(1,"Error\n",6);
            break;
        }
        i++;
    }
    while(map.map[j])
    {
        
        if(ft_strcmp(str,"F") == 0)
        {
            map.rgb = (int *)malloc(sizeof(int) * 3);
            if(!map.rgb)
            {
                write(1,"Error\n",6);
                break;
            }
            map.rgb[0] = ft_atoi(str);
            map.rgb[1] = ft_atoi(str);
            map.rgb[2] = ft_atoi(str);
            check_RGB(map);
        }
        j++;
    }
    // map_draw(map);
    return(0);
}

int check_RGB(t_map map)
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
    return(0);
}
