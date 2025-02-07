/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcohen <jcohen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 16:35:00 by jcohen            #+#    #+#             */
/*   Updated: 2025/02/07 20:19:23 by jcohen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

double	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((double)tv.tv_sec + (double)tv.tv_usec / 1000000.0);
}

void	error_exit(char *message)
{
	ft_putstr_fd("Error\n", 2);
	ft_putstr_fd(message, 2);
	ft_putstr_fd("\n", 2);
	exit(1);
}

int	game_loop(t_game *game)
{
	if (!game->state.is_running)
	{
		mlx_loop_end(game->renderer.mlx);
		return (1);
	}
	update_player_position(game);
	render_frame(game);
	return (0);
}

unsigned int	get_rgb_color(t_color color)
{
	return ((color.r << 16) | (color.g << 8) | color.b);
}

void	free_2d_array(char **array, int height)
{
	int	i;

	if (!array)
		return ;
	i = 0;
	if (height == -1)
	{
		while (array[i])
			free(array[i++]);
	}
	else
	{
		while (i < height)
		{
			if (array[i])
			{
				free(array[i]);
				array[i] = NULL;
			}
			i++;
		}
	}
	free(array);
}
