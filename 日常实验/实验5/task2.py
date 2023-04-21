import cv2
import numpy as np
from matplotlib import pyplot as plt

def nothing(x):
    pass

circuit = cv2.imread('./circuit.tif')
srcBlur = cv2.GaussianBlur(circuit, (3, 3), 0)
gray = cv2.cvtColor(srcBlur, cv2.COLOR_BGR2GRAY)
edges = cv2.Canny(gray, 50, 150, apertureSize=3)
WindowName = '霍夫变换对图像进行直线检测' 
cv2.namedWindow(WindowName, cv2.WINDOW_NORMAL | cv2.WINDOW_KEEPRATIO)  
cv2.createTrackbar('threshold', WindowName, 0, 60, nothing) 

while(1):
    image = circuit.copy()
    threshold = 100 + 2 * cv2.getTrackbarPos('threshold', WindowName)
    lines = cv2.HoughLines(edges, 1, np.pi/180, threshold)
    for line in lines:
        rho = line[0][0]
        theta = line[0][1]
        a = np.cos(theta)
        b = np.sin(theta)
        x0 = a*rho
        y0 = b*rho
        x1 = int(x0 + 1000*(-b))
        y1 = int(y0 + 1000*(a))
        x2 = int(x0 - 1000*(-b))
        y2 = int(y0 - 1000*(a))
        cv2.line(image, (x1, y1), (x2, y2), (0, 0, 255), 2)

    cv2.imshow(WindowName, image)
    k = cv2.waitKey(1) & 0xFF
    if k == 27:
        break
    
cv2.destroyAllWindows()
