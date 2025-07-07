/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_color.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksudyn <ksudyn@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 16:05:04 by ksudyn            #+#    #+#             */
/*   Updated: 2025/07/07 17:54:20 by ksudyn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	ft_isdigit_str(const char *s)
{
	int	i = 0;

	if (!s)
		return (0);
	while (s[i])
	{
		if (!ft_isdigit(s[i]))
			return (0);
		i++;
	}
	return (1);
}

int	parse_color_value(const char *str, int rgb[3])
{
	char	**split;
	int		i;

	split = ft_split(str, ',');
	if (!split)
		return (ft_error(3));
	i = 0;
	while (i < 3)
	{
		if (!split[i] || !ft_isdigit_str(split[i]))
			return (free_matrix(split), ft_error(3));
		rgb[i] = ft_atoi(split[i]);
		if (rgb[i] < 0 || rgb[i] > 255)
			return (free_matrix(split), ft_error(3));
		i++;
	}
	if (split[3])
		return (free_matrix(split), ft_error(3));
	free_matrix(split);
	return (1);
}

static int	parse_floor_color(char **split, t_cub *game)
{
	if (game->textures->floor_set)
		return (ft_error(3));
	if (!parse_color_value(split[1], game->textures->floor_rgb))
		return (0);
	game->textures->floor_set = 1;
	return (1);
}

static int	parse_ceiling_color(char **split, t_cub *game)
{
	if (game->textures->ceiling_set)
		return (ft_error(3));
	if (!parse_color_value(split[1], game->textures->ceiling_rgb))
		return (0);
	game->textures->ceiling_set = 1;
	return (1);
}

int	parse_color_line(char *line, t_cub *game)
{
	char	**split;
	int		result;

	split = ft_split(line, ' ');

	if (!split || !split[0] || !split[1])
		return (free_matrix(split), ft_error(3));

	if (!ft_strncmp(split[0], "F", 2))
		result = parse_floor_color(split, game);
	else if (!ft_strncmp(split[0], "C", 2))
		result = parse_ceiling_color(split, game);
	else
		result = ft_error(3);

	free_matrix(split);
	return (result);
}
