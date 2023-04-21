import cv2
lena = cv2.imread('./lena.jpg')  # 读入原始图像
print(lena.shape)   # 打印出图片尺寸
x, y = lena.shape[0:2]  # 将图片高和宽分别赋值给x，y
cv2.imshow('原始图像', lena)    # 显示原图

# 缩放到原来的四分之一
lena_zoom_1 = cv2.resize(lena, (int(y / 2), int(x / 2)))
cv2.imshow('缩放至原来四分之一的图像', lena_zoom_1)

# 缩放到原来的十六分之一
lena_zoom_2 = cv2.resize(lena, (0, 0), fx=0.25, fy=0.25,
                         interpolation=cv2.INTER_NEAREST)
cv2.imshow('缩放到原来的十六分之一的图像', lena_zoom_2)
cv2.waitKey()
cv2.destroyAllWindows()
