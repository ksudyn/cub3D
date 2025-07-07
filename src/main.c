/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksudyn <ksudyn@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 19:17:33 by ksudyn            #+#    #+#             */
/*   Updated: 2025/07/07 20:40:38 by ksudyn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

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
	int i;
	
	i = 0;
	while (i < NUM_TEXTURES) // Cambia 5 por el número de texturas que tengas
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


int	main(int argc, char **argv)
{
	t_cub 	cub;

	if (argc != 2)
	{
		ft_error(10);
		return (EXIT_FAILURE);
	}
	init_struct(&cub);

	// Cargar mapa y altura
	cub.map = load_map(argv[1], &cub);
	if (!cub.map)
	{
		ft_putstr_fd("Error: No se pudo cargar el mapa.\n", 2);
		cleanup(&cub);
		return (EXIT_FAILURE);
	}

	// Validar mapa
	if (!validate_map(&cub))
	{
		ft_putstr_fd("Mapa inválido.\n", 2);
		cleanup(&cub);
		return (EXIT_FAILURE);
	}

	ft_putstr_fd("Mapa válido.\n", 1);
	cleanup(&cub);	
	return (EXIT_SUCCESS);
}
