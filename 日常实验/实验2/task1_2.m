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

%对椒盐噪声图像进行滤波处理
h = fspecial('average', 3);
I1 = filter2(h, lena_pepper) / 255; %二维数字滤波器
I2 = medfilt2(lena_pepper, [3 3]); %二维中位数滤波
figure, subplot(2, 2, 1);
imshow(lena);
title('原始图像');

subplot(2, 2, 2);
imshow(lena_pepper);
title('椒盐噪声图像');

subplot(2, 2, 3);
imshow(I1);
title('3*3 均值滤波图像');

subplot(2, 2, 4);
imshow(I2);
title('3*3 中值滤波图像');

%对高斯噪声图像进行滤波处理
G1 = filter2(h, lena_gauss) / 255; %二维数字滤波器
G2 = medfilt2(lena_gauss, [3 3]); %二维中位数滤波

figure, subplot(2, 2, 1);
imshow(lena);
title('原始图像');

subplot(2, 2, 2);
imshow(lena_gauss);
title('高斯噪声图像');

subplot(2, 2, 3);
imshow(G1);
title('3*3 均值滤波图像');

subplot(2, 2, 4);
imshow(G2);
title('3*3 中值滤波图像');
