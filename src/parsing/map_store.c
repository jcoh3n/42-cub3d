/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_store.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcohen <jcohen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 15:25:25 by jcohen            #+#    #+#             */
/*   Updated: 2025/02/07 19:09:23 by jcohen           ###   ########.fr       */
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
	ft_memset(new_line, ' ', width);
	i = 0;
	while (i < len)
	{
		new_line[i] = line[i];
		i++;
	}
	new_line[width] = '\0';
	return (new_line);
}

void	store_map_line(t_map_data *map, char *line)
{
	char	*new_line;
	int		len;

	if (!map || !line)
		return ;
	len = ft_strlen(line);
	if (line[len - 1] == '\n')
		len--;
	if (len > map->width)
		map->width = len;
	new_line = create_new_line(map->width, line, len);
	if (!new_line)
		return ;
	update_map_grid(map, new_line);
	update_player_start_position(map, new_line, len);
}
