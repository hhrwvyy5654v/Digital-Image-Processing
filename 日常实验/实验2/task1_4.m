lena=imread('lena.jpg');    %将原始图像读入
lena_gray=rgb2gray(lena);   %将图像灰度化
lena_pepper=imnoise(lena_gray,'salt & pepper',0.02);    %加入椒盐噪声
h=fspecial('average');  %生成均值滤波器
for i=1:10  %对椒盐噪声图像进行10次均值滤波
    J1=imfilter(lena_pepper,h); end
for j=1:20  %对椒盐噪声图像进行20次均值滤波
    J2=imfilter(lena_pepper,h); end;

figure,subplot(1,3,1);
imshow(lena_pepper);
title('椒盐噪声图像');

subplot(1,3,2);
imshow(J1);
title('10次均值滤波');

subplot(1,3,3);
imshow(J2);
title('20次均值滤波');

