# Graphics and Raycasting Technical Guide

## Two-Step Development Approach

### Step 1: Basic Raycasting
- Implementation of raycasting with solid colors
- Focus on core mechanics and distance calculations
- Simple rendering with wall orientation differentiation
- Easy collision and geometry testing
- Simpler debugging with basic rendering

### Step 2: Adding Textures
- Integration of textures once raycasting is functional
- Implementation of texture mapping on walls
- Handling different textures based on orientation (NO, SO, WE, EA)
- Optimization of texture rendering
- Visual polish of the project

This two-step approach allows:
- Breaking down the problem into manageable parts
- Easier testing and debugging
- Getting a working render quickly
- Adding complexity progressively
- Maintaining a clean and tested codebase

## 1. Core Components

### Key Data Structures
```c
typedef struct s_ray {
    double ray_angle;    // Current ray angle
    double distance;     // Distance to wall
    int wall_hit_x;     // Wall hit coordinates
    int wall_hit_y;
    int is_vertical;    // Hit vertical or horizontal wall
    int facing_up;      // Ray direction flags
    int facing_right;
} t_ray;
```

## 2. Step 1: Basic Color Rendering

### Colors Based on Wall Orientation
```c
int get_wall_color(t_ray *ray)
{
    // Different colors for wall orientation
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
```

### Simple Wall Rendering
```c
void render_wall_stripe(t_game *game, int x, int start_y, int end_y, t_ray *ray)
{
    int color = get_wall_color(ray);
    
    // Draw a vertical stripe of the appropriate color
    for (int y = start_y; y < end_y; y++)
        put_pixel(game, x, y, color);
}
```

## 3. Step 2: Texture Implementation

### Texture Mapping
```c
void render_textured_wall(t_game *game, int x, int start_y, int end_y, t_ray *ray)
{
    // Get appropriate texture based on wall orientation
    t_texture *tex = get_wall_texture(game, ray);
    
    // Calculate texture x-coordinate based on wall hit
    int tex_x = get_texture_x(ray, tex->width);
    
    // Calculate texture step for proper scaling
    double step = tex->height / (double)(end_y - start_y);
    double tex_pos = 0;
    
    // Draw the textured wall stripe
    for (int y = start_y; y < end_y; y++)
    {
        int tex_y = (int)tex_pos & (tex->height - 1);
        unsigned int color = get_texture_color(tex, tex_x, tex_y);
        put_pixel(game, x, y, color);
        tex_pos += step;
    }
}
```

### Texture Selection
```c
t_texture *get_wall_texture(t_game *game, t_ray *ray)
{
    if (ray->is_vertical)
    {
        if (ray->facing_right)
            return (&game->textures.east);  // East wall
        return (&game->textures.west);      // West wall
    }
    else
    {
        if (ray->facing_up)
            return (&game->textures.north);  // North wall
        return (&game->textures.south);      // South wall
    }
}
```

## 4. Raycasting Core Algorithm

### Ray Casting Loop
```c
void cast_rays(t_game *game)
{
    double ray_angle = game->player.angle - (FOV / 2);
    
    for (int x = 0; x < WINDOW_WIDTH; x++)
    {
        // Cast a single ray
        t_ray ray = cast_single_ray(game, ray_angle);
        
        // Step 1: Basic color rendering
        if (!game->textures_enabled)
            render_wall_stripe(game, x, ray);
        // Step 2: Texture rendering
        else
            render_textured_wall(game, x, ray);
            
        ray_angle += FOV / WINDOW_WIDTH;
    }
}
```

## 5. Performance Considerations

### Step 1 Optimizations
- Minimize floating-point operations
- Use precalculated values for trigonometry
- Efficient wall hit detection algorithm
- Simple color assignment

### Step 2 Optimizations
- Texture data preloading
- Efficient texture coordinate calculation
- Memory-aligned texture access
- Texture sampling optimization

## 6. Debugging Tips

### Step 1 Debugging
- Use distinct colors for different wall orientations
- Print ray angles and distances
- Visualize rays on minimap
- Check wall detection accuracy

### Step 2 Debugging
- Verify texture mapping coordinates
- Check texture orientation
- Debug texture seams
- Validate texture scaling

## Implementation Workflow
1. Start with basic raycasting and solid colors
2. Test and debug core raycasting functionality
3. Add basic wall rendering with orientation colors
4. Verify collision detection and distance calculations
5. Implement texture loading and management
6. Add texture mapping to walls
7. Fine-tune texture rendering and optimize performance