import numpy as np
import cv2

source = cv2.imread("example.bmp")
img = source.copy()
cv2.imshow("example",source)

img = cv2.GaussianBlur(img, (3, 3), 0)
img = cv2.Laplacian(img, 0, img, 3, 1)

tmp = cv2.getStructuringElement(cv2.MORPH_RECT, (5, 5), (-1, -1))
img = cv2.dilate(img, tmp)
tmp = cv2.getStructuringElement(cv2.MORPH_RECT, (5, 5), (-1, -1))
img = cv2.erode(img, tmp)

img = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)

cv2.imshow("img",img)

(h, w) = img.shape
mask = np.zeros((h + 2, w + 2), np.uint8)

for i in range(0,w) :
    for j in range(0,h) :
        if img[j,i] == 255 :
            _, (left, top, width, height) = cv2.floodFill(img, mask, (i,j), 0)
            cv2.rectangle(source, (left, top - 1), (left + width, top + height - 1), (255,0,0))

cv2.imshow("result",source)
cv2.imwrite("result.bmp",source)
cv2.waitKey(0)