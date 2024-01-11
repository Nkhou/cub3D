/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkhoudro <nkhoudro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/22 13:45:01 by saboulal          #+#    #+#             */
/*   Updated: 2024/01/11 19:49:10 by nkhoudro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"cub.h"

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
	if (!ft_is_space(map[r][c + 1])  ||!ft_is_space( map[r][c - 1]) 
		|| !ft_is_space(map[r + 1][c])  || !ft_is_space(map[r - 1][c]))
		{
            write(2,"Invalid map\n",12);
            exit(0);
        }
	return (0);
}



void	map_checks_(t_map map, int r, int c)
{
	if ((r == 0 && space_waall(map.map, r, c))
		|| (r == map.r - 1 && space_waall(map.map, r, c)))
		{
            write(2,"aInvalid map!.\n",14);
            exit(0);
        }
	else if (c == 0 && space_waall(map.map, r, c))
		{
            write(2,"Invalid map!.\n",14);
            exit(0);
        }
	else if (c == ft_strlen(map.map[r]) - 1
		&& space_waall(map.map, r, c))
		{write(2,"Invalid map!.\n",20);
        exit(0);}
	else if ((r > 0 && r < map.r - 1)
		&& (c > 0 && c < ft_strlen(map.map[r]) - 1))
	{
		if (map.map[r][c] == '0'
			&& (!ft_is_space(map.map[r + 1][c])  || !ft_is_space(map.map[r - 1][c]) 
			|| !ft_is_space(map.map[r][c + 1])  || !ft_is_space(map.map[r][c - 1])))
			{
                write(2,"Invalid map!.\n",14);
                exit(0);
            }
	}
}


void    map_game_full(t_map map)
{
    int    r;
    int i;
    int j;
    int    c;

    r = 0;
    i = 0;
    c = 0;
    while (map.map[r] && !(ft_strncmp(map.map[r], "NO ", 3) && ft_strncmp(map.map[r], "SO ", 3) && ft_strncmp(map.map[r], "WE ", 3) && ft_strncmp(map.map[r], "EA ", 3)  && ft_strncmp(map.map[r], "F ", 2) && ft_strncmp(map.map[r], "C ", 2)))
    {   
        c = 0;
        while(map.map[r][c] == 'N' && map.map[r][c] == 'O' && map.map[r][c] == 'S' && map.map[r][c] == 'O' && map.map[r][c] == 'W' && map.map[r][c] == 'E'&& map.map[r][c] == 'A' && map.map[r][c] == 'F' && map.map[r][c] == 'C' && map.map[r][c] == ' ')
            c++;
        r++;
    }

    i = r;
    while (map.map[i])
    {
        j = c;
        if (found_wall(map.map, i))
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
