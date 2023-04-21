lena=imread("lena.jpg");
lena_gray=rgb2gray(lena);

f1=fft2(lena_gray); %快速傅里叶变换
f=ifft(abs(f1));
figure,subplot(1,3,1);
imshow(lena_gray);
title('原始图像');

subplot(1,3,2);
imshow(log(1+abs(f3)),[]);
title('振幅图像');

subplot(1,3,3);
imshow(log(1+abs(f)),[]);
title('相位图像');