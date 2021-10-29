# Pixelc
An opensource tile/sprite editor in C, using SDL2 and OpenGL, also running on Android.

Based on [some](https://github.com/renehorstmann/some) framework.

Have a look at [Tilec](https://github.com/renehorstmann/Tilec) for a forked tile map editor.

## Status:
Ready to draw.
Saves after each tip on the screen to image.png.
Loads image.png at start, if available.
An import button can load import.png as selection, if available.
Palette, canvas size, animation size can be configured in code (main.c).

![example_image](example.jpg)

## Todo
- some update
  - input ignore others
    - touch + key stuff?, mainly touch
- vkeyboard module
  - font88 with small glyphs...
  - transparent overlay
  - key buttons with a background + back and enter button
  - shows entered text
- options menu
  - size
  - frames + fps
  - palette? or swipe on palette
  - save as?
  - import from?
- savestate has pre allocated memory and max saves like a ring buffer
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
