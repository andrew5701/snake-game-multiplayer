# SnakeGameMultiplayer

A full recreation of the popular Snake Game, allowing two players to play locally.

## Description

This project is a multiplayer version of the classic Snake game, implemented in C. Two players can play the game simultaneously on the same machine, competing to grow their snake by collecting trophies while avoiding collisions with the walls and themselves.

## Features

- Local multiplayer gameplay.
- Real-time snake movement.
- Randomly spawning trophies.
- Collision detection and game-over conditions.

## Files

- `SnakeGame.c`: The single-player version of the game.
- `SnakeGameMultiplayer.c`: The multiplayer version of the game.

## How to Run

1. Clone the repository:
    ```bash
    git clone https://github.com/andrew5701/SnakeGameMultiplayer.git
    ```
2. Navigate to the directory:
    ```bash
    cd SnakeGameMultiplayer
    ```
3. Compile the multiplayer game:
    ```bash
    gcc SnakeGameMultiplayer.c -o SnakeGameMultiplayer -lncurses
    ```
4. Run the game:
    ```bash
    ./SnakeGameMultiplayer
    ```

## Controls

### Player 1
- **W**: Move up
- **S**: Move down
- **A**: Move left
- **D**: Move right

### Player 2
- **Arrow keys**: Move in respective directions

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

## Acknowledgments

Inspired by the classic Snake game.
