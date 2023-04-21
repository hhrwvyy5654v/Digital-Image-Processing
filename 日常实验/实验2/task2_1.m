close all
lena=imread('lena.jpg');    %读入原始图像
lena_gray=rgb2gray(lena);   %将图像灰度化
lena_double=im2double(lena_gray) %将图像转换为双精度值
w=[1,1,1;
    1,-8,1;
    1,1,1]
k=conv2(lena_double,w,"same");

figure,subplot(1,2,1);      
imshow(lena);
title('原始图像');

subplot(1,2,2);      
imshow(k);
title('滤波处理后的图像');
