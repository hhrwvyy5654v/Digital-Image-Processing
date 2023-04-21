import cv2
from matplotlib import pyplot as plt

image = cv2.imread("./rice.png")
gray = cv2.cvtColor(image, cv2.COLOR_BGR2GRAY)

plt.rcParams['font.sans-serif'] = ['SimHei']
plt.rcParams['axes.unicode_minus'] = False
plt.subplot(1, 3, 1), plt.imshow(image, "gray")
plt.title("原始图像"), plt.xticks([]), plt.yticks([])

plt.subplot(1, 3, 2), plt.hist(image.ravel(), 256)
plt.title("直方图"), plt.xticks([]), plt.yticks([])
ret1, th1 = cv2.threshold(gray, 127, 255, cv2.THRESH_BINARY)

plt.subplot(1, 3, 3), plt.imshow(th1, "gray")
plt.title("双峰法分割图像"), plt.xticks([]), plt.yticks([])
plt.show()
