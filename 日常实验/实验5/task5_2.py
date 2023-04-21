import cv2 
import matplotlib.pyplot as plt

# 图像显示函数
def Image_display(image):
    if image.ndim == 2:
        plt.imshow(image, cmap='gray', vmin=0, vmax=255)
    else:
        image = cv2.cvtColor(image, cv2.COLOR_BGR2RGB)
        plt.imshow(image)
    plt.show()

def Iterative_threshold(image):
    T = image.mean()
    while True:
        t0 = image[image < T].mean()
        t1 = image[image >= T].mean()
        t  = (t0 + t1) / 2
        if abs(T - t) < 1:
            break
        T = t
    T = int(T)
    th, image_binary = cv2.threshold(image, T, 255, 0)
    Image_display(image_binary)

if __name__ == '__main__':
    # 将图像调整为单通道的灰度图像
    coin = cv2.imread('./coin.png',cv2.IMREAD_GRAYSCALE)
    lena = cv2.imread('./lena.jpg',cv2.IMREAD_GRAYSCALE)
    baboon = cv2.imread('./baboon.bmp',cv2.IMREAD_GRAYSCALE)
    
    Iterative_threshold(coin)
    Iterative_threshold(lena)
    Iterative_threshold(baboon)
