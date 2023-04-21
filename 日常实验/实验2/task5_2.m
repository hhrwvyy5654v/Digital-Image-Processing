lena=imread('lena.jpg');    %将原始图像读入
lena_gray=rgb2gray(lena);   %将图像灰度化
lena_double=double(lena_gray);
g=fft2(f);  %傅里叶变换
g=fftshift(g);
[M,N]=size(g);

%d0=15的理想高通滤波器
d0=15;
m=fix(M/2);
n=fix(N/2); 
for i=1:M  
    for j=1:N  
        d=sqrt((i-m)^2+(j-n)^2);
        if(d>=d0)
            h=1;
        else
            h=0;
        end
        result(i,j)=h*g(i,j);
    end
end
result=ifftshift(result);
J1=ifft2(result);
J2=uint8(real(J1));

figure,subplot(2,2,1);
imshow(lena);
title('原始图像');

subplot(2,2,2);
imshow(J2);
title('d0=15 理想高通滤波器');



%d0=30的理想高通滤波器
d0=30;
m=fix(M/2);
n=fix(N/2); 
for i=1:M  
    for j=1:N  
        d=sqrt((i-m)^2+(j-n)^2);
        if(d>=d0)
            h=1;
        else
            h=0;
        end
        result(i,j)=h*g(i,j);
    end
end
result=ifftshift(result);
J1=ifft2(result);
J2=uint8(real(J1));

subplot(2,2,3);
imshow(J2);
title('d0=30 理想高通滤波器');



%d0=80的理想高通滤波器
d0=80;
m=fix(M/2);
n=fix(N/2); 
for i=1:M  
    for j=1:N  
        d=sqrt((i-m)^2+(j-n)^2);
        if(d>=d0)
            h=1;
        else
            h=0;
        end
        result(i,j)=h*g(i,j);
    end
end
result=ifftshift(result);
J1=ifft2(result);
J2=uint8(real(J1));

subplot(2,2,4);
imshow(J2);
title('d0=80 理想高通滤波器');



%d0=15的巴特沃斯高通滤波器
nn=2;
d0=15;
m=fix(M/2);
n=fix(N/2);
for i=1:M
    for j=1:N
        d=sqrt((i-m)^2+(j-n)^2);
        if(d==0)
            h=0;
        else
            h=1/(1+0.414*(d0/d)^(2*nn));
        end
        result(i,j)=h*g(i,j);
    end
end
result=ifftshift(result);
J1=ifft2(result);
J2=uint8(real(J1));

figure,subplot(2,2,1);
imshow(lena);
title('原始图像');

subplot(2,2,2);
imshow(J2);
title('d0=15 巴特沃斯高通滤波')


%d0=30的巴特沃斯高通滤波器
d0=30;
m=fix(M/2);
n=fix(N/2);
for i=1:M
    for j=1:N
        d=sqrt((i-m)^2+(j-n)^2);
        if(d==0)
            h=0;
        else
            h=1/(1+0.414*(d0/d)^(2*nn));
        end
        result(i,j)=h*g(i,j);
    end
end
result=ifftshift(result);
J1=ifft2(result);
J2=uint8(real(J1));

subplot(2,2,3);
imshow(J2);
title('d0=30 巴特沃斯高通滤波')



%d0=80的巴特沃斯高通滤波器
d0=80;
m=fix(M/2);
n=fix(N/2);
for i=1:M
    for j=1:N
        d=sqrt((i-m)^2+(j-n)^2);
        if(d==0)
            h=0;
        else
            h=1/(1+0.414*(d0/d)^(2*nn));
        end
        result(i,j)=h*g(i,j);
    end
end
result=ifftshift(result);
J1=ifft2(result);
J2=uint8(real(J1));

subplot(2,2,4);
imshow(J2);
title('d0=80 巴特沃斯高通滤波')









