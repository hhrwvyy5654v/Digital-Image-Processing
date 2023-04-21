lena=imread("lena.jpg");
lena_gray=rgb2gray(lena);   %转换为灰度图像
h=fspecial("sobel");
h1=h'*0.5;
h2=h';
h3=h'*1.5;

z1=imfilter(lena_gray,h1);
z2=imfilter(lena_gray,h2);
z3=imfilter(lena_gray,h3);

figure,subplot(2,2,1);
imshow(lena_gray);
title('原始图像');

subplot(2,2,2);
imshow(z1);
title('梯度算子1');

subplot(2,2,3);
imshow(z2);
title('梯度算子2');

subplot(2,2,4);
imshow(z3);
title('梯度算子3');

