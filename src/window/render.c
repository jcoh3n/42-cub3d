/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcohen <jcohen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 17:23:00 by jcohen            #+#    #+#             */
/*   Updated: 2025/01/30 16:52:37 by jcohen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	draw_mouse_status(t_game *game)
{
	int	i;
	int	j;
	int	color;
	int	size;

	size = 10;
	if (game->state.mouse_captured)
		color = STATUS_ON_COLOR;
	else
		color = STATUS_OFF_COLOR;
	i = -1;
	while (++i < size)
	{
		j = -1;
		while (++j < size)
			put_pixel(&game->renderer.frame, (WINDOW_WIDTH / 2) - (size / 2)
				+ j, 20 + i, color);
	}
}

void	render_frame(t_game *game)
{
	clear_buffer(&game->renderer.frame);
	cast_rays(game);
	draw_mouse_status(game);
	clear_minimap(game);
	update_minimap(game);
	if (game->renderer.win)
	{
		mlx_put_image_to_window(game->renderer.mlx, game->renderer.win,
			game->renderer.frame.img, 0, 0);
		if (game->renderer.minimap.img)
			mlx_put_image_to_window(game->renderer.mlx, game->renderer.win,
				game->renderer.minimap.img, game->renderer.minimap.pos_x,
				game->renderer.minimap.pos_y);
	}
}
