/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_frame.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksudyn <ksudyn@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/15 19:37:36 by ksudyn            #+#    #+#             */
/*   Updated: 2025/08/25 16:35:00 by ksudyn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	put_pixel(t_cub *cub, int x, int y, int color)
{
	char	*pixel;

	if (x < 0 || y < 0 || x >= WIDTH || y >= HEIGHT)
		return ;
	pixel = cub->mlx->data;
	pixel += y * cub->mlx->size_line;
	pixel += x * (cub->mlx->bpp / 8);
	*(unsigned int *)pixel = color;
}
//Coloca un pixel de color en la posición (x, y) de la imagen.
//Calcula en memoria dónde está ese pixel:
//size_line -> cuántos bytes ocupa una fila de la imagen.
//bpp / 8 -> cuántos bytes ocupa cada pixel (ej: 32 bits = 4 bytes).
//Protege contra posiciones fuera de rango (x, y fuera de la ventana).

t_image	set_texture(t_cub *cub, int direction)
{
	t_image	texture;

	if (direction == NORTH)
		texture = cub->image[NORTH];
	else if (direction == SOUTH)
		texture = cub->image[SOUTH];
	else if (direction == EAST)
		texture = cub->image[EAST];
	else
		texture = cub->image[WEST];
	return (texture);
}
//Devuelve la textura que corresponde según la dirección de la pared golpeada
//(NORTE, SUR, ESTE, OESTE).
//Si el rayo impactó en una pared del OESTE, se usará cub->image[WEST] para dibujarla.

int	map_pixel_from_texture(t_image texture, t_collision col, float v_offset)
{
	int	x;
	int	y;
	int	color;	

	x = texture.width * col.offset;
	y = texture.height * v_offset;	
	if (x < 0)
		x = 0;
	if (x >= texture.width)
		x = texture.width - 1;
	if (y < 0)
		y = 0;
	if (y >= texture.height)
		y = texture.height - 1;
	color = *(unsigned int *)(texture.data + y
			* texture.size_line + x * (texture.bpp / 8));
	return (color);
}
//Convierte un punto del mundo 3D proyectado en un pixel de la textura.
//col.offset -> desplazamiento horizontal en la textura
//v_offset -> desplazamiento vertical relativo (0 arriba, 1 abajo del muro proyectado).
//Multiplica por el tamaño de la textura,
// obtiene el (x, y) del pixel dentro de la textura.
//Devuelve el color exacto de ese pixel.
//Gracias a esto, la pared no se pinta con un solo color, sino con su textura real.

void	draw_vertical_section(t_cub *cub, int x, t_collision coll)
{
	int		i;
	int		section_size;
	int		start_height;
	t_image	texture;

	if (coll.direction == SOUTH)
		coll.offset = 1 - coll.offset;
	texture = set_texture(cub, coll.direction);
	if (coll.dist == 0)
		coll.dist = 0.1;
	section_size = (HEIGHT * CELL_SIZE) / coll.dist;
	start_height = (HEIGHT - section_size) / 2;
	i = 0;
	while (i < HEIGHT)
	{
		if (i < start_height)
			put_pixel(cub, x, i, rgb_to_int(cub->textures->ceiling_rgb));
		else if (i < start_height + section_size)
			put_pixel(cub, x, i, map_pixel_from_texture(texture, coll,
					(float)(i - start_height) / section_size));
		else
			put_pixel(cub, x, i, rgb_to_int(cub->textures->floor_rgb));
		i++;
	}
}
// Dibuja una columna vertical completa en la pantalla (correspondiente a un rayo).
// Divide la pantalla en 3 partes:
// Techo (ceiling): desde arriba hasta donde empieza la pared (start_height).
// Pared: un rectángulo centrado en la pantalla.
// La altura (section_size) se calcula con la distancia,
// cuanto más cerca está la pared, más alta se ve.
// Se rellena pixel a pixel con el color de la textura.
// Suelo (floor): desde el final de la pared hasta el final de la pantalla.
//Este es el paso que construye la ilusión 3D columna a columna.

void	render_frame(t_cub *cub)
{
	int		x;
	float	ray_angle;
	float	fov_step;
	t_collision	col;
	float		fov_rad;

	x = 0;
	fov_rad = deg_to_rad(FOV);
	fov_step = fov_rad / WIDTH;
	while (x < WIDTH)
	{
		ray_angle = deg_to_rad(cub->player.angle)
			- (fov_rad / 2.0) + (fov_step * x);
		col = cast_ray(cub, ray_angle);
		col.dist *= cos(ray_angle - deg_to_rad(cub->player.angle));// corrección de fisheye
		draw_vertical_section(cub, x, col);
		x++;
	}
	draw_minimap(cub);
	mlx_put_image_to_window(cub->mlx->mlx, cub->mlx->mlx_win,
		cub->mlx->img, 0, 0);
}
// Recorre todos los pixeles en el eje X (x = 0 hasta WIDTH).
// Para cada columna:
// Calcula el ángulo del rayo (ray_angle) según el campo de visión (FOV).
// Lanza un rayo (cast_ray) y obtiene dónde golpea la pared.
// Corrige la distancia con coseno, elimina la distorsión “ojo de pez”.
// Dibuja la columna (draw_vertical_section).
// Finalmente, manda la imagen completa a la ventana con mlx_put_image_to_window.

// Esto es el render loop 3D estilo Wolfenstein 3D:
// Cada columna de la pantalla corresponde a un rayo.
// La altura de la pared depende de la distancia.
// Texturas y colores de techo/suelo completan la escena.