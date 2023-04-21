import cv2
import numpy as np
lena = cv2.imread("./lena.jpg")  # 读取原图
height, width = lena.shape[:2]  # 获取图像的高度和宽度
x = 120 #向右侧移动 120 个像素
y = 200 #向下方移动 200 个像素
M = np.float32([[1, 0, x], [0, 1, y]])  #转换矩阵M
Panned_lena = cv2.warpAffine(lena, M, (width, height))
cv2.imshow("原始图像", lena)
cv2.imshow("平移图像", Panned_lena)
cv2.waitKey()
cv2.destroyAllWindows()
