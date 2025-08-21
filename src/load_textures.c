/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksudyn <ksudyn@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 20:10:59 by ksudyn            #+#    #+#             */
/*   Updated: 2025/08/21 19:26:34 by ksudyn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	load_textures(t_cub *cub)
{
	int	i;

	if (cub->textures == NULL)
		return (printf("Error: cub->textures no está inicializado.\n"), 1);
	i = -1;
	while (++i < NUM_TEXTURES)
	{
		if (!cub->textures_path[i])
			return (ft_error_mlx(2), 1);
		cub->image[i].img = mlx_xpm_file_to_image(cub->mlx->mlx,
				cub->textures_path[i], &cub->image[i].width,
				&cub->image[i].height);
		if (!cub->image[i].img)
			return (ft_error_mlx(2), 1);
		cub->image[i].data = mlx_get_data_addr(cub->image[i].img,
				&cub->image[i].bpp, &cub->image[i].size_line,
				&cub->image[i].endian);
		if (!cub->image[i].data)
			return (ft_error_mlx(2), 1);
        printf("Textura %d: %dx%d bpp=%d, size_line=%d, endian=%d\n",
       i,
       cub->image[i].width,
       cub->image[i].height,
       cub->image[i].bpp,
       cub->image[i].size_line,
       cub->image[i].endian);
	}
	cub->textures->north = cub->image[0].img;
	cub->textures->south = cub->image[1].img;
	cub->textures->east = cub->image[2].img;
	cub->textures->west = cub->image[3].img;
	return (0);
}
