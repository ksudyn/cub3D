/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_player.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksudyn <ksudyn@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 16:48:58 by ksudyn            #+#    #+#             */
/*   Updated: 2025/09/01 17:27:21 by ksudyn           ###   ########.fr       */
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
//Esta función se llama automáticamente cuando presionas una tecla.
//En lugar de mover al jugador directamente aquí,
//lo que hace es marcar una bandera (1) en la estructura cub->player.
//Ejemplo: si presionas W, se activa cub->player.key_up = 1;.
//Esto permite que el movimiento sea continuo mientras la tecla esté pulsada,
//y no un solo "paso" por pulsación

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
//Esta función se llama cuando suelta la tecla.
//Quita la bandera poniendo 0.
//Ejemplo: cuando sueltas W, se desactiva cub->player.key_up.
//Así el bucle principal sabe cuándo parar el movimiento.

int	main_loop(t_cub *cub)
{
	float	speed;
	float	rot_speed;

	rot_speed = 4.0f;
	// Esto es la velocidad de rotacion por frame.
	// Cuanto mas alto mas rapido rotará.
	speed = 4.0f;
	// Esto es la velocidad de moviemiento por frame.
	// Cuanto mas alto mas rapido se movera.
	if (cub->player.left_rotate)
		rotate_player(&cub->player, -rot_speed);
	if (cub->player.right_rotate)
		rotate_player(&cub->player, rot_speed);
	if (cub->player.key_up)
		move_forward(cub, speed);
	if (cub->player.key_down)
		move_backward(cub, speed);
	if (cub->player.key_left)
		move_left(cub, speed);
	if (cub->player.key_right)
		move_right(cub, speed);
	render_frame(cub);
	return (0);
}
//Este es el bucle de juego principal.
//Se ejecuta en cada frame (gracias a mlx_loop_hook).
//Lee las banderas que pusimos en key_press_hook y key_release_hook.
//Si cub->player.key_up == 1, llama a move_forward.
//Si cub->player.left_rotate == 1, rota al jugador a la izquierda, etc.
//Finalmente, llama a render_frame(cub) para dibujar la nueva escena en pantalla.
//Aquí se aplican los movimientos/rotaciones reales en base a las teclas presionadas.

void	init_hooks(t_cub *cub)
{
	mlx_hook(cub->mlx->mlx_win, ON_DESTROY, NO_EVENT_MASK, safe_exit, cub);
	mlx_hook(cub->mlx->mlx_win, ON_KEYDOWN, KEY_PRESS_MASK, key_press_hook,
		cub);
	mlx_hook(cub->mlx->mlx_win, ON_KEYUP, KEY_RELEASE_MASK, key_release_hook,
		cub);
	mlx_loop_hook(cub->mlx->mlx, main_loop, cub);
}
//Aquí se registran los hooks (eventos) de la librería minilibx.
//mlx_hook escucha eventos específicos en la ventana:
//ON_KEYDOWN → llama a key_press_hook.
//ON_KEYUP → llama a key_release_hook.
//ON_DESTROY → cierra la ventana (safe_exit).
//mlx_loop_hook → ejecuta main_loop en cada frame (mientras el programa corre).
