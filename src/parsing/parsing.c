/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcohen <jcohen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 15:25:52 by jcohen            #+#    #+#             */
/*   Updated: 2025/01/30 17:44:48 by jcohen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	handle_config_line(char *line, t_map_data *map)
{
	if (!line[0])
		return (1);
	if (line[0] == 'N' || line[0] == 'S' || line[0] == 'W' || line[0] == 'E')
		return (parse_textures(line, map));
	if (line[0] == 'F' || line[0] == 'C')
		return (parse_colors(line, map));
	if (ft_strchr(VALID_MAP_CHARS, line[0]))
	{
		if (!map->north.path || !map->south.path || !map->west.path
			|| !map->east.path)
			error_exit(ERR_TEXTURE);
		if (map->floor.r == -1 || map->ceiling.r == -1)
			error_exit(ERR_COLOR);
		if (map->grid)
			error_exit(ERR_MAP_ORDER);
		return (0);
	}
	return (1);
}

static void	check_config_complete(t_map_data *map)
{
	if (!map->north.path || !map->south.path || !map->west.path
		|| !map->east.path)
		error_exit(ERR_TEXTURE);
	if (map->floor.r == -1 || map->ceiling.r == -1)
		error_exit(ERR_COLOR);
}

static void	handle_map_line(char *line, t_map_data *map, int *found_map)
{
	if (!line[0] || line[0] == '\n')
	{
		if (*found_map)
			error_exit(ERR_MAP_EMPTY_LINE);
		return ;
	}
	if (!ft_strchr(VALID_MAP_CHARS, line[0]))
		error_exit(ERR_MAP_CHARS);
	*found_map = 1;
	store_map_line(map, line);
}

static void	handle_line(char *line, t_map_data *map)
{
	static t_parse_state	state = PARSE_CONFIG;
	static int				found_map = 0;

	if (state == PARSE_CONFIG && !line[0])
		return ;
	if (state == PARSE_CONFIG && !handle_config_line(line, map))
	{
		state = PARSE_MAP;
		check_config_complete(map);
		found_map = 1;
		store_map_line(map, line);
		return ;
	}
	if (state == PARSE_MAP)
		handle_map_line(line, map, &found_map);
}

void	parse_map(char *filename, t_map_data *map)
{
	int		fd;
	char	*line;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		error_exit(ERR_FILE);
	line = get_next_line(fd);
	while (line)
	{
		handle_line(line, map);
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	check_texture_files(map);
	validate_map(map);
}
