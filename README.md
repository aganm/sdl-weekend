# Dependencies

- libm
- SDL2
- OpenMP

# Build instructions

To compile and run tests and launch a game:

`./launch.sh <game_folder>`

For example, to launch the game titled '1_shooter', type:

`./launch.sh 1_shooter`


# 1_shooter: Game instructions

- `WASD` keys to move
- `Left Click` to shoot pistol
- `Right Click` to shoot shotgun
- `Space Bar` to spawn more monsters


# OpenMP performance bug

It was reported to me that OpenMP caused performance issues on gcc 9. If you happen to be using this compiler and have performance issues, please use clang instead and it should just work™.
