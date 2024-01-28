/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   norm.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saboulal <saboulal@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 11:10:49 by saboulal          #+#    #+#             */
/*   Updated: 2024/01/28 19:53:42 by saboulal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub.h"

void	ft_norm_oo(t_map map, int i, int k)
{
	int	j;

	j = 0;
	while (map.map[i][j])
	{
		map.map1[k][j] = map.map[i][j];
		j++;
	}
	while (j < map.width)
	{
		map.map1[k][j] = ' ';
		j++;
	}
	map.map1[k][j] = '\0';
}

void	stor_to_map(t_map map)
{
	int	i;
	int	k;

	i = map.start;
	k = 0;
	while (i < map.len)
	{
		map.map1[k] = (char *) malloc(sizeof(char) * (map.width + 1));
		if (map.map1[k] == NULL)
			ft_error();
		if (ft_strlen(map.map[i]) < map.width)
			ft_norm_oo(map, i, k);
		else
		{
			free(map.map1[k]);
			map.map1[k] = ft_strdup(map.map[i]);
		}
		k++;
		i++;
	}
	map.map1[k] = NULL;
}

int	ft_strncmp1(const char *s1, const char *s2, size_t n)
{
	unsigned char	*my_s1;
	unsigned char	*my_s2;
	size_t			i;

	i = 0;
	my_s1 = (unsigned char *)s1;
	my_s2 = (unsigned char *)s2;
	while (i < n && (my_s1[i] != '\0' || my_s2[i] != '\0'))
	{
		if (my_s1[i] != my_s2[i])
			return (my_s1[i] - my_s2[i]);
		i++;
	}
	return (0);
}

void	init_vaar(t_tex *tex)
{
	tex->no = 0;
	tex->so = 0;
	tex->we = 0;
	tex->ea = 0;
	tex->c = 0;
	tex->f = 0;
}

void	check_retour(char *str, int i)
{
	while (str[i] != '\n')
		i++;
}
