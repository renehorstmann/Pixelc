# Pixelc Tutorial
Welcome to the [Pixelc](https://github.com/renehorstmann/pixelc) tutorial.

![logo](icon/icon196.png)

Pixelc is a free pixelart editor for multiple platforms, including a [WebApp](https://renehorstmann.github.io/pixelc).

The main target are touch devices such as smartphones and tablets 
(via the [WebApp](https://renehorstmann.github.io/pixelc) or as Android App on [Google Play](https://play.google.com/store/apps/details?id=de.horsimann.pixelc)).

Its also fine to use on desktops, etc.

> Touch-Users: Use the [Multitouch Mode](#multitouch-mode) for a great user experience!

> Big Screen? Change the internal [Display](#display-settings) size

> Add the WebApp in your browser to the homescreen, to get the real WebApp fullscreen feeling


## App

![img](example.png)

## Table of Contents
- [Draw Modes](#draw-modes)
- [Tooltip](#tooltip)
- [Palette](#palette)
  - [How to edit a palette](#how-to-edit-a-palette)
  - [How load a palette from a file](#how-to-load-a-palette-from-a-file)
  - [Create your own palette, fast](#create-your-own-palette-fast)
- [Multitouch Mode](#multitouch-mode)
- [Kernel](#kernel)
  - [New Brush Size](#new-brush-size)
  - [Kernel Stamps](#kernel-stamps)
- [Funny Rainbow Trick](#funny-rainbow-trick)
- [Secondary Color](#secondary-color)
- [Shading](#shading)
- [Display Settings](#display-settings)
- [Grid](#grid)
- [Save](#save)
- [Import](#import)
- [Selection](#selection)
  - [Create Selection](#create-selection)
  - [Paste Selection](#paste-selection)
  - [Selection Stamps](#selection-stamps)
- [Image Tabs](#image-tabs)
- [Frames](#frames)
- [Layers](#layers)
- [Project Archive](#project-archive)
- [Tiles](#tiles)
  - [Isometric Mode](#isometric-mode)
  - [How to edit a tilesheet](#how-to-edit-a-tilesheet)
  - [How to load a tilesheet from a file](#how-to-load-a-tilesheet-from-a-file)
  - [Tile saving and color codes](#tile-saving-and-color-codes)
- [Find and Replace / Autotile](#find-and-replace)

## Draw Modes
Pixelc supports different modes to draw on the canvas.
### Free
![img](doc/res4/button_free.png)

Draws freely on the canvas (default mode).
### Dot
![img](doc/res4/button_dot.png)

Draws on each tip.
Good to print [Kernel Stamps](#kernel-stamps) on the canvas.
### Line
![img](doc/res4/button_line.png)

Draws a line on the canvas.
### Rect
![img](doc/res4/button_rect.png)

Draws a rect on the canvas.
### Circle
![img](doc/res4/button_circle.png)

Draws a circle on the canvas.
Start position is the circle center.
### Grid
![img](doc/res4/button_dither.png)

Draws the current [Kernel](#kernel) in a grid on the canvas.
Only makes sense for a dithering kernel.

![img](doc/mode_grid.png)

### Inverted Grid
![img](doc/res4/button_dither_inv.png)

As Mode Grid, but inverts the colors of the [Kernel](#kernel).
So you can fill the opposite colors as with the normal Grid mode.
Only makes sense for a dithering kernel.

![img](doc/mode_inv_grid.png)

### Fill 4
![img](doc/res4/button_fill.png)

Fills a touched color with mode 4.
In mode 4, the left, right, top and bottom next pixels are checked for the same color.
Good to fill blobs of pixels.

![img](doc/mode_fill4.png)

### Fill 8
![img](doc/res4/button_fill8.png)

Fills a touched color with mode 8.
Mode 8 also checks the diagonal corners (so checking 8 fields).
Good to replace thin lines.

![img](doc/mode_fill8.png)

### Replace
![img](doc/res4/button_replace.png)

Replaces the touched color.

### Outline
![img](doc/res4/button_outline.png)

Creates an outline with the pressed color.
Uses the kernel to determine if a pixel belongs to the outline.
Functions like the "opening/closing" computer vision algorithm.

> A 1x1 kernel will be replaced by a 3x3 "+" kernel

![img](doc/mode_outline.png)

### None
![img](doc/res4/button_cross.png)

Does nothing on the canvas. Use this mode if you just want to view your pixel art, without accidentally drawing on it.
### Pipette
![img](doc/res4/button_pipette.png)

Click on a color in the canvas to set (and select) it as [secondary color](#secondary-color). 
The app shows a flash effect of that color to show you that the pipette mode is active.
(Also if [shading](#shading) is active)

- If the button is half pressed, the last active draw mode will be reset, if a color was picked.
- If full pressed, the pipette mode stays active

## Tooltip
![img](doc/res4/button_tooltip.png)

Click on the tooltip tool in the toolbar to show tooltips for pressed tools

![img](doc/tooltip.png)

You can now click on a tool (or the palette) to get some tipps.
Click on the tooltip button again to stop the tooltips.

## Palette
### Side Swipe to change
Swipe to the left or right on the palette, to change to the previous or next palette.

You can also use the mouse wheel to switch palettes, when the cursor is above it.

![img](doc/palette_swipe.png)

### Up Swipe for Multitouch Mode
See [Multitouch Mode](#multitouch-mode).
### Hold for Options
Press on the palette for some time to start the palette dialog.

![img](doc/palette_dialog.png)

In this dialog you can:
- ![img](doc/res2/button_delete.png)  delete the current palette
- ![img](doc/res2/button_from.png)  copy the current palette as image into the canvas
  - will overwrite the full image (use undo to reset to the old)
  - Good to edit the palatte in the canvas
- ![img](doc/res2/button_to.png)  Set a (new) palette from the current canvas image
  - Will overwrite the palette with the blue name or create a new one
    - click on the blue name to edit the new palette name

### How to edit a palette
1. ![img](doc/res2/button_tab.png)  use a new image tab
2. hold down on the palette to open the palette dialog
3. ![img](doc/res2/button_from.png)  copy the current palette into the canvas
4. change the [size](#size) to add new colors, or replace the colors in the canvas. 
   - ![img](doc/res2/button_rgb.png)  Use the RGB tool to draw with a custom color
5. hold down on the palette again to open the palette dialog
6. (optional) rename the palette name to a new one
7. ![img](doc/res2/button_to.png)  set palette from canvas (duplicate colors are ignored, up to 128 colors) 

### How to load a palette from a file
1. Download a palette file as png (for example from [LOSCPEC](https://lospec.com/palette-list) PNG Image 1x)
2. ![img](doc/res2/button_tab.png)  use a new image tab
3. ![img](doc/res2/button_import.png) click on the import button 
4. ![img](doc/res2/button_from.png)  in the import dialog, load the image and press "copy into canvas" 
5. hold down on the palette to open the palette dialog
6. (optional) rename the palette name to a new one
7. ![img](doc/res2/button_to.png)  set palette from canvas (duplicate colors are ignored, up to 128 colors) 

### Create your own palette, fast
1. ![img](doc/res2/button_tab.png)  use a new image tab, or use the top of your image
2. Draw some shades of gray
3. Use the [Selection](#selection) tool to crop your shades ![img](doc/res2/button_crop.png)

![img](doc/palette_create_grayshade.png)

4. Create new [Kernel Stamp](#kernel-stamps) of that image
5. ![img](doc/res2/button_tab.png)  use a new image tab, or click undo ![img](doc/res2/button_undo.png)
6. Select a bright color with the RGB tool ![img](doc/res2/button_rgb.png)
7. Draw the kernel with the custom color
8. Repeat until your palette is finished
9. Crop to your custom palette and set it like in ["How to edit a palette"](#how-to-edit-a-palette)

![img](doc/palette_create_palette.png)

> You can also use [Selection Stamps](#selection-stamps) to draw the color shades

## Multitouch Mode
> Makes editing pixelart on touch devices a great experience!

To start, swipe with your thumb (or a finger) up from the palette.
Hold down that finger and move to move the cursor.
Use a second thumb (or finger...) to press the cursors "button".
You can also press the buttons in the toolbar and in the dialogs, too!

![img](doc/multitouchmode.png)

## Kernel
The Kernel is drawn in the Modes: Free, Dot, Line, Rect, Cricle, Grid and InvertedGrid.

![img](doc/res4/button_kernel_minus.png) ![img](doc/res4/button_kernel_plus.png)

Change the current kernel with the minus and plus button. Hold for the first, last kernel 


If you hold on the kernel preview between minus and plus, the kernel options dialog starts.

![img](doc/kernel_dialog.png)

In this dialog you can:
- ![img](doc/res2/button_delete.png)   delete the current kernel
- ![img](doc/res2/button_from.png)   copy the current kernel as image into the canvas
  - will overwrite the full image (use undo to reset to the old)
  - Good to edit the kernel in the canvas
- ![img](doc/res2/button_to.png)  Create a new kernel from the current canvas image

### New Brush Size
1. ![img](doc/res2/button_tab.png) use a new image tab
2. ![img](doc/res2/button_size.png)  Change canvas size to the desired kernel size 
3. Draw a white circle in the canvas and fill it white
4. Hold on the Kernel preview to start the kernel dialog
5. ![img](doc/res2/button_to.png)  Create a new kernel from the current canvas image 
6. Draw with your new brush

![img](doc/kernel_brush_image.png)

![img](doc/kernel_brush_usage.png)

### Kernel Stamps
Also have a look at [Selection Stamps](#selection-stamps)

You can also use kernels as image stamps to quickly draw your stamps in different colors:
1. ![img](doc/res2/button_tab.png)  use a new image tab 
2. Draw your stamp in white, gray and black (other colors work, too. The resulting color is `kernel_color * palette_color // [0:1]`)
3. Hold on the Kernel preview to start the kernel dialog
4. ![img](doc/res2/button_to.png)  Create a new kernel from the current canvas image 
5. Select a color from the palette. Or use the ![img](doc/res2/button_rgb.png) RGB tool with a custom color
6. ![img](doc/res2/button_dot.png)  Use the Dot Mode 
7. Draw your stamp

Lets draw a fish as a stamp in grayscale.

![img](doc/kernel_stamp_image.png)

We can now print the fish in different colors onto our image.

![img](doc/kernel_stamp_usage.png)


##  Funny Rainbow Trick
Just to show you what kernels can do for you:

Choose a palette for the rainbow and copy it into the canvas (or draw your own rainbow)

![img](doc/rainbow_kernel.png)

Create a kernel from that canvas and draw your rainbow.

![img](doc/rainbow.png)



## Secondary Color
An additional color to set and choose from, apart from the palette.

![img](doc/res4/toolbar_color_bg.png)

To use it just tip on the tool in the toolbar.

To set the secondary color:
- select a color from the palette and hold down on the secondary color tool to copy it
- ![img](doc/res2/button_rgb.png)  click on the RGB tool to change the current selected color and set it as secondary color 
- ![img](doc/res2/button_pipette.png)  use the pipette tool and click to the desired color on the canvas 

## Shading 
![img](doc/res4/button_shade.png)

Shading is useful to only paint above a selected color, to shade or highlight edges.

1. set the secondary color to the color you wish to overdraw
2. select the new color from the palette
3. activate the shading mode
4. draw the shades

![img](doc/shading.png)

The app shows a flash effect of the secondary color to show you that the shading mode is active.
(Also if the pipette [draw mode](#draw-modes) is used)



## Display settings
![img](doc/res4/button_display.png)

Click on the display tool to open the display dialog.

![img](doc/display_dialog.png)

Pixelc is rendered in pixel perfect render mode.
In that mode, each pixel unit is drawn with an integer number of real pixels.
The size determines the minimum drawn pixel units in the window.

So a small change may not alter the size of a pixel unit.

Click on the mobile or desktop/tablet button next to the size, to set it to 180 or 270.

The rotate mode is in portrait mode as default.
- In the Portrait Mode, the toolbar is at the top of the window and the palette on the bottom.
- In Landscape Mode, the toolbar is aligned left and the palette right.
- Auto Mode uses the window size to select the mode.

## Grid
![img](doc/res4/button_grid.png)

Click on the grid tool to add a little transparency to the canvas, so you can see the background grid.

Grid option off (default):

![img](doc/grid_off.png)

Grid option on:

![img](doc/grid_on.png)

Hold on the grid tool, to open a dialog in which you can change the pattern size 
and show or hide the entire background grid:

![img](doc/grid_dialog.png)

Now with a background chess pattern of a 16x16 size, instead of the default 8x8:

![img](doc/grid_16.png)

## Save
![img](doc/res4/button_save.png)

Click on the save tool to open the save dialog.

![img](doc/saving_dialog.png)

You can save either as `.png` image file or as animated `.gif` file.
> The CxxDroid Version saves the files as `image.png` or `animation.gif` in the working directory.

![img](doc/res2/button_save.png) Save the image with the actual size.

![img](doc/res2/button_save_hd.png) Upscale the image with the **HD MULTIPLYER**.
Better for sharing the image, because most image viewer will render pixel art wrong.

If **SAVE LAYERS MERGED** is activated, all layers are merged into a single image.

**PNG** will save the frames next to each other, while **GIF** will animate them.

> The gif encoder uses a color palette with max. 256 opaque colors. Color 0 is reserved for transparency.
> The first 255 different colors in the canvas are used to create the color palette.

![img](doc/res2/button_project.png) Open the [project archive](#project-archive) dialog

## Import
![img](doc/res4/button_import.png)

Click on the import tool to open the import dialog.

![img](doc/import_dialog.png)

Click on the **UPLOAD** button to open a file chooser and upload a png image.
> The CxxDroid Version has no file dialog and just trys to load import.png from the working directory.

> Maximal image sizes:
> - 8192*8192
> - 96 Frames
> - 96 Layers
> - 64 MiB image size (~16 million pixel)

![img](doc/res2/button_to.png)
The button **COPY INTO CANVAS** 
Will copy the image into the canvas directly.

![img](doc/res2/button_selection.png)
The button **AS SELECTION** 
will open the image as a [selection](#selection).

> Zoomed in on your Browser while asked for an image upload?
> try:
> - use desktop version in your browser to reset the size
> - empty the browser cache/data (for the Pixelc App)

If you know someone who speaks html better than me, tell me :)

## Size
![img](doc/res4/button_size.png)

Click on the size tool to open the size dialog.

![img](doc/size_dialog.png)

If **KEEP ORDER** is NOT activated (default), the image will be reset as there where no frames or layers.
Frames are placed side by side to the right in the image. Layers are placed below.
> Good to load an image with frames and set the size and frames to match the image.
> For example the image has 128 cols and 4 frames, so 32 cols per frame.
> Reset COLS to 32 and FRAMES to 4 to morph the image into the frames system.

If **KEEP ORDER** is activated, the image will be reset with the frames and layers individually copied.
> Good to resize the actual frame size.

If **SCALE** is NOT activated (default), the image size will just be changed
and non-existent areas are filled transparently.

If **SCALE** is activated, the image will be scaled from the old to the new size 
with the *"nearest"* filter setting.

> Good to downscale an (.png) image into pixel art

![img](doc/res2/button_rotate_left.png)
![img](doc/res2/button_rotate_right.png)
![img](doc/res2/button_vertical.png)
![img](doc/res2/button_horizontal.png)

Toggle the rotate and flip buttons, to manipulate the image after resizing

> Maximal image sizes:
> - 8192*8192
> - 96 Frames
> - 96 Layers
> - 64 MiB image size (~16 million pixel)

## Selection
![img](doc/res4/button_selection.png)


## Create Selection

Click on the selection tool, to start a new selection.

Now swipe down on the canvas to create the selection window.

![img](doc/selection_set.png)

You can now move the selection borders with the arrow keys on the left in the selection toolbar.

While a selection is active, all drawing stuff is only applied inside the selection box.


## Paste Selection

![img](doc/res2/button_copy.png)
The copy button copies the current selection.

![img](doc/res2/button_cut.png)
The cut button cuts the current selection and replaces it with transparency.

![img](doc/res2/button_crop.png)
The crop button crops the canvas onto the current selection (removing everything outside the selection).

If copied or cut, the selection box may be moved on the canvas or in a new frame, layer or image tab.

![img](doc/selection_paste.png)

![img](doc/res2/button_rotate_left.png)
![img](doc/res2/button_rotate_right.png)
![img](doc/res2/button_vertical.png)
![img](doc/res2/button_horizontal.png)

In the new selection toolbar, the selection box may be rotated or flipped.

![img](doc/res2/button_copy.png)
The copy button now copies the selection into the canvas, leaving the selection toolbar open.

![img](doc/res2/button_ok.png)
The ok button copies the selection into the canvas and closes the selection mode.

![img](doc/res2/button_selection.png)
Stop the selection mode to cancel the copying.

![img](doc/res2/button_colordrop.png)
If the color button is activated, the current color will be applied on the selection.

See [Selection Stamps](#selection-stamps) below.

![img](doc/res2/button_blend.png)
If the blend button is activated, the selections will be blended onto the canvas (using transparency).

![img](doc/selection_paste_blend.png)

## Selection Stamps
Also have a look at [Kernel Stamps](#kernel-stamps)

You can also use selections as image stamps to quickly draw your stamps in different colors:
1. Draw your stamp in white, gray and black (other colors work, too. The resulting color is `pixel_color * palette_color // [0:1]`)
2. Create a selection on your drawing (In the image below, its the gift in the black box)
3. ![img](doc/res2/button_copy.png) Copy this selection stamp
4. ![img](doc/res2/button_colordrop.png) Activate the color mode
5. Select a color from the palette. Or use the ![img](doc/res2/button_rgb.png) RGB tool with a custom color
6. ![img](doc/res2/button_copy.png) Drag and copy your stamp


![img](doc/selection_stamps.png)

## Image Tabs
![img](doc/res4/button_tab.png)

You can select up to nine different image tabs via the tab tool.

![img](doc/tab_dialog.png)


## Frames
![img](doc/res4/button_play.png)

Open the frames toolbar and show the animated preview.


If not activated, the frames are side by side on the canvas:

![img](doc/frames_off.png)

![img](doc/res2/button_grid.png)
Click on the [grid](#grid) tool, to show the frame grid in the full image:

![img](doc/frames_grid.png)

If activated, the frames can be selected in the frames toolbar:

![img](doc/frames.png)

Select a frame via the preview.

![img](doc/res2/button_blend3.png) Switch between the three blend modes:
1. Off, only render the current frame
2. Onion skinning, blend in previous frames with a low transparency (alpha) value
3. Full, blend in previous frames with the full alpha value

![img](doc/res2/button_plus.png)
Add a new frame right next to the current.

Hold on a frame to open the frame dialog:

![img](doc/frame_dialog.png)

Here you can:
- ![img](doc/res2/button_delete.png)  delete the current frame 
- ![img](doc/res2/button_move_prev.png) ![img](doc/res2/button_move_next.png)  move the current frame left or right 
- ![img](doc/res2/button_from.png)  merge the frame with the previous frame 
- set the frame time for the animation

![img](doc/res2/button_play.png)
Hold on the frames tool to open the animation dialog

![img](doc/animation_dialog.png)

Here you can:
- show and hide the animation
- reset the animation size
- ![img](doc/res2/button_repeat.png)  repeat the animated preview horizontally or vertically or both 
  - good to show repeated tiles
- ![img](doc/res2/button_sec_fps.png)  reset all frame times via seconds or fps 


## Layers
Frames and layers both are located in a grid on the image.
While frames are set right next to each other on the image, layers are placed below each other.
The layer options behave exactly the same as the frame options (without the animation dialog and the frame times)
So have a look at the [Frames](#frames) section.

![img](doc/res2/button_save.png)
Layers may be merged down in the save dialog

## Project Archive
Open the project dialog within the [Save](#save) dialog.

> ![img](doc/res2/button_save.png) --> ![img](doc/res2/button_project.png)

![img](doc/project_dialog.png)

![img](doc/res2/button_save.png) Save the full project as `.tar` archive file.
> The CxxDroid Version saves the file as `project_save.tar` in the working directory.

A project archive contains:
- All 9 tab images
- All 16 tilesheets
- A config file, that includes the tab frames and layers and the tile sizes

Like with the [import](#import) dialog, you can also upload a project archive `.tar` to restore it.
Use the **UPLOAD** button to open the archive file in a file dialog
and click on ![img](doc/res2/button_import.png) to reload it.

> To open a `.tar` file manually, use an archive reader like WinRar, 7zip, etc.


## Tiles
![img](doc/res4/button_tile.png)

Click on the tile tool to start the tiling mode.

![img](doc/tiling_mode.png)

> In the newest version of Pixelc, the tile button has moved into the grid dialog!

The canvas now renders a tile for each pixel unit.

> (WebApp) limitation:
> The tile mode creates large textures on the GPU.
> If the maximal size is reached on your device, the canvas will be rendered with the maximal GPU texture size and your tilemap will get pixelated.
> If thats the case, a warning will be print as tooltip
> Use a smaller canvas size or reduce the layers to avoid this.

### Tile Palette

The palette now shows tilesheets and some additional tools.

You can zoom and move the tilesheet like the canvas.

Tools:
- ![img](doc/res2/toolbar_color_bg.png) Select to clear tiles
- ![img](doc/res2/button_prev.png) Previous tilesheet
- ![img](doc/res2/button_next.png) Next tilesheet
- ![img](doc/res2/button_camera.png) Reset the tilesheet camera
- ![img](doc/res2/button_tile.png) Render the tiles in the canvas
- ![img](doc/res2/button_iso.png) Render in [isometric mode](#isometric-mode)

> Pixelc supports up to 16 different tilesheets!

Hold down on the palette to open the tile dialog:

![img](doc/tile_dialog.png)

Here you can:
- Reset the size of a single tile for x and y (`8, 16, 32 pixel`)
  - For all tilesheets.
- ![img](doc/res2/button_to.png) Copy the tilesheet into the canvas
  - Good for editing the tilesheet
- ![img](doc/res2/button_from.png) Update the current tilesheet with the canvas image
  - The image size must be a multiple of 32
    - will be filled with transparency to match `%32==0`

### Isometric Mode
![img](doc/res4/button_iso.png)

If the isometric mode is active, the canvas renders the tiles with isometric overlapping:

![img](doc/tiles_isometric.png)

In this example, the tilesize is set as 32x32 pixel
> Use layers to define the z-height of your tilemap.
> Layer 1 is the bottom floor.

In the isometric mode, selections are disabled. Turn it off to use them.

#### Rotating the Isometric Tilemap
Want to view your 3D-Tilemap from a different orientation?
1. ![img](doc/res2/button_size.png) Click on the size tool to open the [size](#size) dialog
2. ![img](doc/res2/button_rotate_left.png) Rotate the image
3. Enjoy your new view:

![img](doc/tiles_isometric_rotate.png)


### How to edit a tilesheet
1. ![img](doc/res2/button_tab.png)  use a new image tab
2. ![img](doc/res2/button_tile.png) start the tiling mode
3. hold down on the tile palette to open the tile dialog
4. ![img](doc/res2/button_from.png)  copy the current tilesheet into the canvas
5. redraw tiles, change the size, draw new tiles, ....
6. ![img](doc/res2/button_tile.png) start the tiling mode again
7. (optional) select a different tilesheet to update
8. hold down on the tile palette again to open the tile dialog
9. ![img](doc/res2/button_to.png) update tilesheet from canvas

### How to load a tilesheet from a file
1. Download a tilesheet file as png (for example from [itch](https://itch.io/game-assets/tag-tileset))
2. ![img](doc/res2/button_tab.png) use a new image tab
3. ![img](doc/res2/button_import.png) click on the import button
4. ![img](doc/res2/button_from.png)  in the import dialog, load the image and press "copy into canvas"
5. (optional) crop the image out to the tiles you want with a [selection](#selection)
6. ![img](doc/res2/button_tile.png) start the tiling mode
7. (optional) select a different tilesheet to update
8. hold down on the tile palette to open the tile dialog
9. ![img](doc/res2/button_to.png) update tilesheet from canvas


### Tile saving and color codes
The tilemap is drawn with color codes for each tile.

The color code is built up as:
```
.r = tile_id;
.g = tile_x;
.b = tile_y;
.a = alpha;
```

`tile_id` is one of the 16 tilesheets.

`tile_x & tile_y` are the position in the tilesheet.

![img](doc/res2/button_save.png) A click on the save tool, opens a new save dialog:

![img](doc/saving_tile_dialog.png)

Here you can:
- Save the tilemap with its color codes as .png image
- Save the rendered preview of the tilemap
- Save the rendered preview of the tilemap in HD, using the **HD MULTIPLYER**
- ![img](doc/res2/button_project.png) Open the [project archive](#project-archive) dialog

## Find and Replace
![img](doc/res4/button_find.png)

With the find tool, you can search for patterns in your image and replace them.

> When using the right choice of pattern, you can also create **Auto Tiled Maps**!

Long press ![img](doc/res2/button_find.png) to open the find dialog:

![img](doc/find_dialog.png)

In this dialog you can:
- ![img](doc/res2/button_from.png)   copy the current pattern as image into the canvas
  - will overwrite the full image (use undo to reset to the old)
  - Good to edit the pattern in the canvas
- ![img](doc/res2/button_to.png)  Create a new pattern from the current canvas image

> A pattern needs 2 or more frames!

**TARGETS** is the amount of replace frames (pattern.frames -1)

**RUNS** is the amount of layers in the pattern image. Layers are evaluated one by one.

> If your canvas had frames or layers enabled, only up to the current frame/layer is used as targets/runs in the pattern.
> So thats where these **TARGETS: 1/2** come from: "2 maximal targets, but only the first is used."

In a nutshell, the find tool looks for patterns in the first frame of the pattern image 
and replaces it with the following target frames.

Suppose you have the following image where you want to replace the eyes:

![img](doc/find_color_blob_before.png)

Your pattern image should look like the following:

On the left is the search frame.
On the right the target (position of the eyes must match)

![img](doc/find_pattern_color_eyes.png)

> The first pixel on the top left is the ignore color. Do NOT place your search patterns on that pixel

After pressing the ![img](doc/res2/button_find.png) find tool, the resulting image will look like this:

![img](doc/find_color_blob_after.png)

> The tooltip will show the match and replace results for each run (pattern image layer)

You can also search for multiple patterns:

> Each pattern must have a border (box) of at least 1 pixel in the ignore color (top left pixel color)

![img](doc/find_pattern_color_shoes.png)

The result will look like this:

![img](doc/find_color_blob_after_2.png)

If you define more than one target frame, the result is randomly chosen:

> Up to valid pattern targets, so the shoe is always replaced with the first target

![img](doc/find_pattern_color_random.png)

![img](doc/find_color_blob_after_3.png)

### Autotiling

The find tool can be used to create auto tile pattern maps.
The default find pattern image is a very simple autotile map for the first default tilesheet:

![img](doc/find_pattern_0.png)

The ignore color (tile) is here set as the small cross (top left pixel in the pattern image)

> So you can search for transparency as well

> Each pattern must have a border of the ignore colors / tiles!

When the ![img](doc/res2/button_find.png) is pressed on an image like this:

![img](doc/find_template.png)

Each pattern is replaced with the next frame in the pattern image:

![img](doc/find_pattern_1.png)

Turn on blending frame ![img](doc/res2/button_blend3.png) to see the searched pattern:

![img](doc/find_pattern_1b.png)

> If your pattern image has more than 2 frames, a random frame is used for each match.
> But only if that target has >= 1 not ignored color, else the previous frame is used

The resulting image will look like this:

![img](doc/find_result.png)

> The default tileset and autotiling pattern are just to play around.
> If you see a template tile that was not replaced, add that condition to the pattern image
