# cub3D
42 cub3D project

Raycasting algorithm based on [Lode's Computer Graphics Raycasting Tutorial](https://lodev.org/cgtutor/raycasting.html)

Works on macOS 10.14. For linux version check out `linuxport` branch

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
Slightly modified X11/Cocoa OpenGL library for macOS made by Olivier Crouzet (Ol)

Changes:
- Added flags to suppress deprecation warnings on macOS 10.14
- Added ```mlx_get_screen_size``` from [42Paris's minilibx-linux](https://github.com/42Paris/minilibx-linux)

MinilibX is licensed under the BSD license: Copyright Olivier Crouzet - 1999-2015
