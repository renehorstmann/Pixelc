# Pixelc Tutorial
Welcome to the [Pixelc](https://github.com/renehorstmann/pixelc) tutorial.

![logo](icon/icon196.png)

Pixelc is a free pixelart editor for multiple platforms, including a [WebApp](https://renehorstmann.github.io/pixelc).

The main target are touch devices such as smartphones and tablets 
(via the [WebApp](https://renehorstmann.github.io/pixelc) or as Android App from [Google Play](https://play.google.com/store/apps/details?id=de.horsimann.pixelc)).

Its also fine to use on desktops, etc.

> Touch-Users: Use the [Multitouch Mode](#S-multitouchmode) for a great user experience!

> Big Screen? Change the internal [Display](#S-display) size

> Add the WebApp in your browser to the homescreen, to get the real WebApp fullscreen feeling


App:


![img](example.png)

## Table of Contents
- [Draw Modes](#S-draw_modes)
- [Tooltip](#S-tooltip)
- [Palette](#S-palette)
  - [How to edit a palette](#S-palette__edit)
  - [How load a palette from a file](#S-palette__load)
- [Multitouch Mode](#S-multitouchmode)
- [Kernel](#S-kernel)
  - [New Brush Size](#S-kernel__brush)
  - [Stamps](#S-kernel__stamps)
- [Funny Rainbow Trick](#S-rainbow)
- [Secondary Color](#S-secondary_color)
- [Shading](#S-shading)
- [Display Settings](#S-display)
- [Grid](#S-grid)
- [Save](#S-save)
- [Import](#S-import)
- [Selection](#S-selection)
- [Image Tabs](#S-image_tabs)
- [Frames](#S-frames)
- [Layers](#S-layers)

## <a name="S-draw_modes"></a>Draw Modes
Pixelc supports different modes to draw on the canvas.
### Free
![img](doc/res4/button_free.png)

Draws freely on the canvas (default mode).
### Dot
![img](doc/res4/button_dot.png)

Draws on each tip.
Good to print [stamps](#S-kernel__stamps) on the canvas.
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

Draws the current [Kernel](#S-kernel) in a grid on the canvas.
Only makes sense for a dithering kernel.

![img](doc/mode_grid.png)

### Inverted Grid
![img](doc/res4/button_dither_inv.png)

As Mode Grid, but inverts the colors of the [Kernel](#S-kernel).
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
### None
![img](doc/res4/button_cross.png)

Does nothing on the canvas. Use this mode if you just want to view your pixel art, without accidentally drawing on it.
### Pipette
![img](doc/res4/button_pipette.png)

Click on a color in the canvas to set it as [secondary color](#S-secondary_color). 
The app shows a flash effect of that color to show you that the pipette mode is active.
(Also if [shading](#S_shading) is active)

## <a name="S-tooltip"></a>Tooltip
![img](doc/res4/button_tooltip.png)

Click on the tooltip tool in the toolbar to show tooltips for pressed tools

![img](doc/tooltip.png)

You can now click on a tool (or the palette) to get some tipps.
Click on the tooltip button again to stop the tooltips.

## <a name="S-palette"></a>Palette
### Side Swipe to change
Swipe to the left or right on the palette, to change to the previous or next palette.

![img](doc/palette_swipe.png)

### Up Swipe for Multitouch Mode
See [Multitouch Mode](#S-multitouchmode).
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

### <a name="S-palette__edit"></a>How to edit a palette
1. ![img](doc/res2/button_tab.png)  use a new image tab
2. hold down on the palette to open the palette dialog
3. ![img](doc/res2/button_from.png)  copy the current palette into the canvas
4. change the size to add new colors, or replace the colors in the canvas. 
   - ![img](doc/res2/button_rgb.png)  Use the RGB tool to draw with a custom color
5. hold down on the palette again to open the palette dialog
6. (optional) rename the palette name to a new one
7. ![img](doc/res2/button_to.png)  set palette from canvas (duplicate colors are ignored, up to 128 colors) 

### <a name="S-palette__load"></a>How to load a palette from a file
1. Download a palette file as png (for example from [LOSCPEC](https://lospec.com/palette-list) PNG Image 1x)
2. ![img](doc/res2/button_tab.png)  use a new image tab
3. ![img](doc/res2/button_import.png)  hold down on the import button 
4. ![img](doc/res2/button_from.png)  in the import dialog, load the image and press "copy into canvas" 
5. hold down on the palette again to open the palette dialog
6. (optional) rename the palette name to a new one
7. ![img](doc/res2/button_to.png)  set palette from canvas (duplicate colors are ignored, up to 128 colors) 

## <a name="S-multitouchmode"></a>Multitouch Mode
> Makes editing pixelart on touch devices a great experience!

To start, swipe with your thumb (or a finger) up from the palette.
Hold down that finger and move to move the cursor.
Use a second thumb (or finger...) to press the cursors "button".
You can also press the buttons in the toolbar and in the dialogs, too!

![img](doc/multitouchmode.png)

## <a name="S-kernel"></a>Kernel
The Kernel is drawn in the Modes: Free, Dot, Line, Rect, Cricle, Grid and InvertedGrid.

![img](doc/res4/button_kernel_minus.png) ![img](doc/res4/button_kernel_plus.png)

Change the current kernel with the minus and plus button. Hold for the first, last kernel 


If you hold on the kernel preview between minus and plus, the kernel options dialog starts.

![img](doc/kernel_dialog.png)

In this dialog you can:
- ![img](doc/res2/button_delete.png)   delete the current kernel
- ![img](doc/res2/button_from.png)   copy the current kernel as image into the canvas
  - will overwrite the full image (use undo to reset to the old)
  - Good to edit the palatte in the canvas
- ![img](doc/res2/button_to.png)  Create a new kernel from the current canvas image

### <a name="S-kernel__brush"></a>New Brush Size
1. ![img](doc/res2/button_tab.png) use a new image tab
2. ![img](doc/res2/button_size.png)  Change canvas size to the desired kernel size 
3. Draw a white circle in the canvas and fill it white
4. Hold on the Kernel preview to start the kernel dialog
5. ![img](doc/res2/button_to.png)  Create a new kernel from the current canvas image 
6. Draw with your new brush

![img](doc/kernel_brush_image.png)

![img](doc/kernel_brush_usage.png)

### <a name="S-kernel__stamps"></a>Stamps
You can also use kernels as image stamps to quickly draw your stamps in different colors:
1. ![img](doc/res2/button_tab.png)  use a new image tab 
2. Draw your stamp in white, gray and black (other colors work, too. The resulting color is `kernel color * palette color`)
3. Hold on the Kernel preview to start the kernel dialog
4. ![img](doc/res2/button_to.png)  Create a new kernel from the current canvas image 
5. Select a color from the palette
6. ![img](doc/res2/button_dot.png)  Use the Dot Mode 
7. Draw your stamp

Lets draw a fish as a stamp in grayscale.

![img](doc/kernel_stamp_image.png)

We can now print the fish in different colors onto our image.

![img](doc/kernel_stamp_usage.png)


## <a name="S-rainbow"></a> Funny Rainbow Trick
Just to show you what kernels can do for you:

Choose a palette for the rainbow and copy it into the canvas (or draw your own rainbow)

![img](doc/rainbow_kernel.png)

Create a kernel from that canvas and draw your rainbow.

![img](doc/rainbow.png)



## <a name="S-secondary_color"></a>Secondary Color
An additional color to set and choose from, apart from the palette.

![img](doc/res4/toolbar_color_bg.png)

To use it just tip on the tool in the toolbar.

To set the secondary color:
- select a color from the palette and hold down on the secondary color tool to copy it
- ![img](doc/res2/button_rgb.png)  click on the RGB tool to change the current selected color and set it as secondary color 
- ![img](doc/res2/button_pipette.png)  use the pipette tool and click to the desired color on the canvas 

## <a name="S-shading"></a>Shading 
![img](doc/res4/button_shade.png)

Shading is useful to only paint above a selected color, to shade or highlight edges.

1. set the secondary color 
2. activate the shading mode
3. draw the shades

![img](doc/shading.png)

The app shows a flash effect of the secondary color to show you that the shading mode is active.
(Also if the pipette [draw mode](#S_draw_modes) is used)

## <a name="S-display"></a>Display settings
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

## <a name="S-grid"></a>Grid
![img](doc/res4/button_grid.png)

Click on the grid tool to add a little transparency to the canvas, so you can see the background grid.

Grid option off (default):

![img](doc/grid_off.png)

Grid option on:

![img](doc/grid_on.png)

Hold on the grid tool, to open a dialog in which you can change the pattern size:

![img](doc/grid_dialog.png)

Now with a background chess pattern of a 16x16 size, instead of the default 8x8:

![img](doc/grid_16.png)

## <a name="S-save"></a>Save
![img](doc/res4/button_save.png)

Click on the save tool to open the save dialog.

![img](doc/saving_dialog.png)

You can save either as `.png` image file or as animated `.gif` file.
> The CxxDroid Version saves the files as `image.png` or `animation.gif` in the working directory.

![img](doc/res2/button_save.png) Save the image with the actual size.

![img](doc/res2/button_save_hd.png) Upscale the image to at least **HD MIN SIZE**.
Better for sharing the image, because most image viewer will render pixel art wrong.

If **SAVE LAYERS MERGED** is activated, all layers are merged into a single image.

**PNG** will save the frames next to each other, while **GIF** will animate them.

> The gif encoder uses a color palette with max. 256 opaque colors. Color 0 is reserved for transparency.
> The first 255 different colors in the canvas are used to create the color palette.

## <a name="S-import"></a>Import
![img](doc/res4/button_import.png)

Click on the import tool to open the import dialog.

![img](doc/import_dialog.png)

Click on the **UPLOAD** button to open a file chooser and upload a png image.
> The CxxDroid Version has no file dialog and just trys to load import.png from the working directory.

![img](doc/res2/button_to.png)
The button **COPY INTO CANVAS** 
Will copy the image into the canvas directly.

![img](doc/res2/button_selection.png)
The button **AS SELECTION** 
will open the image as a [selection](#S-selection).

> Zoomed in on your Browser while asked for an image upload?
> try:
> - use desktop version in your browser to reset the size
> - empty the browser cache/data (for the Pixelc App)

If you know someone who speaks html better than me, tell me :)

## <a name="S-size"></a>Size
![img](doc/res4/button_size.png)

Click on the size tool to open the size dialog.

![img](doc/size_dialog.png)

If keep order is NOT activated (default), the image will be reset as there where no frames or layers.
Frames are placed side by side to the right in the image. Layers are placed below.
> Good to load an image with frames and set the size and frames to match the image.
> For example the image has 128 cols and 4 frames, so 32 cols per frame.
> Reset COLS to 32 and FRAMES to 4 to morph the image into the frames system.

If keep order is activated, the image will be reset with the frames and layers individually copied.
> Good to resize the actual frame size.



## <a name="S-selection"></a>Selection
![img](doc/res4/button_selection.png)

Click on the selection tool, to start a new selection.

Now swipe down on the canvas to create the selection window.

![img](doc/selection_set.png)

You can now move the selection borders with the arrow keys on the left in the selection toolbar.

While a selection is active, all drawing stuff is only applied inside the selection box.

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

![img](doc/res2/button_blend.png)
If the blend button is activated, the selections will be blended onto the canvas (using transparency).

![img](doc/selection_paste_blend.png)


## <a name="S-image_tabs"></a>Image Tabs
![img](doc/res4/button_tab.png)

You can select up to nine different image tabs via the tab tool.

![img](doc/tab_dialog.png)


## <a name="S-frames"></a>Frames
![img](doc/res4/button_play.png)
Open the frames toolbar and show the animated preview.


If not activated, the frames are side by side on the canvas.

![img](doc/frames_off.png)

![img](doc/res2/button_grid.png)
Click on the [grid](#S-grid) tool, to show the frame grid in the full image 

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
- reset the animation size
- ![img](doc/res2/button_repeat.png)  repeat the animated preview horizontally or vertically or both 
  - good to show repeated mod_tiles
- ![img](doc/res2/button_sec_fps.png)  reset all frame times via seconds or fps 


## <a name="S-layers"></a>Layers
Frames and layers both are located in a grid of the image.
While frames are set right next to each other on the image, layers are placed below each other.
The layer options behave exactly the same as the frame options (without the animation dialog and the frame times)
So have a look at the [Frames](#S-frames) section.

![img](doc/res2/button_save.png)
Layers may be merged down in the save dialog
