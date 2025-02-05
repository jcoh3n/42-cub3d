/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcohen <jcohen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 20:12:39 by wander            #+#    #+#             */
/*   Updated: 2025/02/05 15:22:40 by jcohen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	get_texture_x(t_ray *ray, t_texture *texture)
{
	double	wall_x;
	int		tex_x;

	if (ray->is_vertical)
		wall_x = ray->wall_hit_y + (ray->distance * sin(ray->ray_angle));
	else
		wall_x = ray->wall_hit_x + (ray->distance * cos(ray->ray_angle));
	wall_x -= floor(wall_x);
	tex_x = (int)(wall_x * (double)texture->width);
	if ((ray->is_vertical && !ray->facing_right) || (!ray->is_vertical
			&& ray->facing_up))
		tex_x = texture->width - tex_x - 1;
	if (tex_x < 0)
		tex_x = 0;
	if (tex_x >= texture->width)
		tex_x = texture->width - 1;
	return (tex_x);
}

unsigned int	get_texture_color(t_texture *texture, int tex_x, int tex_y)
{
	char			*pixel_addr;
	unsigned char	*p;

	if (!texture->addr)
		return (0x0);
	pixel_addr = texture->addr + (tex_y * texture->line_length + tex_x
			* (texture->bits_per_pixel / 8));
	if (texture->endian == 1)
	{
		p = (unsigned char *)pixel_addr;
		return (p[0] << 24 | p[1] << 16 | p[2] << 8 | p[3]);
	}
	else
		return (*(unsigned int *)pixel_addr);
}

static void	init_wall_texture_aux(t_wall_render *wall, t_ray *ray,
		t_texture *texture)
{
	double	wall_x;

	if (ray->is_vertical)
		wall_x = wall->game->player.y + ray->distance * sin(ray->ray_angle);
	else
		wall_x = wall->game->player.x + ray->distance * cos(ray->ray_angle);
	wall_x -= floor(wall_x);
	wall->tex_x = (int)(wall_x * texture->width);
	if ((ray->is_vertical && !ray->facing_right) || (!ray->is_vertical
			&& ray->facing_up))
		wall->tex_x = texture->width - wall->tex_x - 1;
	if (wall->tex_x < 0)
		wall->tex_x = 0;
	if (wall->tex_x >= texture->width)
		wall->tex_x = texture->width - 1;
}

void	init_wall_texture(t_wall_render *wall, t_ray *ray, t_texture *texture,
		double perp_distance)
{
	init_wall_texture_aux(wall, ray, texture);
	wall->step = (double)texture->height / wall->wall_height;
	wall->tex_pos = (wall->wall_top - WINDOW_HEIGHT / 2 + wall->wall_height / 2)
		* wall->step;
	wall->shade = 1.0;
	if (perp_distance > 1.0)
	{
		wall->shade = 1.0 - (perp_distance / MAX_RENDER_DISTANCE) * SHADE_STEP;
		if (wall->shade < MIN_SHADE)
			wall->shade = MIN_SHADE;
	}
}
