/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_store.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcohen <jcohen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 15:25:25 by jcohen            #+#    #+#             */
/*   Updated: 2025/01/20 15:49:27 by jcohen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	store_map_line(t_map *map, char *line)
{
	char	**new_grid;
	int		len;

	len = ft_strlen(line);
	if (line[len - 1] == '\n')
		len--;
	if (len > map->width)
		map->width = len;
	new_grid = create_new_grid(map, line, len);
	if (!new_grid)
		return (0);
	update_map_grid(map, new_grid);
	return (check_player_position(map, new_grid));
}

char	**create_new_grid(t_map *map, char *line, int len)
{
	char	**new_grid;
	int		i;
	char	*trimmed_line;

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
	trimmed_line = ft_substr(line, 0, len);
	if (!trimmed_line)
		error_exit(ERR_MALLOC);
	new_grid[i] = trimmed_line;
	new_grid[i + 1] = NULL;
	return (new_grid);
}

void	update_map_grid(t_map *map, char **new_grid)
{
	free_map(map);
	map->grid = new_grid;
	map->height++;
}

int	check_player_position(t_map *map, char **new_grid)
{
	int	i;
	int	j;

	i = 0;
	while (new_grid[i])
	{
		j = 0;
		while (new_grid[i][j])
		{
			if (ft_strchr("NSEW", new_grid[i][j]))
			{
				if (map->player_dir)
					return (0);
				map->player_dir = new_grid[i][j];
				map->player_x = j + 0.5;
				map->player_y = i + 0.5;
			}
			j++;
		}
		i++;
	}
	return (1);
}

char	**copy_map(t_map *map)
{
	char	**copy;
	int		i;

	copy = (char **)malloc(sizeof(char *) * (map->height + 1));
	if (!copy)
		error_exit(ERR_MALLOC);
	i = 0;
	while (i < map->height)
	{
		copy[i] = ft_strdup(map->grid[i]);
		if (!copy[i])
		{
			while (--i >= 0)
				free(copy[i]);
			free(copy);
			error_exit(ERR_MALLOC);
		}
		i++;
	}
	copy[i] = NULL;
	return (copy);
}

void	free_char_array(char **array)
{
	int	i;

	if (!array)
		return;
	i = 0;
	while (array[i])
		free(array[i++]);
	free(array);
}
