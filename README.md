# Pixelc
An opensource tile/sprite editor in C, using SDL2 and OpenGL, also running on Android.
Based on [some](https://github.com/renehorstmann/some) framework.

## Status:
Ready to draw.
Saves after each tip on the screen to sprite.png.
Loads sprite.png at start, if available.
An import button can load import.png as selection, if available.
Palette, canvas size, animation size can be configured in code (main.c).

![example_image](example.jpg)

## Todo
- create SOME Framework
   - comments
- Frame Selection (or grid shows frames?)
- Layer Selection
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
