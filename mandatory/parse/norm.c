/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   norm.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkhoudro <nkhoudro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 11:10:49 by saboulal          #+#    #+#             */
/*   Updated: 2024/01/28 16:17:34 by nkhoudro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub.h"

void	ft_norm_oo(t_map map, int i, int k)
{
	int	j;

	j = 0;
	while (map.map[i][j])
	{
		map.map1[k][j] = map.map[i][j];
		j++;
	}
	while (j < map.width)
	{
		map.map1[k][j] = ' ';
		j++;
	}
	map.map1[k][j] = '\0';
}

void	stor_to_map(t_map map)
{
	int	i;
	int	k;

	i = map.start;
	k = 0;
	while (i < map.len)
	{
		map.map1[k] = (char *) malloc(sizeof(char) * (map.width + 1));
		if (map.map1[k] == NULL)
			ft_error();
		if (ft_strlen(map.map[i]) < map.width)
			ft_norm_oo(map, i, k);
		else
		{
			free(map.map1[k]);
			map.map1[k] = ft_strdup(map.map[i]);
		}
		k++;
		i++;
	}
	map.map1[k] = NULL;
}
int	ft_strncmp1(const char *s1, const char *s2, size_t n)
{
	unsigned char	*my_s1;
	unsigned char	*my_s2;
	size_t			i;

	i = 0;
	my_s1 = (unsigned char *)s1;
	my_s2 = (unsigned char *)s2;
	while (i < n && (my_s1[i] != '\0' || my_s2[i] != '\0'))
	{
		if (my_s1[i] != my_s2[i])
			return (my_s1[i] - my_s2[i]);
		i++;
	}
	return (0);
}
void	check_line(char *str)
{
	int	i;
	t_tex tex;

	i = 0;
	tex.c = 0;
	tex.f = 0;
	tex.no = 0;
	tex.so = 0;
	tex.we = 0;
	tex.ea = 0;
	while (str[i])
	{
		while (str[i] == '\n' || str[i] == ' ')
			i++;
		if (str[i] == 'N' && str[i + 1] == 'O')
		{
			while (str[i] != '\n')
				i++;
			tex.no++;
		}
		else if (str[i] == 'S' && str[i + 1] == 'O')
		{
			while (str[i] != '\n')
				i++;
			tex.so++;
		}
		else if (str[i] == 'W' && str[i + 1] == 'E')
		{
			while (str[i] != '\n')
				i++;
			tex.we++;
		}
		else if (str[i] == 'E' && str[i + 1] == 'A')
		{
			while (str[i] != '\n')
				i++;
			tex.ea++;
		}
		else if (str[i] == 'C' && str[i + 1] == ' ')
		{
			while (str[i] != '\n')
				i++;
			tex.c++;
		}
		else if (str[i] == 'F' && str[i + 1] == ' ')
		{
			while (str[i] != '\n')
				i++;
			tex.f++;
		}
		if (tex.c > 1 || tex.f > 1 || tex.no > 1 || tex.so > 1 || tex.we > 1 || tex.ea > 1)
			ft_error();
		if (str[i] == '1')
			break ;
		i++;
	}
	while (str[i])
	{
		if (str[i] == '\n' && str[i + 1] && str[i + 1] == '\n')
			ft_error();
		i++;
	}
	
}
int check_map(char **map)
{
	int i;
	char *p;
	char *p1;

	i = 0;
	while (map[i])
		i++;
	if (map[i - 1])
	{
		p = ft_strtrim(map[i - 1], " ");
		printf("p     = %c\n", p[ft_strchr2(p, '1')]);
		if (p && ft_strchr2(p, '1') && p[ft_strchr2(p, '1')] != ' ')
			ft_error();
		free(p);
	}
	p1 = ft_strtrim(map[0], " ");
	if (p1 && ft_strchr2(p1, '1') && p1[ft_strchr2(p1, '1')] != ' ')	
		ft_error();
	free(p1);
	return (0);
}
void	init_part_map(t_map *map)
{
	map->map1 = (char **) malloc(sizeof(char *) * (map->len - map->start + 1));
	if (map->map1 == NULL)
		ft_error();
	check_line(map->str);
	stor_to_map(*map);
	if (check_map(map->map1))
		ft_error();
}

void	init_infos(t_map *map, char **argv)
{
	map->str = check_before_map(argv[1]);
	map->map = ft_split(map->str, '\n');
	map->len = cmp_line(map->map);
	map->width = check_nbr_char(map->map);
	map->start = check_nbr_height(map->map);
	map->height = (map->len - map->start);
	map->player.rays = malloc(sizeof(t_ray) * NB_RAYS);
	if (!map->player.rays)
		ft_error();
	if (map->map == NULL)
		ft_error();
}

void	init_parse(t_map *map)
{
	get_map(map);
	check_texture_map(map);
	map_game(map->map1);
	map_game_full(*map);
	if (check_white_space(map))
	{
		write(2, "ERROR NOT VALID\n", 16);
		exit(0);
	}
}
