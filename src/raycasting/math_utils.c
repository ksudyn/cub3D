/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksudyn <ksudyn@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 18:00:06 by ksudyn            #+#    #+#             */
/*   Updated: 2025/08/15 19:38:07 by ksudyn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

float	deg_to_rad(float deg)
{
	return (deg * M_PI / 180);
}
// deg_to_rad: Convierte grados a radianes, necesario porque sin y cos en C usan radianes.

float	sqr(float n)
{
	return (n * n);
}
// sqr: Devuelve el cuadrado de un número, usado para calcular distancias.

void	put_pixel(t_mlx *mlx, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT)
		return ;
	dst = mlx->data + (y * mlx->size_line + x * (mlx->bpp / 8));
	*(unsigned int *)dst = color;
}
// Dibuja un píxel en la pantalla en (x, y) con un color dado.
// Comprueba límites para no escribir fuera de la memoria de la imagen.
// Es la base para cualquier render 2D que hagas con MiniLibX.

int	safe_exit(t_cub *cub)
{
	int	i;

	i = 0;
	while (i < NUM_TEXTURES)
	{
		if (cub->image[i].img)
			mlx_destroy_image(cub->mlx->mlx, cub->image[i].img);
		i++;
	}
	if (cub->mlx->mlx_win)
		mlx_destroy_window(cub->mlx->mlx, cub->mlx->mlx_win);
	if (cub->mlx->mlx)
	{
		mlx_destroy_display(cub->mlx->mlx);
		free(cub->mlx->mlx);
	}
	exit(0);
}
