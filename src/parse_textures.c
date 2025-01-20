/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_textures.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcohen <jcohen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 15:25:28 by jcohen            #+#    #+#             */
/*   Updated: 2025/01/20 15:45:08 by jcohen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	check_textures(t_map *map)
{
	if (!map->north.path || !map->south.path || !map->west.path
		|| !map->east.path)
		error_exit(ERR_TEXTURE);
	return (check_texture_files(map));
}

int	check_texture_files(t_map *map)
{
	int	fd;

	fd = open(map->north.path, O_RDONLY);
	if (fd < 0)
		error_exit(ERR_TEXTURE_ACCESS);
	close(fd);
	fd = open(map->south.path, O_RDONLY);
	if (fd < 0)
		error_exit(ERR_TEXTURE_ACCESS);
	close(fd);
	fd = open(map->west.path, O_RDONLY);
	if (fd < 0)
		error_exit(ERR_TEXTURE_ACCESS);
	close(fd);
	fd = open(map->east.path, O_RDONLY);
	if (fd < 0)
		error_exit(ERR_TEXTURE_ACCESS);
	close(fd);
	return (1);
}

int	parse_textures(char *line, t_map *map)
{
	char		*trim;
	t_texture	*texture;

	trim = ft_strtrim(line + 2, " \t");
	if (!trim)
		error_exit(ERR_MALLOC);
	texture = get_texture_direction(line, map);
	if (!texture)
	{
		free(trim);
		return (0);
	}
	if (texture->path)
	{
		free(trim);
		error_exit(ERR_TEXTURE);
	}
	texture->path = trim;
	return (1);
}

t_texture	*get_texture_direction(char *line, t_map *map)
{
	if (!ft_strncmp(line, "NO", 2))
		return (&map->north);
	else if (!ft_strncmp(line, "SO", 2))
		return (&map->south);
	else if (!ft_strncmp(line, "WE", 2))
		return (&map->west);
	else if (!ft_strncmp(line, "EA", 2))
		return (&map->east);
	return (NULL);
}
