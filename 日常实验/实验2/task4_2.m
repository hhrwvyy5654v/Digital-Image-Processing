lena=imread("lena.jpg");
lena_gray=rgb2gray(lena);
f=double(lena_gray);
g=fft2(f);  %傅里叶变换
g=fftshift(g);
[M,N]=size(g);

%d0=15 理想低通滤波
d0=15;
m=fix(M/2);
n=fix(N/2);
for i=1:M
    for j=1:N
        d=sqrt((i-m)^2+(j-n)^2);
        if(d<d0)
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
title('d0=15 理想低通滤波器');



%d0=30 的理想低通滤波
d0=30;  
m=fix(M/2); 
n=fix(N/2); 
for i=1:M  
    for j=1:N  
        d=sqrt((i-m)^2+(j-n)^2);  
        if(d<=d0)  
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
title('d0=30 理想低通滤波器');


%d0=100 的理想低通滤波
d0=100;  
m=fix(M/2); 
n=fix(N/2); 
for i=1:M  
    for j=1:N  
        d=sqrt((i-m)^2+(j-n)^2);  
        if(d<=d0)  
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
 title('d0=100 理想低通滤波器');









