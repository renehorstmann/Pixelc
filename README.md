# Pixelc
An opensource tile/sprite editor in C, using SDL2 and OpenGL, also running on Android

## Status:
Ready to draw.
Saves after each tip on the screen to sprite.png.
Loads sprite.png at start, if available.
Palette, brush, size can be configured in code

## Todo
- Toolbar
  - Brush mode
    - dot
    - free
    - line
    - circle
    - fill
    - shade (from color to color)
  - clear
  - replace (from color to color)
  - move mode
  - undo and redo
- Zoom n Pinch 
- Layer Selection
- Frame Selection
- ...

## Compiling on Windows
Compiling with Mingw (msys2).
Currently not working with cmake, but with the following gcc call.
I had to put all source files into one dir (from src/e/*, r/*, p/*, u/* into src/*) to get the linker happy.
```
gcc -o pixelc src/* -Iinclude $(sdl2-config --cflags --libs) -lSDL2_image -lSDL2_ttf -lglew32 -lopengl32 -lglu32 -DUSING_GLEW
```
