/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksudyn <ksudyn@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 19:47:05 by ksudyn            #+#    #+#             */
/*   Updated: 2025/06/26 20:03:21 by ksudyn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

#include <fcntl.h>     // open
#include <unistd.h>    // read, write, close
#include <stdlib.h>    // malloc, free, exit
#include <stdio.h>     // printf, perror
#include <string.h>    // strerror
#include <sys/time.h>  // gettimeofday

# include "../libft/libft.h"
# include "../minilibx-linux/mlx.h"

typedef struct s_mlx
{
	void	*mlx;
	void	*mlx_win;
	void	*img;
}			t_mlx;
typedef struct s_textures
{
    char *nort;
    char *south;
    char *eats;
    char *west;
}       t_textures;

typedef struct s_cub
{
    float   p_y;
    float   p_x;
    t_textures  *textures;
    t_mlx       *mlx;
}       t_cub;

//....error.c....//
int	ft_error(int i);
//....parse.c....//
int is_valid_map_char(char c);

#endif