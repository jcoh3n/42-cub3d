/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buffer_management.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcohen <jcohen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 15:32:51 by jcohen            #+#    #+#             */
/*   Updated: 2025/01/20 19:25:23 by jcohen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	put_pixel(t_img *img, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || x >= WINDOW_WIDTH || y < 0 || y >= WINDOW_HEIGHT)
		return ;
	dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void	clear_buffer(t_img *img)
{
	ft_memset(img->addr, 0, WINDOW_HEIGHT * img->line_length);
}

void	swap_buffers(t_game *game)
{
	if (game->window_focused)
		mlx_put_image_to_window(game->mlx, game->win, game->img.img, 0, 0);
}

void	draw_test_pattern(t_game *game)
{
	int	x;
	int	y;
	int	color;

	y = 0;
	while (y < WINDOW_HEIGHT)
	{
		x = 0;
		while (x < WINDOW_WIDTH)
		{
			if ((x / 32 + y / 32) % 2)
				color = 0x00FF00;
			else
				color = 0x0000FF;
			put_pixel(&game->img, x, y, color);
			x++;
		}
		y++;
	}
}

int	create_rgb(int r, int g, int b)
{
	return (r << 16 | g << 8 | b);
}
