/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_cast.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksudyn <ksudyn@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 17:30:36 by ksudyn            #+#    #+#             */
/*   Updated: 2025/08/22 19:53:20 by ksudyn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

// Estas dos funciones (init_collision y cast_ray)
// son responsables de lanzar un rayo desde el jugador
// y detectar contra qué pared choca primero
// y asi poder dibujar correctamente las paredes en 3D.

void	init_collision(t_collision *col)
{
	col->dist = 1e30; // Sirve como “infinito”,
			// cualquier colisión real será más cercana y reemplazará este valor
	col->offset = 0; // Inicialización segura:
			// aún no hay impacto, así que el offset no importa.
	col->direction = -1; // Significa “sin dirección todavía”;
			// cualquier dirección válida (NORTE, SUR, ESTE, OESTE) sobrescribirá esto
}

t_collision	cast_ray(t_cub *cub, float ray_angle)
{
	t_collision	hit_h;
	t_collision	hit_v;
	t_collision	final;

	init_collision(&hit_h);
	init_collision(&hit_v);
	init_collision(&final);
	ray_angle = fmod(ray_angle, 2 * M_PI);
	if (ray_angle < 0)
		ray_angle += 2 * M_PI;
	if (ray_angle > 0 && ray_angle < M_PI)
		cast_row_ray_down(cub, ray_angle, &hit_h);
	else
		cast_row_ray_up(cub, ray_angle, &hit_h);
	if (ray_angle < M_PI / 2 || ray_angle > 3 * M_PI / 2)
		cast_column_ray_right(cub, ray_angle, &hit_v);
	else
		cast_column_ray_left(cub, ray_angle, &hit_v);
	if (hit_h.dist < hit_v.dist)
		final = hit_h;
	else
		final = hit_v;
	return (final);
}
//Aquí se inicializan las colisiones
// hit_h hace el impacto contra una línea horizontal del grid
// (pared detectada arriba o abajo).
// hit_v → impacto contra una línea vertical del grid
// (pared detectada a izquierda o derecha).

// ray_angle normaliza el ángulo del rayo (0 a 2π),
// para que siempre esté en el rango correcto.

// Lanza un rayo horizontal:
// Si el ángulo está entre 0 y π, el rayo apunta hacia abajo (cast_row_ray_down).
// Si no → apunta hacia arriba (cast_row_ray_up).

// Lanza un rayo vertical:
// Si el ángulo está entre 0 y π/2 o mayor a 3π/2,
// apunta hacia la derecha (cast_column_ray_right).
// Si no → apunta hacia la izquierda (cast_column_ray_left).

// Compara distancias (hit_h.dist vs hit_v.dist).
// El más pequeño es la pared real más cercana que el rayo golpea.
// Se guarda en final y se devuelve.