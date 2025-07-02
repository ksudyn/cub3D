/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksudyn <ksudyn@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 19:17:33 by ksudyn            #+#    #+#             */
/*   Updated: 2025/07/02 15:41:51 by ksudyn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	init_struct(t_cub *cub)
{
	ft_bzero(cub, sizeof(t_cub));
	cub->textures = ft_calloc(1, sizeof(t_textures));
	cub->mlx = ft_calloc(1, sizeof(t_mlx));
	if (!cub->textures || !cub->mlx)
		exit(ft_error(9));
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
		return (EXIT_FAILURE);
	}

	// Validar mapa
	if (!validate_map(&cub))
	{
		ft_putstr_fd("Mapa inválido.\n", 2);
		free_matrix(cub.map);
		return (EXIT_FAILURE);
	}

	ft_putstr_fd("Mapa válido.\n", 1);
	free_matrix(cub.map);
	return (EXIT_SUCCESS);
}
