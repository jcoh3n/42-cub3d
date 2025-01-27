/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcohen <jcohen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 17:38:04 by jcohen            #+#    #+#             */
/*   Updated: 2025/01/27 17:26:39 by jcohen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "libft.h"
# include <fcntl.h>
# include <math.h>
# include <mlx.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>

/* Math Constants */
# define M_PI 3.14159265358979323846

/* Minimap Settings */
# define MINIMAP_SCALE 15
# define MINIMAP_RADIUS 100
# define MINIMAP_CENTER_X (WINDOW_WIDTH - MINIMAP_RADIUS - 20)
# define MINIMAP_CENTER_Y (MINIMAP_RADIUS + 20)
# define WALL_COLOR 0x444444
# define FLOOR_COLOR 0x666666
# define PLAYER_COLOR 0xFF0000
# define PLAYER_DIR_COLOR 0xFF4444
# define MINIMAP_BORDER_COLOR 0x222222
# define MINIMAP_BACKGROUND 0x111111
# define BORDER_THICKNESS 3

/* Window Settings */
# define WINDOW_WIDTH 1280
# define WINDOW_HEIGHT 720

/* Key Codes */
# define KEY_ESC 65307
# define KEY_W 119
# define KEY_A 97
# define KEY_S 115
# define KEY_D 100
# define KEY_LEFT 65361
# define KEY_RIGHT 65363
# define KEY_M 109


/* Movement Constants */
# define MOVE_SPEED 0.02
# define ROT_SPEED 0.003

/* Error Messages - File */
# define ERR_USAGE "Usage: ./cub3D <map.cub>"
# define ERR_FILE "Could not open map file"
# define ERR_FILE_EXT "Invalid file extension (must be .cub)"
# define ERR_IS_DIR "Path is a directory"

/* Error Messages - Config */
# define ERR_TEXTURE "Missing texture configuration"
# define ERR_TEXTURE_PATH "Invalid texture path"
# define ERR_TEXTURE_ACCESS "Could not access texture file"
# define ERR_TEXTURE_DUP "Duplicate texture definition"
# define ERR_COLOR "Invalid color configuration"
# define ERR_COLOR_RANGE "Color values must be between 0 and 255"
# define ERR_COLOR_DUP "Duplicate color definition"

/* Error Messages - Map */
# define ERR_MAP "Invalid map configuration"
# define ERR_MAP_CHARS "Invalid character in map"
# define ERR_MAP_WALLS "Map not enclosed by walls"
# define ERR_MAP_EMPTY "Empty line in map"
# define ERR_MAP_EMPTY_LINE "Empty line within map"
# define ERR_MAP_ORDER "Map must come after all other elements"
# define ERR_PLAYER_NONE "No player position found"
# define ERR_PLAYER_MULTIPLE "Multiple player positions found"

/* Error Messages - System */
# define ERR_MALLOC "Memory allocation failed"
# define ERR_WINDOW_INIT "Failed to initialize window"
# define ERR_IMAGE_INIT "Failed to create image"
# define ERR_IMAGE_ADDR "Failed to get image address"

/* Map Elements */
# define EMPTY '0'
# define WALL '1'
# define NORTH 'N'
# define SOUTH 'S'
# define EAST 'E'
# define WEST 'W'

/* Valid Map Characters */
# define VALID_MAP_CHARS "01 NSEW"
# define PLAYER_CHARS "NSEW"

typedef enum e_parse_state
{
	PARSE_CONFIG,
	PARSE_MAP
}				t_parse_state;

/* Color Structure */
typedef struct s_color
{
	int			r;
	int			g;
	int			b;
}				t_color;

/* Image Structure */
typedef struct s_img
{
	void		*img;
	char		*addr;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
	int			width;
	int			height;
}				t_img;

/* Texture Structure */
typedef struct s_texture
{
	void		*img;
	char		*path;
	int			width;
	int			height;
}				t_texture;

/* Map Structure */
typedef struct s_map
{
	char		**grid;
	int			width;
	int			height;
	char **flood_grid; // Ajout du flood_grid
	char		player_dir;
	double		player_x;
	double		player_y;
	t_color		floor;
	t_color		ceiling;
	t_texture	north;
	t_texture	south;
	t_texture	east;
	t_texture	west;
}				t_map;

/* Dimensions Structure */
typedef struct s_dims
{
	int			width;
	int			height;
}				t_dims;

/* Player Structure */
typedef struct s_player
{
	double		x;
	double		y;
	double		pos_x;
	double		pos_y;
	double		dir_x;
	double		dir_y;
	double		plane_x;
	double		plane_y;
	double		move_speed;
	double		rot_speed;
	int			move_forward;
	int			move_backward;
	int			move_left;
	int			move_right;
	int			rotate_left;
	int			rotate_right;
	int			rotation_direction;
}				t_player;

/* Minimap Structure */
typedef struct s_minimap
{
	int			scale;
	int			width;
	int			height;
	int			pos_x;
	int			pos_y;
	void		*img;
	int			*addr;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
}				t_minimap;

/* Game Structure */
typedef struct s_game
{
	void		*mlx;
	void		*win;
	char		**map;
	t_map		*map_data;
	t_img		img;
	t_player	player;
	t_minimap	minimap;
	int			is_running;
	int			window_focused;
	double		move_speed;
	double		last_frame;
	double		delta_time;
}				t_game;

/* Main Functions */
void			error_exit(char *message);
void			free_map(t_map *map);
void			cleanup_game(t_game *game);
t_game			*init_game(void);
t_map			*init_map(void);

/* Parsing Functions */
void			parse_map(char *filename, t_map *map);
void			validate_map(t_map *map);
int				parse_textures(char *line, t_map *map);
int				parse_colors(char *line, t_map *map);
void			check_texture_files(t_map *map);
void			store_map_line(t_map *map, char *line);

/* Window Management Functions */
int				init_window(t_game *game);
void			setup_window_hooks(t_game *game);
int				handle_window_close(t_game *game);
int				handle_window_focus(int focused, t_game *game);
int				handle_keypress(int keycode, t_game *game);
int				handle_keyrelease(int keycode, t_game *game);

/* Buffer Management Functions */
void			put_pixel(t_img *img, int x, int y, int color);
void			clear_buffer(t_img *img);
void			swap_buffers(t_game *game);

/* Texture Functions */
void			check_texture_files(t_map *map);

/* Map Validation Functions */
void			check_map_consistency(t_map *map);
void			free_map_grid(char **grid);
int				flood_fill(char **map, int x, int y, t_dims dims);
int				is_map_char(char c);

/* Map Storage Functions */
char			**create_temp_map(t_map *map);
void			free_temp_map(char **temp_map);
void			cleanup_map(t_map *map);

/* Map Copying Functions */
char			**copy_map(t_map *map);
void			free_char_array(char **array);

/* Player Functions */
void			init_player(t_game *game);
void			update_player_position(t_game *game);
void			rotate_player(t_game *game, double angle);
int				handle_player_keypress(int keycode, t_game *game);
int				handle_player_keyrelease(int keycode, t_game *game);
double			get_time(void);

/* Minimap Functions */
void			init_minimap(t_game *game);
void			update_minimap(t_game *game);
void			clear_minimap(t_game *game);
void			draw_border(t_game *game);
void			draw_player(t_game *game);
void			draw_square(t_game *game, int map_x, int map_y, int color);
void			put_pixel_minimap(t_game *game, int x, int y, int color);

/* Game Loop */
int				game_loop(t_game *game);

/* Function Declarations */
void			error_exit(char *message);
t_game			*init_game(void);
void			init_minimap(t_game *game);
void			init_player(t_game *game);
int				init_window(t_game *game);
void			parse_map(char *filename, t_map *map);
void			setup_window_hooks(t_game *game);
void			store_map_line(t_map *map, char *line);
void			update_player_position(t_game *game);
void			render_frame(t_game *game);

typedef enum e_bool
{
	FALSE = 0,
	TRUE = 1
}				t_bool;

#endif