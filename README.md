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

## Compiling for Web

Using Emscripten:

```sh
mkdir web && cp index.html web && cp icon/* web && cd web
```

```sh
emcc -O3 \
-I../include/ \
-s USE_SDL=2 -s USE_SDL_IMAGE=2 -s USE_SDL_TTF=2 -s FULL_ES3=1 -s \
EXPORTED_FUNCTIONS='["_main", "_e_io_idbfs_synced", "_e_io_file_upload_done"]' \
-s EXPORTED_RUNTIME_METHODS=FS \
-s SDL2_IMAGE_FORMATS='["png"]' \
--preload-file ./res \
-s ALLOW_MEMORY_GROWTH=1 -s ASYNCIFY=1 -s EXIT_RUNTIME=1 -s FETCH=1 \
-lidbfs.js \
-DOPTION_GLES -DOPTION_SDL -DOPTION_TTF -DOPTION_FETCH \
../src/e/*.c ../src/p/*.c ../src/r/*.c ../src/u/*.c ../src/*.c \
-o index.js
```

test the website:
```sh
python3 -m http.server --bind localhost  # [port]
```


## Without Cmake

Instead of cmake, the following call to gcc may work, too.

```sh
mkdir build && cd build

cp -r ../res .

gcc ../src/e/*.c ../src/p/*.c ../src/r/*.c ../src/u/*.c ../src/*.c -I../include/ $(sdl2-config --cflags --libs) -lSDL2_image -lglew32 -lopengl32 -lglu32 -DOPTION_GLEW -DOPTION_SDL -o pixelc
```

## Todo
- some
  - uImage
    - scale as + interpolation options
    - merge layers (single or all)
  - update swarm and santasdayoff
- camera ctrl not as compile option
- palette swipe up activates multitouch cursor
- tool abtraction:
  - list of active tools
  - render in container flow
  - tooltip title text
- options menu
  - size
  - frames + fps
  - palette? or swipe on palette
  - save as
  - save in HD
  - import from?
  - import kernel
  - import palette
  - tool sub menu
    - in container stack
    - shows tooltip, etc.
    - turn on / off
    - change position (move up / down)

- combine layers and save them to combined.png
- Frame Selection? (or grid shows frames?)
- background image option?


## Author
René Horstmann

## Licence
- The app and its assets are licenced under GPLv3, see LICENCE.
- The [some](https://github.com/renehorstmann/some) framework is under MIT licence, see someLICENCE.
- Have a look at [some_examples](https://github.com/renehorstmann/some_examples) for some shared modules, under the MIT licence
