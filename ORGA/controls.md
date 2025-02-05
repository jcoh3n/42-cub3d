# Player Controls Implementation Guide

## Overview
Implementation of player movement and camera controls using keyboard input, including collision detection and smooth movement.

## 1. Core Components

### Key Mapping Structure
```c
typedef struct s_keys {
    int     w_pressed;      // Forward
    int     s_pressed;      // Backward
    int     a_pressed;      // Strafe left
    int     d_pressed;      // Strafe right
    int     left_pressed;   // Rotate left
    int     right_pressed;  // Rotate right
    int     esc_pressed;    // Exit game
} t_keys;
```

### Player Structure
```c
typedef struct s_player {
    double  pos_x;          // X position in map
    double  pos_y;          // Y position in map
    double  dir_x;          // X direction vector
    double  dir_y;          // Y direction vector
    double  plane_x;        // Camera plane X
    double  plane_y;        // Camera plane Y
    double  move_speed;     // Movement speed
    double  rot_speed;      // Rotation speed
} t_player;
```

## 2. Implementation Steps

### 2.1 Key Hook Setup
```c
void setup_controls(t_game *game)
{
    mlx_hook(game->win, 2, 1L<<0, key_press, game);   // Key press
    mlx_hook(game->win, 3, 1L<<1, key_release, game); // Key release
    mlx_hook(game->win, 17, 0, close_window, game);   // Window close
}
```

### 2.2 Key Event Handlers

#### Key Press
```c
int key_press(int keycode, t_game *game)
{
    if (keycode == KEY_W)
        game->keys.w_pressed = 1;
    else if (keycode == KEY_S)
        game->keys.s_pressed = 1;
    else if (keycode == KEY_A)
        game->keys.a_pressed = 1;
    else if (keycode == KEY_D)
        game->keys.d_pressed = 1;
    else if (keycode == KEY_LEFT)
        game->keys.left_pressed = 1;
    else if (keycode == KEY_RIGHT)
        game->keys.right_pressed = 1;
    else if (keycode == KEY_ESC)
        close_window(game);
    return (0);
}
```

#### Key Release
```c
int key_release(int keycode, t_game *game)
{
    if (keycode == KEY_W)
        game->keys.w_pressed = 0;
    else if (keycode == KEY_S)
        game->keys.s_pressed = 0;
    else if (keycode == KEY_A)
        game->keys.a_pressed = 0;
    else if (keycode == KEY_D)
        game->keys.d_pressed = 0;
    else if (keycode == KEY_LEFT)
        game->keys.left_pressed = 0;
    else if (keycode == KEY_RIGHT)
        game->keys.right_pressed = 0;
    return (0);
}
```

### 2.3 Movement Implementation

#### Process Movement
```c
void process_movement(t_game *game)
{
    // Forward/Backward
    if (game->keys.w_pressed)
        move_forward(game);
    if (game->keys.s_pressed)
        move_backward(game);
    
    // Strafe Left/Right
    if (game->keys.a_pressed)
        strafe_left(game);
    if (game->keys.d_pressed)
        strafe_right(game);
    
    // Rotation
    if (game->keys.left_pressed)
        rotate_left(game);
    if (game->keys.right_pressed)
        rotate_right(game);
}
```

#### Movement Functions
```c
void move_forward(t_game *game)
{
    double new_x = game->player.pos_x + game->player.dir_x * game->player.move_speed;
    double new_y = game->player.pos_y + game->player.dir_y * game->player.move_speed;
    
    if (is_valid_move(game, new_x, new_y))
    {
        game->player.pos_x = new_x;
        game->player.pos_y = new_y;
    }
}

void strafe_left(t_game *game)
{
    double new_x = game->player.pos_x - game->player.plane_x * game->player.move_speed;
    double new_y = game->player.pos_y - game->player.plane_y * game->player.move_speed;
    
    if (is_valid_move(game, new_x, new_y))
    {
        game->player.pos_x = new_x;
        game->player.pos_y = new_y;
    }
}
```

### 2.4 Rotation Implementation
```c
void rotate_left(t_game *game)
{
    double old_dir_x = game->player.dir_x;
    double old_plane_x = game->player.plane_x;
    double cos_rot = cos(-game->player.rot_speed);
    double sin_rot = sin(-game->player.rot_speed);
    
    game->player.dir_x = game->player.dir_x * cos_rot - game->player.dir_y * sin_rot;
    game->player.dir_y = old_dir_x * sin_rot + game->player.dir_y * cos_rot;
    game->player.plane_x = game->player.plane_x * cos_rot - game->player.plane_y * sin_rot;
    game->player.plane_y = old_plane_x * sin_rot + game->player.plane_y * cos_rot;
}
```

### 2.5 Collision Detection
```c
int is_valid_move(t_game *game, double new_x, double new_y)
{
    // Add buffer for smooth wall collision
    double buffer = 0.2;
    
    // Check if new position would be inside a wall
    if (game->map.grid[(int)(new_y)][(int)(new_x)] == '1')
        return (0);
    
    // Check buffer zones around walls
    if (game->map.grid[(int)(new_y + buffer)][(int)(new_x + buffer)] == '1'
        || game->map.grid[(int)(new_y - buffer)][(int)(new_x - buffer)] == '1'
        || game->map.grid[(int)(new_y + buffer)][(int)(new_x - buffer)] == '1'
        || game->map.grid[(int)(new_y - buffer)][(int)(new_x + buffer)] == '1')
        return (0);
    
    return (1);
}
```

## 3. Integration with Game Loop

### Main Loop Integration
```c
int game_loop(t_game *game)
{
    // Process movement and rotation
    process_movement(game);
    
    // Update display
    update_display(game);
    
    return (0);
}
```

## 4. Testing and Debugging

### Key Features to Test
1. Smooth movement in all directions
2. Proper collision detection
3. Accurate rotation
4. No key sticking
5. Proper diagonal movement
6. Clean exit on ESC

### Common Issues and Solutions
1. Jerky movement
   - Implement frame-independent movement using delta time
2. Wall clipping
   - Adjust collision buffer size
3. Rotation issues
   - Check rotation matrix calculations
4. Key combination problems
   - Ensure proper key state tracking

## 5. Optimization Tips

1. Use frame-independent movement
2. Pre-calculate trigonometric values
3. Implement smooth acceleration/deceleration
4. Use efficient collision detection
5. Minimize floating-point operations
``` 