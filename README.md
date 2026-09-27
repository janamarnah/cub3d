*This project has been created as part of the 42 curriculum by siwhusse, jalamarn.*

# cub3D

## Description
cub3D is a mandatory-only ray-casting project written in C with MiniLibX. Its goal is
to render a first-person view of a maze from a `.cub` scene file. The parser reads
wall textures, floor and ceiling colors, and the map, then a ray-casting renderer
draws the scene with directional wall textures. The project also includes movement,
rotation, collision handling, and a minimap.

## Instructions
This project targets Linux and requires a C compiler, `make`, X11 development
libraries, and the Linux MiniLibX sources. The MiniLibX source is included in
`minilibx-linux/`. On Debian or Ubuntu, install the system dependencies with:

    sudo apt-get install build-essential libx11-dev libxext-dev libbsd-dev

Compile the project from the repository root:

    make

Run it with exactly one `.cub` scene file:

    ./cub3D maps/valid.cub

Controls: W/A/S/D move, left/right arrows rotate, and ESC exits. Closing the window
also exits cleanly.

To run the parser and invalid-map checks:

    ./run_tests.sh

Other useful Make targets are `make clean`, `make fclean`, and `make re`. Example
scene files are available in `maps/` and `maps/tests/`.

## Resources
- 42 cub3D subject v12.0
- MiniLibX documentation and source code
- Lode Vandevenne, [Raycasting tutorial](https://lodev.org/cgtutor/raycasting.html)
- [MiniLibX Linux documentation](https://harm-smits.github.io/42resources/libs/minilibx)

## AI Usage
AI was used to clarify some cub3D concepts and better understand the project requirements.
It was also used to discuss testing approaches and edge cases during development.

