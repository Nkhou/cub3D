/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saboulal <saboulal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 17:14:15 by saboulal          #+#    #+#             */
/*   Updated: 2023/12/21 15:49:47 by saboulal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include"cub.h"

int check_nub_line(char *path)
{
    
    int i;
    int fd;
   static char *str;
   char *line ;
   
   i = 0;
   
   fd = open(path,O_RDONLY);
   if(fd == -1)
   {
      write(1,"Error\n",6);
      exit(0);
   }
   line = get_next_line(fd);
   while(line)
   {
     line = get_next_line(fd);
     str = ft_strjoin(str,line);
     i++;
     free(line);
   }
   close(fd);
   return(i);
}
//check extention
int check_exet(char *str,char *exe)
{
    int len_all;
    int len_exe;
    
    len_all = ft_strlen(str);
    len_exe = ft_strlen(exe);

    while(len_all > len_exe)
    {
        str++;
        len_all--;
    }
    return(ft_strncmp(str,exe,len_all));
}

char *check_before_map(char *path)
{
    int fd;
   static char *str;
   char *line ;
   
   fd = open(path,O_RDONLY);
   line = get_next_line(fd);
   while(line)
   {
     str = ft_strjoin(str,line);
     line = get_next_line(fd);
     free(line);
   }
        
   close(fd);
   return(str);
}

void check_texture_map(t_map *map,int *i,int *k)
{
   char **p;
     while(*i < 6 && map->map[*i])
      {
        if(ft_strncmp(map->map[*i],"NO ",3) == 0)
        {
            map->North = ft_open_texture(map->map[*i]);
            (*k)++;
        }
        else if(ft_strncmp(map->map[*i],"SO ",3) == 0)
        {
            map->South = ft_open_texture(map->map[*i]);
            (*k)++;
        }
        else if(ft_strncmp(map->map[*i],"WE ",3) == 0)
        {
            map->West = ft_open_texture(map->map[*i]);
            (*k)++;
        }
        else if(ft_strncmp(map->map[*i],"EA ",3) == 0)
        {
            map->East = ft_open_texture(map->map[*i]);
            (*k)++;
        }
       else if(map->map[*i] && ft_strncmp(map->map[*i],"F ",2) == 0)
        {
            p = ft_split(map->map[*i] + 1,',');            
            ft_rgb_color(map,p);
            tabfree(p);
            (*k)++;
        }
        else if(ft_strncmp(map->map[*i],"C ",2) == 0)
        {
            p = ft_split(map->map[*i] + 1,',');            
            ft_rgb_color(map,p);
            tabfree(p);
            (*k)++;
        }
        else
        {
            write(1,"Error\n",6);
            exit(0);
        }
        (*i)++;
    }
}
int ft_identifier(char c)
{
    if(c == 'N' || c == 'S' || c == 'W' || c == 'E' )
        return(1);
    return(0);
}

int check_maps(t_map *map)
{
   map->i = 6;
  while (map->map[map->i])
  { 
    map->j = 0;
    while (map->map[map->i][map->j])
    {
      if (!(map->map[map->i][map->j] == '1' || map->map[map->i][map->j] == ' ' || ft_identifier(map->map[map->i][map->j])  || map->map[map->i][map->j] == '0'))
        {
          write(1,"7Not valid Map\n",14);
          exit(0);
        }
        if(ft_identifier(map->map[map->i][map->j]) == 1)
        {
          
        }
        map->j++;
    }
        map->i++;
   }
    return(1);                                                                                                                                                                                                                                                                                                                               
}

void check_position_players(t_map map)
{
   int i;
   int j;
   int a;
 
   i = 0;
   while(map.map[i])
   {
     j = 0;
     a = 0;
      while(map.map[i][j])
      {
         if(ft_identifier(map.map[i][j]) != 1 && a == 1)
         {
            write(1,"Not valid Position\n",19);
            exit(0);
         }
         a++;
         j++;
      }
      i++;
   }
}

void check_RGB(int *rgb)
{
    int i;

    i = 0;
    while(i < 3)
    {
        if(rgb[i] >= 0 && rgb[i]<= 255)
            i++;
        else
        {
            write(1,"HORS Range Try Again\n",21);
            exit(0);
        }
    }
}

void ft_rgb_color(t_map *map,char **p)
{
    map->rgb = (int *)malloc(sizeof(int) * 3);
    if(!map->rgb)
    {
        write(1,"Error\n",6);
        exit(0);
    }
    map->rgb[0] = ft_atoi(p[0]);
    map->rgb[1] = ft_atoi(p[1]);
    map->rgb[2] = ft_atoi(p[2]);
    check_RGB(map->rgb);
}

static	int check_wall(char **map, int row, int col)
{
	if (map[row][col] != '1' && map[row][col] != ' ')
		return (0);
	return (1);
}

static int	check_wall_(char **map, int row, int i)
{
	while (map[row][i])
	{
		if (map[row][i] != '1' && map[row][i] != ' ')
			return (0);
		i++;
	}
	return (1);
}

static int	check_extended_wall(char **map, int row)
{
	int	l1;
	int	l2;

	l1 = ft_strlen(map[row]);
	l2 = 0;
    while (map[row] && map[row][l2] && map[row][l2] == ' ')
        l2++;
    printf("%c\n",map[row][l2]);
	// if (map[row + 1])
    // {
	// 	l2 = ft_strlen(map[row + 1]);
    // }
	if (l1 > l2 && l2 > 0)
	{
		if (check_wall_(map, row, l2))
			return (0);
	}
	else if (l2 > l1)
	{
		if (check_wall_(map, row + 1, l1))
			return (0);
	}
	return (1);
}

void	map_checks_(t_map map, int row, int col)
{
	if ((row == 0 && check_wall(map.map, row, col))
		|| (row == map.row - 1 && check_wall(map.map, row, col)))
		{
            write(1,"Invalid map!\n",13);
            exit(0);
        }
	else if (col == 0 && check_wall(map.map, row, col))
		{
            write(1,"Invalid map!\n",13);
            exit(0);
        }
	else if (col == ft_strlen(map.map[row]) - 1 && check_wall(map.map, row, col))
		{
            write(1,"Invalid map!\n",13);
            exit(0);
        }
	else if ((row > 0 && row < map.row - 1)
		&& (col > 0 && col < ft_strlen(map.map[row]) - 1))
	{
		if (map.map[row][col] == '0'
			&& (map.map[row + 1][col] == ' ' || map.map[row - 1][col] == ' '
			|| map.map[row][col + 1] == ' ' || map.map[row][col - 1] == ' '))
			{
                write(1,"Invalid map!\n",13);
                exit(0);
            }
	}
}

void	check_walls(t_map map)
{
	int	row;
	int	col;

	row = map.start;
    // while (map.map[row] && !(ft_strncmp(map.map[row], "NO ", 3) && ft_strncmp(map.map[row], "SO ", 3) && ft_strncmp(map.map[row], "WE ", 3) && ft_strncmp(map.map[row], "EA ", 3)  && ft_strncmp(map.map[row], "F ", 2) && ft_strncmp(map.map[row], "C ", 2)))
    //     row++;
	while (map.map[row])
	{
		col = 0;
		if (check_extended_wall(map.map, row))
		{	
            write(1,"Invalid map!\n",13);
            exit(0);
        }
		while (map.map[row][col])
		{
			map_checks_(map, row, col);
			col++;
		}
		row++;
	}
    // printf("%d\n",row);
    // printf("%d\n",col);
    // exit(0);
}