/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_colors_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcohen <jcohen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 17:19:37 by jcohen            #+#    #+#             */
/*   Updated: 2025/01/30 17:29:08 by jcohen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	is_valid_number(char *str)
{
	int	i;

	i = 0;
	while (str[i] && ft_isspace(str[i]))
		i++;
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

static void	set_rgb_value(t_color *color, char *value, int index)
{
	int	num;

	num = ft_atoi(value);
	if (num < 0 || num > 255)
		error_exit(ERR_COLOR_RANGE);
	if (index == 0)
		color->r = num;
	else if (index == 1)
		color->g = num;
	else
		color->b = num;
}

static int	is_valid_color_char(char c)
{
	return (c == ',' || ft_isdigit(c) || ft_isspace(c));
}

void	validate_color_format(char *str)
{
	int	i;
	int	comma_count;

	i = 0;
	comma_count = 0;
	while (str[i])
	{
		if (!is_valid_color_char(str[i]))
			error_exit(ERR_COLOR_FORMAT);
		if (str[i] == ',')
			comma_count++;
		i++;
	}
	if (comma_count != 2)
		error_exit(ERR_COLOR_FORMAT);
}

void	parse_rgb_values(char *str, t_color *color)
{
	char	**split;
	char	*trimmed;
	int		i;

	validate_color_format(str);
	split = ft_split(str, ',');
	if (!split)
		error_exit(ERR_MALLOC);
	i = 0;
	while (split[i])
		i++;
	if (i != 3)
		error_exit(ERR_COLOR_FORMAT);
	i = 0;
	while (i < 3)
	{
		trimmed = ft_strtrim(split[i], " \t\n\v\f\r");
		if (!trimmed || !*trimmed || !is_valid_number(trimmed))
			error_exit(ERR_COLOR_FORMAT);
		set_rgb_value(color, trimmed, i);
		free(trimmed);
		free(split[i]);
		i++;
	}
	free(split);
}
