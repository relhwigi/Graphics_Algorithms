# Graphics_Algorithms

This program, given the specifications of a camera system, performs the transformation of the 3D pipeline by transforming world co-ordinates into normalised device co-ordinates. it also opens a simple viewport using OpenGL and displays a polygon that was placed in the world. <br />

Program input <HR>
  
  1. camera position
  2. camera aim point
  3. the up-vector
  4. two numbers that respresent the distance to the near and far plane of the frustum from the apex of the pyramid.
  5. the width and height of the clipping window on the near plane.
  <br />
  Queries and their inputs <HR>
  1. What is the Zv vector? no additional parameters required. <br />
  2. What is the Yv vector? no additional parameters required.<br />
  3. what are the 8 corners of the frustum in vc? no additional parameters required. outputs in the order front then back in counter clockwise, starting in the     bottom left corner.<br />
  4. Given p1 in WC what is it in VC? requires an additional 3 parameters of 3 doubles as the point.<br />
  5. Given p2 in WC what is it in VC? requires an additional 3 parameters of 3 doubles as the point.<br />
  6. Given p1 in WC what is it in NDC? requires an additional 3 parameters of 3 doubles as the point.<br />
  7. Draw a given triangle in a given viewport. requires an additional 11 parameter. 3 points of 3 doubles each and 2 ints.<br />
