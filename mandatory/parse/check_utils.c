/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saboulal <saboulal@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 16:02:47 by saboulal          #+#    #+#             */
/*   Updated: 2024/01/25 21:17:26 by saboulal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub.h"


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