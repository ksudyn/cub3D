/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_horiz.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksudyn <ksudyn@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 17:11:22 by ksudyn            #+#    #+#             */
/*   Updated: 2025/08/20 20:28:37 by ksudyn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

// Estas funciones calculan dónde choca un rayo con las líneas horizontales de la cuadrícula del mapa.
// Idea matemática
// Si el ángulo del rayo es hacia abajo (sin(angle) > 0),
// buscamos la primera intersección horizontal abajo del jugador.
// Si el ángulo es hacia arriba (sin(angle) < 0),
// buscamos la primera intersección horizontal arriba del jugador.
// Usamos trigonometría:
// Distancia vertical entre intersecciones = CELL_SIZE.
// Distancia horizontal correspondiente = CELL_SIZE / tan(angle).
// Avanzamos celda por celda hasta encontrar una pared o salir del mapa.

void	set_collision(t_collision *col, float dist, float offset, int dir)
{
	col->dist = dist;
	col->offset = offset;
	col->direction = dir;
}
//set_collision: Guarda en t_collision la distancia al impacto,
//el desplazamiento dentro del bloque (para texturas) y la dirección de la pared golpeada.

void	cast_row_ray_down(t_cub *cub, float angle, t_collision *hit)
{
	float	x;
    float y;
    float x_step;
    float y_step;

	y = floor(cub->player.y / CELL_SIZE) * CELL_SIZE + CELL_SIZE;
	x = cub->player.x + (y - cub->player.y) / tan(angle);
	y_step = CELL_SIZE;
	x_step = CELL_SIZE / tan(angle);
	while (1)
	{
		if (check_collision(cub, x, y))
		{
			set_collision(hit, sqrt(sqr(x - cub->player.x)
					+ sqr(y - cub->player.y)),
					fmod(x, CELL_SIZE) / CELL_SIZE, SOUTH);
			return ;
		}
		x += x_step;
		y += y_step;
	}
}
// cast_row_ray_down:
// Calcula el primer cruce horizontal abajo del jugador.
// Calcula los pasos en X y Y para saltar de línea horizontal en línea horizontal.
// Avanza hasta que check_collision detecta una pared.
// Guarda la información en hit

void	cast_row_ray_up(t_cub *cub, float angle, t_collision *hit)
{
	float	x, y, x_step, y_step;

	y = floor(cub->player.y / CELL_SIZE) * CELL_SIZE - 0.0001f;
	x = cub->player.x + (y - cub->player.y) / tan(angle);
	y_step = -CELL_SIZE;
	x_step = CELL_SIZE / tan(angle);
	while (1)
	{
		if (check_collision(cub, x, y))
		{
			set_collision(hit, sqrt(sqr(x - cub->player.x)
					+ sqr(y - cub->player.y)),
					fmod(x, CELL_SIZE) / CELL_SIZE, NORTH);
			return ;
		}
		x += x_step;
		y += y_step;
	}
}
//cast_row_ray_up: Igual que la anterior,
//pero buscando hacia arriba y restando un poco (-0.0001f)
//para evitar colisiones dobles en el mismo bloque.