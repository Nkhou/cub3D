/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkhoudro <nkhoudro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 16:19:04 by saboulal          #+#    #+#             */
/*   Updated: 2023/12/11 15:33:36 by nkhoudro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"cub.h"

int main(int argc, char **argv)
{
    int len;
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
    len = check_nub_line(argv[1]);
    map.map = (char **)malloc(sizeof(char *) * (len + 1));
    if(!map.map)
    {
        write(1,"Error\n",6);
        exit(0);
    }
    str = check_before_map(argv[1]);
    printf("%s\n",str);
    map.map = ft_split(str,'\n');
    
    j = 0;
    while(str[j])
    {
        if(ft_strcmp(str,"F") == 0)
        {
            map.rgb = (int *)malloc(sizeof(int) * 3);
            if(!map.rgb)
            {
                write(1,"Error\n",6);
                exit(0);
            }
            map.rgb[0] = ft_atoi(str);
            map.rgb[1] = ft_atoi(str);
            map.rgb[2] = ft_atoi(str);
            check_RGB(map);
        }
        j++;
    }
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
