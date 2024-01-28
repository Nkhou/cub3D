/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saboulal <saboulal@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 17:14:15 by saboulal          #+#    #+#             */
/*   Updated: 2024/01/28 17:53:56 by saboulal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub.h"

int	check_nub_line(char *path)
{
	int			i;
	int			fd;
	static char	*str;
	char		*line ;

	i = 0;
	fd = open(path, O_RDONLY);
	if (fd == -1)
	{
		ft_error();
		exit(0);
	}
	line = get_next_line(fd);
	while (line)
	{
		line = get_next_line(fd);
		str = ft_strjoin(str, line);
		i++;
		free(line);
	}
	close(fd);
	return (i);
}

int	check_exet(char *str, char *exe)
{
	int	len_all;
	int	len_exe;

	len_all = ft_strlen(str);
	len_exe = ft_strlen(exe);
	while (len_all > len_exe)
	{
		str++;
		len_all--;
	}
	return (ft_strncmp(str, exe, len_all));
}

char	*check_before_map(char *path)
{
	int		fd;
	char	*str;
	char	*line;

	fd = open(path, O_RDONLY);
	str = NULL;
	if (fd == -1)
		ft_error();
	line = get_next_line(fd);
	while (line)
	{
		str = ft_strjoin(str, line);
		free(line);
		line = NULL;
		line = get_next_line(fd);
	}
	close(fd);
	return (str);
}

void	check_texture_map(t_map *map)
{
	int	i;
	int	k;

	i = 0;
	k = 0;
	ft_north(map, i, k);
	ft_south(map, i, k);
	ft_west(map, i, k);
	ft_east(map, i, k);
	floor_(map);
	ceilling_(map);
}

void	check_rgb_ceil(t_map *map)
{
	int	i;

	i = 0;
	while (i < 3)
	{
		if ((map->ceil->r >= 0 && map->ceil->r <= 255)
			&& (map->ceil->g >= 0 && map->ceil->g <= 255)
			&& (map->ceil->b >= 0 && map->ceil->b <= 255))
			i++;
		else
			ft_error();
	}
}
