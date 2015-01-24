import numpy as np
from math import * 
import cv2

def dist((x1, y1), (x2, y2)):
  return np.sqrt((x1 - x2) ** 2 + (y1 - y2) ** 2)

src = cv2.imread("mandril.bmp", 0)
(r, c) = src.shape
M = cv2.getRotationMatrix2D((c/2, r/2), 45, 0.5)
Mi = cv2.invertAffineTransform(M)

i1 = src.copy()
(kp1, d1) = cv2.SIFT().detectAndCompute(i1, None)

i2 = src.copy()
i2 = cv2.warpAffine(i2, M, (r, c))
(kp2, d2) = cv2.SIFT().detectAndCompute(i2, None)

FLANN_INDEX_KDTREE = 0
index_params = dict(algorithm = FLANN_INDEX_KDTREE, trees = 5)
search_params = dict(checks=50)
flann = cv2.FlannBasedMatcher(index_params,search_params)

matches = flann.match(d1, d2)

k = 0
for m in matches:
  p1 = kp1[m.queryIdx].pt
  p2 = kp2[m.trainIdx].pt
  p2 = np.dot(Mi,(p2[0], p2[1], 1.0))
  length = sqrt( pow((p1[0] - p2[0]),2) + pow((p1[1] - p2[1]),2) )
  if length < 3: k += 1

result = k * 100.0 / len(matches)
print str(result)

cv2.waitKey(0)