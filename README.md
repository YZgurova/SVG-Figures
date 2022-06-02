# SVG-Figures

SVG figures is an application that works with 3 shapes (line, circle, rectangle) and has the following functionalities
-Reads the SVG file and takes information about the figures in it
Example file:
<?xml version="1.0" standalone="no"?>
<!DOCTYPE svg PUBLIC "-//W3C//DTD SVG 1.1//EN"
 "http://www.w3.org/Graphics/SVG/1.1/DTD/svg11.dtd">
<svg>
 <rect x="5" y="5" width="10" height="10" fill="green" />
 <circle cx="5" cy="5" r="10" fill="blue" />
 <line x1="100" y1="60" x2="10" y2="10" fill="red" />
</svg>
-Displays all figures on the screen
  print
-Creates a new figure
  create figure points fill
  example: create rect 1 2 3 4 blue
-Erases the figure
  erase index
-Translates one or all figures
  translate index vertical horizontal (withouth index translate all)
  example translate 10 20
-Displays all figures that are completely contained in a region(the region can be circle or reectangle)
  wihin area points
  within circle 0 0 5
-Displays on the screen all figures that contain a given point
  pointIn point
  pointIn 1 2
-Displays the areas of all figures
  areas
-Display the pers for all figures
  pers
