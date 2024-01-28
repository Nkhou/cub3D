/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_util.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkhoudro <nkhoudro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 15:07:49 by saboulal          #+#    #+#             */
/*   Updated: 2024/01/28 15:22:28 by nkhoudro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub.h"

char	*ft_strjoin(char *left_str, char *buff)
{
	size_t	i;
	size_t	j;
	char	*str;
	size_t	lenleft;
	size_t	lsbuff;

	lenleft = ft_strlen(left_str);
	lsbuff = ft_strlen(buff);
	str = (char *) malloc(sizeof(char) * ((lenleft + lsbuff) + 1));
	if (str == NULL)
		return (free(left_str), NULL);
	i = -1;
	j = -1;
	while (++i < lenleft)
		str[i] = left_str[i];
	while (++j < lsbuff)
		str[i++] = buff[j];
	str[i] = '\0';
	if (left_str)
	{
		free(left_str);
		left_str = NULL;
	}
	return (str);
}

int	ft_strchr(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i] != '\0')
	{
		if (str[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}
int	ft_strchr2(char *str, char c)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i] != '\0')
	{
		if (str[i] != c)
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strdup(char *str)
{
	int		i;
	int		len;
	char	*s;

	if (str == NULL)
		return (NULL);
	i = 0;
	len = ft_strlen(str);
	s = (char *) malloc ((len + 1) * sizeof(char));
	if (s == NULL)
		return (NULL);
	while (str[i])
	{
		s[i] = str[i];
		i++;
	}
	s[i] = '\0';
	return (s);
}
