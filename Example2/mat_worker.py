import cv2
import numpy as np

def make_box(img):
    if len(img.shape)==3:
        img= cv2.rectangle(img,(10,10),(100,100),(0,0,255),3)
        return img
    if len(img.shape)==2:
        img= cv2.rectangle(img,(10,10),(100,100),255,3)
        return img
