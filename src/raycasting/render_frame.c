/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_frame.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksudyn <ksudyn@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/15 19:37:36 by ksudyn            #+#    #+#             */
/*   Updated: 2025/08/15 21:21:46 by ksudyn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

t_collision	cast_ray_grid(t_cub *cub, float ray_dx, float ray_dy)
{
	t_collision	col;
	float	x;
	float	y;
	float	step = 0.05f; // tamaño del paso

	x = cub->player.x;
	y = cub->player.y;

	col.dist = 0;
	while (1)
	{
		if (check_collision(cub, x, y)) // tu función de colisión con muro
			break ;
		x += ray_dx * step;
		y += ray_dy * step;
		col.dist += step;
	}
	col.offset = (ray_dx != 0) ? fmod(y, CELL_SIZE) / CELL_SIZE
		: fmod(x, CELL_SIZE) / CELL_SIZE;
	col.direction = (ray_dx > 0) ? EAST : WEST; // simplificado
	return (col);
}

t_image *select_texture(t_cub *cub, int direction)
{
	if (direction == NORTH)
		return &cub->image[0];
	if (direction == SOUTH)
		return &cub->image[1];
	if (direction == EAST)
		return &cub->image[2];
	return &cub->image[3]; // WEST
}

void	draw_column_rec(t_cub *cub, int x, int y, int start_y, int section_height, t_image *tex, int texture_x)
{
	int	color;
	int	texture_y;

	if (y >= HEIGHT)
		return;

	if (y < start_y)
		put_pixel(cub->mlx, x, y, cub->textures->ceiling_rgb); // techo
	else if (y < start_y + section_height)
	{
		texture_y = ((y - start_y) * tex->height) / section_height;
		color = get_texture_pixel(tex, texture_x, texture_y);
		put_pixel(cub->mlx, x, y, color);
	}
	else
		put_pixel(cub->mlx, x, y, cub->textures->floor_rgb); // suelo

	draw_column_rec(cub, x, y + 1, start_y, section_height, tex, texture_x);
}

void	draw_vertical_section(t_cub *cub, int x, t_collision collision)
{
	int	section_height;
	int	start_y;
	t_image *tex;
    int texture_x;

	if (collision.dist == 0)
		collision.dist = 0.1f;

	section_height = (CELL_SIZE * HEIGHT) / collision.dist;
	start_y = (HEIGHT - section_height) / 2;
	if (start_y < 0)
		start_y = 0;

	tex = select_texture(cub, collision.direction);

    // Coordenada X de la textura según dónde golpeó el muro
	texture_x = (int)(collision.offset * tex->width);

	draw_column_rec(cub, x, 0, HEIGHT, tex, start_y, section_height);
}


void	render_frame(t_cub *cub)
{
	int			x;
	float		ray_angle;
	float		fov_step;
	t_collision	col;
	float		ray_dx;
	float		ray_dy;

	x = 0;
	fov_step = (float)FOV / WIDTH;
	while (x < WIDTH)
	{
		ray_angle = cub->player.angle - (FOV / 2) + (fov_step * x);
		ray_dx = cos(ray_angle);
		ray_dy = sin(ray_angle);
		col = cast_ray_grid(cub, ray_dx, ray_dy);
		col.dist *= cos(ray_angle - cub->player.angle);// fisheye
		draw_vertical_section(cub, x, col);
		x++;
	}
}
