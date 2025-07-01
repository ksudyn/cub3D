/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksudyn <ksudyn@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 17:59:42 by ksudyn            #+#    #+#             */
/*   Updated: 2025/07/01 19:16:58 by ksudyn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_free(char **str)
{
	free(*str);
	*str = NULL;
	return (NULL);
}

char	*readfd(int fd, char *rest)
{
	int		bts_read;
	char	*buffer;

	bts_read = 1;
	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (buffer == NULL)
		return (ft_free(&rest));
	buffer[0] = '\0';
	while (bts_read > 0 && ft_strchr(buffer, '\n') == NULL)
	{
		bts_read = read(fd, buffer, BUFFER_SIZE);
		if (bts_read > 0)
		{
			buffer[bts_read] = '\0';
			rest = ft_strjoin(rest, buffer);
		}
	}
	free(buffer);
	if (bts_read == -1)
		return (ft_free(&rest));
	return (rest);
}

char	*next_line(char *res)
{
	char	*next;
	char	*temp;
	int		len;

	temp = ft_strchr(res, '\n');
	if (temp == NULL)
	{
		next = NULL;
		return (ft_free(&res));
	}
	else
	{
		len = (temp - res) + 1;
	}
	if (res[len] == '\0')
		return (ft_free(&res));
	next = ft_substr(res, len, ft_strlen(res) - len);
	ft_free(&res);
	if (next == NULL)
		return (NULL);
	return (next);
}

char	*get_next_line(int fd)
{
	static char	*rest;
	char		*temp;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (rest == NULL || (rest != NULL && ft_strchr(rest, '\n') == NULL))
		rest = readfd(fd, rest);
	if (rest == NULL)
		return (NULL);
	temp = ft_strchr(rest, '\n');
	line = ft_substr(rest, 0, (temp - rest) + 1);
	if (line == NULL)
		return (ft_free(&rest));
	rest = next_line(rest);
	return (line);
}
