/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window_events.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcohen <jcohen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 15:32:51 by jcohen            #+#    #+#             */
/*   Updated: 2025/01/20 19:11:52 by jcohen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	handle_window_close(t_game *game)
{
	game->is_running = 0;
	cleanup_game(game);
	exit(0);
	return (0);
}

int	handle_window_focus(int focused, t_game *game)
{
	game->window_focused = focused;
	return (0);
}

int	handle_keypress(int keycode, t_game *game)
{
	if (keycode == KEY_ESC)
		handle_window_close(game);
	return (0);
}

void	setup_window_hooks(t_game *game)
{
	mlx_hook(game->win, 17, 0, handle_window_close, game);
	mlx_hook(game->win, 9, 1L << 21, handle_window_focus, game);
	mlx_hook(game->win, 2, 1L << 0, handle_keypress, game);
}
