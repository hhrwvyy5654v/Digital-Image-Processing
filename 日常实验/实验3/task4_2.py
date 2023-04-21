import cv2
lena = cv2.imread("./lena.jpg")  # 读取原图
height, width = lena.shape[:2]  # 获取图像的高度和宽度
# 以图像中心为圆点，逆时针旋转 60°，并将目标图像缩小为原始图像的 0.7 倍
M = cv2.getRotationMatrix2D((width/2, height/2), 60, 0.7)   #生成转换矩阵M
rotate_lena = cv2.warpAffine(lena, M, (width, height))
cv2.imshow("原始图像", lena)
cv2.imshow("旋转图像", rotate_lena)
cv2.waitKey()
cv2.destroyAllWindows()
