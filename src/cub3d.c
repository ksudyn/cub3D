/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksudyn <ksudyn@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 16:01:22 by ksudyn            #+#    #+#             */
/*   Updated: 2025/07/09 16:43:33 by ksudyn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int     cub3d(t_cub *cub)
{
    cub->mlx->mlx = mlx_init();
    if(!cub->mlx->mlx)
        return(ft_error_mlx (1));
    cub->mlx->mlx_win = mlx_new_window(cub->mlx->mlx, WIDTH, HEIGHT, "CUB3D");
    if (!cub->mlx->mlx_win)
        return( free(cub->mlx->mlx), ft_error_mlx (1));
    cub->mlx->img = mlx_new_image(cub->mlx->mlx, WIDTH, HEIGHT);
    //Crea una imagen en memoria (off-screen) donde se va a dibujar el juego.
    //No se dibuja directamente en la ventana para evitar parpadeos (double buffering).
    cub->mlx->data = mlx_get_data_addr(cub->mlx->img, &cub->mlx->bpp,
                    &cub->mlx->size_line, &cub->mlx->endian);



    if(load_textures(cub) == 1)
        return(1);
    mlx_put_image_to_window(cub->mlx->mlx, cub->mlx->mlx_win,
            cub->mlx->img, 0, 0);
    mlx_loop(cub->mlx->mlx);
    return(0);
}