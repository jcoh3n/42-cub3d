/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_store.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcohen <jcohen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 15:25:25 by jcohen            #+#    #+#             */
/*   Updated: 2025/01/29 15:48:45 by jcohen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	update_player_start_position(t_map_data *map, char *line, int len)
{
	int	i;

	i = 0;
	while (line[i] && i < len)
	{
		if (ft_strchr("NSEW", line[i]))
		{
			map->player_dir = line[i];
			map->player_x = i + 0.5;
			map->player_y = map->height - 1 + 0.5;
		}
		i++;
	}
}

static char	*create_new_line(int width, char *line, int len)
{
	char	*new_line;

	new_line = (char *)malloc(width + 1);
	if (!new_line)
		error_exit(ERR_MALLOC);
	ft_memcpy(new_line, line, len);
	while (len < width)
		new_line[len++] = ' ';
	new_line[len] = '\0';
	return (new_line);
}

static char	**init_grid_rows(t_map_data *map)
{
	char	**new_grid;
	int		i;

	new_grid = (char **)malloc(sizeof(char *) * (map->height + 2));
	if (!new_grid)
		error_exit(ERR_MALLOC);
	i = 0;
	while (i < map->height)
	{
		new_grid[i] = ft_strdup(map->grid[i]);
		if (!new_grid[i])
		{
			while (--i >= 0)
				free(new_grid[i]);
			free(new_grid);
			error_exit(ERR_MALLOC);
		}
		i++;
	}
	return (new_grid);
}

static char	**create_new_grid(t_map_data *map, char *line, int len)
{
	char	**new_grid;
	char	*new_line;
	int		i;

	new_grid = init_grid_rows(map);
	i = map->height;
	new_line = create_new_line(map->width, line, len);
	new_grid[i] = new_line;
	new_grid[i + 1] = NULL;
	return (new_grid);
}

static void	update_map_grid(t_map_data *map, char **new_grid)
{
	int	i;

	if (map->grid)
	{
		i = 0;
		while (i < map->height)
			free(map->grid[i++]);
		free(map->grid);
	}
	map->grid = new_grid;
	map->height++;
}

void	store_map_line(t_map_data *map, char *line)
{
	char	**new_grid;
	int		len;

	len = ft_strlen(line);
	if (line[len - 1] == '\n')
		len--;
	if (len > map->width)
		map->width = len;
	new_grid = create_new_grid(map, line, len);
	update_map_grid(map, new_grid);
	update_player_start_position(map, line, len);
}
