/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_store.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcohen <jcohen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 15:25:25 by jcohen            #+#    #+#             */
/*   Updated: 2025/01/30 17:20:53 by jcohen           ###   ########.fr       */
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
	int		i;

	new_line = (char *)malloc(width + 1);
	if (!new_line)
		error_exit(ERR_MALLOC);
	i = 0;
	while (i < len)
	{
		new_line[i] = line[i];
		i++;
	}
	while (i < width)
		new_line[i++] = ' ';
	new_line[i] = '\0';
	return (new_line);
}

void	store_map_line(t_map_data *map, char *line)
{
	char	*new_line;
	int		len;

	len = ft_strlen(line);
	if (line[len - 1] == '\n')
		len--;
	if (len > map->width)
		map->width = len;
	new_line = create_new_line(map->width, line, len);
	update_map_grid(map, new_line);
	update_player_start_position(map, new_line, len);
}
