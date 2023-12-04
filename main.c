/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saboulal <saboulal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 16:19:04 by saboulal          #+#    #+#             */
/*   Updated: 2023/12/04 17:22:09 by saboulal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"cub.h"

int main(int argc, char **argv)
{
    int i;
    int j;
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
    i = check_nub_line(argv[1]);
    str = check_before_map(argv[1]);
    map.map = ft_split(str,'\n');
   
    
    // printf("%d\n",i);
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
