lena=imread('lena.jpg');    %读入原始图像
lena_gray=rgb2gray(lena);   %将图像灰度化
lena_pepper=imnoise(lena_gray,'salt & pepper',0.02);    %加入椒盐噪声
h=fspecial('average');  %生成均值滤波器
J1=imfilter(lena_pepper,h);
J2=medfilt2(lena_pepper);

figure,subplot(1,3,1);
imshow(lena_pepper);
title('椒盐噪声图像');

subplot(1,3,2);
imshow(J1);
title('均值滤波法');

subplot(1,3,3);
imshow(J2);
title('中值滤波法');