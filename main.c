/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkhoudro <nkhoudro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 16:19:04 by saboulal          #+#    #+#             */
/*   Updated: 2023/12/13 15:11:19 by nkhoudro         ###   ########.fr       */
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
    
    i = 6;
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
    map.width = check_nbr_char(map.map) * 32;
    check_texture_map(&map,&i,&k);
    map.start = check_nbr_height(map.map);
    map.height = (len - map.start) * 32;
    map_draw(map);
    return(0);
}


