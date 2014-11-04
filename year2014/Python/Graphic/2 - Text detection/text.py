import cv2
import numpy as np

def show(name, img):
    cv2.imshow(name, img)

def blur(src, w, h, x):
    cpy = src.copy()
    #cpy = cv2.blur(cpy, (w,h), x)
    cv2.GaussianBlur(cpy, (w,h), x, cpy, 0)
    return cpy

def laplacian(src, size):
    cpy = src.copy()
    cv2.Laplacian(cpy, 0, cpy, size, 1)
    return cpy

def main():
    src = cv2.imread('example.bmp', 0)
    bl = src.copy()
    bl = blur(bl, 61, 3, 20)
    la = laplacian(bl, 15)
    
    show("Source", src)
    show("Blur", bl)
    show("Laplacian", la)
    cv2.waitKey(0)

main()