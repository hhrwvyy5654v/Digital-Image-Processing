import cv2  # 导入opencv库
lena_color = cv2.imread("./images/lena.jpg")  # 读取图像lena.jpg
lena_gray = cv2.cvtColor(lena_color, cv2.COLOR_BGR2GRAY)  # 将原图进行灰度化处理
# 通过窗口展示图片
cv2.imshow('lena_color', lena_color)
cv2.imshow('lena_gray', lena_gray)
cv2.waitKey(0)  # 设置waitKey(0),代表按任意键继续
