# cub3D Mandatory Test Checklist

## Build / Norm
make
make
make clean
make
make fclean
make
make re
norminette src include

Expected: no compilation errors with -Wall -Wextra -Werror, relink only when needed, Norminette OK.

## Parser
Run:
./run_tests.sh

Every file under maps/tests/invalid must exit non-zero and start its diagnostic with:
Error

Valid maps under maps/tests/valid must open normally.

## Graphics / controls
For each N/S/E/W spawn map:
- Confirm initial view matches spawn direction.
- Confirm North/South/West/East walls use the correct distinct texture.
- Hold Left and Right arrows: rotation must stay smooth.
- Hold W/A/S/D: movement must stay smooth.
- Switch/minimize/restore the window and verify it remains responsive.
- ESC must close cleanly.
- Window X must close cleanly.

## Valgrind
Run once and exit with ESC:
valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./cub3D maps/valid.cub

Run again and exit with X:
valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./cub3D maps/valid.cub

Focus on your own allocations: definitely lost / indirectly lost / possibly lost should be zero.
The known MiniLibX/X11 uninitialised writev context may still appear on Linux.

Also run invalid-input paths through Valgrind, for example:
valgrind --leak-check=full ./cub3D maps/tests/invalid/07_two_players.cub
valgrind --leak-check=full ./cub3D maps/tests/invalid/18_rgb_over_255.cub
valgrind --leak-check=full ./cub3D maps/tests/invalid/24_missing_texture_file.cub

## Mandatory subject coverage
- .cub extension and one scene argument
- NO/SO/WE/EA texture elements
- F/C RGB in [0,255]
- elements in arbitrary order
- spaces between non-map element fields
- empty lines allowed between non-map elements
- map last
- map characters only 0,1,N,S,E,W plus spaces as map layout
- exactly one player start
- map closed by walls
- irregular maps and spaces handled as they look in the file
- distinct wall textures by orientation
- distinct floor and ceiling colors
- W/A/S/D, left/right arrows
- ESC and red-cross clean exit
- smooth window management

## Showcase maps
Main evaluation/demo level:
./cub3D maps/valid.cub

Simple courtyard with two entrances:
./cub3D maps/tests/valid/11_simple_courtyard.cub

Open showroom for checking perspective and all directional textures:
./cub3D maps/tests/valid/12_showroom.cub
