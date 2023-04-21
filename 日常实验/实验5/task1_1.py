import cv2
import matplotlib.pyplot as plt
import numpy as np

# 读取为灰度图像
cion = cv2.imread('./coin.png', cv2.IMREAD_GRAYSCALE)
lena = cv2.imread('./lena.jpg', cv2.IMREAD_GRAYSCALE)
baboon = cv2.imread('./baboon.bmp')


def Roberts(image):
    # roberts算子
    kernelx = np.array([[-1, 0], [0, 1]], dtype=int)
    kernely = np.array([[0, -1], [1, 0]], dtype=int)
    x = cv2.filter2D(image, cv2.CV_16S, kernelx)
    y = cv2.filter2D(image, cv2.CV_16S, kernely)
    # 转uint8
    absX = cv2.convertScaleAbs(x)
    absY = cv2.convertScaleAbs(y)
    # 加权和
    image_Roberts = cv2.addWeighted(absX, 0.5, absY, 0.5, 0)
    return image_Roberts


if __name__ == '__main__':
    cion_roberts = Roberts(cion)
    lena_roberts = Roberts(lena)
    baboon_roberts = Roberts(baboon)

    # 图像显示
    images = [cion, lena, baboon, cion_roberts, lena_roberts, baboon_roberts]
    titles = ["cion", "lena", "baboon", "cion_roberts",
              "lena_roberts", "baboon_roberts"]
    for i in range(len(images)):
        plt.rcParams['font.sans-serif']=['SimHei']
        plt.rcParams['axes.unicode_minus'] = False
        plt.suptitle('采用Roberts算子对灰度图像进行边缘检测')
        plt.subplot(2, 3, i+1)
        plt.imshow(images[i], 'gray')
        plt.xticks([]), plt.yticks([])
        plt.title(titles[i])
    plt.show()
