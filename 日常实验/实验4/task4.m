lena = imread('lena.jpg');
lena_gray=rgb2gray(lena);
subplot(1,3,1);
imshow(lena_gray);
title('原始图像');

LEN1=50;
THREN1=100;
PFS2=fspecial("motion",LEN1,THREN1);
fuzzy_lena=imfilter(lena_gray,PFS2,'circular'); %对图像进行模糊劣化
median_filtering_lena=adpmedian(fuzzy_lena,15);

subplot(1,3,2);
imshow(fuzzy_lena);
title('劣化图像');

subplot(1,3,3);
imshow(median_filtering_lena);
title('中值滤波图像')

