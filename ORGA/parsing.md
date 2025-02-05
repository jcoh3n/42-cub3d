# Cub3D Parsing Instructions

## Map File Format (`.cub`)
Your program must take a `.cub` file as its first argument. This file defines the game environment and must be properly parsed.

### Allowed Characters in the Map
- `0` → Empty space
- `1` → Wall
- `N, S, E, W` → Player's starting position and orientation (North, South, East, West)

### Example of a Valid Map
```
111111
100101
101001
1100N1
111111
```
- The map must be **fully enclosed** by walls (`1`), otherwise, the program should return an error.
- Spaces (`0`) must be handled correctly during parsing.

### Parsing Rules
- The map must be **parsed exactly as it appears in the file**.
- Empty lines between sections are allowed.
- The **map description must always be the last section** in the file.
- Elements can appear in any order **before the map**.
- Apart from the map itself, elements can be separated by one or more spaces.

## Map Elements
Each element has a strict format:

### Textures
| Identifier | Description | Example |
|------------|------------|----------|
| `NO` | North texture | `NO ./path_to_north_texture` |
| `SO` | South texture | `SO ./path_to_south_texture` |
| `WE` | West texture | `WE ./path_to_west_texture` |
| `EA` | East texture | `EA ./path_to_east_texture` |

### Colors
| Identifier | Description | Example |
|------------|------------|----------|
| `F` | Floor color (RGB 0-255) | `F 220,100,0` |
| `C` | Ceiling color (RGB 0-255) | `C 225,30,0` |

## Parsing Techniques
### 1. Flood Fill (for Map Validation)
- Ensures the map is **fully enclosed** by walls (`1`).
- Starts from the player's position (`N, S, E, W`) and spreads recursively (or using BFS/DFS).
- If it reaches an **empty space outside the walls**, the map is invalid.

### 2. Line-by-Line Parsing
- Extract all **non-map** elements (`NO, SO, WE, EA, F, C`) and store them.
- Identify the **start of the map** and parse it separately.
- Check for **duplicate or missing** required elements.

### 3. Regular Expressions / String Parsing
- Use functions like `strtok`, `sscanf`, or regex (if allowed) to extract **textures & colors**.
- Validate RGB values (`F` and `C`) are within `0-255`.

### 4. MiniLibX Functions (for Rendering and Display)
- Use `mlx_new_window()` to create the game window.
- Use `mlx_pixel_put()` to draw individual pixels (useful for debugging parsing output).
- Use `mlx_put_image_to_window()` to render textures.
- Use `mlx_key_hook()` to handle player movement and interactions.

### 5. Edge Case Handling
- Detect **invalid characters** in the map and return an error.
- Ensure **no duplicate definitions** for textures or colors.
- Validate **RGB values** for floor and ceiling to be within the `0-255` range.
- Check for missing player start position (`N, S, E, W` must appear exactly **once**).

### 6. Performance Considerations
- Optimize parsing by **preloading textures** before rendering.
- Handle large maps efficiently by using **buffered reading** instead of character-by-character parsing.
- Store parsed data in **structured arrays** to reduce lookup time during rendering.

## Additional Examples
### Example of an Invalid `.cub` File (Missing Walls)
```
NO ./path_to_north_texture
SO ./path_to_south_texture
WE ./path_to_west_texture
EA ./path_to_east_texture

F 220,100,0
C 225,30,0

111111111111
100000000011
101100000111
100100000000
100000000000
111111111111
```
Error: Map is not enclosed by walls.

## Minimal Example of a Valid `.cub` File
```
NO ./path_to_north_texture
SO ./path_to_south_texture
WE ./path_to_west_texture
EA ./path_to_east_texture

F 220,100,0
C 225,30,0

1111111111111111111111111
1000000000110000000000001
1011000001110000000000001
1001000000000000000000001

111111111011000001110000000000001
100000000011000001110111111111111
11110111111111011100000010001
11110111111111011101010010001
11000000110101011100000010001
10000000000000001100000010001
10000000000000001101010010001
11000001110101011111011110N0111
11110111 1110101 101111010001
11111111 1111111 111111111111
```

## Error Handling
If any configuration issue occurs in the `.cub` file, the program must **exit and print**:
```
Error
[Descriptive error message]
```


