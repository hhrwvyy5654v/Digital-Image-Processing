image=imread('./coins.png');
image=image>128;
[m n]=size(image);

image_boundary_tracking=zeros(m,n);        %边界跟踪图像
ed=[-1 -1;0 -1;1 -1;1 0;1 1;0 1;-1 1;-1 0]; %从左上角像素判断
for i=2:m-1
    for j=2:n-1
        if image(i,j)==1      %如果当前像素是前景像素
            
            for k=1:8
                ii=i+ed(k,1);
                jj=j+ed(k,2);
                if image(ii,jj)==0    %当前像素周围如果是背景，边界标记图像相应像素标记
                    image_boundary_tracking(ii,jj)=1;
                end
            end
            
        end
    end
end

figure,subplot(1, 2, 1);
imshow(image);
title('原始图像');

subplot(1, 2, 2);
imshow(image_boundary_tracking,[]);
title('边界跟踪图像');