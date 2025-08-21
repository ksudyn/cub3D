/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksudyn <ksudyn@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 19:17:33 by ksudyn            #+#    #+#             */
/*   Updated: 2025/08/21 20:05:29 by ksudyn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

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
    t_cub   cub;

    if (argc != 2)
        return (ft_error(10), EXIT_FAILURE);
    init_struct(&cub);
    init_texture_paths(&cub);
    cub.map = load_map(argv[1], &cub);
    if (!cub.map)
        return (cleanup(&cub), EXIT_FAILURE);
    if (!validate_map(&cub))
        return (cleanup(&cub), EXIT_FAILURE);
    ft_putstr_fd("Mapa válido.\n", 1);
    init_player(&cub);
    if (cub3d(&cub) != 0)
        return (cleanup(&cub), EXIT_FAILURE);
    mlx_loop(cub.mlx->mlx);
    cleanup (&cub);
        return (EXIT_SUCCESS);
}
