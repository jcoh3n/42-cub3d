/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_drw_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcohen <jcohen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 17:54:06 by jcohen            #+#    #+#             */
/*   Updated: 2025/01/30 17:54:27 by jcohen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	is_point_in_triangle(t_point p, t_point *triangle)
{
	int	inside;
	int	i;
	int	j;

	inside = 0;
	i = 0;
	while (i < 3)
	{
		j = (i + 1) % 3;
		if ((triangle[i].y - triangle[j].y) * (p.x - triangle[j].x)
			- (triangle[i].x - triangle[j].x) * (p.y - triangle[j].y) > 0)
			inside++;
		i++;
	}
	return (inside == 3);
}

void	draw_player_triangle(t_game *game, t_draw_player_data *data)
{
	t_point	p;
	t_point	triangle[3];
	int		size;
	int		i;

	size = data->size;
	i = 0;
	while (i < 3)
	{
		triangle[i].x = data->arrow_x[i];
		triangle[i].y = data->arrow_y[i];
		i++;
	}
	p.y = MINIMAP_RADIUS - size * 2;
	while (p.y <= MINIMAP_RADIUS + size * 2)
	{
		p.x = MINIMAP_RADIUS - size * 2;
		while (p.x <= MINIMAP_RADIUS + size * 2)
		{
			if (is_point_in_triangle(p, triangle))
				put_pixel_minimap(game, p.x, p.y, PLAYER_COLOR);
			p.x++;
		}
		p.y++;
	}
}

void	draw_border(t_game *game)
{
	int		angle;
	double	rad;
	int		r;
	t_point	p;

	angle = 0;
	while (angle < 360)
	{
		rad = angle * M_PI / 180;
		r = MINIMAP_RADIUS - BORDER_THICKNESS;
		while (r <= MINIMAP_RADIUS)
		{
			p.x = MINIMAP_RADIUS + r * cos(rad);
			p.y = MINIMAP_RADIUS + r * sin(rad);
			put_pixel_minimap(game, p.x, p.y, MINIMAP_BORDER_COLOR);
			r++;
		}
		angle++;
	}
}
