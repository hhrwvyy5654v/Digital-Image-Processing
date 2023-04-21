close all
lena=imread("./images/lena.jpg");
lena_gray1=rgb2gray(lena);
subplot(2,2,1);
imshow(lena_gray1);
title("灰色图像");
subplot(2,2,2);
imhist(lena_gray1);
title("调整前的灰度直方图");

lena_gray2=imadjust(lena_gray1,[0,0.4],[0,1],1);
subplot(2,2,3);
imshow(lena_gray2);
title("imadjust灰度变换调整后图像");
subplot(2,2,4);