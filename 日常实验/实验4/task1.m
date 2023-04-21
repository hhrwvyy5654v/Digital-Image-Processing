lena = imread('lena.jpg');
lena_gray = rgb2gray(lena);

subplot(1, 3, 1);
imshow(lena_gray);
title('原始图像');

PSF = fspecial('motion', 15, 45);
h1 = fspecial('disk', 40);
J1 = imfilter(lena_gray, PSF, 'circular');
J2 = imfilter(lena_gray, h1, 'circular');

subplot(1, 3, 2);
imshow(J1);
title('模糊运动图像');

subplot(1, 3, 3);
imshow(J2);
title('disk模糊图像');
