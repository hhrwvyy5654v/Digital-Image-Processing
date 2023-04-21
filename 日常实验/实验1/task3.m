%直方图均衡化
lena = imread("./images/lena.jpg");
lena1 = rgb2gray(lena);

subplot(1, 2, 1);
imshow(lena1);
title("原图");
ylim("auto");
g = histeq(lena1, 256);
subplot(1, 2, 2);
imshow(g);
title("直方图均衡化图");
