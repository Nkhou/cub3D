/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   function_utils_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saboulal <saboulal@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/16 15:05:29 by saboulal          #+#    #+#             */
/*   Updated: 2024/01/25 21:16:47 by saboulal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../../include/cub.h"

int len_map(char **map)
{
    int i;
   
   i = 0;
   if(!map)
	return(0);
    while(map[i])
         i++;
    return(i);
}


char	*ft_strtrim(char  *s1, char  *set)
{
	size_t	i;
	size_t	j;
	char	*p;

	if (!s1 || !set)
		return (NULL);
	else
	{
		i = 0;
		j = ft_strlen (s1) - 1;
		while (s1[i] && ft_strchr_1(set, s1[i]))
			i++;
		while (s1[j] && ft_strchr_1(set, s1[j]))
			j--;
		p = ft_substr(s1, i, (j - i) + 1);
	}
	return (p);
}