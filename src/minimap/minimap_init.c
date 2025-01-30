/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_init.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcohen <jcohen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 17:51:47 by jcohen            #+#    #+#             */
/*   Updated: 2025/01/30 17:51:57 by jcohen           ###   ########.fr       */
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

int	is_in_circle(int x, int y, int center_x, int center_y)
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
