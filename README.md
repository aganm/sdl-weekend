# Dependencies

- libm
- SDL2
- OpenMP

# Build instructions

To compile and run tests and launch a game:

`./launch.sh <game>`

For example, to launch the game titled '1_shooter', type:

`./launch.sh 1_shooter` or `./launch.sh 1`

# OpenMP performance bug

It was reported to me that OpenMP caused performance issues on gcc 9. If you happen to be using this compiler and have performance issues, try using clang instead.

# 1_shooter: Game instructions

- `WASD` keys to move
- `Left Click` to shoot pistol
- `Right Click` to shoot shotgun
- `Space Bar` to spawn more monsters
- `Z` to switch between 2D and 3D rendering (experimental, not functional)

# 2_batching: Game instructions (more a benchmark than a game)

- `WASD` keys to move the rectangles
- `Left Shift` to move faster
- `Space Bar` to spawn more rectangles
- `Left Click` on a rectangle to spawn particles on this rectangle
- `Tab` to toggle between batching on and off
