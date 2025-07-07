/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksudyn <ksudyn@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 19:47:05 by ksudyn            #+#    #+#             */
/*   Updated: 2025/07/07 16:25:31 by ksudyn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# define T_NORTH "./textures/north.xpm"
# define T_SOUTH "./textures/south.xpm"
# define T_EAST  "./textures/east.xpm"
# define T_WEST  "./textures/west.xpm"

# define WIDTH 1280
# define HEIGHT 1200
# define CELL_SIZE 64
#define NORTH 0
#define SOUTH 1
#define EAST  2
#define WEST  3

#define NUM_TEXTURES 4

# include "../libft/libft.h"
# include "../minilibx-linux/mlx.h"
# include <fcntl.h>    // open
# include <stdio.h>    // printf, perror
# include <stdlib.h>   // malloc, free, exit
# include <string.h>   // strerror
# include <sys/time.h> // gettimeofday
# include <unistd.h>   // read, write, close

typedef struct s_image
{
	void	*img;         // puntero a la imagen MLX
	char	*data;        // dirección de los píxeles
	int		width;        // ancho de la imagen
	int		height;       // alto de la imagen
	int		bpp;          // bits por píxel
	int		size_line;    // cantidad de bytes por fila
	int		endian;       // orden de bytes (endianness)
}				t_image;

typedef struct s_mlx
{
	void		*mlx;
	void		*mlx_win;
	void		*img;
	char		*data;
	int			bpp;
	int			size_line;
	int			endian;
}				t_mlx;

typedef struct s_textures
{
	void		*north;
	void		*south;
	void		*east;
	void		*west;

	int		ceiling_rgb[3];
	int		floor_rgb[3];
	int		ceiling_set;
	int		floor_set;
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
	char	*textures_path[NUM_TEXTURES];
	t_image		image[NUM_TEXTURES];
}				t_cub;

//....check_map.c....//
int				check_valid_chars(t_cub *game);
int				check_player_count(t_cub *game);
int				check_top_bottom_walls(t_cub *game);
int				check_side_walls(t_cub *game);
//....dimensions.c....//
int				dimensions(char *line, char ***map, int *height, t_cub *cub);
//....flood_fill.c....//
void			flood_fill(t_cub *game, int x, int y, char **map_copy);
char			**copy_map(char **map, int height);
void			free_matrix(char **matrix);
int				check_closed_map(t_cub *game);
//....load_map.c....//
char			**load_map(const char *file, t_cub *cub);
//....normalize_map.c....//
int				normalize_map(t_cub *game);
//....textures_color.c....//
int				parse_color_line(char *line, t_cub *game);

void	parse_texture_line(char *line, t_cub *cub);

//....utils_parse.c....//
int				is_valid_map_char(char c);
int				is_player(char c);
//....validate_map.c....//
int				validate_map(t_cub *game);
//....error.c....//
int				ft_error(int i);
int 			ft_error_mlx(int i);

int	load_textures(t_cub *cub);
int     cub3d(t_cub *cub);

#endif