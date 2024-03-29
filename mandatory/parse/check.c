/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkhoudro <nkhoudro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/22 13:45:01 by saboulal          #+#    #+#             */
/*   Updated: 2024/02/01 12:57:58 by nkhoudro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub.h"

int	found_char(char c, char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (c == str[i])
			return (1);
		i++;
	}
	return (0);
}

void	var_norm(int found)
{
	if (!found)
	{
		write(1, "Error\n", 6);
		write(2, "Player not found!.\n", 20);
		exit(1);
	}
	else if (found > 1)
	{
		write(1, "Error\n", 6);
		write(2, "This is not a multiplayer game..\n", 34);
		exit(1);
	}
}

void	map_game(char **map)
{
	int	r;
	int	c;
	int	found;

	r = 0;
	found = 0;
	while (map[r])
	{
		c = 0;
		while (map[r][c])
		{
			if (!found_char(map[r][c], " 01NSEW"))
			{
				write(1, "Error\n", 6);
				write(2, "Invalid character found in map.\n", 33);
				exit(1);
			}
			if (found_char(map[r][c], "NSEW"))
				found++;
			c++;
		}
		r++;
	}
	var_norm(found);
}

void	ft_error_wall(void)
{
	write(1, "Error\n", 6);
	write(2, "Invalid map!.\n", 14);
	exit(1);
}
