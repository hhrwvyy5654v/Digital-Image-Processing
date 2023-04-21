lena=imread("lena.jpg");
lena_gray=rgb2gray(lena);
f1=fft2(lena_gray); %快速傅里叶变换
f2=log(1+abs(f1));  %振幅谱
f3=fftshift(f1);    
f4=angle(f1);   %相位谱

figure,subplot(1,3,1);
imshow(lena_gray);
title('原始图像');

subplot(1,3,2);
imshow(log(1+abs(f3)),[]);
title('幅度图像');

subplot(1,3,3);
imshow(f4);
title('相位图像');