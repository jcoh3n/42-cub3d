/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcohen <jcohen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 17:23:00 by jcohen            #+#    #+#             */
/*   Updated: 2025/01/28 12:32:57 by jcohen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	render_frame(t_game *game)
{
	clear_buffer(&game->img);
	cast_rays(game);
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
