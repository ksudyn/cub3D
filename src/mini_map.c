/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksudyn <ksudyn@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 16:28:11 by ksudyn            #+#    #+#             */
/*   Updated: 2025/08/25 18:12:52 by ksudyn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

#define MINIMAP_SCALE 8 // Cada celda se verá como 8x8 píxeles
#define PLAYER_COLOR 0xFF0000// rojo
#define WALL_COLOR 0x444444// gris oscuro
#define FLOOR_COLOR 0xFFFFFF// blanco

void	draw_player_minimap(t_cub *cub)
{
	int	px;
	int	py;
	int	radius;
	int	dx;
	int	dy;

	px = (cub->player.x / CELL_SIZE) * MINIMAP_SCALE;
	py = (cub->player.y / CELL_SIZE) * MINIMAP_SCALE;
    // Convierte coordenadas del mundo (cub->player.x/y) a coordenadas de minimapa.
    // Se divide entre CELL_SIZE para obtener la celda del mapa,
    // luego se multiplica por MINIMAP_SCALE para convertirlo a píxeles del minimapa.
	radius = 3;
    // radius -> radio del círculo que representa al jugador.
	dy = -radius;
	while (dy <= radius)
	{
		dx = -radius;
		while (dx <= radius)
		{
			if (dx * dx + dy * dy <= radius * radius)
				put_pixel(cub, px + dx, py + dy, PLAYER_COLOR);
			dx++;
		}
		dy++;
	}
}

// px, py -> posición del jugador en píxeles en el minimapa.
// dx, dy -> offsets para dibujar cada pixel del círculo.
// Dibuja un círculo de radio 3 píxeles usando la ecuación 
// dx2 + dy2 ≤ radius2
// put_pixel pinta cada pixel rojo (PLAYER_COLOR) centrado en (px, py).
// Al final hay un círculo rojo en el minimapa representando al jugador

void	draw_player_direction(t_cub *cub)
{
	int	px;
	int	py;
	int	i;
	int	dx;
	int	dy;

	px = (cub->player.x / CELL_SIZE) * MINIMAP_SCALE;
	py = (cub->player.y / CELL_SIZE) * MINIMAP_SCALE;
    //convertimos coordenadas del jugador a píxeles del minimapa.
	i = 0;
	while (i < 7)//longitud de la flecha que indica dirección
	{
		dx = (int)(cub->player.delta_x * i);
		dy = (int)(cub->player.delta_y * i);
		put_pixel(cub, px + dx, py + dy, 0x00FF00);
		i++;
	}
}
// dx, dy incrementos para dibujar línea.
// cub->player.delta_x/y representan la dirección en la que mira el jugador.
// Se multiplica por i para crear una línea de píxeles que apunta hacia esa dirección.
// Pinta la línea de color verde 0x00FF00.

void	draw_square(t_cub *cub, int x, int y, int color)
{
	int	i;
	int	j;
	int	scale;

	scale = MINIMAP_SCALE;
	i = 0;
	while (i < scale)
	{
		j = 0;
		while (j < scale)
		{
			put_pixel(cub, x * scale + j, y * scale + i, color);
			j++;
		}
		i++;
	}
}
// Dibuja un cuadrado relleno de scale x scale píxeles.
// (x, y) son coordenadas de celda,
// se multiplican por MINIMAP_SCALE para convertir a píxeles.
// Usa doble bucle para recorrer todos los píxeles del cuadrado.
// color define si es pared (WALL_COLOR) o suelo (FLOOR_COLOR).

void	draw_minimap(t_cub *cub)
{
	int		y;
	int		x;
	char	cell;

	y = 0;
	while (y < cub->height)
	{
		x = 0;
		while (x < cub->width)
		{
			cell = cub->map[y][x];
			if (cell == '1')
				draw_square(cub, x, y, WALL_COLOR);
			else if (cell == '0' || cell == 'N' || cell == 'S' || cell == 'E'
				|| cell == 'W')
				draw_square(cub, x, y, FLOOR_COLOR);
			x++;
		}
		y++;
	}
	draw_player_minimap(cub);
	draw_player_direction(cub);
}

// x, y -> coordenadas de celda del mapa.
// cell -> carácter de la celda
// ('1' para pared, '0' para piso, 'N'/'S'/'E'/'W' para jugador).
// Recorre todo el mapa 2D.
// Dibuja cada celda:
// Pared -> gris.
// Piso / posición del jugador -> blanco.
// Se dibuja círculo rojo del jugador y su flecha verde de dirección sobre el minimapa.