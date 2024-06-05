#/usr/bin/env python3
import hector_math
import matplotlib.pyplot as plt
import numpy as np
WIDTH = 640
HEIGHT = 48

def segmentColorImage(index):
  img = np.empty((HEIGHT, HEIGHT, 3), dtype=np.uint8)
  c = hector_math.coloring.segment_color(index)
  for x in range(HEIGHT):
    for y in range(HEIGHT):
      img[x, y, :] = (c.r, c.g, c.b)
  aximage = plt.imshow(img)
  aximage.axes.set_axis_off()


def gradientColorImage(method):
  img = np.empty((WIDTH, HEIGHT, 3), dtype=np.uint8)
  for x in range(WIDTH):
    c = hector_math.coloring.gradient_color(x/WIDTH, method=method)
    for y in range(HEIGHT):
      img[x, y, :] = (c.r, c.g, c.b)
  aximage = plt.imshow(img.transpose((1, 0, 2)))
  ax = aximage.axes
  ax.set_xticks([0, WIDTH])
  ax.set_xticklabels(['0', '1'])
  ax.set_yticklabels([])
  ax.set_yticks([])

plt.figure()
for i in range(hector_math.coloring.NUM_SEGMENT_COLORS):
  plt.subplot(int(np.ceil(hector_math.coloring.NUM_SEGMENT_COLORS / 5)), 5, i + 1)
  plt.title(i)
  segmentColorImage(i)
plt.tight_layout()
plt.savefig('pages/img/generated_segment_colors.png')

plt.figure()
METHODS = hector_math.coloring.GradientMethod.__members__.keys()
for i, method in enumerate(METHODS):
  plt.subplot(len(METHODS), 1, i+1)
  plt.title(method)
  gradientColorImage(getattr(hector_math.coloring.GradientMethod, method))
plt.tight_layout()
plt.savefig('pages/img/generated_gradient_methods.png')
