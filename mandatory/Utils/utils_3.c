/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saboulal <saboulal@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 21:28:28 by saboulal          #+#    #+#             */
/*   Updated: 2024/01/26 21:35:50 by saboulal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub.h"

int	ft_atoi(const char *str)
{
	long	i;
	long	sgn;
	long	res;

	i = 0;
	sgn = 1;
	res = 0;
	while ((str[i] > 8 && str[i] < 14) || (str[i] == ' '))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sgn *= (-1);
		i++;
	}
	res = ft_at(str + i, sgn);
	return (res * sgn);
}

char	*ft_strchr_1(const char *s, int c)
{
	size_t	i;
	char	*p;

	i = 0;
	p = (char *)s;
	while (p[i])
	{
		if (p[i] == (char)c)
		{
			return (p + i);
		}
		i++;
	}
	if (p[i] == '\0' && (char)c == '\0')
		return (&p[i]);
	return (NULL);
}

void	ft_error(void)
{
	write(2, "Error\n", 6);
	exit(0);
}

void	ft_free(char **p)
{
	int	i;

	i = 0;
	while (p[i])
	{
		free(p[i]);
		i++;
	}
	free(p);
}