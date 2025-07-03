/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksudyn <ksudyn@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 20:10:59 by ksudyn            #+#    #+#             */
/*   Updated: 2025/07/03 16:58:43 by ksudyn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	load_textures(t_cub *cub)
{
	int	w;
	int	h;

	cub->textures->north = mlx_xpm_file_to_image(cub->mlx->mlx, T_NORTH, &w, &h);
	cub->textures->south = mlx_xpm_file_to_image(cub->mlx->mlx, T_SOUTH, &w, &h);
	cub->textures->east = mlx_xpm_file_to_image(cub->mlx->mlx, T_EAST, &w, &h);
	cub->textures->west = mlx_xpm_file_to_image(cub->mlx->mlx, T_WEST, &w, &h);

	if (!cub->textures->north || !cub->textures->south ||
		!cub->textures->east || !cub->textures->west)
	{
		ft_error_mlx(2);
		exit(EXIT_FAILURE);
	}
}


