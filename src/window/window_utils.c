/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcohen <jcohen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 14:32:17 by jcohen            #+#    #+#             */
/*   Updated: 2025/01/30 14:35:44 by jcohen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	get_minimap_center_x(void)
{
	return (WINDOW_WIDTH - MINIMAP_RADIUS - 20);
}

int	get_minimap_center_y(void)
{
	return (MINIMAP_RADIUS + 20);
}

int	get_mouse_center_x(void)
{
	return (WINDOW_WIDTH / 2);
}

int	get_mouse_center_y(void)
{
	return (WINDOW_HEIGHT / 2);
}
