import cv2
lena = cv2.imread("./lena.jpg")
vertical_mirror_lena = cv2.flip(lena, 1)
cv2.imshow("原始图像", lena)
cv2.imshow("垂直镜像翻转图像", vertical_mirror_lena)
cv2.waitKey()
cv2.destroyAllWindows()
