#include "cub3d.h"

#define MAX_RENDER_DISTANCE 10.0
#define MIN_SHADE 0.3
#define SHADE_STEP 0.7

t_texture	*get_wall_texture(t_game *game, t_ray *ray)
{
	if (ray->is_vertical)
	{
		if (ray->facing_right)
			return (&game->map_data->east);
		return (&game->map_data->west);
	}
	else
	{
		if (ray->facing_up)
			return (&game->map_data->north);
		return (&game->map_data->south);
	}
}

void	init_wall_dimensions(t_wall_render *wall, double perp_distance)
{
	wall->wall_height = (int)((double)WINDOW_HEIGHT / perp_distance);
	wall->wall_top = -wall->wall_height / 2 + WINDOW_HEIGHT / 2;
	wall->wall_bottom = wall->wall_height / 2 + WINDOW_HEIGHT / 2;
	if (wall->wall_top < 0)
		wall->wall_top = 0;
	if (wall->wall_bottom >= WINDOW_HEIGHT)
		wall->wall_bottom = WINDOW_HEIGHT - 1;
}

void	render_wall_stripe(t_game *game, int x, t_ray *ray)
{
	double			player_angle;
	double			perp_distance;
	t_texture		*texture;
	t_wall_render	wall;
	t_color_data	colors;

	player_angle = atan2(game->player.dir_y, game->player.dir_x);
	perp_distance = ray->distance * cos(ray->ray_angle - player_angle);
	init_wall_dimensions(&wall, perp_distance);
	draw_ceiling(game, x, &wall, &colors);
	texture = get_wall_texture(game, ray);
	init_wall_texture(&wall, ray, texture, perp_distance, game);
	draw_textured_wall(game, x, &wall, texture, &colors);
	draw_floor(game, x, &wall, &colors);
}
