/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_colors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcohen <jcohen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 15:25:27 by jcohen            #+#    #+#             */
/*   Updated: 2025/01/29 15:48:44 by jcohen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	is_valid_number(char *str)
{
	int	i;

	i = 0;
	// Skip leading spaces
	while (str[i] && ft_isspace(str[i]))
		i++;
	// Check if we have at least one digit
	if (!str[i])
		return (0);
	while (str[i])
	{
		if (!ft_isdigit(str[i]) && !ft_isspace(str[i]))
			return (0);
		i++;
	}
	return (1);
}

static void	validate_color_format(char *str)
{
	int	i;
	int	comma_count;
	int	digit_count;

	i = 0;
	comma_count = 0;
	digit_count = 0;
	while (str[i])
	{
		if (str[i] == ',')
		{
			if (!digit_count)
				error_exit(ERR_COLOR_FORMAT);
			comma_count++;
			digit_count = 0;
		}
		else if (ft_isdigit(str[i]))
		{
			digit_count++;
		}
		else if (!ft_isspace(str[i]))
			error_exit(ERR_COLOR_FORMAT);
		i++;
	}
	if (comma_count != 2 || !digit_count)
		error_exit(ERR_COLOR_FORMAT);
}

static char	*trim_spaces(char *str)
{
	char	*trimmed;
	
	trimmed = ft_strtrim(str, " \t\n\v\f\r");
	if (!trimmed)
		error_exit(ERR_MALLOC);
	return (trimmed);
}

static void	set_rgb_values(char **split, t_color *color)
{
	int		i;
	char	*trimmed;

	i = 0;
	while (i < 3)
	{
		trimmed = trim_spaces(split[i]);
		if (!trimmed || !*trimmed)
		{
			free(trimmed);
			while (i < 3)
				free(split[i++]);
			free(split);
			error_exit(ERR_COLOR_FORMAT);
		}
		if (!is_valid_number(trimmed))
		{
			free(trimmed);
			while (i < 3)
				free(split[i++]);
			free(split);
			error_exit(ERR_COLOR_FORMAT);
		}
		if (i == 0)
			color->r = ft_atoi(trimmed);
		else if (i == 1)
			color->g = ft_atoi(trimmed);
		else
			color->b = ft_atoi(trimmed);
		free(trimmed);
		i++;
	}
	i = 0;
	while (i < 3)
		free(split[i++]);
	free(split);
	if (color->r < 0 || color->r > 255 || color->g < 0 || color->g > 255
		|| color->b < 0 || color->b > 255)
		error_exit(ERR_COLOR_RANGE);
}

static void	parse_rgb(char *str, t_color *color)
{
	char	**split;
	int		i;

	validate_color_format(str);
	split = ft_split(str, ',');
	if (!split)
		error_exit(ERR_MALLOC);
	i = 0;
	while (split[i])
		i++;
	if (i != 3)
	{
		while (i >= 0)
			free(split[i--]);
		free(split);
		error_exit(ERR_COLOR_FORMAT);
	}
	set_rgb_values(split, color);
}

int	parse_colors(char *line, t_map_data *map)
{
	char	*trim;

	trim = ft_strtrim(line + 1, " \t");
	if (!trim)
		error_exit(ERR_MALLOC);
	if (line[0] == 'F')
	{
		if (map->floor.r != -1)
		{
			free(trim);
			error_exit(ERR_COLOR_DUP);
		}
		parse_rgb(trim, &map->floor);
	}
	else if (line[0] == 'C')
	{
		if (map->ceiling.r != -1)
		{
			free(trim);
			error_exit(ERR_COLOR_DUP);
		}
		parse_rgb(trim, &map->ceiling);
	}
	else
		return (free(trim), 0);
	return (free(trim), 1);
}
