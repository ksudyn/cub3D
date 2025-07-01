/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksudyn <ksudyn@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 19:47:05 by ksudyn            #+#    #+#             */
/*   Updated: 2025/07/01 20:47:11 by ksudyn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../libft/libft.h"
# include "../minilibx-linux/mlx.h"
# include <fcntl.h>    // open
# include <stdio.h>    // printf, perror
# include <stdlib.h>   // malloc, free, exit
# include <string.h>   // strerror
# include <sys/time.h> // gettimeofday
# include <unistd.h>   // read, write, close

typedef struct s_mlx
{
	void		*mlx;
	void		*mlx_win;
	void		*img;
}				t_mlx;
typedef struct s_textures
{
	char		*nort;
	char		*south;
	char		*eats;
	char		*west;
}				t_textures;

typedef struct s_cub
{
	char		**map;
	int			width;
	int			height;
	float		player_x;
	float		player_y;
	char		player_dir;

	t_textures	*textures;
	t_mlx		*mlx;
}				t_cub;

//....dimensions.c....//
int				dimensions(char *line, char ***map, int *height, t_cub *cub);
//....error.c....//
int				ft_error(int i);
//....flood_fill.c....//
void			flood_fill(t_cub *game, int x, int y, char **map_copy);
char			**copy_map(char **map, int height);
void			free_matrix(char **matrix);
int				check_closed_map(t_cub *game);
//....parse.c....//
int				normalize_map(t_cub *game);
int				check_valid_chars(t_cub *game);
int				check_player_count(t_cub *game);
int				check_top_bottom_walls(t_cub *game);
int				check_side_walls(t_cub *game);
//....utils_parse.c....//
int				is_valid_map_char(char c);
int				is_player(char c);
//....validate_map.c....//
int				validate_map(t_cub *game);

#endif