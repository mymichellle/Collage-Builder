Michelle Alexander
Computer Graphics (CS4300)
Assignment 3
2D Project

To Compile type the following in the terminal:
./buildscript

To Execute type the following in the terminal:
./Collage


Incomplete / Bugs:
- Only .png files are supported for uploading, other image types will crash the program OR be displayed incorrectly. ( there are some png files included in the "t" folder )
	
- Large images are not supported and will crash the program. Images up to 667 x 500 pixels have been tested and work correctly.

- I have locked the window size, dragging the corner of the window will break the coordinate system.

- There is currently only one font and so the user is not given a way to change the font. The font is created from on .png file of characters that I had to visually decipher the coordinates of each letter. I didn't have time to go back and calculate these for another font image.

- There is currently no functionality to save a collage. All progress on the current collage will stay while flipping through the menus but will no longer exist if the program exits.