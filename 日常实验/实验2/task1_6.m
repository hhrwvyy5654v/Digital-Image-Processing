lena=imread('lena.jpg');    %读入原始图像
lena_gray=rgb2gray(lena);   %将图像灰度化
lena_pepper=imnoise(lena_gray,'salt & pepper',0.02);    %加入椒盐噪声
[m,n]=size(lena_pepper);


figure,subplot(1,2,1);
imshow(lena_pepper);
title('椒盐噪声图');
s=zeros(1,9);

for i=2:1:m-1
    for j=2:1:n-1
        h=1;
        for p=i-1:1:i+1
            for q=j-1:1:j+1
                s(h)=lena_pepper(p,q);
                h=h+1;
            end
        end
        s=sort(s);
        I(i,j)=s(5);    
    end
end

subplot(1,2,2);
imshow(I);
title('噪声处理后的图像');
