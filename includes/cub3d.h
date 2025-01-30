/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcohen <jcohen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 17:38:04 by jcohen            #+#    #+#             */
/*   Updated: 2025/01/30 17:29:08 by jcohen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# define _DEFAULT_SOURCE
# define _POSIX_C_SOURCE 200809L

# include "libft.h"
# include <fcntl.h>
# include <math.h>
# include <mlx.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/stat.h>
# include <sys/time.h>
# include <sys/types.h>
# include <unistd.h>

/* Math Constants */
# define M_PI 3.14159265358979323846

/* Minimap Settings */
# define MINIMAP_SCALE 15
# define MINIMAP_RADIUS 100
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
# define EXTENSION_NAME ".cub"
# define WINDOW_NAME "cub3D"

/* Status Indicator Settings */
# define STATUS_HEIGHT 25
# define STATUS_WIDTH 100
# define STATUS_PADDING 15
# define STATUS_ON_COLOR 0x44FF44
# define STATUS_OFF_COLOR 0xFF4444
# define STATUS_BG_COLOR 0x222222
# define STATUS_ANIM_FRAMES 10

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
# define MOVE_SPEED 0.05
# define ROT_SPEED 0.03

/* Mouse Settings */
# define MOUSE_SENSITIVITY 0.0001
# define MOUSE_CAPTURE_KEY 109
# define MOUSE_DEADZONE 2

/* FOV Settings */
# define FOV 1.0472
# define FOV_BIGGER 1.5708
# define WALL_STRIP_WIDTH 1

# define DIRECTION_VECTOR 1.0
# define PLANE_VECTOR 0.66

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
# define ERR_COLOR_FORMAT "Invalid color format"

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
}					t_parse_state;

/* Color Structure */
typedef struct s_color
{
	int				r;
	int				g;
	int				b;
}					t_color;

/* Image Structure */
typedef struct s_img
{
	void			*img;
	char			*addr;
	int				bits_per_pixel;
	int				line_length;
	int				endian;
	int				width;
	int				height;
}					t_img;

/* Texture Structure */
typedef struct s_texture
{
	void			*img;
	char			*addr;
	char			*path;
	int				width;
	int				height;
	int				bits_per_pixel;
	int				line_length;
	int				endian;
}					t_texture;

/* Map Structure */
typedef struct s_map
{
	char			**grid;
	int				width;
	int				height;
	char			**flood_grid;
	char			player_dir;
	double			player_x;
	double			player_y;
	t_color			floor;
	t_color			ceiling;
	t_texture		north;
	t_texture		south;
	t_texture		east;
	t_texture		west;
}					t_map;

/* Dimensions Structure */
typedef struct s_dims
{
	int				width;
	int				height;
}					t_dims;

/* Player Structure */
typedef struct s_player
{
	double			x;
	double			y;
	double			pos_x;
	double			pos_y;
	double			dir_x;
	double			dir_y;
	double			plane_x;
	double			plane_y;
	double			move_speed;
	double			rot_speed;
	int				move_forward;
	int				move_backward;
	int				move_left;
	int				move_right;
	int				rotate_left;
	int				rotate_right;
	int				rotation_direction;
}					t_player;

/* Minimap Structure */
typedef struct s_minimap
{
	int				scale;
	int				width;
	int				height;
	int				pos_x;
	int				pos_y;
	void			*img;
	int				*addr;
	int				bits_per_pixel;
	int				line_length;
	int				endian;
}					t_minimap;

typedef struct s_ray
{
	double			ray_angle;
	double			distance;
	int				wall_hit_x;
	int				wall_hit_y;
	int				is_vertical;
	int				facing_up;
	int				facing_right;
}					t_ray;

/* Rendering Related Structures */
typedef struct s_renderer
{
	void			*mlx;
	void			*win;
	t_img			frame;
	t_minimap		minimap;
	t_texture		*current_texture;
	int				render_flags;
}					t_renderer;

/* Game State Management */
typedef struct s_game_state
{
	int				is_running;
	int				window_focused;
	int				mouse_captured;
	double			last_frame;
	double			delta_time;
	double			fps;
	int				status_anim_frame;
	int				status_transitioning;
}					t_game_state;

/* Input Management */
typedef struct s_input
{
	int				move_forward;
	int				move_backward;
	int				move_left;
	int				move_right;
	int				rotate_left;
	int				rotate_right;
	int				last_mouse_x;
	int				last_mouse_y;
	double			mouse_sensitivity;
}					t_input;

/* Map Data Management */
typedef struct s_map_data
{
	char			**grid;
	int				width;
	int				height;
	char			**flood_grid;
	t_color			floor;
	t_color			ceiling;
	t_texture		north;
	t_texture		south;
	t_texture		east;
	t_texture		west;
	char			player_start_dir;
	double			player_start_x;
	double			player_start_y;
	char			player_dir;
	double			player_x;
	double			player_y;
}					t_map_data;

/* Main Game Structure */
typedef struct s_game
{
	t_renderer		renderer;
	t_game_state	state;
	t_input			input;
	t_map_data		*map_data;
	t_player		player;
	char			**map;
	double			move_speed;
}					t_game;

typedef enum e_bool
{
	FALSE = 0,
	TRUE = 1
}					t_bool;

/* Main Functions */
void				error_exit(char *message);
void				free_map(t_map_data *map);
void				cleanup_game(t_game *game);
void				clean_map_data(t_map_data *map, void *mlx);
t_game				*init_game(void);
t_map_data			*init_map(void);

/* Parsing Functions */
void				parse_map(char *filename, t_map_data *map);
void				validate_map(t_map_data *map);
int					parse_textures(char *line, t_map_data *map);
int					parse_colors(char *line, t_map_data *map);
void				check_texture_files(t_map_data *map);
void				store_map_line(t_map_data *map, char *line);

/* map_consistency_utils.c */
void				check_map_chars(t_map_data *map);
void				check_player(t_map_data *map);
int					check_line_consistency(t_map_data *map, int i, int len);
int					is_valid_position(t_map_data *map, int i, int j);

/* parse_colors_utils.c */
void				parse_rgb_values(char *str, t_color *color);

/* map_store_utils.c */
void				update_map_grid(t_map_data *map, char *new_line);

/* Window Management Functions */
int					init_window(t_game *game);
int					init_textures(t_game *game);
void				setup_window_hooks(t_game *game);
int					handle_window_close(t_game *game);
int					handle_window_focus(int focused, t_game *game);
int					handle_keypress(int keycode, t_game *game);
int					handle_keyrelease(int keycode, t_game *game);

/* Buffer Management Functions */
void				put_pixel(t_img *img, int x, int y, int color);
void				clear_buffer(t_img *img);
void				swap_buffers(t_game *game);

/* Map Validation Functions */
void				check_map_consistency(t_map_data *map);
void				free_map_grid(char **grid);
int					flood_fill(char **map, int x, int y, t_dims dims);
int					is_map_char(char c);

/* Map Storage Functions */
char				**create_temp_map(t_map_data *map);
void				free_temp_map(char **temp_map);

/* Player Functions */
void				init_player_direction(t_player *player, char dir);
void				init_player_position(t_player *player, double x, double y);
void				init_player(t_game *game);
void				update_player_position(t_game *game);
void				rotate_player(t_game *game, double angle);
double				get_time(void);

/* Minimap Functions */
void				init_minimap(t_game *game);
void				update_minimap(t_game *game);
void				clear_minimap(t_game *game);
void				draw_border(t_game *game);
void				draw_player(t_game *game);
void				draw_square(t_game *game, int map_x, int map_y, int color);
void				put_pixel_minimap(t_game *game, int x, int y, int color);

/* Game Loop */
int					game_loop(t_game *game);

/* Raycasting Functions */
void				cast_rays(t_game *game);
t_ray				cast_single_ray(t_game *game, double ray_angle);
void				render_wall_stripe(t_game *game, int x, t_ray *ray);

/* Mouse Events */
void				toggle_mouse_capture(t_game *game);
int					handle_mouse_move(int x, int y, t_game *game);

/* Rendering Functions */
void				render_frame(t_game *game);

/* Function declarations for dynamic calculations */
int					get_minimap_center_x(void);
int					get_minimap_center_y(void);
int					get_mouse_center_x(void);
int					get_mouse_center_y(void);

/* Color Parsing Utils */
void				validate_color_format(char *str);

#endif