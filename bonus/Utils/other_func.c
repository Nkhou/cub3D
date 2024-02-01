/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   other_func.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saboulal <saboulal@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/28 18:54:18 by saboulal          #+#    #+#             */
/*   Updated: 2024/02/01 11:41:12 by saboulal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub.h"

void	check_line_a(char *str, t_tex *tex, t_map *map)
{
	int		i;

	i = 0;
	while (str[i++])
	{
		_norm(str, &i, tex);
		if (str[i] == 'C' && str[i + 1] == ' ')
		{
			while (str[i] != '\n')
				i++;
			tex->c++;
		}
		if (str[i] == 'F' && str[i + 1] == ' ')
		{
			while (str[i] != '\n')
				i++;
			tex->f++;
		}
		check_wesfc(tex);
		if (str[i] == '1')
			break ;
	}
	check_line_str(str, &i, map);
}

void	check_last_line(char *p)
{
	int	i;

	i = 0;
	if (!p)
		ft_error();
	while (p[i])
	{
		if (p[i] != '1' && p[i] != ' ')
			ft_error();
		i++;
	}
}

int	check_map(char **map)
{
	int		i;
	char	*p;
	char	*p1;

	i = 0;
	if (!map)
		ft_error();
	while (map[i])
		i++;
	if (i > 0 && map[i - 1])
	{
		p = ft_strtrim(map[i - 1], " ");
		if (p && ft_strchr2(p, '1') && p[ft_strchr2(p, '1')] != ' ')
			ft_error();
		free(p);
	}
	p1 = ft_strtrim(map[0], " ");
	check_last_line(p1);
	free(p1);
	return (0);
}

void	check_pos_line_no(char *str, int *i, t_tex *tex)
{
	if (str[*i] == 'N' && str[*i + 1] == 'O')
	{
		check_retour(str, i);
		tex->no++;
	}
}

void	check_pos_line_so(char *str, int *i, t_tex *tex)
{
	if (str[*i] == 'S' && str[*i + 1] == 'O')
	{
		check_retour(str, i);
		tex->so++;
	}
}
