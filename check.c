/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saboulal <saboulal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/22 13:45:01 by saboulal          #+#    #+#             */
/*   Updated: 2023/12/26 10:59:52 by saboulal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"cub.h"

 int	in_charset(char c, char *set)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (c == set[i])
			return (1);
		i++;
	}
	return (0);
}


int	check_player_surroundings(char **map, int row, int col)
{
	if (map[row][col + 1] == ' ' || map[row][col - 1] == ' '
		|| map[row + 1][col] == ' ' || map[row - 1][col] == ' ')
		{
            write(2,"Invalid map\n",12);
            exit(0);
        }
	return (0);
}

void	check_map(char **map)
{
	int	row;
	int	col;
	int	found;

	row = 0;
	found = 0;
	while (map[row])
	{
		col = 0;
		while (map[row][col])
		{
			if (!in_charset(map[row][col], " 01NSEW"))
				{
                    write(2,"Invalid character found in map.\n",20);
                    exit(0);
                }
			if (in_charset(map[row][col], "NSEW")
				&& !check_player_surroundings(map, row, col))
				found++;
			col++;
		}
		row++;
	}
	if (!found)
		{
			write(2,"Player not found!.\n",20);
    	    exit(0);
		}
	else if (found > 1)
		{
            write(2,"This is not a multiplayer game..\n",20);
            exit(0);
        }
}

void	map_checks_(t_map map, int row, int col)
{
	if ((row == 0 && check_wall(map.map, row, col))
		|| (row == map.row - 1 && check_wall(map.map, row, col)))
		{
            write(2,"aInvalid map!.\n",14);
            exit(0);
        }
	else if (col == 0 && check_wall(map.map, row, col))
		{
            write(2,"Invalid map!.\n",14);
            exit(0);
        }
	else if (col == ft_strlen(map.map[row]) - 1
		&& check_wall(map.map, row, col))
		{write(2,"Invalid map!.\n",20);
        exit(0);}
	else if ((row > 0 && row < map.row - 1)
		&& (col > 0 && col < ft_strlen(map.map[row]) - 1))
	{
		if (map.map[row][col] == '0'
			&& (map.map[row + 1][col] == ' ' || map.map[row - 1][col] == ' '
			|| map.map[row][col + 1] == ' ' || map.map[row][col - 1] == ' '))
			{
                write(2,"Invalid map!.\n",14);
                exit(0);
            }
	}
}


void    check_map_full(t_map map)
{
    int    row;
    int i;
    int j;
    int    col;

    row = 0;
    i = 0;
    col = 0;
    while (map.map[row] && !(ft_strncmp(map.map[row], "NO ", 3) && ft_strncmp(map.map[row], "SO ", 3) && ft_strncmp(map.map[row], "WE ", 3) && ft_strncmp(map.map[row], "EA ", 3)  && ft_strncmp(map.map[row], "F ", 2) && ft_strncmp(map.map[row], "C ", 2)))
    {   
        col = 0;
        while(map.map[row][col] == 'N' && map.map[row][col] == 'O' && map.map[row][col] == 'S' && map.map[row][col] == 'O' && map.map[row][col] == 'W' && map.map[row][col] == 'E'&& map.map[row][col] == 'A' && map.map[row][col] == 'F' && map.map[row][col] == 'C' && map.map[row][col] == ' ')
            col++;
        row++;
    }

    i = row;
    while (map.map[i])
    {
        j = col;
        if (check_extended_wall(map.map, i))
            {    
                write(2,"1Invalid map!. (new)\n",22);
                exit(0);
            }
        while (map.map[i][j])
        {
            map_checks_(map, i, j);
            j++;
        }
        i++;
    }
}
