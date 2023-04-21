%理想低通滤波器的透视图
a=100;
b=100;
U=0:a;
V=0:b;
M=length(U);
N=length(V);
D0=10;  %D0是频带的中心半径
x1=50;
y1=50;
x0=-50;
y0=-50;

m=fix(M/2);
n=fix(N/2);
H=zeros(M,N);
n=2;

for u=1:M
    for v=1:N
        a=sqrt((U(u)-50).*(U(u)-50)+(V(v)-50).*(V(v)-50));  %(u,v)的值
        if(a<=D0)   %理想滤波器
            H(u,v)=1;
        else
            H(u,v)=0;
        end
    end
end

figure,subplot(1,3,1);
surf(U,V,H);
title('理想低通滤波透视图');



%巴特沃斯低通滤波器透视图
a=100;    
b=100;    
U=0:a;    
V=0:b;    
M=length(U);N=length(V);    
D0=10;%W=200;%D0 是频带的中心半径;W 是频带的宽度
x1=50;y1=50;    
x0=-50;y0=-50;    
m=fix(M/2); 
n=fix(N/2);    
H=zeros(M,N);    
n=2;    
for u=1:M    
    for v=1:N    
        a=sqrt((U(u) - 50) .* (U(u)-50) + (V(v) - 50) .* (V(v) - 50));%D(u,v)的值
        b=1+(a/D0)^2*n;    
        H(u,v)=1/b;  
    end    
end    

subplot(1,3,2);
surf(U,V,H);  
title('巴特沃斯低通滤波器透视图');



%高斯低通滤波
a=100;    
b=100;    
U=0:a;    
V=0:b;    
M=length(U);
N=length(V);    
D0=10; %D0 是频带的中心半径
x1=50;
y1=50;    
x0=-50;
y0=-50;    
m=fix(M/2);
n=fix(N/2);    
H=zeros(M,N);          
for u=1:M    
    for v=1:N    
        D1=((u-m-x0)^2+(v-n-y0).^2)^0.5;    
        D2=((u-m+x0)^2+(v-n+y0).^2)^0.5;    
        D11=((u-m-x1)^2+(v-n-y1).^2)^0.5;    
        D21=((u-m+x1)^2+(v-n+y1).^2)^0.5;    
        H(u,v) = (U(u) - 50) .* (U(u)-50) + (V(v) - 50) .* (V(v)  - 50);   
    end    
end   

S=50;    
H = -H/(2*S);    
H = exp(H) / (sqrt(2*pi) * sqrt(S));    
subplot(1,3,3),surf(U,V,H),title('高斯低通滤波');











