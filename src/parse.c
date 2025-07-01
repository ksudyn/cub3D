/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksudyn <ksudyn@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 20:39:07 by ksudyn            #+#    #+#             */
/*   Updated: 2025/07/01 20:37:08 by ksudyn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

// int	is_rectangular(t_cub *game)
// {
// 	int	len;
// 	int	i;

// 	i = 1;
// 	len = ft_strlen(game->map[0]);
// 	while (i < game->height)
// 	{
// 		if ((int)ft_strlen(game->map[i]) != len)
// 			return (ft_error(5));  // "Map not rectangular"
// 		i++;
// 	}
// 	game->width = len;
// 	return (1);
// }


int	normalize_map(t_cub *game)
{
	int		i;
	int		max_len;
	int		len;

	// 1. Encuentra la línea más larga
	max_len = 0;
	i = 0;
	while (i < game->height)
	{
		len = ft_strlen(game->map[i]);
		if (len > max_len)
			max_len = len;
		i++;
	}
	game->width = max_len;

	// 2. Rellena con espacios las líneas más cortas
	i = 0;
	while (i < game->height)
	{
		len = ft_strlen(game->map[i]);
		if (len < max_len)
		{
			char *new_line = malloc(max_len + 1);
			if (!new_line)
				return (ft_error(9));
			ft_memset(new_line, ' ', max_len);
			ft_memcpy(new_line, game->map[i], len);
			new_line[max_len] = '\0';
			free(game->map[i]);
			game->map[i] = new_line;
		}
		i++;
	}
	return (1);
}

int	check_valid_chars(t_cub *game)
{
	int	i;
	int	j;

	i = 0;
	while (i < game->height)
	{
		j = 0;
		while (game->map[i][j])
		{
			if (!is_valid_map_char(game->map[i][j]))
				return (ft_error(6));
			j++;
		}
		i++;
	}
	return (1);
}

int	check_player_count(t_cub *game)
{
	int	i;
	int	j;
	int	count;

	i = 0;
	count = 0;
	while (i < game->height)
	{
		j = 0;
		while (game->map[i][j])
		{
			if (is_player(game->map[i][j]))
			{
				game->player_dir = game->map[i][j];
				game->player_x = j;
				game->player_y = i;
				count++;
			}
			j++;
		}
		i++;
	}
	if (count != 1)
		return (ft_error(4));
	return (1);
}

int	check_top_bottom_walls(t_cub *game)
{
	int	i;

	i = 0;
	while (game->map[0][i])
	{
		if (game->map[0][i] != '1' && game->map[0][i] != ' ')
			return (ft_error(1));
		i++;
	}
	i = 0;
	while (game->map[game->height - 1][i])
	{
		if (game->map[game->height - 1][i] != '1'
                && game->map[game->height - 1][i] != ' ')
			return (ft_error(1));
		i++;
	}
	return (1);
}

int	check_side_walls(t_cub *game)
{
	int	i;
	int	len;

	i = 0;
	while (i < game->height)
	{
		len = ft_strlen(game->map[i]);
		if (!is_valid_map_char(game->map[i][0])
			|| !is_valid_map_char(game->map[i][len - 1]))
			return (ft_error(1));
		i++;
	}
	return (1);
}
