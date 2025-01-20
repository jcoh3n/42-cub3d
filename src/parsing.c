#include "../includes/cub3d.h"

static int is_map_char(char c)
{
    return (c == EMPTY || c == WALL || 
            c == NORTH || c == SOUTH || 
            c == EAST || c == WEST || c == ' ');
}

static int parse_rgb(char *str, t_color *color)
{
    char    **split;
    int     i;

    split = ft_split(str, ',');
    if (!split)
        return (0);
    i = 0;
    while (split[i])
        i++;
    if (i != 3)
    {
        while (i >= 0)
            free(split[i--]);
        free(split);
        error_exit(ERR_COLOR);
    }
    color->r = ft_atoi(split[0]);
    color->g = ft_atoi(split[1]);
    color->b = ft_atoi(split[2]);
    i = 0;
    while (i < 3)
        free(split[i++]);
    free(split);
    if (color->r < 0 || color->r > 255 ||
        color->g < 0 || color->g > 255 ||
        color->b < 0 || color->b > 255)
        error_exit(ERR_COLOR_RANGE);
    return (1);
}

int parse_colors(char *line, t_map *map)
{
    char    *trim;
    int     ret;

    trim = ft_strtrim(line + 1, " \t");
    if (!trim)
        error_exit(ERR_MALLOC);
    if (line[0] == 'F')
        ret = parse_rgb(trim, &map->floor);
    else if (line[0] == 'C')
        ret = parse_rgb(trim, &map->ceiling);
    else
        ret = 0;
    free(trim);
    return (ret);
}

int parse_textures(char *line, t_map *map)
{
    char        *trim;
    t_texture   *texture;

    trim = ft_strtrim(line + 2, " \t");
    if (!trim)
        error_exit(ERR_MALLOC);
    if (!ft_strncmp(line, "NO", 2))
        texture = &map->north;
    else if (!ft_strncmp(line, "SO", 2))
        texture = &map->south;
    else if (!ft_strncmp(line, "WE", 2))
        texture = &map->west;
    else if (!ft_strncmp(line, "EA", 2))
        texture = &map->east;
    else
    {
        free(trim);
        return (0);
    }
    if (texture->path)
    {
        free(trim);
        error_exit(ERR_TEXTURE);  // Duplicate texture
    }
    texture->path = trim;
    return (1);
}

int check_textures(t_map *map)
{
    if (!map->north.path || !map->south.path || 
        !map->west.path || !map->east.path)
        error_exit(ERR_TEXTURE);
    // TODO: Check if texture files exist and are readable
    return (1);
}

static int flood_fill(char **map, int x, int y, int *dims)
{
    if (x < 0 || x >= dims[0] || y < 0 || y >= dims[1])
        return (0);
    if (map[y][x] == ' ' || map[y][x] == '\0')
        error_exit(ERR_MAP_WALLS);
    if (map[y][x] == '1')
        return (1);
    if (!is_map_char(map[y][x]))
        error_exit(ERR_MAP_CHARS);
    map[y][x] = '1';  // Mark as visited
    if (!flood_fill(map, x + 1, y, dims) ||
        !flood_fill(map, x - 1, y, dims) ||
        !flood_fill(map, x, y + 1, dims) ||
        !flood_fill(map, x, y - 1, dims))
        error_exit(ERR_MAP_WALLS);
    return (1);
}

static int store_map_line(t_map *map, char *line)
{
    char    **new_grid;
    int     i;
    int     len;

    len = ft_strlen(line);
    if (line[len - 1] == '\n')
        len--;
    if (len > map->width)
        map->width = len;

    new_grid = (char **)malloc(sizeof(char *) * (map->height + 2));
    if (!new_grid)
        error_exit(ERR_MALLOC);

    i = 0;
    while (i < map->height)
    {
        new_grid[i] = map->grid[i];
        i++;
    }

    new_grid[i] = ft_substr(line, 0, len);
    if (!new_grid[i])
    {
        free(new_grid);
        error_exit(ERR_MALLOC);
    }

    new_grid[i + 1] = NULL;
    if (map->grid)
        free(map->grid);
    map->grid = new_grid;
    map->height++;

    // Check for player position
    i = 0;
    while (new_grid[map->height - 1][i])
    {
        if (ft_strchr("NSEW", new_grid[map->height - 1][i]))
        {
            if (map->player_dir)  // Player already found
                error_exit(ERR_PLAYER_MULTIPLE);
            map->player_dir = new_grid[map->height - 1][i];
            map->player_x = i;
            map->player_y = map->height - 1;
        }
        else if (!is_map_char(new_grid[map->height - 1][i]))
            error_exit(ERR_MAP_CHARS);
        i++;
    }
    return (1);
}

int validate_map(t_map *map)
{
    int dims[2];
    char **temp_map;
    int valid;
    int i;

    if (!map->player_dir)
        error_exit(ERR_PLAYER_NONE);

    dims[0] = map->width;
    dims[1] = map->height;
    
    // Create a copy of the map for flood fill
    temp_map = (char **)malloc(sizeof(char *) * (map->height + 1));
    if (!temp_map)
        error_exit(ERR_MALLOC);
    i = 0;
    while (i < map->height)
    {
        temp_map[i] = ft_strdup(map->grid[i]);
        if (!temp_map[i])
        {
            while (--i >= 0)
                free(temp_map[i]);
            free(temp_map);
            error_exit(ERR_MALLOC);
        }
        i++;
    }
    temp_map[i] = NULL;

    valid = flood_fill(temp_map, (int)map->player_x, 
                      (int)map->player_y, dims);

    // Free temporary map
    i = 0;
    while (temp_map[i])
        free(temp_map[i++]);
    free(temp_map);

    return (valid);
}

int parse_map(char *filename, t_map *map)
{
    int     fd;
    char    *line;
    int     in_map;

    fd = open(filename, O_RDONLY);
    if (fd < 0)
        error_exit(ERR_FILE);
    
    in_map = 0;
    while (1)
    {
        line = get_next_line(fd);
        if (!line)
            break;
        if (!in_map && line[0] && ft_strchr("NSWEFC", line[0]))
        {
            if (line[0] == 'N' || line[0] == 'S' || 
                line[0] == 'W' || line[0] == 'E')
            {
                if (!parse_textures(line, map))
                {
                    free(line);
                    close(fd);
                    error_exit(ERR_TEXTURE);
                }
            }
            else if (line[0] == 'F' || line[0] == 'C')
            {
                if (!parse_colors(line, map))
                {
                    free(line);
                    close(fd);
                    error_exit(ERR_COLOR);
                }
            }
        }
        else if (line[0] && is_map_char(line[0]))
        {
            in_map = 1;
            if (!store_map_line(map, line))
            {
                free(line);
                close(fd);
                error_exit(ERR_MAP);
            }
        }
        else if (in_map && *line != '\n' && *line != '\0')
        {
            free(line);
            close(fd);
            error_exit(ERR_MAP_CHARS);
        }
        else if (in_map && (*line == '\n' || *line == '\0'))
        {
            free(line);
            close(fd);
            error_exit(ERR_MAP_EMPTY);
        }
        free(line);
    }
    close(fd);
    check_textures(map);
    return (validate_map(map));
} 