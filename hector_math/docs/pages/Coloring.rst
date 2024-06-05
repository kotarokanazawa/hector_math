========
Coloring
========

segmentColor
------------
Returns colors for segmentation.
These are handpicked colors for good contrast and limited in number.
The following are currently available. You can get the maximum from `NUM_SEGMENT_COLORS`.

.. figure:: img/generated_segment_colors.png
   :width: 75%
   :alt: The image displays a grid of segment colors.
   :align: center

gradientColor
-------------
A method to obtain a color gradient value for a given value in the range `min` (default 0) to `max` (default 1).
The following methods are available: (Default = Turbo)

.. figure:: img/generated_gradient_methods.png
   :width: 75%
   :alt: The image displays multiple color gradients from 0 to 1 titled with the name of each method.
   :align: center

Python
------
These methods can also be used from python (note the different naming convention):

.. code:: python
   
      import hector_math.coloring as coloring
   
      # Get a color for a segment
      color = coloring.segment_color( 3 )
   
      # Get a color for a value in a range
      color = coloring.gradient_color( 0.5, 0, 1, coloring.GradientMethod.Turbo )
   
      # Get a color for a value in a range with default min and max
      color = coloring.gradient_color( 0.5, coloring.GradientMethod.Civides )
   
      # Get a color for a value in a range with default min and max and default method
      color = coloring.gradient_color( 0.5 )

API
---
.. doxygenfunction:: hector_math::coloring::segmentColor( int index )
.. doxygenfunction:: hector_math::coloring::gradientColor( float value, float min, float max,GradientMethod method )
.. doxygenfunction:: hector_math::coloring::gradientColor( float value, GradientMethod method )
