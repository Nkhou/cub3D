/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saboulal <saboulal@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/22 13:46:14 by saboulal          #+#    #+#             */
/*   Updated: 2024/01/30 15:23:54 by saboulal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub.h"

int	space_waall(char **map, int r, int c)
{
	if (!map)
		return (1);
	if (map[r][c] != '1' && map[r][c] != ' ')
		return (1);
	return (0);
}

int	space_waall_(char **map, int r, int i)
{
	if (!map)
		return (1);
	while (map[r][i])
	{
		if (map[r][i] != '1' && map[r][i] != ' ')
			return (0);
		i++;
	}
	return (1);
}

int	check_new_line(char *str)
{
	return (str[ft_strlen(str) - 1] == '\n');
}

int	found_wall(char **map, int r)
{
	int	l1;
	int	l2;

	l1 = ft_strlen(map[r]);
	l2 = 0;
	if (map[r + 1])
	{
		l2 = ft_strlen(map[r + 1]);
	}
	if (l1 > l2 && l2 > 0)
	{
		if (space_waall_(map, r, l2))
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
