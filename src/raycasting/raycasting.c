/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcohen <jcohen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/27 17:55:00 by jcohen            #+#    #+#             */
/*   Updated: 2025/01/27 18:06:04 by jcohen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int get_wall_color(t_ray *ray)
{
    if (ray->is_vertical)
    {
        if (ray->facing_right)
            return (0x00FF0000);  // Red for east walls
        return (0x0000FF00);      // Green for west walls
    }
    else
    {
        if (ray->facing_up)
            return (0x000000FF);  // Blue for north walls
        return (0x00FFFF00);      // Yellow for south walls
    }
}

void render_wall_stripe(t_game *game, int x, t_ray *ray)
{
    // Calculate perpendicular distance to prevent fisheye effect
    double player_angle = atan2(game->player.dir_y, game->player.dir_x);
    double perp_distance = ray->distance * cos(ray->ray_angle - player_angle);
    
    // Calculate wall height
    int wall_height = (int)(WINDOW_HEIGHT / perp_distance);
    
    // Calculate wall top and bottom
    int wall_top = (WINDOW_HEIGHT - wall_height) / 2;
    int wall_bottom = (WINDOW_HEIGHT + wall_height) / 2;
    
    // Clamp values
    if (wall_top < 0)
        wall_top = 0;
    if (wall_bottom > WINDOW_HEIGHT)
        wall_bottom = WINDOW_HEIGHT;
    
    // Draw ceiling
    int ceiling_color = (game->map_data->ceiling.r << 16) | 
                       (game->map_data->ceiling.g << 8) | 
                       game->map_data->ceiling.b;
    for (int y = 0; y < wall_top; y++)
        put_pixel(&game->img, x, y, ceiling_color);
    
    // Draw wall
    int wall_color = get_wall_color(ray);
    for (int y = wall_top; y < wall_bottom; y++)
        put_pixel(&game->img, x, y, wall_color);
    
    // Draw floor
    int floor_color = (game->map_data->floor.r << 16) | 
                     (game->map_data->floor.g << 8) | 
                     game->map_data->floor.b;
    for (int y = wall_bottom; y < WINDOW_HEIGHT; y++)
        put_pixel(&game->img, x, y, floor_color);
}

t_ray cast_single_ray(t_game *game, double ray_angle)
{
    t_ray ray;
    ray.ray_angle = ray_angle;
    
    // Initialize ray direction flags
    ray.facing_up = (sin(ray_angle) < 0);
    ray.facing_right = (cos(ray_angle) > 0);
    
    // Ray direction vector
    double ray_dir_x = cos(ray_angle);
    double ray_dir_y = sin(ray_angle);
    
    // Calculate delta distance
    double delta_dist_x = fabs(1.0 / ray_dir_x);
    double delta_dist_y = fabs(1.0 / ray_dir_y);
    
    // Current map position
    int map_x = (int)game->player.x;
    int map_y = (int)game->player.y;
    
    // Length of ray from current position to next x or y-side
    double side_dist_x;
    double side_dist_y;
    
    // Direction to step in x or y direction (either +1 or -1)
    int step_x = (ray_dir_x < 0) ? -1 : 1;
    int step_y = (ray_dir_y < 0) ? -1 : 1;
    
    // Calculate initial side_dist
    if (ray_dir_x < 0)
        side_dist_x = (game->player.x - map_x) * delta_dist_x;
    else
        side_dist_x = (map_x + 1.0 - game->player.x) * delta_dist_x;
    if (ray_dir_y < 0)
        side_dist_y = (game->player.y - map_y) * delta_dist_y;
    else
        side_dist_y = (map_y + 1.0 - game->player.y) * delta_dist_y;
    
    // Perform DDA
    while (1)
    {
        // Jump to next map square
        if (side_dist_x < side_dist_y)
        {
            side_dist_x += delta_dist_x;
            map_x += step_x;
            ray.is_vertical = 1;
        }
        else
        {
            side_dist_y += delta_dist_y;
            map_y += step_y;
            ray.is_vertical = 0;
        }
        
        // Check if ray has hit a wall
        if (map_x >= 0 && map_x < game->map_data->width &&
            map_y >= 0 && map_y < game->map_data->height &&
            game->map_data->grid[map_y][map_x] == '1')
        {
            ray.wall_hit_x = map_x;
            ray.wall_hit_y = map_y;
            break;
        }
    }
    
    // Calculate distance
    if (ray.is_vertical)
        ray.distance = (map_x - game->player.x + (1 - step_x) / 2) / ray_dir_x;
    else
        ray.distance = (map_y - game->player.y + (1 - step_y) / 2) / ray_dir_y;
    
    return (ray);
}

void cast_rays(t_game *game)
{
    // Calculate starting ray angle based on player's direction
    double player_angle = atan2(game->player.dir_y, game->player.dir_x);
    double ray_angle = player_angle - (FOV / 2);
    double angle_step = FOV / WINDOW_WIDTH;
    
    for (int x = 0; x < WINDOW_WIDTH; x++)
    {
        // Cast a single ray
        t_ray ray = cast_single_ray(game, ray_angle);
        
        // Render wall stripe
        render_wall_stripe(game, x, &ray);
        
        // Move to next ray
        ray_angle += angle_step;
    }
}
