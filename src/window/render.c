/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcohen <jcohen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 17:23:00 by jcohen            #+#    #+#             */
/*   Updated: 2025/01/27 17:29:06 by jcohen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	render_frame(t_game *game)
{
	clear_minimap(game);
	update_minimap(game);
	if (game->minimap.img && game->win)
		mlx_put_image_to_window(game->mlx, game->win, game->minimap.img,
			game->minimap.pos_x, game->minimap.pos_y);
}
