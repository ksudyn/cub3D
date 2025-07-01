/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksudyn <ksudyn@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 16:07:49 by ksudyn            #+#    #+#             */
/*   Updated: 2025/07/01 20:24:23 by ksudyn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int validate_map(t_cub *game)
{
	if (!normalize_map(game))
		return (0);
	if (!check_valid_chars(game))
		return (0);
	if (!check_player_count(game))
		return (0);
	if (!check_top_bottom_walls(game))
		return (0);
	if (!check_side_walls(game))
		return (0);
	if (!check_closed_map(game))
		return (0);
	return (1);
}
