lena=imread('lena.jpg');    %将原始图像读入
lena_gray=rgb2gray(lena);   %将图像灰度化
h=fspecial('motion',50,45);  %创建预定义的二维滤波器

filteredimg=imfilter(lena_gray,h);    % 对图像进行滤波,默认通过使用相关来完成
boundaryReplicate=imfilter(lena_gray,h,"replicate") ;    %图像大小通过复制外边界的值来扩展
boundary0=imfilter(lena_gray,h,0);   % 输入图像的边界通过用值X（无引号）来填充扩展，其默认值为0
boundarysymmetric=imfilter(lena_gray,h,"symmetric");  %图像大小通过镜像反射其边界来扩展
boundarycircular=imfilter(lena_gray,h,'circular');   %图像大小通过将图像看成是一个二维周期函数的一个周期来扩展

figure,subplot(3,2,1);%为各个分块创建分区
imshow(lena);   
title('原始图像');

subplot(3,2,2);
imshow(filteredimg);
title('Motion Blurred');

subplot(3,2,3);
imshow(boundaryReplicate);
title('Replicate');

subplot(3,2,4);
imshow(boundary0);
title('0-Padding');

subplot(3,2,5);
imshow(boundarysymmetric);
title('symmetric');

subplot(3,2,6);
imshow(boundarycircular);
title('cicular');