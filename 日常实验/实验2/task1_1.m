lena = imread('lena.jpg'); %读入原始图像
lena_gray = rgb2gray(lena); %原始图像灰度化

figure, subplot(1, 3, 1);
imshow(lena_gray);
title('原始图像');
lena_pepper = imnoise(lena_gray, 'salt & pepper', 0.02); %加入椒盐噪声

subplot(1, 3, 2);
imshow(lena_pepper);
title('椒盐噪声图像');

lena_gauss = imnoise(lena_gray, "gaussian", 0.02); %加入高斯噪声
subplot(1, 3, 3);
imshow(lena_gauss);
title('高斯噪声图像');
