/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_vert.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksudyn <ksudyn@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 17:15:01 by ksudyn            #+#    #+#             */
/*   Updated: 2025/08/14 17:20:22 by ksudyn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	cast_column_ray_right(t_cub *cub, float angle, t_collision *hit)
{
	float	x, y, x_step, y_step;

	x = floor(cub->player.x / CELL_SIZE) * CELL_SIZE + CELL_SIZE;
	y = cub->player.y + (x - cub->player.x) * tan(angle);
	x_step = CELL_SIZE;
	y_step = CELL_SIZE * tan(angle);
	while (1)
	{
		if (check_collision(cub, x, y))
		{
			set_collision(hit, sqrt(sqr(x - cub->player.x)
					+ sqr(y - cub->player.y)),
					fmod(y, CELL_SIZE) / CELL_SIZE, EAST);
			return ;
		}
		x += x_step;
		y += y_step;
	}
}
// cast_column_ray_right:
// Calcula el primer cruce vertical a la derecha del jugador.
// Calcula pasos en X y Y para ir de pared vertical en pared vertical.
// Avanza hasta que encuentra un muro.
// Guarda la colisión con dirección EAST y offset basado en y.

void	cast_column_ray_left(t_cub *cub, float angle, t_collision *hit)
{
	float	x, y, x_step, y_step;

	x = floor(cub->player.x / CELL_SIZE) * CELL_SIZE - 0.0001f;
	y = cub->player.y + (x - cub->player.x) * tan(angle);
	x_step = -CELL_SIZE;
	y_step = CELL_SIZE * tan(angle);
	while (1)
	{
		if (check_collision(cub, x, y))
		{
			set_collision(hit, sqrt(sqr(x - cub->player.x)
					+ sqr(y - cub->player.y)),
					fmod(y, CELL_SIZE) / CELL_SIZE, WEST);
			return ;
		}
		x += x_step;
		y += y_step;
	}
}
//cast_column_ray_left: Igual pero hacia la izquierda,
//usando -CELL_SIZE y un pequeño -0.0001f para no chocar dos veces en el mismo bloque
