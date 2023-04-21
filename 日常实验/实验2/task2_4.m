[I,map]=imread('lena_gray.jpg'); 
I=double(I); 

subplot(2,3,1) 
imshow(I,map); 
title('原始图像'); 

[Gx,Gy]=gradient(I); % 梯度计算 
G=sqrt(Gx.*Gx+Gy.*Gy); % 矩阵 
J1=G; % 梯度1 
subplot(2,3,2)
imshow(J1,map); 
title(' 操作1图像'); 

J2=I; % 梯度2 
K=find(G>=7); 
J2(K)=G(K); 
subplot(2,3,3) 
imshow(J2,map); 
title('操作2图像'); 

J3=I; % 梯度3 
K=find(G>=7); 
J3(K)=255; 
subplot(2,3,4) 
imshow(J3,map); 
title('操作3图像'); 

J4=I; % 梯度4 
K=find(G<=7); 
J4(K)=255; 
subplot(2,3,5) 
imshow(J4,map); 
title('操作4图像'); 

J5=I; %梯度5 
K=find(G<=7); 
J5(K)=0; 
Q=find(G>=7); 
J5(Q)=255; 
subplot(2,3,6) 
imshow(J5,map); 
title('操作5图像');