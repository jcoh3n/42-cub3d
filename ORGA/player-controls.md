# Player Controls and Input Management

## 1. Movement Controls
### WASD Movement
- `W`: Move forward in looking direction
- `S`: Move backward from looking direction
- `A`: Strafe left (perpendicular to looking direction)
- `D`: Strafe right (perpendicular to looking direction)

### Implementation Features
- Frame-independent movement using delta time
- Advanced collision detection with buffer zones
- Wall sliding for smoother movement
- Unified movement system for all directions
- Independent X/Y collision checks

## 2. Camera Controls
### Arrow Key Rotation
- Left Arrow: Rotate camera left
- Right Arrow: Rotate camera right

### Technical Implementation
```c
// Camera rotation with delta time
float rotSpeed = ROT_SPEED * delta_time;
float oldDirX = dirX;
dirX = dirX * cos(rotSpeed) - dirY * sin(rotSpeed);
dirY = oldDirX * sin(rotSpeed) + dirY * cos(rotSpeed);
```

## 3. Program Control
### Exit Controls
- ESC key: Clean program exit
- Window close button (X): Clean program exit

### Exit Requirements
- Free all allocated memory
- Destroy all MLX windows and images
- Ensure no memory leaks
- Close all opened files

## 4. Event Handling
### MinilibX Events
```c
// Event hooks
mlx_hook(win_ptr, 2, 1L<<0, key_press, data);    // Key press
mlx_hook(win_ptr, 3, 1L<<1, key_release, data);  // Key release
mlx_hook(win_ptr, 17, 0, close_window, data);    // Window close
mlx_hook(win_ptr, 9, 1L<<21, handle_focus, data); // Window focus
```

### Event Types
- KeyPress events
- KeyRelease events
- Window focus events
- Window close events

## 5. Movement System
### Unified Movement Implementation
```c
// Single function handling all movement types
static void apply_movement(t_game *game, t_player *p, double dir_x, double dir_y)
{
    double move_distance = MOVE_SPEED * game->delta_time;
    double new_x = p->pos_x + dir_x * move_distance;
    double new_y = p->pos_y + dir_y * move_distance;
    try_movement(game, new_x, new_y, p);
}

// Movement direction vectors
Forward:    ( dir_x,  dir_y)
Backward:   (-dir_x, -dir_y)
Strafe Left:(-dir_y,  dir_x)
Strafe Right:( dir_y, -dir_x)
```

### Collision System
```c
static t_bool check_collision(t_game *game, double new_x, double new_y)
{
    double buffer = 0.2;
    int map_x = (int)new_x;
    int map_y = (int)new_y;
    
    if (game->map_data->grid[map_y][map_x] == '1')
        return TRUE;
        
    // Buffer zone checks for smooth wall interaction
    return (game->map_data->grid[(int)(new_y + buffer)][(int)(new_x + buffer)] == '1'
        || game->map_data->grid[(int)(new_y - buffer)][(int)(new_x - buffer)] == '1'
        || game->map_data->grid[(int)(new_y + buffer)][(int)(new_x - buffer)] == '1'
        || game->map_data->grid[(int)(new_y - buffer)][(int)(new_x + buffer)] == '1');
}
```