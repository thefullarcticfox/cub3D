# cub3D
42 cub3D project

Raycasting algorithm based on [Lode's Computer Graphics Raycasting Tutorial](https://lodev.org/cgtutor/raycasting.html)

Works on Arch Linux

### Differences from master
- Image needs to be redrawn constantly because X11 clears window if any part of it is not seen on screen. macOS's Cocoa preserves image in window so i don't need to redraw image if i'm standing still in game.
- i'm using [42Paris's minilibx-linux](https://github.com/42Paris/minilibx-linux) submodule so to build you will need to run `git submodule update --init` after checkouting to this branch

### Build and run
```
make
./cub3D ./maps/e1m1.cub [--save]
```
> `--save` is an optional parameter to take a bmp screenshot and exit

### Controls
- `W` `A` `S` `D` to walk
- `<-` `->` to rotate
- `Esc` to exit

### ./minilibx/
[42Paris's minilibx-linux](https://github.com/42Paris/minilibx-linux)

MinilibX is licensed under the BSD license: Copyright Olivier Crouzet - 1999-2015
