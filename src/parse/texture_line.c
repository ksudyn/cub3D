/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_line.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksudyn <ksudyn@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 16:20:13 by ksudyn            #+#    #+#             */
/*   Updated: 2025/07/07 17:54:48 by ksudyn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	check_texture_format(char **split)
{
	if (!split || !split[0] || !split[1] || split[2])
	{
		free_matrix(split);
		ft_error(8); // Invalid map
		return (0);
	}
	return (1);
}
//Verifica que la línea tenga solo 2 partes (ID ruta) y no más.

int	set_texture_path(char **split, t_cub *cub)
{
	if (!ft_strncmp(split[0], "NO", 3))
	{
		if (cub->textures_path[NORTH])
			return (ft_error(8));
		cub->textures_path[NORTH] = ft_strdup(split[1]);
	}
	else if (!ft_strncmp(split[0], "SO", 3))
	{
		if (cub->textures_path[SOUTH])
			return (ft_error(8));
		cub->textures_path[SOUTH] = ft_strdup(split[1]);
	}
	else if (!ft_strncmp(split[0], "WE", 3))
	{
		if (cub->textures_path[WEST])
			return (ft_error(8));
		cub->textures_path[WEST] = ft_strdup(split[1]);
	}
	else if (!ft_strncmp(split[0], "EA", 3))
	{
		if (cub->textures_path[EAST])
			return (ft_error(8));
		cub->textures_path[EAST] = ft_strdup(split[1]);
	}
	else
		return (ft_error(6)); // Invalid identifier
	return (0);
}
//Asigna la ruta a la textura adecuada según el identificador (NO, SO, etc.).


void	parse_texture_line(char *line, t_cub *cub)
{

	char	**split;

	split = ft_split(line, ' ');
	if (!check_texture_format(split))
		exit(1);
	if (set_texture_path(split, cub))
	{
		free_matrix(split);
		exit(1);
	}
	free_matrix(split);
}
//Función principal que llama a las anteriores.