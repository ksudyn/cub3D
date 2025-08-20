/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksudyn <ksudyn@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 19:17:33 by ksudyn            #+#    #+#             */
/*   Updated: 2025/08/20 18:22:11 by ksudyn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void init_player(t_cub *cub)
{
    cub->player.x = cub->player_x * CELL_SIZE + CELL_SIZE / 2;
    cub->player.y = cub->player_y * CELL_SIZE + CELL_SIZE / 2;

    // Inicializar ángulo según dirección
    if (cub->player_dir == 'N')
        cub->player.angle = 270; // hacia arriba
    else if (cub->player_dir == 'S')
        cub->player.angle = 90;  // hacia abajo
    else if (cub->player_dir == 'E')
        cub->player.angle = 0;   // hacia derecha
    else if (cub->player_dir == 'W')
        cub->player.angle = 180; // hacia izquierda

    cub->player.key_up = 0;
    cub->player.key_down = 0;
    cub->player.key_left = 0;
    cub->player.key_right = 0;
    cub->player.left_rotate = 0;
    cub->player.right_rotate = 0;

    cub->player.delta_x = cos(deg_to_rad(cub->player.angle));
    cub->player.delta_y = sin(deg_to_rad(cub->player.angle)); 
}


void	init_texture_paths(t_cub *cub)
{
	int	i;

	i = 0;
	while (i < NUM_TEXTURES)
	{
		cub->textures_path[i] = NULL;
		i++;
	}
}

void	init_struct(t_cub *cub)
{
	ft_bzero(cub, sizeof(t_cub));
	cub->textures = ft_calloc(1, sizeof(t_textures));
	cub->mlx = ft_calloc(1, sizeof(t_mlx));
	if (!cub->textures || !cub->mlx)
		exit(ft_error(9));
}

void	cleanup(t_cub *cub)
{
	int	i;

	i = 0;
	while (i < NUM_TEXTURES)
	{
		if (cub->textures_path[i])
		{
			free(cub->textures_path[i]);
			cub->textures_path[i] = NULL;
		}
		i++;
	}
	if (cub->textures)
	{
		free(cub->textures);
		cub->textures = NULL;
	}
	if (cub->mlx)
	{
		free(cub->mlx);
		cub->mlx = NULL;
	}
	if (cub->map)
	{
		free_matrix(cub->map);
		cub->map = NULL;
	}
}

int main(int argc, char **argv)
{
    t_cub cub;

    if (argc != 2)
        return (ft_error(10), EXIT_FAILURE);

    init_struct(&cub);               // mallocs y bzero
    init_texture_paths(&cub);        // inicializa paths a NULL

    // Cargar mapa y validar
    cub.map = load_map(argv[1], &cub);
    if (!cub.map)
        return (ft_putstr_fd("Error: No se pudo cargar el mapa.\n", 2), cleanup(&cub), EXIT_FAILURE);

    if (!validate_map(&cub))
        return (ft_putstr_fd("Mapa inválido.\n", 2), cleanup(&cub), EXIT_FAILURE);

    ft_putstr_fd("Mapa válido.\n", 1);
    // Inicializar jugador
    init_player(&cub);

    // Inicializar MLX, ventana, imagen, cargar texturas y hooks
    if (cub3d(&cub) != 0)
        return cleanup(&cub), EXIT_FAILURE;

    // Lanzar loop principal
    mlx_loop(cub.mlx->mlx);

    // Limpieza (opcional, nunca se llega a esta línea normalmente)
    cleanup(&cub);
    return EXIT_SUCCESS;
}
