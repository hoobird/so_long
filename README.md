![walleeve](./Extra/wallebg.png)
# so_long
![gameplay](./Extra/gameplay.gif)
## Description

The "so_long" project is a small 2D game where the player, Wall-E, must collect all the Sapling Plants and reach Eve to win the game. This project helps you work with textures, sprites, and basic gameplay elements, using the MiniLibX graphical library.

## Getting Started

### Prerequisites

- CC
- Make
- Git
- MiniLibX

### Installation

1. Clone the repository and navigate to the project directory:
    ```bash
    cd 42cursus/RANK02/so_long
    ```

2. Compile the project:
    ```bash
    make
    ```

## Usage

### Running the Game

To run the game, provide a map file in the `.ber` format:
```bash
./so_long maps map1.ber
```

### Example Map

Here is an example of a simple valid map (`map1.ber`):

```
1111111
1P00001
100C001
100E001
1111111
```

- `1` represents walls.
- `P` is Wall-E's starting position.
- `C` represents a Sapling Plant.
- `E` is the exit point (Eve).

### Map Requirements

- The map must be rectangular.
- The map must be surrounded by walls (`1`).
- The map must contain at least one exit (`E`), one collectible (`C`), and one starting position (`P`).
- The map must ensure there is a valid path from the start to all collectibles and the exit.

## Implementation Details

### Objectives

This project aims to improve your skills in:
- Window management
- Event handling
- Colors and textures
- Using the MiniLibX library

### Game Rules

| Instruction   | Description                           |
|---------------|---------------------------------------|
| Player        | Wall-E                                |
| Collectible   | Sapling Plant                         |
| Exit          | Eve                                   |
| Movement Keys | W (up), A (left), S (down), D (right) |
| Display Moves | Number of moves is displayed in the shell at every move |

### Game Features

- The game runs in a window and uses a 2D view.
- Wall-E collects all Sapling Plants and reaches Eve to win.
- Wall-E can move up, down, left, and right but cannot move through walls.
- The window must close cleanly when pressing ESC or clicking the window's close button.
- The game can handle maps of any size, rendering only the portion of the map that fits the screen. Wall-E will always be centered on the screen as it moves.

## Common Instructions

- The project must be written in C.
- The project must adhere to the Norm.
- No segmentation faults, bus errors, double frees, etc.
- All dynamically allocated memory must be freed to prevent memory leaks.
- A Makefile must be provided with the following rules: `$(NAME)`, `all`, `clean`, `fclean`, and `re`.
- To include bonuses, add a `bonus` rule to the Makefile, with bonuses in separate `_bonus.{c/h}` files.
- If using `libft`, copy its sources and Makefile into a `libft` folder.

### Error Handling

- If the map is misconfigured, the program must exit cleanly and display an error message:
  ```
  Error
  Invalid map configuration.
  ```

## Bonus Part

For the bonus part, additional features such as animations, more complex enemy behaviors, or other gameplay elements can be implemented. Ensure these are separated into appropriate `_bonus.{c/h}` files.

## Examples

### Running the Game

To start the game with a specific map:
```bash
./so_long maps example_map.ber
```

### Example Output

When moving Wall-E:
```
Player moves: 1
Player moves: 2
...
```

