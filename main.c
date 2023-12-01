/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saboulal <saboulal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 16:19:04 by saboulal          #+#    #+#             */
/*   Updated: 2023/12/01 21:12:01 by saboulal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"cub.h"

int main(int argc, char **argv)
{
    int i = 0;
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
    str = check_before_map(argv[1]);
    map.map = ft_split(str,'\n');
    return(0);
}