/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksudyn <ksudyn@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 19:47:05 by ksudyn            #+#    #+#             */
/*   Updated: 2025/08/20 18:48:31 by ksudyn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# define FOV 60
# define WIDTH 800
# define HEIGHT 600
# define CELL_SIZE 64
# define NORTH 0
# define SOUTH 1
# define EAST 2
# define WEST 3

# define NUM_TEXTURES 4

#ifndef M_PI
# define M_PI 3.14159265358979323846
#endif

# define KEY_ESC 65307

# define KEY_LEFT 65361
# define KEY_RIGHT 65363
# define KEY_W 119
# define KEY_A 97
# define KEY_S 115
# define KEY_D 100

#define ON_KEYDOWN 2      // Evento cuando se presiona una tecla
#define ON_KEYUP 3        // Evento cuando se suelta una tecla
#define ON_DESTROY 17     // Evento cuando se cierra la ventana (X button de la ventana)

#define NO_EVENT_MASK 0   // Máscara vacía, sin condiciones especiales
#define KEY_PRESS_MASK 1L // Máscara para evento de pulsar tecla
#define KEY_RELEASE_MASK 2L // Máscara para evento de soltar tecla


# include "../libft/libft.h"
# include "../minilibx-linux/mlx.h"
# include <fcntl.h>    // open
# include <stdio.h>    // printf, perror
# include <stdlib.h>   // malloc, free, exit
# include <string.h>   // strerror
# include <sys/time.h> // gettimeofday
# include <unistd.h>   // read, write, close
# include <math.h>
# include <stdbool.h>

typedef struct s_image
{
	void *img;     // puntero a la imagen MLX
	char *data;    // dirección de los píxeles
	int width;     // ancho de la imagen
	int height;    // alto de la imagen
	int bpp;       // bits por píxel
	int size_line; // cantidad de bytes por fila
	int endian;    // orden de bytes (endianness)
}				t_image;

typedef struct s_player
{
	float		x;
	float		y;
	float		angle;
	float		delta_x;
	float		delta_y;

	int			key_up;
	int			key_down;
	int			key_left;
	int			key_right;
	int			left_rotate;
	int			right_rotate;
}				t_player;

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

	int			ceiling_rgb[3];
	int			floor_rgb[3];
	int			ceiling_set;
	int			floor_set;
}				t_textures;

typedef struct s_cub
{
	char		**map;
	int			width;
	int			height;
	float		player_x;
	float		player_y;
	char		player_dir;
	int			map_started;
	int			map_finished;

	t_textures	*textures;
	t_mlx		*mlx;
	t_player	player;
	char		*textures_path[NUM_TEXTURES];
	t_image		image[NUM_TEXTURES];
}				t_cub;

typedef struct s_collision
{
	float	dist;    // distancia en UNIDADES DE CELDA
	float	offset;  // desplazamiento (0..1) sobre la cara impactada
	int		direction; // NORTH/SOUTH/EAST/WEST
}	t_collision;

char	get_map_cell(t_cub *cub, int grid_x, int grid_y);
int	is_walkable_char(char c);
int	check_collision(t_cub *cub, float world_x, float world_y);
int	check_collision_radius(t_cub *cub, float x, float y, float r);
float	deg_to_rad(float deg);
float	sqr(float n);
void	move_forward(t_cub *cub, float speed);
void	move_backward(t_cub *cub, float speed);
void	move_left(t_cub *cub, float speed);
void	move_right(t_cub *cub, float speed);
void	rotate_player(t_player *p, float angle);
void	set_collision(t_collision *col, float dist, float offset, int dir);

void	render_frame(t_cub *cub);
int	safe_exit(t_cub *cub);
void    cast_row_ray_down(t_cub *cub, float ray_angle, t_collision *hit);
void    cast_row_ray_up(t_cub *cub, float ray_angle, t_collision *hit);
void    cast_column_ray_right(t_cub *cub, float ray_angle, t_collision *hit);
void    cast_column_ray_left(t_cub *cub, float ray_angle, t_collision *hit);
t_collision	cast_ray(t_cub *cub, float ray_angle);
void    init_collision(t_collision *col);
void	init_hooks(t_cub *cub);
int	rgb_to_int(int rgb[3]);


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

void			parse_texture_line(char *line, t_cub *cub);

//....utils_parse.c....//
int				is_valid_map_char(char c);
int				is_player(char c);
//....validate_map.c....//
int				validate_map(t_cub *game);
//....error.c....//
int				ft_error(int i);
int				ft_error_mlx(int i);

int				load_textures(t_cub *cub);
int				cub3d(t_cub *cub);

#endif