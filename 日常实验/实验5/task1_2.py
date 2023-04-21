import cv2
import matplotlib.pyplot as plt
import numpy as np

# 读取为灰度图像
coin = cv2.imread('./coin.png', cv2.IMREAD_GRAYSCALE)
lena = cv2.imread('./lena.jpg', cv2.IMREAD_GRAYSCALE)
baboon = cv2.imread('./baboon.bmp')


def Prewitt(image):
    width, height = image.shape[:2]
    image_prewitt = np.zeros((width-3, height-3))
    image_prewitt_X = np.zeros((width-3, height-3))
    image_prewitt_Y = np.zeros((width-3, height-3))
    s_suanziX = np.array([[-1, 0, 1], [-1, 0, 1], [-1, 0, 1]])      # X方向
    s_suanziY = np.array([[-1, -1, -1], [0, 0, 0], [1, 1, 1]])
    for i in range(width-3):
        for j in range(height-3):
            image_prewitt_X[i, j] = abs(np.sum(image[i:i+3, j:j+3] * s_suanziX))
            image_prewitt_Y[i, j] = abs(np.sum(image[i:i+3, j:j+3] * s_suanziY))
            image_prewitt[i, j] = max(image_prewitt_X[i, j], image_prewitt_Y[i, j])
    return image_prewitt


if __name__ == '__main__':
    coin_prewitt = Prewitt(coin)
    lena_prewitt = Prewitt(lena)
    baboon_prewitt = Prewitt(baboon)

    # 图像显示
    images = [coin, lena, baboon, coin_prewitt, lena_prewitt, baboon_prewitt]
    titles = ["coin", "lena", "baboon", "coin_prewitt",
              "lena_prewitt", "baboon_prewitt"]
    for i in range(len(images)):
        plt.rcParams['font.sans-serif']=['SimHei']
        plt.rcParams['axes.unicode_minus'] = False
        plt.suptitle('采用Prewitt算子对灰度图像进行边缘检测')
        plt.subplot(2, 3, i+1)
        plt.imshow(images[i], "gray")
        plt.xticks([]), plt.yticks([])
        plt.title(titles[i])
    plt.show()
