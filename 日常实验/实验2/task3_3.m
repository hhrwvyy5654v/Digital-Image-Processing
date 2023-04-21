lena=imread("lena.jpg");
lena_gray=rgb2gray(lena);
f1=fft2(lena_gray); %快速傅里叶变换
f2=log(1+abs(f1));
f3=fftshift(f1);
f4=angle(f1);
f5=-f4;
f6=double(f3*exp(f4));   %傅里叶变换的复共轭
f7=ifft2(f6);   %反傅里叶变换
figure,subplot(1,2,1);
imshow(lena_gray);
title('原始图像');
subplot(1,2,2);
imshow(real(f7),[]);
title('逆傅里叶变换');
