/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dimensions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksudyn <ksudyn@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 18:19:28 by ksudyn            #+#    #+#             */
/*   Updated: 2025/07/01 20:32:28 by ksudyn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	copy_map_lines(char ***old_map, char **new_map, int height)
{
	int	i;

	i = 0;
	while (i < height)
	{
		new_map[i] = (*old_map)[i];
		i++;
	}
	return (1);
}

int	update_map(char ***map, char **temp, char *line, int *height)
{
	copy_map_lines(map, temp, *height);
	if (*map)
		free(*map);
	temp[*height] = line;
	(*height)++;
	temp[*height] = NULL;
	*map = temp;
	return (1);
}

void	initialize_width(char *line, t_cub *cub)
{
	size_t	len;

	len = ft_strlen(line);
	if (line[len - 1] == '\n')
		cub->width = len - 1;
	else
		cub->width = len;
}

void	handle_map_error(char ***map, char *line)
{
	ft_error(9);
	if (*map)
		free_matrix(*map);
	free(line);
	exit(1);
}

int	dimensions(char *line, char ***map, int *height, t_cub *cub)
{
	char	**temp;

	if (!cub->width)
		initialize_width(line, cub);
	temp = ft_calloc(*height + 2, sizeof(char *));
	if (!temp)
	{
		handle_map_error(map, line);
		return (0);
	}
	return (update_map(map, temp, line, height));
}
