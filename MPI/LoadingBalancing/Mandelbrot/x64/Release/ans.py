import numpy as np
import cv2
a=np.loadtxt("Mandelbrot.txt")
cv2.imwrite("Mandelbrot.png",a)