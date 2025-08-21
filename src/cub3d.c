/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksudyn <ksudyn@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 16:01:22 by ksudyn            #+#    #+#             */
/*   Updated: 2025/08/21 19:03:09 by ksudyn           ###   ########.fr       */
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
    if (!cub->mlx->img)
        return ft_error_mlx(1);
    //Crea una imagen en memoria (off-screen) donde se va a dibujar el juego.
    //No se dibuja directamente en la ventana para evitar parpadeos (double buffering).
    cub->mlx->data = mlx_get_data_addr(cub->mlx->img, &cub->mlx->bpp,
                                    &cub->mlx->size_line, &cub->mlx->endian);
    if (!cub->mlx->data)
        return ft_error_mlx(1);
    if(load_textures(cub) == 1)
        return(1);
        // Inicializa hooks (teclas, cerrar ventana, loop)
    init_hooks(cub);

    return 0; // cub3d completó la inicialización
}

