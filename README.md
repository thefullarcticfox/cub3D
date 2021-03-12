# cub3D
42 cub3D project

Works on macOS 10.14.

### Build and run
```
make
./cub3D ./maps/e1m1.cub [--save]
```

### Minilibx
Slightly modified X11/Cocoa OpenGL library for macOS made by Olivier Crouzet (Ol)

Changes:
- Added flags to suppress deprecation warnings on macOS 10.14
- Added ```mlx_get_screen_size``` from [42Paris's minilibx-linux](https://github.com/42Paris/minilibx-linux)

MinilibX is licensed under the BSD license: Copyright Olivier Crouzet - 1999-2015
