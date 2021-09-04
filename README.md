# Pixelc
An opensource tile/sprite editor in C, using SDL2 and OpenGL, also running on Android.

Based on [some](https://github.com/renehorstmann/some) framework.

Have a look at [Tilec](https://github.com/renehorstmann/Tilec) for a forked tile map editor.

## Status:
Ready to draw.
Saves after each tip on the screen to sprite.png.
Loads sprite.png at start, if available.
An import button can load import.png as selection, if available.
Palette, canvas size, animation size can be configured in code (main.c).

![example_image](example.jpg)

## Todo
- selection mirror, rotate is buggy
- selection should grow to the border, if pointer is out of the canvas
- selection adjust
  - left top, width height (+- 1 with buttons)
- combine layers and save them to combined.png
- Frame Selection? (or grid shows frames?)
- VertexColors?
  - white to color like the palette
- background image option?


## Without Cmake

Instead of cmake, the following call to gcc should work, too.

```sh
mkdir build && cd build

cp -r ../res .

gcc ../src/e/*.c ../src/p/*.c ../src/r/*.c ../src/u/*.c ../src/*.c -I../include/ $(sdl2-config --cflags --libs) -lSDL2_image -lSDL2_ttf -lglew32 -lopengl32 -lglu32 -DOPTION_GLEW -DOPTION_SDL -o pixelc
```
