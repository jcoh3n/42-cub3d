/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wander <wander@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 20:12:26 by wander            #+#    #+#             */
/*   Updated: 2025/02/04 20:12:27 by wander           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_ray_and_dda(t_ray *ray, t_dda_data *dda, double ray_angle,
		t_game *game)
{
	ray->ray_angle = ray_angle;
	ray->facing_up = (sin(ray_angle) < 0);
	ray->facing_right = (cos(ray_angle) > 0);
	dda->ray_dir_x = cos(ray_angle);
	dda->ray_dir_y = sin(ray_angle);
	dda->delta_dist_x = fabs(1.0 / dda->ray_dir_x);
	dda->delta_dist_y = fabs(1.0 / dda->ray_dir_y);
	dda->map_x = (int)game->player.x;
	dda->map_y = (int)game->player.y;
}

void	calculate_step_and_side_dist(t_dda_data *dda, t_game *game)
{
	if (dda->ray_dir_x < 0)
		dda->step_x = -1;
	else
		dda->step_x = 1;
	if (dda->ray_dir_y < 0)
		dda->step_y = -1;
	else
		dda->step_y = 1;
	if (dda->ray_dir_x < 0)
		dda->side_dist_x = (game->player.x - dda->map_x) * dda->delta_dist_x;
	else
		dda->side_dist_x = (dda->map_x + 1.0 - game->player.x)
			* dda->delta_dist_x;
	if (dda->ray_dir_y < 0)
		dda->side_dist_y = (game->player.y - dda->map_y) * dda->delta_dist_y;
	else
		dda->side_dist_y = (dda->map_y + 1.0 - game->player.y)
			* dda->delta_dist_y;
}

static int	check_wall_hit(t_dda_data *dda, t_game *game)
{
	return (dda->map_x >= 0 && dda->map_x < game->map_data->width
		&& dda->map_y >= 0 && dda->map_y < game->map_data->height
		&& game->map_data->grid[dda->map_y][dda->map_x] == '1');
}

void	perform_dda(t_ray *ray, t_dda_data *dda, t_game *game)
{
	while (1)
	{
		if (dda->side_dist_x < dda->side_dist_y)
		{
			dda->side_dist_x += dda->delta_dist_x;
			dda->map_x += dda->step_x;
			ray->is_vertical = 1;
		}
		else
		{
			dda->side_dist_y += dda->delta_dist_y;
			dda->map_y += dda->step_y;
			ray->is_vertical = 0;
		}
		if (check_wall_hit(dda, game))
		{
			ray->wall_hit_x = dda->map_x;
			ray->wall_hit_y = dda->map_y;
			break ;
		}
	}
}

void	calculate_ray_distance(t_ray *ray, t_dda_data *dda, t_game *game)
{
	if (ray->is_vertical)
	{
		ray->distance = fabs((dda->map_x - game->player.x + (1 - dda->step_x)
					/ 2) / dda->ray_dir_x);
	}
	else
	{
		ray->distance = fabs((dda->map_y - game->player.y + (1 - dda->step_y)
					/ 2) / dda->ray_dir_y);
	}
}
