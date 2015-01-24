import cv2
import numpy as np

source = cv2.imread("mandril.bmp", cv2.IMREAD_GRAYSCALE)

fft = np.fft.fft2(source.copy())
fs = np.fft.fftshift(fft)
mspec = 18 * np.log(np.abs(fft))

(h, w) = source.shape
(r, c) = h/2 , w/2
d = 30
fs[r-d:r+d, c-d:c+d] = 0
ifft = np.fft.ifftshift(fs)
img = np.fft.ifft2(ifft)
img = np.abs(img)
img = img.astype(np.uint8)

l = source.copy()
l = cv2.Laplacian(l, 0, l, 3, 1)
l = l/2

cv2.imshow("Original", source)
cv2.imshow("HPF", img)
cv2.imshow("Laplacian", l)

cv2.imwrite("hpf_img.bmp", img)
cv2.imwrite("laplacian_img.bmp", l)

cv2.waitKey(0)


