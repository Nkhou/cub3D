/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkhoudro <nkhoudro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 16:02:47 by saboulal          #+#    #+#             */
/*   Updated: 2024/02/01 12:57:58 by nkhoudro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub.h"

void	check(char *str)
{
	int	i;

	i = 0;
	if (!str)
		ft_error();
	while (str[i])
	{
		while (str[i] && str[i] == ' ')
			i++;
		if (str[i] && ft_isdigit(str[i]) && str[i] != ' ' && str[i] != ',')
			ft_error();
		i++;
	}
}

int	cmp_comma(char *str)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] == ',')
			j++;
		i++;
	}
	if (j != 2)
		return (1);
	return (0);
}

void	get_ceilling(t_map *map, char *c, int *find)
{
	char	**p;

	check(c + 1);
	if (cmp_comma(c))
		ft_error();
	p = ft_split(c + 1, ',');
	ft_rgb_cor(p, map);
	ft_free(p);
	(*find)++;
}

int	ceilling_(t_map *map)
{
	int		i;
	int		find;
	char	*c;

	i = -1;
	find = 0;
	c = NULL;
	while (++i < map->start && map->map[i])
	{
		c = ft_skip_1(map->map[i], c);
		if (c && ft_strncmp(c, "C ", 2) == 0)
		{
			get_ceilling(map, c, &find);
			free(c);
			c = NULL;
		}
		if (find > 1)
			ft_error();
	}
	if (c)
		free(c);
	if (find != 1)
		ft_error();
	return (0);
}

void	ft_extention(char **argv)
{
	if (check_exet(argv[1], ".cub") || ft_strlen(argv[1]) < 5)
	{
		write(1, "Error\n", 6);
		write(2, "Error Not Valid Extention\n", 26);
		exit(1);
	}
}
