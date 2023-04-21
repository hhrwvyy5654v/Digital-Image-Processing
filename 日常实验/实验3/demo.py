import cv2
import numpy as np
lena=cv2.imread('./lena.jpg')    #导入原图
rows,cols=lena.shape[:2] #获取图像的行数和列数
pts1 = np.float32([[150,50],[400,50],[60,450],[310,450]])
pts2 = np.float32([[50,50],[rows-50,50],[50,cols-50],[rows-50,cols-50]])
M=cv2.getPerspectiveTransform(pts1,pts2)    #转换矩阵 M
dst=cv2.warpPerspective(lena,M,(cols,rows))
cv2.imshow("原始图像",lena)
cv2.imshow("透视变换图像",dst)
cv2.waitKey()
cv2.destroyAllWindows()