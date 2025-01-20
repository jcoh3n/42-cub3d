#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <math.h>
# include <mlx.h>
# include "libft.h"

/* Window Settings */
# define WINDOW_WIDTH 1280
# define WINDOW_HEIGHT 720

/* Key Codes */
# define KEY_ESC 65307

/* Error Messages */
# define ERR_USAGE "Usage: ./cub3D <map.cub>"
# define ERR_FILE "Could not open map file"
# define ERR_MAP "Invalid map configuration"
# define ERR_MAP_CHARS "Invalid character in map"
# define ERR_MAP_WALLS "Map not enclosed by walls"
# define ERR_MAP_EMPTY "Empty line in map"
# define ERR_TEXTURE "Missing texture configuration"
# define ERR_TEXTURE_PATH "Invalid texture path"
# define ERR_COLOR "Invalid color configuration"
# define ERR_COLOR_RANGE "Color values must be between 0 and 255"
# define ERR_PLAYER_NONE "No player position found"
# define ERR_PLAYER_MULTIPLE "Multiple player positions found"
# define ERR_MALLOC "Memory allocation failed"
# define ERR_TEXTURE_ACCESS "Could not access texture file"
# define ERR_MAP_EMPTY_LINE "Empty line within map"
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

/* Color Structure */
typedef struct s_color
{
    int r;
    int g;
    int b;
} t_color;

/* Image Structure */
typedef struct s_img
{
    void    *img;
    char    *addr;
    int     bits_per_pixel;
    int     line_length;
    int     endian;
    int     width;
    int     height;
} t_img;

/* Texture Structure */
typedef struct s_texture
{
    void    *img;
    char    *path;
    int     width;
    int     height;
} t_texture;

/* Map Structure */
typedef struct s_map
{
    char    **grid;
    int     width;
    int     height;
    char    player_dir;
    double  player_x;
    double  player_y;
    t_color floor;
    t_color ceiling;
    t_texture north;
    t_texture south;
    t_texture east;
    t_texture west;
} t_map;

/* Game Structure */
typedef struct s_game
{
    void    *mlx;
    void    *win;
    t_map   *map;
    t_img   img;
    int     is_running;
    int     window_focused;
} t_game;

/* Dimensions Structure */
typedef struct s_dims
{
    int width;
    int height;
} t_dims;

/* Main Functions */
void    error_exit(char *message);
void    free_map(t_map *map);
void    cleanup_game(t_game *game);
t_game  *init_game(void);
t_map   *init_map(void);

/* Parsing Functions */
int     parse_map(char *filename, t_map *map);
int     handle_line(char *line, t_map *map, int *in_map);
int     validate_map(t_map *map);
int     parse_textures(char *line, t_map *map);
int     parse_colors(char *line, t_map *map);
int     check_textures(t_map *map);
int     store_map_line(t_map *map, char *line);

/* Window Management Functions */
int     init_window(t_game *game);
void    setup_window_hooks(t_game *game);
int     handle_window_close(t_game *game);
int     handle_window_focus(int focused, t_game *game);
int     handle_keypress(int keycode, t_game *game);

/* Buffer Management Functions */
void    put_pixel(t_img *img, int x, int y, int color);
void    clear_buffer(t_img *img);
void    swap_buffers(t_game *game);
void    draw_test_pattern(t_game *game);
int     create_rgb(int r, int g, int b);

/* Texture Functions */
int     check_texture_files(t_map *map);
t_texture *get_texture_direction(char *line, t_map *map);

/* Color Functions */
int     set_rgb_values(char **split, t_color *color);

/* Map Validation Functions */
char    **create_temp_map(t_map *map);
void    free_temp_map(char **temp_map);
int     check_line_consistency(t_map *map, int i, int len);
int     check_surrounding_walls(t_map *map, int i, int j);
int     check_map_consistency(t_map *map);
int     flood_fill(char **map, int x, int y, t_dims dims);
int     is_map_char(char c);

/* Map Storage Functions */
char    **create_new_grid(t_map *map, char *line, int len);
void    update_map_grid(t_map *map, char **new_grid);
int     check_player_position(t_map *map, char **new_grid);
void    cleanup_map(t_map *map);

/* Map Copying Functions */
char    **copy_map(t_map *map);
void    free_char_array(char **array);

#endif