import cv2
import matplotlib.pyplot as plt
import numpy as np

# 读取为灰度图像
coin = cv2.imread('./coin.png', cv2.IMREAD_GRAYSCALE)
lena = cv2.imread('./lena.jpg', cv2.IMREAD_GRAYSCALE)
baboon = cv2.imread('./baboon.bmp')

def Laplacian(image):
    image_dst = cv2.Laplacian(image, cv2.CV_16S, ksize=3)
    image_laplacian = cv2.convertScaleAbs(image_dst)
    return image_laplacian


if __name__ == '__main__':
    coin_laplacian = Laplacian(coin)
    lena_laplacian = Laplacian(lena)
    baboon_laplacian = Laplacian(baboon)

    # 图像显示
    images = [coin, lena, baboon, coin_laplacian,
              lena_laplacian, baboon_laplacian]
    titles = ["coin", "lena", "baboon", "coin_laplacian",
              "lena_laplacian", "baboon_laplacian"]
    for i in range(len(images)):
        plt.rcParams['font.sans-serif']=['SimHei']
        plt.rcParams['axes.unicode_minus'] = False
        plt.suptitle('采用Laplacian算子对灰度图像进行边缘检测')
        plt.subplot(2, 3, i+1)
        plt.imshow(images[i], "gray")
        plt.xticks([]), plt.yticks([])
        plt.title(titles[i])
    plt.show()
