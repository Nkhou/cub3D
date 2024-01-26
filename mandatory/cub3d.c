/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saboulal <saboulal@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 16:19:04 by saboulal          #+#    #+#             */
/*   Updated: 2024/01/26 11:00:33 by saboulal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../include/cub.h"

int check_nbr_char(char **map)
{     
    int i;
    int j;
    int max;
    int len;

    i = 0;
    j = 0;
    max = 0;
    while(map[i])
    {
        len = ft_strlen(map[i]);
        if(len > max)
            max = len;
        i++;
    }
    return(max);
}

int check_nbr_height(char **map)
{
    int i;
    int j;
    
    i = 0;
    while (map[i] && !(ft_strncmp(map[i], "NO ", 3) && ft_strncmp(map[i], "SO ", 3) && ft_strncmp(map[i], "WE ", 3) && ft_strncmp(map[i], "EA ", 3)  && ft_strncmp(map[i], "F ", 2) && ft_strncmp(map[i], "C ", 2)))
        i++;
    while (map[i])
    {
        j = 0;
        while(map[i][j])
        {
            if(map[i][j] == '1')
            {
                return(i);
            }
            j++;
        }
        i++;
    }
    return(i);
}
int cmp_line(char **str)
{
    int i;
    
    i = 0;
    while(str[i])
    {
        i++;
    }
    return(i);
}

void free_programme(char *str,t_map map)
{
    free(str);
    free(map.ceil);
    ft_free(map.map);
    free(map.floor);
}
void ft_exit(void)
{
   system("leaks cub3D");
}
void stor_to_map(t_map map)
{
    int i;
    int k ;

    i = map.start;
    k = 0;
    while(i < map.len)
    {
        map.map1[k] = (char *)malloc(sizeof(char) * (map.width + 1));
        if (map.map1[k] == NULL)
            ft_error();
        if (ft_strlen(map.map[i]) < map.width)
        {
            int j = 0;
            while(map.map[i][j])
            {
                map.map1[k][j] = map.map[i][j];
                j++;
            }
            while(j < map.width)
            {
                map.map1[k][j] = ' ';
                j++;
            }
            map.map1[k][j] = '\0';
        }
        else
            map.map1[k] = ft_strdup(map.map[i]);
        k++;
        i++;
    }
    map.map1[k] = NULL;
}

int	invalid_white_space(t_map *map, int i, int j)
{
	if (map->map1[i][j] == ' ' || map->map1[i][j] == '\t')
	{
		if (i != 0 && map->map1[i - 1][j] != '1' && map->map1[i - 1][j] != ' ')
			return (1);
		if (i != map->r - 1 && map->map1[i + 1][j] != '1' && map->map1[i
			+ 1][j] != ' ' )
			return (1);
		if (j != 0 && map->map1[i][j - 1] != '1' && map->map1[i][j - 1] != ' '
			)
			return (1);
		if (j != map->c - 1 && map->map1[i][j + 1] != '1' && map->map1[i][j
			+ 1] != ' ' )
			return (1);
	}
	return (0);
}
int waall(char *str)
{
    int i;

    i = 0;
    while(str[i])
    {
        if(str[i] != '1' && str[i] != ' ' && str[i] != '\t' )
            return(1);
        i++;
    }
    return(0);
}
char	*ft_str(const char *s, int c)
{
	while (*s)
	{
		if (*(char *)s == (char)c)
		{
			return ((char *)s);
		}
		s++;
	}
	if (*(char *)s == (char)c)
	{
		return ((char *)s);
	}
	return (NULL);
}
int check_white_space(t_map *map)
{
    int i;
    int j;
    i = 0;
    while(i < map->r)
    {
        if(ft_str(map->map1[i],' ') || ft_str(map->map1[i],'\t'))
        {

            j = 0;
         while(map->map1[i][j])
         {
             if(invalid_white_space(map,i,j))
                 return(1);
             j++;
         }
        }
        i++;
    }
    return(0);
}

void get_space_wall(t_map map)
{
    int i = 0;
    while(map.map1[i])
    {
        int j = 0;
        while(map.map1[i][j])
        {
            if(map.map1[i][j] == ' ')
                map.map1[i][j] = '1';
            j++;
        }
        i++;
    }
}

void init_parse(t_map *map)
{
    get_map(map);
    check_texture_map(map);
    map_game(map->map1);
    map_game_full(*map);
    if(check_white_space(map))
    {
        write(2,"ERROR NOT VALID\n",16);
        exit(0);
    }
}

void init_part_map(t_map *map)
{
    map->map1 = (char **)malloc(sizeof(char *) * (map->len - map->start + 1));
    if (map->map1 == NULL)
        ft_error();
    stor_to_map(*map);
}
void init_infos(t_map *map,char **argv)
{
    map->str = check_before_map(argv[1]);
    map->map = ft_split(map->str,'\n');
    map->len = cmp_line(map->map);
    map->width = check_nbr_char(map->map);
    map->start = check_nbr_height(map->map);
    map->height = (map->len - map->start);
    map->player.rays = malloc(sizeof(ray_t) * NB_RAYS);
    if (!map->player.rays)
        ft_error();
    if (map->map == NULL)
        ft_error();
}

int main(int argc, char **argv)
{
    t_map map;
    
    // atexit(ft_exit);
    ini_map(&map,argc);
    ft_extention(argv);
    init_infos(&map,argv);
    init_part_map(&map);
    init_parse(&map);
    get_space_wall(map);
    map_draw(map);
    free_programme(map.str,map);
    return(0);
 }
 

void ini_map(t_map *map,int argc)
{
    if (argc  != 2)
    {
        write(2,"ERROR NOT VALID\n",16);
        exit(0);
    }
     map->j = 0;  
     map->i = 0;
     map->k = 0;
    
}

void ft_extention(char **argv)
{
    if (check_exet(argv[1],".cub") || ft_strlen(argv[1]) < 5)
    {
        write(2,"Error Not Valid Extention\n",26);
        exit(0);
    }
}
