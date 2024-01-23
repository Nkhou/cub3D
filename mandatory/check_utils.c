/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkhoudro <nkhoudro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 16:02:47 by saboulal          #+#    #+#             */
/*   Updated: 2024/01/23 10:11:38 by nkhoudro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub.h"


int check_space(char *str)
{
    int i ;

i = 0;


while(str[i])
{
    if((ft_strncmp(str, "NO ", 3) && ft_strncmp(str, "SO ", 3) && ft_strncmp(str, "WE ", 3) && ft_strncmp(str, "EA ", 3)  && ft_strncmp(str, "F ", 2) && ft_strncmp(str, "C ", 2)))
       i++;
    else 
        break;
    
 }
 return(i);
}