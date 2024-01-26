/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saboulal <saboulal@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 16:13:40 by saboulal          #+#    #+#             */
/*   Updated: 2024/01/25 21:15:53 by saboulal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub.h"

size_t	ft_strlcpy(char *dest, char *src, size_t size)
{
	size_t	i;
	size_t	x;

	i = 0;
	x = ft_strlen(src);
	if (size == 0)
		return (x);
	while (src[i] && (i < size - 1))
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (x);
}

char	*ft_strdup_1( char	*str)
{
	int		i;
	int		len;
	char	*s;

	i = 0;
	len = ft_strlen(str);
	s = malloc (sizeof(char *) * len + 1);
	if (s == NULL)
		return (NULL);
	ft_strlcpy(s, str, len + 1);
	return (s);
}

char	*ft_substr(char *s, unsigned int start, size_t len)
{
	char			*sub;
	unsigned int	i;
	unsigned int	count;

	i = 0;
	if (!s)
		return (NULL);
	count = ft_strlen(s);
	if (start > count)
		return (ft_strdup_1(""));
	if (count <= start + len)
		len = count - start;
	sub = malloc(sizeof(char) * (len + 1));
	if (sub == NULL)
		return (NULL);
	while (s[start] && i < len)
	{
		sub[i] = s[start];
		i++;
		start++;
	}
	sub[i] = '\0';
	return (sub);
}
