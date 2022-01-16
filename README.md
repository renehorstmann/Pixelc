# Pixelc
An opensource tile/sprite editor in C, using SDL2 and OpenGL, also running on Android.

Based on [some](https://github.com/renehorstmann/some) framework.

Have a look at [Tilec](https://github.com/renehorstmann/Tilec) for a forked tile map editor.

## Live demo
Compiled with emscripten [live demo](https://renehorstmann.github.io/pixelc)
Lots of features are missing in the web demo! (Loading, Saving, options like size, ...)

## Status:
Ready to draw.
Saves after each tip on the screen to image.png.
Loads image.png at start, if available.
An import button can load import.png as selection, if available.
Palette, canvas size, animation size can be configured in code (main.c).

![example_image](example.jpg)

## Without Cmake

Instead of cmake, the following call to gcc may work, too.

```sh
mkdir build && cd build

cp -r ../res .

gcc ../src/e/*.c ../src/p/*.c ../src/r/*.c ../src/u/*.c ../src/*.c -I../include/ $(sdl2-config --cflags --libs) -lSDL2_image -lglew32 -lopengl32 -lglu32 -DOPTION_GLEW -DOPTION_SDL -o pixelc
```

## Todo
- some update
  - e_io combine load into mount
  - e_io name as namespace (web may use the files on multiple games)
  - fix texture artifacts
    - MIN_FILTER = LINEAR?
    - CLAMP_TO_BORDER + functions
    - set the text poses to an integral position
  - custom index.html
  - file up n download
- dont draw multiple times if pos not changed
- config
  - each module may load and save config.json
  - each module uses its name as an object
  - on error: remove the item and reset
- camera ctrl not as compile option
- palette swipe activates multitouch cursor
- options menu
  - size
  - frames + fps
  - palette? or swipe on palette
  - save as?
  - import from?
- buttons are not fixed in position and are in a flow container
- buttons can be moved and turned on + off in the options menu
  - tooltip / title / text for the button
- brushshape loaded from file
- palette loaded from file (png) + display name
- scale as + interpolation options
- save in HD
- combine layers and save them to combined.png
- Frame Selection? (or grid shows frames?)
- VertexColors?
  - white to color like the palette
- background image option?


## Author
René Horstmann

## Licence
- The app and its assets are licenced under GPLv3, see LICENCE.
- The [some](https://github.com/renehorstmann/some) framework is under MIT licence, see someLICENCE.
- Have a look at [some_examples](https://github.com/renehorstmann/some_examples) for some shared modules, under the MIT licence
