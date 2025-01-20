/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcohen <jcohen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 15:25:26 by jcohen            #+#    #+#             */
/*   Updated: 2025/01/20 15:46:16 by jcohen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	validate_map(t_map *map)
{
	char	**temp_map;
	t_dims	dims;
	int		valid;

	dims.width = map->width;
	dims.height = map->height;
	if (!check_map_consistency(map))
		return (0);
	temp_map = copy_map(map);
	if (!temp_map)
		error_exit(ERR_MALLOC);
	valid = flood_fill(temp_map, (int)map->player_x, (int)map->player_y, dims);
	free_char_array(temp_map);
	return (valid);
}
