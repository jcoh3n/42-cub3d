/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_textures.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcohen <jcohen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 15:25:28 by jcohen            #+#    #+#             */
/*   Updated: 2025/01/29 15:48:44 by jcohen           ###   ########.fr       */
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
	if (!real_path)
		error_exit(ERR_MALLOC);
	fd = open(real_path, O_RDONLY);
	free(real_path);
	if (fd < 0)
		return (0);
	close(fd);
	return (1);
}

void	check_texture_files(t_map_data *map)
{
	if (!check_single_texture(map->north.path)
		|| !check_single_texture(map->south.path)
		|| !check_single_texture(map->west.path)
		|| !check_single_texture(map->east.path))
		error_exit(ERR_TEXTURE_ACCESS);
}

static t_texture	*get_texture_direction(char *line, t_map_data *map)
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

int	parse_textures(char *line, t_map_data *map)
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
