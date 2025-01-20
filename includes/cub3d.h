#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <math.h>
# include <mlx.h>
# include "libft.h"
# include "ft_printf.h"
# include "get_next_line.h"

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
} t_game;

/* Function Prototypes */

/* Parsing Functions */
int     parse_map(char *filename, t_map *map);
int     validate_map(t_map *map);
int     parse_textures(char *line, t_map *map);
int     parse_colors(char *line, t_map *map);
int     check_textures(t_map *map);

/* Error Handling */
void    error_exit(char *message);
void    free_map(t_map *map);
void    cleanup_game(t_game *game);

/* Initialization */
t_game  *init_game(void);
t_map   *init_map(void);

void    cleanup_map(t_map *map);

#endif 