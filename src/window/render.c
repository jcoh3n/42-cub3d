/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcohen <jcohen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 17:23:00 by jcohen            #+#    #+#             */
/*   Updated: 2025/01/28 17:51:03 by jcohen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	draw_rounded_rectangle(t_img *img, int x, int y, int width,
		int height, int color)
{
	int		i;
	int		j;
	int		radius;
	double	distance;

	radius = height / 4;
	i = -1;
	while (++i < height)
	{
		j = -1;
		while (++j < width)
		{
			// Check corners
			if (i < radius && j < radius)
			{
				distance = sqrt(pow(radius - j, 2) + pow(radius - i, 2));
				if (distance > radius)
					continue ;
			}
			else if (i < radius && j > width - radius)
			{
				distance = sqrt(pow(j - (width - radius), 2) + pow(radius - i,
							2));
				if (distance > radius)
					continue ;
			}
			else if (i > height - radius && j < radius)
			{
				distance = sqrt(pow(radius - j, 2) + pow(i - (height - radius),
							2));
				if (distance > radius)
					continue ;
			}
			else if (i > height - radius && j > width - radius)
			{
				distance = sqrt(pow(j - (width - radius), 2) + pow(i - (height
								- radius), 2));
				if (distance > radius)
					continue ;
			}
			put_pixel(img, x + j, y + i, color);
		}
	}
}

static void	draw_mouse_status(t_game *game)
{
	int	x;
	int	y;
	int	color;

	// Calculate position (centered at top)
	x = (WINDOW_WIDTH - STATUS_WIDTH) / 2;
	y = STATUS_PADDING;
	// Draw background with rounded corners
	draw_rounded_rectangle(&game->img, x, y, STATUS_WIDTH, STATUS_HEIGHT,
		STATUS_BG_COLOR);
	// Draw status indicator with rounded corners (slightly smaller)
	color = game->mouse_captured ? STATUS_ON_COLOR : STATUS_OFF_COLOR;
	draw_rounded_rectangle(&game->img, x + 2, y + 2, STATUS_WIDTH - 4,
		STATUS_HEIGHT - 4, color);
}

void	render_frame(t_game *game)
{
	clear_buffer(&game->img);
	cast_rays(game);
	draw_mouse_status(game);
	clear_minimap(game);
	update_minimap(game);
	if (game->win)
	{
		mlx_put_image_to_window(game->mlx, game->win, game->img.img, 0, 0);
		if (game->minimap.img)
			mlx_put_image_to_window(game->mlx, game->win, game->minimap.img,
				game->minimap.pos_x, game->minimap.pos_y);
	}
}
