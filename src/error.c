/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksudyn <ksudyn@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 19:44:30 by ksudyn            #+#    #+#             */
/*   Updated: 2025/06/26 19:50:30 by ksudyn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	ft_error(int i)
{
	if (i == 1)
		printf("Error: map don't closed.\n");
	if (i == 2)
		printf("Failed to open map file");
	if (i == 3)
		printf("Invalid floor color format");
	if (i == 4)
		printf("More than one player position in map");
	return (1);
}