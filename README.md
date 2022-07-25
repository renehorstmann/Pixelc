# Pixelc
An opensource tile/sprite editor in C, using SDL2 and OpenGL

> Main target are touch devices such as smartphones and tablets.
> Runs also fine on desktops.

Based on [some](https://github.com/renehorstmann/some) framework.

## Web version
[Pixelc WebApp](https://renehorstmann.github.io/pixelc) compiled with emscripten 

## Tutorial
A documentation / tutorial can be found [here / doc.md](doc.md)
Or just use the tooltip tool ![img](res/button_tooltip.png)

## Highlights:
- Multitouchmode for a great touch experience
- Full mobile friendly [WebApp](https://renehorstmann.github.io/pixelc) compiled with emscripten
- Frames and a .gif export
- Layers
- Onion Skinning for frames and layers
- Multiple drawing modes
- Shading
- Selections
- Undo and Redo system that also works on App reload
- 9 Image Tabs
- Contains the most popular [LOSCPEC](https://lospec.com/palette-list) palettes
- Custom Brush / Kernel / Stamps
- Custom Palettes
- **COMPLETELY FREE and open**
- and many more

## Status:

![example_image](example.png)

## Install and run on Desktop
Have a look at the section of [some](https://github.com/renehorstmann/some)


## Compiling for Web
Using Emscripten https://emscripten.org/
Tested under Ubuntu and WSL Ubuntu.
You should have already cloned the project and `cd` to that dir:

- Create a sub directory to compile the website
```sh
mkdir web && cp index.html web && cp icon/* web && cd web
```

- Copy all resources, because emscripten may not be able to use `../res`
```sh
cp -r ../res .
```

- Compile
```sh
emcc -O3 \
-I../include/ \
-s USE_SDL=2 -s USE_SDL_IMAGE=2 -s FULL_ES3=1 -s \
EXPORTED_FUNCTIONS='["_main", "_e_io_idbfs_synced", "_e_io_file_upload_done"]' \
-s EXPORTED_RUNTIME_METHODS=FS \
-s SDL2_IMAGE_FORMATS='["png"]' \
--preload-file ./res \
-s ALLOW_MEMORY_GROWTH=1 -s ASYNCIFY=1 -s EXIT_RUNTIME=1 \
-lidbfs.js \
-DPLATFORM_EMSCRIPTEN -DOPTION_GLES -DOPTION_SDL \
../src/e/*.c ../src/p/*.c ../src/r/*.c ../src/u/*.c ../src/*.c ../src/dialog/*.c ../src/tool/*.c \
-o index.js
```

- Test the website (open a browser and call localhost:8000)
```sh
python3 -m http.server --bind localhost  # [port]
```


# Todo
- android .apk for the Play Store

## Author
René Horstmann

## Licence
- The app and its assets are licenced under GPLv3, see LICENCE.
- The [some](https://github.com/renehorstmann/some) framework is under MIT licence, see someLICENCE.
- Have a look at [some_examples](https://github.com/renehorstmann/some_examples) for some shared modules, under the MIT licence
- the .gif encoder [gifenc](https://github.com/lecram/gifenc) is licenced under public domain
