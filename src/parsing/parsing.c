/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcohen <jcohen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 15:25:52 by jcohen            #+#    #+#             */
/*   Updated: 2025/01/24 14:56:01 by jcohen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	is_map_char(char c)
{
	return (c == EMPTY || c == WALL || c == NORTH || c == SOUTH || c == EAST
		|| c == WEST || c == ' ');
}

int	parse_map(char *filename, t_map *map)
{
	int		fd;
	char	*line;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		error_exit(ERR_FILE);
	line = get_next_line(fd);
	while (line)
	{
		if (!handle_line(line, map))
		{
			free(line);
			close(fd);
			return (0);
		}
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (validate_map(map));
}

static int	check_config_complete(t_map *map)
{
	if (!map->north.path || !map->south.path || !map->west.path 
		|| !map->east.path)
		error_exit(ERR_TEXTURE);
	if (map->floor.r == -1 || map->ceiling.r == -1)
		error_exit(ERR_MAP_ORDER);
	check_texture_files(map);
	return (1);
}

static int	handle_config_line(char *line, t_map *map)
{
	if (!line[0])
		return (1);
	if (line[0] == 'N' || line[0] == 'S' || line[0] == 'W' || line[0] == 'E')
		return (parse_textures(line, map));
	if (line[0] == 'F' || line[0] == 'C')
		return (parse_colors(line, map));
	if (is_map_char(line[0]))
		return (0);
	return (1);
}

int	handle_line(char *line, t_map *map)
{
	static t_parse_state	state = PARSE_CONFIG;

	if (state == PARSE_CONFIG)
	{
		if (!handle_config_line(line, map))
		{
			check_config_complete(map);
			state = PARSE_MAP;
			return (store_map_line(map, line));
		}
		return (1);
	}
	if (!line[0] || line[0] == '\n')
		error_exit(ERR_MAP_EMPTY_LINE);
	if (!is_map_char(line[0]))
		error_exit(ERR_MAP_CHARS);
	return (store_map_line(map, line));
}
