# Minimap Implementation Guide

## Overview
The minimap provides a top-down 2D visualization of the game map, essential for debugging and player orientation.

## 1. Core Components

### Structure Definition
```c
typedef struct s_minimap {
    int     scale;          // Pixels per map unit (e.g., 10)
    int     width;          // Total width in pixels
    int     height;         // Total height in pixels
    int     pos_x;         // Position in main window
    int     pos_y;         // Position in main window
    void    *img;          // Minimap image pointer
    int     *addr;         // Image address for pixel manipulation
    int     bits_per_pixel;
    int     line_length;
    int     endian;
} t_minimap;
```

## 2. Implementation Steps

### 2.1 Initialization
1. Calculate minimap dimensions based on map size and scale
2. Create minimap image using mlx_new_image
3. Get image address for pixel manipulation
4. Initialize position in main window (typically top-left corner)

```c
void init_minimap(t_game *game)
{
    game->minimap.scale = 10;
    game->minimap.width = game->map.width * game->minimap.scale;
    game->minimap.height = game->map.height * game->minimap.scale;
    game->minimap.pos_x = 10;  // Padding from window edge
    game->minimap.pos_y = 10;  // Padding from window edge
    
    game->minimap.img = mlx_new_image(game->mlx, 
                                     game->minimap.width, 
                                     game->minimap.height);
    game->minimap.addr = (int *)mlx_get_data_addr(game->minimap.img,
                                                 &game->minimap.bits_per_pixel,
                                                 &game->minimap.line_length,
                                                 &game->minimap.endian);
}
```

### 2.2 Rendering Functions

#### Draw Map Grid
```c
void draw_map_grid(t_game *game)
{
    int x;
    int y;
    int color;

    y = 0;
    while (y < game->map.height)
    {
        x = 0;
        while (x < game->map.width)
        {
            if (game->map.grid[y][x] == '1')
                color = WALL_COLOR;    // Define colors (e.g., 0x808080 for walls)
            else if (game->map.grid[y][x] == '0')
                color = FLOOR_COLOR;   // e.g., 0xFFFFFF for floor
            draw_square(game, x, y, color);
            x++;
        }
        y++;
    }
}
```

#### Draw Player
```c
void draw_player(t_game *game)
{
    int center_x = game->player.pos_x * game->minimap.scale;
    int center_y = game->player.pos_y * game->minimap.scale;
    int radius = game->minimap.scale / 4;
    
    // Draw player circle
    draw_circle(game, center_x, center_y, radius, PLAYER_COLOR);
    
    // Draw direction indicator
    int dir_x = center_x + cos(game->player.angle) * (radius * 2);
    int dir_y = center_y + sin(game->player.angle) * (radius * 2);
    draw_line(game, center_x, center_y, dir_x, dir_y, DIRECTION_COLOR);
}
```

### 2.3 Helper Drawing Functions

#### Draw Square
```c
void draw_square(t_game *game, int map_x, int map_y, int color)
{
    int start_x = map_x * game->minimap.scale;
    int start_y = map_y * game->minimap.scale;
    int x = 0;
    int y = 0;

    while (y < game->minimap.scale)
    {
        x = 0;
        while (x < game->minimap.scale)
        {
            put_pixel_minimap(game, start_x + x, start_y + y, color);
            x++;
        }
        y++;
    }
}
```

#### Put Pixel
```c
void put_pixel_minimap(t_game *game, int x, int y, int color)
{
    if (x >= 0 && x < game->minimap.width && 
        y >= 0 && y < game->minimap.height)
    {
        game->minimap.addr[y * game->minimap.line_length / 4 + x] = color;
    }
}
```

## 3. Main Render Loop

### Update and Display
```c
void update_minimap(t_game *game)
{
    // Clear previous frame
    clear_minimap(game);
    
    // Draw new frame
    draw_map_grid(game);
    draw_player(game);
    
    // Put image to window
    mlx_put_image_to_window(game->mlx, game->win, 
                           game->minimap.img,
                           game->minimap.pos_x, 
                           game->minimap.pos_y);
}
```

## 4. Integration with Main Game Loop

### Hook into Main Loop
```c
int game_loop(t_game *game)
{
    // Process player movement
    process_input(game);
    
    // Update minimap
    update_minimap(game);
    
    return (0);
}
```

## 5. Testing and Debugging

### Key Features to Test
1. Correct map representation
2. Accurate player position
3. Proper scaling
4. Smooth updates with movement
5. Proper collision detection visualization
6. Direction indicator accuracy

### Common Issues and Solutions
1. Inverted coordinates
2. Scale calculation errors
3. Memory leaks in image handling
4. Performance issues with large maps
5. Color bleeding between cells

## 6. Optimization Tips

1. Only redraw changed portions
2. Use integer math where possible
3. Minimize memory allocation/deallocation
4. Pre-calculate common values
5. Use efficient drawing algorithms
``` 