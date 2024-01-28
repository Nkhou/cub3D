/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   other_func.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saboulal <saboulal@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/28 18:54:18 by saboulal          #+#    #+#             */
/*   Updated: 2024/01/28 20:29:38 by saboulal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub.h"

void	check_line_a(char *str, t_tex *tex)
{
	int		i;

	i = 0;
	init_vaar(tex);
	while (str[i++])
	{
		_norm(str, i, tex);
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
	check_line_str(str, i);
	free(tex);
}

int	check_map(char **map)
{
	int		i;
	char	*p;
	char	*p1;

	i = 0;
	while (map[i])
		i++;
	if (map[i - 1])
	{
		p = ft_strtrim(map[i - 1], " ");
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

void	check_pos_line_no(char *str, int i, t_tex *tex)
{
	if (str[i] == 'N' && str[i + 1] == 'O')
	{
		check_retour(str, i);
		tex->no++;
	}
}

void	check_pos_line_so(char *str, int i, t_tex *tex)
{
	if (str[i] == 'S' && str[i + 1] == 'O')
	{
		check_retour(str, i);
		tex->so++;
	}
}

void	check_pos_line_we(char *str, int i, t_tex *tex)
{
	if (str[i] == 'W' && str[i + 1] == 'E')
	{
		check_retour(str, i);
		tex->we++;
	}
}
