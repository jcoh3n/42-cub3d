/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_store.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcohen <jcohen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 15:25:25 by jcohen            #+#    #+#             */
/*   Updated: 2025/01/20 16:23:00 by jcohen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	store_map_line(t_map *map, char *line)
{
	char	**new_grid;
	int		len;
	int		i;

	len = ft_strlen(line);
	if (line[len - 1] == '\n')
		len--;
	
	// Update map width if this line is longer
	if (len > map->width)
		map->width = len;

	new_grid = create_new_grid(map, line, len);
	if (!new_grid)
		error_exit("Failed to allocate memory for map grid");

	update_map_grid(map, new_grid);
	
	// Check for player position in the new line
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
	return (1);
}

char	**create_new_grid(t_map *map, char *line, int len)
{
	char	**new_grid;
	int		i;
	char	*new_line;

	new_grid = (char **)malloc(sizeof(char *) * (map->height + 2));
	if (!new_grid)
		error_exit("Failed to allocate memory for map grid");

	i = 0;
	while (i < map->height)
	{
		new_grid[i] = ft_strdup(map->grid[i]);
		if (!new_grid[i])
		{
			while (--i >= 0)
				free(new_grid[i]);
			free(new_grid);
			error_exit("Failed to allocate memory for map line");
		}
		i++;
	}

	// Create new line padded to map width
	new_line = (char *)malloc(map->width + 1);
	if (!new_line)
	{
		while (--i >= 0)
			free(new_grid[i]);
		free(new_grid);
		error_exit("Failed to allocate memory for map line");
	}

	// Copy line content and pad with spaces
	ft_memcpy(new_line, line, len);
	while (len < map->width)
		new_line[len++] = ' ';
	new_line[len] = '\0';
	
	new_grid[i] = new_line;
	new_grid[i + 1] = NULL;

	return (new_grid);
}

void	update_map_grid(t_map *map, char **new_grid)
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
