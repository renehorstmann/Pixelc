# Pixelc
An opensource tile/sprite editor in C, using SDL2 and OpenGL, also running on Android

## Status:
Ready to draw.
Saves after each tip on the screen to sprite.png.
Loads sprite.png at start, if available.
Palette, brush, size can be configured in code

![example_image](example.jpg)

## Todo
- Toolbar
  - Brush mode
    - line
    - circle
  - replace (from color to color)
  - move mode
  - selection
    - copy
    - move
- Tile repeat
- Layer Selection
- Frame Selection
- VertexColors?
  - white to color like the palette
- background image option?


## Compiling on Windows
Compiling with Mingw (msys2).
Currently not working with cmake, but with the following gcc call.
I had to put all source files into one dir (from src/e/*, r/*, p/*, u/* into src/*) to get the linker happy.
```
gcc -o pixelc src/* -Iinclude $(sdl2-config --cflags --libs) -lSDL2_image -lSDL2_ttf -lglew32 -lopengl32 -lglu32 -DUSING_GLEW
```
