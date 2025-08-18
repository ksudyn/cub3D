/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksudyn <ksudyn@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 20:10:59 by ksudyn            #+#    #+#             */
/*   Updated: 2025/08/18 20:20:51 by ksudyn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

// void	load_textures(t_cub *cub)
// {
// 	int	w;
// 	int	h;

// 	cub->textures->north = mlx_xpm_file_to_image(cub->mlx->mlx, T_NORTH, &w,&h);
// 	cub->textures->south = mlx_xpm_file_to_image(cub->mlx->mlx, T_SOUTH, &w,&h);
// 	cub->textures->east = mlx_xpm_file_to_image(cub->mlx->mlx, T_EAST, &w, &h);
// 	cub->textures->west = mlx_xpm_file_to_image(cub->mlx->mlx, T_WEST, &w, &h);

// 	if (!cub->textures->north || !cub->textures->south ||
// 		!cub->textures->east || !cub->textures->west)
// 	{
// 		ft_error_mlx(2);
// 		exit(EXIT_FAILURE);
// 	}
// }

// int	load_textures(t_cub *cub)
// {
// 	int	i;

// 	i = 0;
// 	while (i < NUM_TEXTURES)
// 	{
// 		printf("Loading texture %d: %s\n", i, cub->textures_path[i]);
// 		cub->image[i].img = mlx_xpm_file_to_image(cub->mlx,
// 				cub->textures_path[i], &cub->image[i].width,
// 				&cub->image[i].height);
// 		if (!cub->image[i].img)
// 		{
// 			printf("Error cargando textura %d (%s)\n", i, cub->textures_path[i]);
// 			//ft_putstr_fd("Error: textura no encontrada.\n", 2);
// 			return (1);
// 		}
// 		cub->image[i].data = mlx_get_data_addr(cub->image[i].img,
// 				&cub->image[i].bpp, &cub->image[i].size_line,
// 				&cub->image[i].endian);
// 		printf("Texture %d loaded: img=%p, data=%p\n", i, cub->image[i].img, cub->image[i].data);
// 		i++;
// 	}
// 	return (0);
// }

int load_textures(t_cub *cub)
{
    int i;
	
	i = 0;
    while (i < NUM_TEXTURES)
    {
        if (!cub->textures_path[i])
            return (ft_error_mlx(2), 1);
        cub->image[i].img = mlx_xpm_file_to_image(cub->mlx->mlx,
                                                 cub->textures_path[i],
                                                 &cub->image[i].width,
                                                 &cub->image[i].height);
        if (!cub->image[i].img)
			return (ft_error_mlx(2), 1);
        cub->image[i].data = mlx_get_data_addr(cub->image[i].img,
                                              &cub->image[i].bpp,
                                              &cub->image[i].size_line,
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

		i++;
    }
    cub->textures->north = cub->image[0].img;
    cub->textures->south = cub->image[1].img;
    cub->textures->east  = cub->image[2].img;
    cub->textures->west  = cub->image[3].img;
	return (0);
}
