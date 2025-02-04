/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcohen <jcohen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/27 17:55:00 by jcohen            #+#    #+#             */
/*   Updated: 2025/02/04 20:03:24 by jcohen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_ray	cast_single_ray(t_game *game, double ray_angle)
{
	t_ray		ray;
	t_dda_data	dda;

	init_ray_and_dda(&ray, &dda, ray_angle, game);
	calculate_step_and_side_dist(&dda, game);
	perform_dda(&ray, &dda, game);
	calculate_ray_distance(&ray, &dda, game);
	return (ray);
}

void	cast_rays(t_game *game)
{
	double	player_angle;
	double	ray_angle;
	double	angle_step;
	t_ray	ray;
	int		x;

	player_angle = atan2(game->player.dir_y, game->player.dir_x);
	ray_angle = player_angle - (FOV / 2);
	angle_step = FOV / WINDOW_WIDTH;
	x = 0;
	while (x < WINDOW_WIDTH)
	{
		ray = cast_single_ray(game, ray_angle);
		render_wall_stripe(game, x, &ray);
		ray_angle += angle_step;
		x++;
	}
}
