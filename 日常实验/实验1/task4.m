lena = imread('./images/lena.jpg'); %读入原始图像
lena = rgb2gray(lena);
subplot(2, 2, 1); imshow(lena, []); title('原图像');

%分段线性变换
[M, N] = size(lena);
lena = im2double(lena);
out = zeros(M, N);
X1 = 0.125;
Y1 = 0.250; %转折点1
X2 = 0.750;
Y2 = 0.625; %转折点2

for i = 1:M
    for j = 1:N %遍历图像每个像素
        if lena(i, j) < X1
            out(i, j) = Y1 * lena(i, j) / X1;
        elseif lena(i, j) > X2
            out(i, j) = (lena(i, j) - X2) * (1 - Y2) / (1 - X2) + Y2;
        else
            out(i, j) = (lena(i, j) - X1) * (Y2 - Y1) / (X2 - X1) + Y1;
        end
    end
end

subplot(2, 2, 2); imshow(out, []); title('变换的后图像')
subplot(2, 2, 3); imhist(lena); title('原始图像');
subplot(2, 2, 4); imhist(out); title('变换后的图像')
