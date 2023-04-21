# 导包
import cv2
import numpy as np
import matplotlib.pyplot as plt

# 定义像素点集
class Point(object):
    def __init__(self, x, y):
        self.x = x
        self.y = y

    def getX(self):
        return self.x

    def getY(self):
        return self.y

# 计算两个像素点的灰度差异
def getGrayDiff(image, currentPoint, tmpPoint):
    return abs(int(image[currentPoint.x, currentPoint.y]) - int(image[tmpPoint.x, tmpPoint.y]))

# 连通区域选择
def selectConnects(p):
    if p != 0:  # 8连通区域
        connects = [Point(-1, -1), Point(0, -1), Point(1, -1), Point(1, 0),
                    Point(1, 1), Point(0, 1), Point(-1, 1), Point(-1, 0)]
    else:   # 4连通区域
        connects = [Point(0, -1), Point(1, 0), Point(0, 1), Point(-1, 0)]
    return connects

# 区域生长
def regionGrow(image, seeds, thresh, p=1):
    # thresh:生长时候的相似性阈值,默认即灰度级不相差超过15以内的都算为相同
    height, weight = image.shape  # 获取图像的高度和宽度
    seedMark = np.zeros(image.shape)  # 建立与图像等大的空矩阵
    seedList = []   # 定义种子坐标列表
    for seed in seeds:  # 将种子像素入栈
        seedList.append(seed)
    flag = 1  # 设立是否判断的标记
    connects = selectConnects(p)  # 选择连通区域
    while (len(seedList) > 0):  # 若种子坐标列表非空
        currentPoint = seedList.pop(0)  # 将最前面的那个抛出
        seedMark[currentPoint.x, currentPoint.y] = flag  # 将对应位置的点标志为1
        for i in range(8):  # 对该点周围的8个点进行相似性判断
            tmpX = currentPoint.x + connects[i].x
            tmpY = currentPoint.y + connects[i].y
            if tmpX < 0 or tmpY < 0 or tmpX >= height or tmpY >= weight:   # 如果超出限定的阈值范围
                continue    # 跳过并继续
            grayDiff = getGrayDiff(image, currentPoint,
                                   Point(tmpX, tmpY))  # 计算该点与像素点的灰度级之差
            # 如果灰度差异小于阈值且种子坐标未被标记
            if grayDiff < thresh and seedMark[tmpX, tmpY] == 0:
                seedMark[tmpX, tmpY] = flag  # 标记该种子坐标
                seedList.append(Point(tmpX, tmpY))  # 将像素点加入种子列表
    return seedMark


if __name__ == '__main__':
    # 将原始图像读取为灰度图像
    lena = cv2.imread('./lena.jpg', cv2.IMREAD_GRAYSCALE)
    # 设第一个未归属的像素为(x0, y0);
    seeds = [Point(320, 240)]
    lena_split = regionGrow(lena, seeds, 5)
    # 显示图像
    images = [lena, lena_split]
    titles = ["lena", "lena_split"]
    for i in range(len(images)):
        plt.subplot(1, 2, i+1)
        plt.imshow(images[i], 'gray')
        plt.xticks([]), plt.yticks([])
        plt.title(titles[i])
    plt.show()
