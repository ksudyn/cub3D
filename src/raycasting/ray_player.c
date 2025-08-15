/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_player.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksudyn <ksudyn@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 16:48:58 by ksudyn            #+#    #+#             */
/*   Updated: 2025/08/15 20:53:24 by ksudyn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	key_press_hook(int keycode, t_cub *cub)
{
	if (keycode == KEY_LEFT)
		cub->player.left_rotate = 1;
	else if (keycode == KEY_RIGHT)
		cub->player.right_rotate = 1;
	else if (keycode == KEY_W)
		cub->player.key_up = 1;
	else if (keycode == KEY_A)
		cub->player.key_left = 1;
	else if (keycode == KEY_S)
		cub->player.key_down = 1;
	else if (keycode == KEY_D)
		cub->player.key_right = 1;
	else if (keycode == KEY_ESC)
		safe_exit(cub);
	return (0);
}

int	key_release_hook(int keycode, t_cub *cub)
{
	if (keycode == KEY_LEFT)
		cub->player.left_rotate = 0;
	else if (keycode == KEY_RIGHT)
		cub->player.right_rotate = 0;
	else if (keycode == KEY_W)
		cub->player.key_up = 0;
	else if (keycode == KEY_A)
		cub->player.key_left = 0;
	else if (keycode == KEY_S)
		cub->player.key_down = 0;
	else if (keycode == KEY_D)
		cub->player.key_right = 0;
	return (0);
}

int	main_loop(t_cub *cub)
{
	float	speed = 2.0f;
	float	rot_speed = 0.05f;

	if (cub->player.left_rotate)
		rotate_player(&cub->player, -rot_speed);
	if (cub->player.right_rotate)
		rotate_player(&cub->player, rot_speed);
	if (cub->player.key_up)
		move_forward(cub, speed);
	if (cub->player.key_down)
		move_forward(cub, -speed);
	if (cub->player.key_left)
		move_left(cub, speed);
	if (cub->player.key_right)
		move_right(cub, speed);

    render_frame(cub);
	return (0);
}

void	init_hooks(t_cub *cub)
{
	mlx_hook(cub->mlx->mlx_win, ON_DESTROY, NO_EVENT_MASK, safe_exit, cub);
	mlx_hook(cub->mlx->mlx_win, ON_KEYDOWN, KEY_PRESS_MASK, key_press_hook, cub);
	mlx_hook(cub->mlx->mlx_win, ON_KEYUP, KEY_RELEASE_MASK, key_release_hook, cub);
	mlx_loop_hook(cub->mlx->mlx, main_loop, cub);
}
