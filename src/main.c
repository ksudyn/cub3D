/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksudyn <ksudyn@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 19:17:33 by ksudyn            #+#    #+#             */
/*   Updated: 2025/07/01 20:34:04 by ksudyn           ###   ########.fr       */
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

void	remove_newline(char *line)
{
	int	len;
    
    len = ft_strlen(line);
	if (len > 0 && line[len - 1] == '\n')
		line[len - 1] = '\0';
}

char	**read_map_lines(int fd, t_cub *cub)
{
	char	*line;
	char	**map;
	int		height;

	map = NULL;
	height = 0;
	line = get_next_line(fd);
	while (line)
	{
        remove_newline(line);
		if (!dimensions(line, &map, &height, cub))
		{
		    free(line);
		    free_matrix(map);
		    return (NULL);
	    }
		line = get_next_line(fd);
	}
	cub->height = height;
	return (map);
}


char	**load_map(const char *file, t_cub *cub)
{
	int		fd;
	char	**map;

	fd = open(file, O_RDONLY);
	if (fd == -1)
	{
		perror("Error al abrir el archivo");
		return (NULL);
	}
	map = read_map_lines(fd, cub);
	close(fd);
	if (!map || !map[0])
	{
		ft_putstr_fd("Error: el mapa está vacío o inválido\n", 2);
		return (NULL);
	}
	return (map);
}

int	main(int argc, char **argv)
{
	t_cub cub;
	
    if(argc != 2)
    {
        ft_error(10);
        return(EXIT_FAILURE);
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