%生成一个120×120的棋盘图像
chessboard = checkerboard(10, 60, 60);
PSF1 = fspecial('motion', 7, 45);
GB1 = imfilter(chessboard, PSF1, 'circular');

subplot(2, 3, 1);
imshow(chessboard);
title('棋盘格式图像');

%对棋盘图像进行加噪
noise_mean = 0;
noise_var = 0.05;
GB1 = imnoise(GB1, 'gaussian', noise_mean, noise_var);
subplot(2, 3, 2);
imshow(GB1);
title('模糊加噪图像');

% 使用点扩散函数恢复降质图像
frest1 = deconvwnr(GB1, PSF1);
subplot(2, 3, 3);
imshow(frest1);
title('点扩散函数恢复降质图像');

Sn = abs(fft2(GB1)).^2;
nA = sum(Sn(:)) / numel(GB1); %噪声平均功率1
Sf = abs(fft2(chessboard)).^2; %图像功率谱1
fA = sum(Sf(:)) / numel(chessboard); %图像平均功率1
R = nA / fA; %计算噪声和信号比例

% 使用NSR恢复降质图像
fr2 = deconvwnr(GB1, PSF, R); %使用deconvwnr函数生成常数比率的维纳滤波图像
subplot(2, 3, 4);
imshow(fr2);
title('NSR恢复降质图像');

% 使用NCORR和ICORR恢复降质图像
NCORR = fftshift(real(ifft2(Sn))); %噪声自相关函数
ICORR = fftshift(real(ifft2(Sf))); %原图像自相关函数
fr3 = deconvwnr(GB1, PSF, NCORR, ICORR); %使用deconvwnr函数生成自相关函数的维纳滤波图像

subplot(2, 3, 5);
imshow(fr3);
title('NCORR和ICORR恢复降质图像');
