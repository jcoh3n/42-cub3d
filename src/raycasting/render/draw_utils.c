/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcohen <jcohen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 20:12:36 by wander            #+#    #+#             */
/*   Updated: 2025/02/05 15:34:17 by jcohen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_ceiling(t_game *game, int x, t_wall_render *wall,
		t_color_data *colors)
{
	int				y;
	unsigned int	r;
	unsigned int	g;
	unsigned int	b;

	r = game->map_data->ceiling.r;
	g = game->map_data->ceiling.g;
	b = game->map_data->ceiling.b;
	colors->ceiling_color = (r << 16) | (g << 8) | b;
	y = 0;
	while (y < wall->wall_top)
	{
		put_pixel(&game->renderer.frame, x, y, colors->ceiling_color);
		y++;
	}
}

static unsigned int	get_pixel_color(char *pixel_addr, int endian)
{
	unsigned char	*p;

	p = (unsigned char *)pixel_addr;
	if (endian == 1)
		return (p[0] << 24 | p[1] << 16 | p[2] << 8 | p[3]);
	return (*(unsigned int *)pixel_addr);
}

static void	draw_textured_wall_aux(t_wall_render *wall, t_texture *texture,
		t_color_data *colors, char *pixel_addr)
{
	if (texture->endian == 1)
		colors->color = get_pixel_color(pixel_addr, texture->endian);
	else
		colors->color = *(unsigned int *)pixel_addr;
	colors->r = ((colors->color >> 16) & 0xFF) * wall->shade;
	colors->g = ((colors->color >> 8) & 0xFF) * wall->shade;
	colors->b = (colors->color & 0xFF) * wall->shade;
	colors->color = (colors->r << 16) | (colors->g << 8) | colors->b;
}

void	draw_textured_wall(t_game *game, int x, t_wall_render *wall,
		t_texture *texture)
{
	int				y;
	char			*pixel_addr;
	t_color_data	colors;

	y = wall->wall_top;
	while (y < wall->wall_bottom)
	{
		wall->tex_y = (int)wall->tex_pos & (texture->height - 1);
		pixel_addr = texture->addr + (wall->tex_y * texture->line_length
				+ wall->tex_x * (texture->bits_per_pixel / 8));
		draw_textured_wall_aux(wall, texture, &colors, pixel_addr);
		put_pixel(&game->renderer.frame, x, y, colors.color);
		wall->tex_pos += wall->step;
		y++;
	}
}

void	draw_floor(t_game *game, int x, t_wall_render *wall,
		t_color_data *colors)
{
	int	y;

	colors->floor_color = get_rgb_color(game->map_data->floor);
	y = wall->wall_bottom;
	while (y < WINDOW_HEIGHT)
	{
		put_pixel(&game->renderer.frame, x, y, colors->floor_color);
		y++;
	}
}
