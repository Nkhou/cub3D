/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   direction.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkhoudro <nkhoudro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 21:07:07 by nkhoudro          #+#    #+#             */
/*   Updated: 2024/01/26 13:22:54 by nkhoudro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub.h"

int	distance_between_points(double x1, double y1, double x2, double y2)
{
	return (sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2)));
}

int	israyfacingdown(double rayangle)
{
	return (sin(rayangle) > 0);
}

int	israyfacingup(double rayangle)
{
	return (!israyfacingdown(rayangle));
}

int	israyfacingright(double rayangle)
{
	return (cos(rayangle) > 0);
}

int	israyfacingleft(double rayangle)
{
	return (!israyfacingright(rayangle));
}
