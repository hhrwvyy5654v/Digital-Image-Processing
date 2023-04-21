lena=imread("lena.jpg");    %读入原始图像
lena_double=im2double(lena);    %将图像转换为双精度值

figure,subplot(2,3,1);
imshow(lena_double);
title('原始图像');

w0=lapulasi(3);
w1=lapulasi(5);
w2=lapulasi(9);
w3=lapulasi(15);
w4=lapulasi(25);

lena_0=lena_double-imfilter(lena_double,w0,"replicate");
subplot(2,3,2);
imshow(lena_0);
title('3*3 拉普拉斯');

lena_1=lena_double-imfilter(lena_double,w1,"replicate");
subplot(2,3,3);
imshow(lena_1);
title('5*5 拉普拉斯');

lena_2=lena_double-imfilter(lena_double,w2,"replicate");
subplot(2,3,2);
imshow(lena_2);
title('9*9 拉普拉斯');

lena_3=lena_double-imfilter(lena_double,w3,"replicate");
subplot(2,3,5);
imshow(lena_3);
title('15*15 拉普拉斯');

lena_4=lena_double-imfilter(lena_double,w4,"replicate");
subplot(2,3,6);
imshow(lena_4);
title('25*25 拉普拉斯');


