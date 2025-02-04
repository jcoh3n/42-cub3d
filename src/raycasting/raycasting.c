/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcohen <jcohen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/27 17:55:00 by jcohen            #+#    #+#             */
/*   Updated: 2025/02/04 19:09:06 by jcohen           ###   ########.fr       */
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

void	render_wall_stripe(t_game *game, int x, t_ray *ray)
{
	double			player_angle;
	double			perp_distance;
	int				wall_height;
	int				wall_top;
	int				wall_bottom;
	int				ceiling_color;
	t_texture		*texture;
	double			wall_x;
	int				tex_x;
	double			step;
	double			tex_pos;
	double			shade;
	int				tex_y;
	char			*pixel_addr;
	unsigned int	color;
	unsigned char	r;
	unsigned char	g;
	unsigned char	b;
	int				floor_color;
	int				y;

	player_angle = atan2(game->player.dir_y, game->player.dir_x);
	perp_distance = ray->distance * cos(ray->ray_angle - player_angle);
	wall_height = (int)(WINDOW_HEIGHT / perp_distance);
	wall_top = (WINDOW_HEIGHT - wall_height) / 2;
	wall_bottom = (WINDOW_HEIGHT + wall_height) / 2;
	if (wall_top < 0)
		wall_top = 0;
	if (wall_bottom >= WINDOW_HEIGHT)
		wall_bottom = WINDOW_HEIGHT - 1;
	ceiling_color = (game->map_data->ceiling.r << 16) | (game->map_data->ceiling.g << 8) | game->map_data->ceiling.b;
	y = 0;
	while (y < wall_top)
	{
		put_pixel(&game->renderer.frame, x, y, ceiling_color);
		y++;
	}
	texture = get_wall_texture(game, ray);
	if (ray->is_vertical)
		wall_x = game->player.y + ray->distance * sin(ray->ray_angle);
	else
		wall_x = game->player.x + ray->distance * cos(ray->ray_angle);
	wall_x -= floor(wall_x);
	tex_x = (int)(wall_x * texture->width);
	if ((ray->is_vertical && !ray->facing_right) || (!ray->is_vertical
			&& ray->facing_up))
		tex_x = texture->width - tex_x - 1;
	if (tex_x < 0)
		tex_x = 0;
	if (tex_x >= texture->width)
		tex_x = texture->width - 1;
	step = (double)texture->height / wall_height;
	tex_pos = (wall_top - WINDOW_HEIGHT / 2 + wall_height / 2) * step;
	shade = 1.0;
	if (perp_distance > 1.0)
	{
		shade = 1.0 - (perp_distance / MAX_RENDER_DISTANCE) * SHADE_STEP;
		if (shade < MIN_SHADE)
			shade = MIN_SHADE;
	}
	y = wall_top;
	while (y < wall_bottom)
	{
		tex_y = (int)tex_pos & (texture->height - 1);
		pixel_addr = texture->addr + (tex_y * texture->line_length + tex_x
				* (texture->bits_per_pixel / 8));
		if (texture->endian == 1)
			color = ((unsigned char)pixel_addr[0] << 24 | (unsigned char)pixel_addr[1] << 16 | (unsigned char)pixel_addr[2] << 8 | (unsigned char)pixel_addr[3]);
		else
			color = *(unsigned int *)pixel_addr;
		r = ((color >> 16) & 0xFF) * shade;
		g = ((color >> 8) & 0xFF) * shade;
		b = (color & 0xFF) * shade;
		color = (r << 16) | (g << 8) | b;
		put_pixel(&game->renderer.frame, x, y, color);
		tex_pos += step;
		y++;
	}
	floor_color = (game->map_data->floor.r << 16) | (game->map_data->floor.g << 8) | game->map_data->floor.b;
	y = wall_bottom;
	while (y < WINDOW_HEIGHT)
	{
		put_pixel(&game->renderer.frame, x, y, floor_color);
		y++;
	}
}

t_ray	cast_single_ray(t_game *game, double ray_angle)
{
	t_ray	ray;
	double	ray_dir_x;
	double	ray_dir_y;
	double	delta_dist_x;
	double	delta_dist_y;
	int		map_x;
	int		map_y;
	double	side_dist_x;
	double	side_dist_y;
	int		step_x;
	int		step_y;

	ray.ray_angle = ray_angle;
	ray.facing_up = (sin(ray_angle) < 0);
	ray.facing_right = (cos(ray_angle) > 0);
	ray_dir_x = cos(ray_angle);
	ray_dir_y = sin(ray_angle);
	delta_dist_x = fabs(1.0 / ray_dir_x);
	delta_dist_y = fabs(1.0 / ray_dir_y);
	map_x = (int)game->player.x;
	map_y = (int)game->player.y;
	if (ray_dir_x < 0)
		step_x = -1;
	else
		step_x = 1;
	if (ray_dir_y < 0)
		step_y = -1;
	else
		step_y = 1;
	if (ray_dir_x < 0)
		side_dist_x = (game->player.x - map_x) * delta_dist_x;
	else
		side_dist_x = (map_x + 1.0 - game->player.x) * delta_dist_x;
	if (ray_dir_y < 0)
		side_dist_y = (game->player.y - map_y) * delta_dist_y;
	else
		side_dist_y = (map_y + 1.0 - game->player.y) * delta_dist_y;
	while (1)
	{
		if (side_dist_x < side_dist_y)
		{
			side_dist_x += delta_dist_x;
			map_x += step_x;
			ray.is_vertical = 1;
		}
		else
		{
			side_dist_y += delta_dist_y;
			map_y += step_y;
			ray.is_vertical = 0;
		}
		if (map_x >= 0 && map_x < game->map_data->width && map_y >= 0
			&& map_y < game->map_data->height
			&& game->map_data->grid[map_y][map_x] == '1')
		{
			ray.wall_hit_x = map_x;
			ray.wall_hit_y = map_y;
			break ;
		}
	}
	if (ray.is_vertical)
		ray.distance = (map_x - game->player.x + (1 - step_x) / 2) / ray_dir_x;
	else
		ray.distance = (map_y - game->player.y + (1 - step_y) / 2) / ray_dir_y;
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
