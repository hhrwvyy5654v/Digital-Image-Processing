import cv2
lena = cv2.imread("./lena.jpg")
horizontal_mirror_lena = cv2.flip(lena, 0)
cv2.imshow("原始图像", lena)
cv2.imshow("水平镜像翻转图像", horizontal_mirror_lena)
cv2.waitKey()
cv2.destroyAllWindows()
