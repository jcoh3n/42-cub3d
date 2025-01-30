/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcohen <jcohen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 15:00:00 by jcohen            #+#    #+#             */
/*   Updated: 2025/01/30 17:09:51 by jcohen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_minimap(t_game *game)
{
	t_minimap	*minimap;
	int			bits_per_pixel;
	int			line_length;
	int			endian;

	if (!game)
		error_exit(ERR_MALLOC);
	minimap = &game->renderer.minimap;
	ft_bzero(minimap, sizeof(t_minimap));
	minimap->width = MINIMAP_RADIUS * 2;
	minimap->height = MINIMAP_RADIUS * 2;
	minimap->scale = MINIMAP_SCALE;
	minimap->pos_x = get_minimap_center_x() - MINIMAP_RADIUS;
	minimap->pos_y = get_minimap_center_y() - MINIMAP_RADIUS;
	minimap->img = mlx_new_image(game->renderer.mlx, minimap->width,
			minimap->height);
	if (!minimap->img)
		error_exit(ERR_IMAGE_INIT);
	minimap->addr = (int *)mlx_get_data_addr(minimap->img, &bits_per_pixel,
			&line_length, &endian);
	if (!minimap->addr)
		error_exit(ERR_IMAGE_ADDR);
	minimap->bits_per_pixel = bits_per_pixel;
	minimap->line_length = line_length;
	minimap->endian = endian;
}

static int	is_in_circle(int x, int y, int center_x, int center_y)
{
	int	dx;
	int	dy;

	dx = x - center_x;
	dy = y - center_y;
	return (dx * dx + dy * dy <= MINIMAP_RADIUS * MINIMAP_RADIUS);
}

void	put_pixel_minimap(t_game *game, int x, int y, int color)
{
	t_minimap	*minimap;
	int			index;

	minimap = &game->renderer.minimap;
	if (x < 0 || x >= minimap->width || y < 0 || y >= minimap->height)
		return ;
	if (!is_in_circle(x, y, MINIMAP_RADIUS, MINIMAP_RADIUS))
		return ;
	index = y * (minimap->line_length / 4) + x;
	minimap->addr[index] = color;
}

void	draw_square(t_game *game, int map_x, int map_y, int color)
{
	int	x;
	int	y;
	int	scale;
	int	screen_x;
	int	screen_y;
	int	player_offset_x;
	int	player_offset_y;

	scale = game->renderer.minimap.scale;
	player_offset_x = (int)(game->player.x * scale) - MINIMAP_RADIUS;
	player_offset_y = (int)(game->player.y * scale) - MINIMAP_RADIUS;
	y = 0;
	while (y < scale)
	{
		x = 0;
		while (x < scale)
		{
			screen_x = map_x * scale + x - player_offset_x;
			screen_y = map_y * scale + y - player_offset_y;
			put_pixel_minimap(game, screen_x, screen_y, color);
			x++;
		}
		y++;
	}
}

void	draw_player(t_game *game)
{
	double	angle;
	int		size;
	int		arrow_x[3];
	int		arrow_y[3];
	int		px;
	int		py;
	int		inside;
	int		j;

	size = game->renderer.minimap.scale * 1.5;
	if (size < 12)
		size = 12;
	angle = atan2(game->player.dir_y, game->player.dir_x);
	arrow_x[0] = MINIMAP_RADIUS + (int)(size * 1.1 * cos(angle));
	arrow_y[0] = MINIMAP_RADIUS + (int)(size * 1.1 * sin(angle));
	arrow_x[1] = MINIMAP_RADIUS + (int)(size * 0.7 * cos(angle + M_PI * 0.72));
	arrow_y[1] = MINIMAP_RADIUS + (int)(size * 0.7 * sin(angle + M_PI * 0.72));
	arrow_x[2] = MINIMAP_RADIUS + (int)(size * 0.7 * cos(angle - M_PI * 0.72));
	arrow_y[2] = MINIMAP_RADIUS + (int)(size * 0.7 * sin(angle - M_PI * 0.72));
	for (int y = -size * 2; y <= size * 2; y++)
	{
		for (int x = -size * 2; x <= size * 2; x++)
		{
			px = MINIMAP_RADIUS + x;
			py = MINIMAP_RADIUS + y;
			inside = 0;
			for (int i = 0; i < 3; i++)
			{
				j = (i + 1) % 3;
				if ((arrow_y[i] - arrow_y[j]) * (px - arrow_x[j]) - (arrow_x[i]
						- arrow_x[j]) * (py - arrow_y[j]) > 0)
					inside++;
			}
			if (inside == 3)
			{
				put_pixel_minimap(game, px, py, PLAYER_COLOR);
			}
		}
	}
}

void	draw_border(t_game *game)
{
	int		x;
	int		y;
	int		center_x;
	int		center_y;
	double	rad;

	center_x = MINIMAP_RADIUS;
	center_y = MINIMAP_RADIUS;
	for (int angle = 0; angle < 360; angle++)
	{
		rad = angle * M_PI / 180;
		for (int r = MINIMAP_RADIUS
			- BORDER_THICKNESS; r <= MINIMAP_RADIUS; r++)
		{
			x = center_x + r * cos(rad);
			y = center_y + r * sin(rad);
			put_pixel_minimap(game, x, y, MINIMAP_BORDER_COLOR);
		}
	}
}

void	clear_minimap(t_game *game)
{
	int	x;
	int	y;

	for (y = 0; y < game->renderer.minimap.height; y++)
	{
		for (x = 0; x < game->renderer.minimap.width; x++)
		{
			if (is_in_circle(x, y, MINIMAP_RADIUS, MINIMAP_RADIUS))
				put_pixel_minimap(game, x, y, MINIMAP_BACKGROUND);
		}
	}
}

void	update_minimap(t_game *game)
{
	int	view_range;
	int	map_x;
	int	map_y;

	int x, y;
	view_range = (MINIMAP_RADIUS / game->renderer.minimap.scale) + 1;
	map_x = (int)game->player.x;
	map_y = (int)game->player.y;
	clear_minimap(game);
	for (y = map_y - view_range; y <= map_y + view_range; y++)
	{
		for (x = map_x - view_range; x <= map_x + view_range; x++)
		{
			if (x >= 0 && x < game->map_data->width && y >= 0
				&& y < game->map_data->height)
			{
				if (game->map_data->grid[y][x] == '1')
					draw_square(game, x, y, WALL_COLOR);
				else if (game->map_data->grid[y][x] == '0' || ft_strchr("NSEW",
						game->map_data->grid[y][x]))
				{
					if (game->map_data->flood_grid[y][x] == 'F')
						draw_square(game, x, y, FLOOR_COLOR);
					else
						draw_square(game, x, y, WALL_COLOR);
				}
			}
		}
	}
	draw_player(game);
	draw_border(game);
}
