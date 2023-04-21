lena = imread('lena.jpg');
lena_gray=rgb2gray(lena);
subplot(2,2,1);
imshow(lena_gray);
title('原始图像');


LEN1=12;
THREN1=22;
PFS2=fspecial("motion",LEN1,THREN1);
fuzzy_lena=imfilter(lena_gray,PFS2,'circular'); %对图像进行模糊劣化
subplot(2,2,2);
imshow(fuzzy_lena);
title('模糊劣化图像');


deconvwnr_lena=deconvwnr(fuzzy_lena,PFS2);
subplot(2,2,3);
imshow(deconvwnr_lena);
title('采用维纳滤波复原图像');

least_squares_lena=deconvreg(fuzzy_lena,PFS2);
subplot(2,2,4);
imshow(least_squares_lena);
title('采用最小二乘法复原图像')