import cv2
import matplotlib.pyplot as plt

# 将图像调整为单通道的灰度图像
coin = cv2.imread('./coin.png',cv2.IMREAD_GRAYSCALE)
lena = cv2.imread('./lena.jpg',cv2.IMREAD_GRAYSCALE)
baboon = cv2.imread('./baboon.bmp',cv2.IMREAD_GRAYSCALE)

# 采用Otsu算法进行图像分割
t1,coin_otsu=cv2.threshold(coin,cv2.IMREAD_GRAYSCALE,255,cv2.THRESH_BINARY|cv2.THRESH_OTSU)
t2,lena_otsu=cv2.threshold(lena,cv2.IMREAD_GRAYSCALE,255,cv2.THRESH_BINARY|cv2.THRESH_OTSU)
t3,baboon_otsu=cv2.threshold(baboon,cv2.IMREAD_GRAYSCALE,255,cv2.THRESH_BINARY|cv2.THRESH_OTSU)


# 图像显示
images = [coin, lena, baboon, coin_otsu, lena_otsu, baboon_otsu]
titles = ["coin", "lena", "baboon", "coin_otsu",
              "lena_otsu", "baboon_otsu"]
for i in range(len(images)):
    plt.rcParams['font.sans-serif']=['SimHei']
    plt.rcParams['axes.unicode_minus'] = False
    plt.suptitle('采用Otsu算法进行图像分割')
    plt.subplot(2, 3, i+1)
    plt.imshow(images[i], 'gray')
    plt.xticks([]), plt.yticks([])
    plt.title(titles[i])
plt.show()