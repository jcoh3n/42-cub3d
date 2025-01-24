/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_textures.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcohen <jcohen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 15:25:28 by jcohen            #+#    #+#             */
/*   Updated: 2025/01/24 22:57:11 by jcohen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <errno.h>

static int	check_single_texture(char *texture_path)
{
	int		fd;
	char	*real_path;
	size_t	len;
	size_t	i;

	len = ft_strlen(texture_path);
	i = len - 1;
	while (i > 0 && (texture_path[i] == '\n' || texture_path[i] == ' '))
		i--;
	texture_path[i + 1] = '\0';
	if (ft_strncmp(texture_path, "./", 2) == 0)
		real_path = ft_strdup(texture_path + 2);
	else
		real_path = ft_strdup(texture_path);
	fd = open(real_path, O_RDONLY);
	if (fd < 0)
	{
		free(real_path);
		return (0);
	}
	close(fd);
	free(real_path);
	return (1);
}

int	check_textures(t_map *map)
{
	if (!map->north.path || !map->south.path || !map->west.path
		|| !map->east.path)
		error_exit(ERR_TEXTURE);
	return (check_texture_files(map));
}

int	check_texture_files(t_map *map)
{
	if (!check_single_texture(map->north.path)
		|| !check_single_texture(map->south.path)
		|| !check_single_texture(map->west.path)
		|| !check_single_texture(map->east.path))
		error_exit(ERR_TEXTURE_ACCESS);
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
		error_exit(ERR_TEXTURE_DUP);
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
