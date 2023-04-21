import cv2
import matplotlib.pyplot as plt
import numpy as np

# 读取为灰度图像
coin = cv2.imread('./coin.png', cv2.IMREAD_GRAYSCALE)
lena = cv2.imread('./lena.jpg', cv2.IMREAD_GRAYSCALE)
baboon = cv2.imread('./baboon.bmp')


def Sobel(image):
    x = cv2.Sobel(image, cv2.CV_16S, 1, 0)
    y = cv2.Sobel(image, cv2.CV_16S, 0, 1)
    absX = cv2.convertScaleAbs(x)
    absY = cv2.convertScaleAbs(y)
    image_sobel = cv2.addWeighted(absX, 0.5, absY, 0.5, 0)
    return image_sobel


if __name__ == '__main__':
    coin_sobel = Sobel(coin)
    lena_sobel = Sobel(lena)
    baboon_sobel = Sobel(baboon)

    # 图像显示
    images = [coin, lena, baboon, coin_sobel, lena_sobel, baboon_sobel]
    titles = ["coin", "lena", "baboon", "coin_sobel",
              "lena_sobel", "baboon_sobel"]
    for i in range(len(images)):
        plt.rcParams['font.sans-serif']=['SimHei']
        plt.rcParams['axes.unicode_minus'] = False
        plt.suptitle('采用Sobel算子对灰度图像进行边缘检测')
        plt.subplot(2, 3, i+1)
        plt.imshow(images[i], "gray")
        plt.xticks([]), plt.yticks([])
        plt.title(titles[i])
    plt.show()