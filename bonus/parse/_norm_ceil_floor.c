/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _norm_ceil_floor.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saboulal <saboulal@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 15:16:00 by saboulal          #+#    #+#             */
/*   Updated: 2024/02/01 11:41:43 by saboulal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub.h"

int	ft_at(const char *str, int sgn)
{
	long	i;
	long	res;
	long	rv;

	i = 0;
	res = 0;
	while (str[i] >= '0' && str[i] <= '9' && str[i] != '\0')
	{
		rv = res;
		res = (res * 10) + (str[i] - '0');
		if (res / 10 != rv)
		{
			if (sgn == -1)
				return (0);
			return (-1);
		}
		i++;
	}
	if (str[i] && ft_isdigit(str[i]))
		ft_error();
	return (res);
}

void	check_pos_line_we(char *str, int *i, t_tex *tex)
{
	if (str[*i] == 'W' && str[*i + 1] == 'E')
	{
		check_retour(str, i);
		tex->we++;
	}
}

char	*ft_skip_1(char *map, char *p)
{
	int	i;

	i = 0;
	if (!map)
		ft_error();
	while (map[i])
	{
		if (map[i] == '\t')
			map[i] = ' ';
		i++;
	}
	if (p)
	{
		free(p);
		p = NULL;
	}
	p = ft_strtrim(map, " ");
	return (p);
}
