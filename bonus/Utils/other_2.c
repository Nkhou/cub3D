/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   other_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saboulal <saboulal@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/28 19:46:26 by saboulal          #+#    #+#             */
/*   Updated: 2024/01/28 19:59:03 by saboulal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub.h"

void	check_pos_line_f(char *str, int i, t_tex *tex)
{
	if (str[i] == 'F' && str[i + 1] == ' ')
	{
		while (str[i] != '\n')
			i++;
		tex->f++;
	}
}

void	count_line_str(char *str, int i)
{
	while (str[i] == '\n' || str[i] == ' ')
		i++;
}

void	_norm(char *str, int i, t_tex *tex)
{
	count_line_str(str, i);
	check_pos_line_no(str, i, tex);
	check_pos_line_so(str, i, tex);
	check_pos_line_we(str, i, tex);
	check_pos_line_ea(str, i, tex);
}

void	_norm_1(char *str, int i)
{
	while (str[i] != '\n')
		i++;
}

void	check_pos_line_ea(char *str, int i, t_tex *tex)
{
	if (str[i] == 'E' && str[i + 1] == 'A')
	{
		check_retour(str, i);
		tex->ea++;
	}
}
