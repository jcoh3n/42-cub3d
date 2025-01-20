/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_colors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcohen <jcohen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 15:25:27 by jcohen            #+#    #+#             */
/*   Updated: 2025/01/20 16:53:30 by jcohen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	set_rgb_values(char **split, t_color *color)
{
	int	i;

	color->r = ft_atoi(split[0]);
	color->g = ft_atoi(split[1]);
	color->b = ft_atoi(split[2]);
	i = 0;
	while (i < 3)
		free(split[i++]);
	free(split);
	if (color->r < 0 || color->r > 255 || color->g < 0 || color->g > 255
		|| color->b < 0 || color->b > 255)
		error_exit("Error\nColor values must be between 0 and 255");
	return (1);
}
static int	parse_rgb(char *str, t_color *color)
{
	char	**split;
	int		i;

	split = ft_split(str, ',');
	if (!split)
		return (0);
	i = 0;
	while (split[i])
		i++;
	if (i != 3)
	{
		while (i >= 0)
			free(split[i--]);
		free(split);
		error_exit("Error\nInvalid color format - expected R,G,B");
	}
	return (set_rgb_values(split, color));
}

int	parse_colors(char *line, t_map *map)
{
	char	*trim;
	int		ret;

	trim = ft_strtrim(line + 1, " \t");
	if (!trim)
		error_exit("Error\nMemory allocation failed");
	if (line[0] == 'F')
		ret = parse_rgb(trim, &map->floor);
	else if (line[0] == 'C')
		ret = parse_rgb(trim, &map->ceiling);
	else
		ret = 0;
	free(trim);
	return (ret);
}
