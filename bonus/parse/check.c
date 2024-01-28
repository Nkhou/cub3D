/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saboulal <saboulal@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/22 13:45:01 by saboulal          #+#    #+#             */
/*   Updated: 2024/01/28 20:29:13 by saboulal         ###   ########.fr       */
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

int	check_player_surroundings(char **map, int r, int c)
{
	if (map[r][c + 1] == ' ' || map[r][c - 1] == ' '
		|| map[r + 1][c] == ' ' || map[r - 1][c] == ' ')
	{
		write(2, "Invalid map\n", 12);
		exit(0);
	}
	return (0);
}

void	var_norm(int found)
{
	if (!found)
	{
		write(2, "Player not found!.\n", 20);
		exit(0);
	}
	else if (found > 1)
	{
		write(2, "This is not a multiplayer game..\n", 34);
		exit(0);
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
				write(2, "Invalid character found in map.\n", 33);
				exit(0);
			}
			if (found_char(map[r][c], "NSEW")
				&& !check_player_surroundings(map, r, c))
				found++;
			c++;
		}
		r++;
	}
	var_norm(found);
}

void	ft_error_wall(void)
{
	write(2, "Invalid map!.\n", 14);
	exit(0);
}
