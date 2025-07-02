/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksudyn <ksudyn@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 15:33:05 by ksudyn            #+#    #+#             */
/*   Updated: 2025/07/02 15:40:18 by ksudyn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	remove_newline(char *line)
{
	int	len;

	len = ft_strlen(line);
	if (len > 0 && line[len - 1] == '\n')
		line[len - 1] = '\0';
}

char	**read_map_lines(int fd, t_cub *cub)
{
	char	*line;
	char	**map;
	int		height;

	map = NULL;
	height = 0;
	line = get_next_line(fd);
	while (line)
	{
		remove_newline(line);
		if (!dimensions(line, &map, &height, cub))
		{
			free(line);
			free_matrix(map);
			return (NULL);
		}
		line = get_next_line(fd);
	}
	cub->height = height;
	return (map);
}

char	**load_map(const char *file, t_cub *cub)
{
	int		fd;
	char	**map;

	fd = open(file, O_RDONLY);
	if (fd == -1)
	{
		ft_error(2);
		return (NULL);
	}
	map = read_map_lines(fd, cub);
	close(fd);
	if (!map || !map[0])
	{
		ft_error(8);
		return (NULL);
	}
	return (map);
}
