/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saboulal <saboulal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 15:07:52 by saboulal          #+#    #+#             */
/*   Updated: 2023/12/01 15:34:58 by saboulal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

char	*ft_read(int fd, char *str)
{
	ssize_t	r;
	char	*buf;

	r = 1;
	while (r > 0 && ft_strchr(str) == 0)
	{
		buf = (char *) malloc((BUFFER_SIZE + 1) * sizeof(char));
		if (!buf)
			return (free(str), NULL);
		r = read(fd, buf, BUFFER_SIZE);
		if (r == -1)
			return (free(str), free(buf), NULL);
		if (r == 0)
			return (free(buf), str);
		buf[r] = '\0';
		str = ft_strjoin(str, buf);
		free(buf);
	}
	return (str);
}

char	*ft_get_line(char **str)
{
	int		i;
	char	*temp;
	char	*line;

	i = 0;
	if (ft_strchr(*str) == 0)
	{
		if (**str == '\0')
			return (NULL);
		return (temp = *str, *str = NULL, temp);
	}
	while ((*str)[i] != '\n')
		i++;
	line = (char *) malloc ((i + 2) * sizeof(char));
	if (!line)
		return (NULL);
	i = 0;
	while ((*str)[i] != '\n')
	{
		line[i] = (*str)[i];
		i++;
	}
	line[i++] = '\n';
	line[i] = '\0';
	return (line);
}

char	*ft_next_right(char *str)
{
	size_t	i;
	size_t	j;
	char	*right;

	i = 0;
	j = 0;
	if (!str || *str == '\0')
		return (free(str), NULL);
	while (str[i] != '\n' && str[i])
		i++;
	right = (char *) malloc((ft_strlen(str) - i) * sizeof(char));
	if (!right)
		return (free(str), NULL);
	i++;
	while (str[i])
	{
		right[j] = str[i];
		i++;
		j++;
	}
	right[j] = '\0';
	return (free(str), right);
}

char	*get_next_line(int fd)
{
	char				*buf;
	static char			*str = NULL;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	str = ft_read(fd, str);
	if (!str)
		return (NULL);
	buf = ft_get_line(&str);
	str = ft_next_right(str);
	return (buf);
}
