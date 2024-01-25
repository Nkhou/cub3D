/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_check_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saboulal <saboulal@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/22 13:46:14 by saboulal          #+#    #+#             */
/*   Updated: 2024/01/25 16:24:37 by saboulal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../include/cub.h"

int    space_waall(char **map, int r, int c)
{
	//printf("abcd\n");
    if (map[r][c] != '1' && map[r][c] != ' ')
		return (1);
	return (0);
}

static int     space_waall_(char **map, int r, int i)
{
	printf("efgh\n");
   while (map[r][i])
	{
		if (map[r][i] != '1' && map[r][i] != ' ')
			return (1);
		i++;
	}
	return (0);
}
int	check_new_line(char *str)
{
	return (str[ft_strlen(str) - 1] == '\n');
}

int    found_wall(char **map, int r)
{
    int	l1;
	int	l2;

	l1 = ft_strlen(map[r]);
	l2 = 0;
	if (map[r + 1])
		l2 = ft_strlen(map[r + 1]);
	if (l1 > l2 && l2 > 0)
	{
		if (space_waall(map, r, l2))
			return (1);
	}
	else if (l2 > l1)
	{
		if (space_waall_(map, r + 1, l1))
			return (1);
	}
	return (0);
}
char	*ft_strndup(char *s1, int n)
{
	char	*copy;
	size_t	s1_len;
	int		i;

	i = 0;
	s1_len = ft_strlen(s1);
	copy = malloc(sizeof(char) * (s1_len + 1));
	if (!copy)
		return (NULL);
	while (s1[i] && i < n)
	{
		copy[i] = s1[i];
		i++;
	}
	copy[i] = '\0';
	return (copy);
}

void   get_map(t_map *map)
{
    int		i;
	int		j;

	i = 0;
	j = 0;
	map->r = len_map(map->map1);
	map->tab = malloc(sizeof(char *) * (map->r + 1));
	map->c = 0;
	if (!map->tab)
		ft_error();
	while (map->map1[i])
	{
		if (map->map1[i][0] == '1'
				|| map->map1[i][0] == ' '
				|| map->map1[i][0] == '0')
		{
			map->tab[j++] = ft_strndup(map->map1[i],
					ft_strlen(map->map1[i]) - \
					check_new_line(map->map1[i]));
			if (map->c < ft_strlen(map->tab[j - 1]))
				map->c = ft_strlen(map->tab[j - 1]);
		}
		i++;
	}
	map->tab[j] = 0;
    
}
 