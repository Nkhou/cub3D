/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Drawing_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saboulal <saboulal@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 16:57:44 by saboulal          #+#    #+#             */
/*   Updated: 2024/01/27 16:48:36 by saboulal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub.h"

void	get_draw(t_map *map, int tex)
{
	double	y;

	y = 0;
	while (y < HEIGHT)
	{
		if (tex == north || tex == south)
			mlx_pixel_put(map->mlx, map->win, map->x, y, map->color);
		y++;
	}
}
