/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collision.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksudyn <ksudyn@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 18:01:12 by ksudyn            #+#    #+#             */
/*   Updated: 2025/08/13 20:19:19 by ksudyn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

char	get_map_cell(t_cub *cub, int grid_x, int grid_y)
{
	if (grid_y < 0 || grid_y >= cub->height)
		return (' ');
	if (grid_x < 0 || grid_x >= cub->width)
		return (' ');
	return (cub->map[grid_y][grid_x]);
}
// Devuelve el carácter del mapa en la celda (grid_x, grid_y).
// Si la coordenada está fuera del mapa, devuelve un espacio ' '.
// Esto permite consultar cualquier celda sin causar un error de acceso a memoria,
// y es la base para verificar colisiones o dibujar el mapa.

int	is_walkable_char(char c)
{
	return (c == '0' || c == 'N' || c == 'S' || c == 'E' || c == 'W');
}
// Determina si un carácter del mapa se puede caminar.
// '0' es suelo vacío, 'N', 'S', 'E', 'W' son posiciones de inicio del jugador.
// Lo usas para saber si el jugador puede moverse a una celda o si choca con un muro.

int	check_collision(t_cub *cub, float world_x, float world_y)
{
	int		grid_x;
	int		grid_y;
	char	tile;

	grid_x = (int)(world_x / (float)CELL_SIZE);
	grid_y = (int)(world_y / (float)CELL_SIZE);
	tile = get_map_cell(cub, grid_x, grid_y);
	if (is_walkable_char(tile))
		return (0);
	return (1);
}
//Convierte coordenadas del mundo (world_x, world_y) a coordenadas de celda (grid_x, grid_y).
//Esta función verifica si un punto (x, y) choca con un muro o está fuera del mapa.
//Devuelve true si hay colisión y false si se puede mover libremente.

int	check_collision_radius(t_cub *cub, float x, float y, float r)
{
	if (check_collision(cub, x - r, y - r))
		return (1);
	if (check_collision(cub, x + r, y - r))
		return (1);
	if (check_collision(cub, x - r, y + r))
		return (1);
	if (check_collision(cub, x + r, y + r))
		return (1);
	return (0);
}
// Comprueba colisiones para un círculo alrededor del jugador, no solo un punto.
// Esto evita que el jugador se “pegue” a las paredes.
// r es el radio de colisión del jugador