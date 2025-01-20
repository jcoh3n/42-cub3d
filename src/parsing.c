/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcohen <jcohen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 15:25:52 by jcohen            #+#    #+#             */
/*   Updated: 2025/01/20 17:02:45 by jcohen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	is_map_char(char c)
{
	return (c == EMPTY || c == WALL || c == NORTH || c == SOUTH || c == EAST
		|| c == WEST || c == ' ');
}

int	parse_map(char *filename, t_map *map)
{
	int		fd;
	char	*line;
	int		in_map;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		error_exit(ERR_FILE);
	in_map = 0;
	line = get_next_line(fd);
	while (line)
	{
		if (!handle_line(line, map, &in_map))
		{
			free(line);
			close(fd);
			return (0);
		}
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	check_textures(map);
	return (validate_map(map));
}

int	handle_line(char *line, t_map *map, int *in_map)
{
	if (!*in_map && line[0] && ft_strchr("NSWEFC", line[0]))
	{
		if (line[0] == 'N' || line[0] == 'S' || line[0] == 'W'
			|| line[0] == 'E')
			return (parse_textures(line, map));
		else if (line[0] == 'F' || line[0] == 'C')
			return (parse_colors(line, map));
	}
	else if (line[0] && is_map_char(line[0]))
	{
		*in_map = 1;
		return (store_map_line(map, line));
	}
	else if (*in_map && *line != '\n' && *line != '\0')
		error_exit(ERR_MAP_CHARS);
	else if (*in_map && (*line == '\n' || *line == '\0'))
		error_exit(ERR_MAP_EMPTY_LINE);
	return (1);
}
