/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksudyn <ksudyn@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 15:33:05 by ksudyn            #+#    #+#             */
/*   Updated: 2025/09/01 17:27:46 by ksudyn           ###   ########.fr       */
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

int	is_texture_line(char *line)
{
	return (ft_strncmp(line, "NO", 2) == 0 || ft_strncmp(line, "SO", 2) == 0
		|| ft_strncmp(line, "WE", 2) == 0 || ft_strncmp(line, "EA", 2) == 0);
}

int	process_line(char **line_ptr, char ***map, int *height, t_cub *cub)
{
	char	*line;

	line = *line_ptr;
	remove_newline(line);
	if (line[0] == '\0')
	{
		if (cub->map_started)
			cub->map_finished = 1;
		free(line);
		return (1);
	}
	if (cub->map_finished)
		return (ft_error(8), free(line), 0);
	if (is_texture_line(line))
		parse_texture_line(line, cub);
	else if (line[0] == 'F' || line[0] == 'C')
		parse_color_line(line, cub);
	else
	{
		cub->map_started = 1;
		if (!dimensions(line, map, height, cub))
			return (free(line), free_matrix(*map), 0);
	}
	return (1);
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
		// printf("Leyendo línea del archivo: %s", line);
		if (!process_line(&line, &map, &height, cub))
			return (NULL);
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
	cub->map_started = 0;
	cub->map_finished = 0;
	map = read_map_lines(fd, cub);
	close(fd);
	if (!map || !map[0])
	{
		ft_error(8);
		return (NULL);
	}
	return (map);
}
