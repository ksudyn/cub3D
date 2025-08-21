/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_move.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksudyn <ksudyn@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 18:08:16 by ksudyn            #+#    #+#             */
/*   Updated: 2025/08/21 18:53:59 by ksudyn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	move_forward(t_cub *cub, float speed)
{
	float	new_x;
	float	new_y;
	float	r;

	r = 6.0f;
	new_x = cub->player.x + cub->player.delta_x * speed;
	new_y = cub->player.y + cub->player.delta_y * speed;
	if (!check_collision_radius(cub, new_x, new_y, r))
	{
		cub->player.x = new_x;
		cub->player.y = new_y;
	}
}

void	move_backward(t_cub *cub, float speed)
{
	float	new_x;
	float	new_y;
	float	r;

	r = 6.0f;
	// Estás usando un radio r = 6.0f para evitar que el jugador atraviese paredes
	// y el cálculo de celdas está correcto.
	new_x = cub->player.x - cub->player.delta_x * speed;
	new_y = cub->player.y - cub->player.delta_y * speed;
	if (!check_collision_radius(cub, new_x, new_y, r))
	{
		cub->player.x = new_x;
		cub->player.y = new_y;
	}
}

void	move_left(t_cub *cub, float speed)
{
	float	new_x;
	float	new_y;
	float	r;

	r = 6.0f;
	new_x = cub->player.x + cub->player.delta_y * speed;
	new_y = cub->player.y - cub->player.delta_x * speed;
	if (!check_collision_radius(cub, new_x, new_y, r))
	{
		cub->player.x = new_x;
		cub->player.y = new_y;
	}
}

void	move_right(t_cub *cub, float speed)
{
	float	new_x;
	float	new_y;
	float	r;

	r = 6.0f;
	new_x = cub->player.x - cub->player.delta_y * speed;
	new_y = cub->player.y + cub->player.delta_x * speed;
	if (!check_collision_radius(cub, new_x, new_y, r))
	{
		cub->player.x = new_x;
		cub->player.y = new_y;
	}
}
// Calculan el desplazamiento en x y y usando trigonometría:
// Todas calculan la nueva posición del jugador en función de delta_x y delta_y (la dirección hacia donde mira).
// Antes de mover,llaman a check_collision_radius para asegurarse de que no chocarán con paredes.

// move_left y move_right intercambian dx y dy para hacer el “strafe” (desplazamiento lateral).
// r = 6.0f es el radio de colisión.

void	rotate_player(t_player *player, float angle)
{
	player->angle += angle;
	player->delta_x = cos(deg_to_rad(player->angle));
	player->delta_y = sin(deg_to_rad(player->angle));
	// Esto significa que delta_x y delta_y
	// representan la dirección hacia donde mira el jugador.
}

// Rota al jugador cambiando su ángulo.
// Calcula delta_x y delta_y que indican la dirección hacia donde mira.
// delta_x y delta_y se usan luego en los movimientos para saber hacia dónde moverse.
