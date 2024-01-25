/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saboulal <saboulal@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/22 13:45:01 by saboulal          #+#    #+#             */
/*   Updated: 2024/01/25 13:04:15 by saboulal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../include/cub.h"

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
            write(2,"Invalid map\n",12);
            exit(0);
        }
	return (0);
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
			if (!found_char(map[r][c], " 01NSEWD"))
				{
                    write(2,"Invalid character found in map.\n",33);
                    exit(0);
                }
			if (found_char(map[r][c], "NSEW")
				&& !check_player_surroundings(map, r, c))
				found++;
			c++;
		}
		r++;
	}
	if (!found)
		{
			write(2,"Player not found!.\n",20);
    	    exit(0);
		}
	else if (found > 1)
		{
            write(2,"This is not a multiplayer game..\n",34);
            exit(0);
        }
}

void	map_checks_(t_map map, int r, int c)
{
    printf("row: %d, col: %d\n", r, c);
	if ((r == 0 && space_waall(map.map1, r, c))
		|| (r == map.r - 1 && space_waall(map.map1, r, c)))
		{
            write(2,"aInvalid map!.\n",14);
            exit(0);
        }
	else if (c == 0 && space_waall(map.map1, r, c))
		{
            write(2,"Invalid map!.\n",14);
            exit(0);
        }
	else if (c == ft_strlen(map.map1[r]) - 1
		&& space_waall(map.map1, r, c))
		
    {
    
        write(2,"Invalid map!.\n",20);
        exit(0);
        }
	else if ((r > 0 && r < map.r - 1)
		&& (c > 0 && c < ft_strlen(map.map[r]) - 1))
	{
		if (map.map[r][c] == '0'
			&& (map.map[r + 1][c] == ' ' || map.map[r - 1][c] == ' '
			|| map.map[r][c + 1] == ' ' || map.map[r][c - 1] == ' '))
			{ 
                write(2,"2Invalid map!.\n",20);
               exit(0);
            }
	}
    // printf("hi\n");
}


void    map_game_full(t_map map)
{
    // // int    r;
    // int i;
    // int j;
    // int    c;

    
    // i = 0;
    // c = 0;
    // // while (map.map[r] && !(ft_strncmp(map.map[r], "NO ", 3) && ft_strncmp(map.map[r], "SO ", 3) && ft_strncmp(map.map[r], "WE ", 3) && ft_strncmp(map.map[r], "EA ", 3)  && ft_strncmp(map.map[r], "F ", 2) && ft_strncmp(map.map[r], "C ", 2)))
    // // {   
    // //     c = 0;
    // //     while(map.map[r][c] == 'N' && map.map[r][c] == 'O' && map.map[r][c] == 'S' && map.map[r][c] == 'O' && map.map[r][c] == 'W' && map.map[r][c] == 'E'&& map.map[r][c] == 'A' && map.map[r][c] == 'F' && map.map[r][c] == 'C' && map.map[r][c] == ' ')
    // //         c++;
    // //     r++;
    // // }

    // i = 0;
    // while (map.map1[i])
    // {
    //     j = 0;
    //     if (found_wall(map.map1, i))
    //         {    
    //             write(2,"1Invalid map!. (new)\n",22);
    //             exit(0);
    //         }
    //     while (map.map1[i][j])
    //     {
    //         map_checks_(map, i, j);
    //         j++;
    //     }
    //     i++;
    // }
    int	row;
	int	col;

	row = 0;
	while (map.map1[row])
	{
		col = 0;
		if (found_wall(map.map1, row))
        {
            write(2,"Invalid map!.\n",14);
			ft_error();
        }
		while (map.map1[row][col])
		{
			map_checks_(map, row, col);
			col++;
		}
		row++;
	}
}

// newwwwww functions
int check_readd(t_map *map,char *str,int fd)
{
    int len_x;
    int fch;

    len_x = 0;
    fch = 0;
    while(1)
    {
        str = get_next_line(fd);
        if(str == NULL)
            break;
        if(ft_is_space(str))
        {
            fch = 1;
            free(str);
            continue;
        }
        if(!ft_is_space(str) && fch == 1)
          return(free(str),1);
        len_x = ft_strlen(str) - 1;
        if(len_x > map->c)
            map->c = len_x;
            
        map->r++;
        free(str);
    }
    return(0);
}

int retir_space(t_map *map,int fd)
{
    char *line;

    line = NULL;
    map->c = ft_strlen(map->map1[0]);
    map->r = 1;
    if(check_readd(map,line,fd))
        return(1);
    close(fd);
    return(0);
}

int ft_is_space(char *str)
{
    int i;

    i = 0;
    while(str[i])
    {
        if(str[i] != ' ' && str[i] != '\t' && str[i] != '\n')
            return(0);
        i++;
    }
    return(1);
}