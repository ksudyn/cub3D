/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_frame.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksudyn <ksudyn@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/15 19:37:36 by ksudyn            #+#    #+#             */
/*   Updated: 2025/08/21 19:35:19 by ksudyn           ###   ########.fr       */
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
	mlx_put_image_to_window(cub->mlx->mlx, cub->mlx->mlx_win,
		cub->mlx->img, 0, 0);
}
