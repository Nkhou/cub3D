/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   function_util.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saboulal <saboulal@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 16:01:53 by saboulal          #+#    #+#             */
/*   Updated: 2024/01/27 13:29:03 by saboulal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub.h"

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i] != '\0')
		i++;
	return (i);
}

int	ft_strncmp(const char *f, const char *s, int len)
{
	int	i;

	i = 0;
	if ((!f || !s) && !len)
		return (0);
	while ((f[i] || s[i]) && i < len)
	{
		if (f[i] != s[i])
			return ((unsigned char )f[i] - (unsigned char )s[i]);
		i++;
	}
	return (0);
}

int	ft_isalpha(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	return (0);
}

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] && s2[i] && s1[i] == s2[i])
	{
		i++;
	}
	return (s1[i] - s2[i]);
}

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
	return (res);
}
