/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcohen <jcohen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/27 17:55:00 by jcohen            #+#    #+#             */
/*   Updated: 2025/02/04 19:24:28 by jcohen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

#define MAX_RENDER_DISTANCE 10.0
#define MIN_SHADE 0.3
#define SHADE_STEP 0.7

t_texture	*get_wall_texture(t_game *game, t_ray *ray)
{
	if (ray->is_vertical)
	{
		if (ray->facing_right)
			return (&game->map_data->east);
		return (&game->map_data->west);
	}
	else
	{
		if (ray->facing_up)
			return (&game->map_data->north);
		return (&game->map_data->south);
	}
}

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
	char	*pixel_addr;

	if (!texture->addr)
		return (0x0);
	pixel_addr = texture->addr + (tex_y * texture->line_length + tex_x
			* (texture->bits_per_pixel / 8));
	if (texture->endian == 1)
		return ((unsigned char)pixel_addr[0] << 24 | (unsigned char)pixel_addr[1] << 16 | (unsigned char)pixel_addr[2] << 8 | (unsigned char)pixel_addr[3]);
	else
		return (*(unsigned int *)pixel_addr);
}

void	init_wall_dimensions(t_wall_render *wall, double perp_distance)
{
	wall->wall_height = (int)((double)WINDOW_HEIGHT / perp_distance);
	wall->wall_top = -wall->wall_height / 2 + WINDOW_HEIGHT / 2;
	wall->wall_bottom = wall->wall_height / 2 + WINDOW_HEIGHT / 2;
	if (wall->wall_top < 0)
		wall->wall_top = 0;
	if (wall->wall_bottom >= WINDOW_HEIGHT)
		wall->wall_bottom = WINDOW_HEIGHT - 1;
}

void	draw_ceiling(t_game *game, int x, t_wall_render *wall,
		t_color_data *colors)
{
	int	y;

	colors->ceiling_color = (game->map_data->ceiling.r << 16) | (game->map_data->ceiling.g << 8) | game->map_data->ceiling.b;
	y = 0;
	while (y < wall->wall_top)
	{
		put_pixel(&game->renderer.frame, x, y, colors->ceiling_color);
		y++;
	}
}

void	init_wall_texture(t_wall_render *wall, t_ray *ray, t_texture *texture,
		double perp_distance, t_game *game)
{
	double	wall_x;

	if (ray->is_vertical)
		wall_x = game->player.y + ray->distance * sin(ray->ray_angle);
	else
		wall_x = game->player.x + ray->distance * cos(ray->ray_angle);
	wall_x -= floor(wall_x);
	wall->tex_x = (int)(wall_x * texture->width);
	if ((ray->is_vertical && !ray->facing_right) || (!ray->is_vertical
			&& ray->facing_up))
		wall->tex_x = texture->width - wall->tex_x - 1;
	if (wall->tex_x < 0)
		wall->tex_x = 0;
	if (wall->tex_x >= texture->width)
		wall->tex_x = texture->width - 1;
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

void	draw_textured_wall(t_game *game, int x, t_wall_render *wall,
		t_texture *texture, t_color_data *colors)
{
	int		y;
	char	*pixel_addr;

	y = wall->wall_top;
	while (y < wall->wall_bottom)
	{
		wall->tex_y = (int)wall->tex_pos & (texture->height - 1);
		pixel_addr = texture->addr + (wall->tex_y * texture->line_length
				+ wall->tex_x * (texture->bits_per_pixel / 8));
		if (texture->endian == 1)
			colors->color = ((unsigned char)pixel_addr[0] << 24 | (unsigned char)pixel_addr[1] << 16 | (unsigned char)pixel_addr[2] << 8 | (unsigned char)pixel_addr[3]);
		else
			colors->color = *(unsigned int *)pixel_addr;
		colors->r = ((colors->color >> 16) & 0xFF) * wall->shade;
		colors->g = ((colors->color >> 8) & 0xFF) * wall->shade;
		colors->b = (colors->color & 0xFF) * wall->shade;
		colors->color = (colors->r << 16) | (colors->g << 8) | colors->b;
		put_pixel(&game->renderer.frame, x, y, colors->color);
		wall->tex_pos += wall->step;
		y++;
	}
}

void	draw_floor(t_game *game, int x, t_wall_render *wall,
		t_color_data *colors)
{
	int	y;

	colors->floor_color = (game->map_data->floor.r << 16) | (game->map_data->floor.g << 8) | game->map_data->floor.b;
	y = wall->wall_bottom;
	while (y < WINDOW_HEIGHT)
	{
		put_pixel(&game->renderer.frame, x, y, colors->floor_color);
		y++;
	}
}

void	render_wall_stripe(t_game *game, int x, t_ray *ray)
{
	double			player_angle;
	double			perp_distance;
	t_texture		*texture;
	t_wall_render	wall;
	t_color_data	colors;

	player_angle = atan2(game->player.dir_y, game->player.dir_x);
	perp_distance = ray->distance * cos(ray->ray_angle - player_angle);
	init_wall_dimensions(&wall, perp_distance);
	draw_ceiling(game, x, &wall, &colors);
	texture = get_wall_texture(game, ray);
	init_wall_texture(&wall, ray, texture, perp_distance, game);
	draw_textured_wall(game, x, &wall, texture, &colors);
	draw_floor(game, x, &wall, &colors);
}

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

int	check_wall_hit(t_dda_data *dda, t_game *game)
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
