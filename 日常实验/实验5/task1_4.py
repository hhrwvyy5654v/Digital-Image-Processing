import cv2
import matplotlib.pyplot as plt
import numpy as np

# 读取为灰度图像
coin = cv2.imread('./coin.png', cv2.IMREAD_GRAYSCALE)
lena = cv2.imread('./lena.jpg', cv2.IMREAD_GRAYSCALE)
baboon = cv2.imread('./baboon.bmp')


if __name__ == '__main__':
    coin_canny = cv2.Canny(coin,128,200)
    lena_canny = cv2.Canny(lena,128,200)
    baboon_canny =cv2.Canny(baboon,128,200)

    # 图像显示
    images = [coin, lena, baboon, coin_canny, lena_canny, baboon_canny]
    titles = ["coin", "lena", "baboon", "coin_canny",
              "lena_canny", "baboon_canny"]
    for i in range(len(images)):
        plt.rcParams['font.sans-serif']=['SimHei']
        plt.rcParams['axes.unicode_minus'] = False
        plt.suptitle('采用Canny算子对灰度图像进行边缘检测')
        plt.subplot(2, 3, i+1)
        plt.imshow(images[i], "gray")
        plt.xticks([]), plt.yticks([])
        plt.title(titles[i])
    plt.show()