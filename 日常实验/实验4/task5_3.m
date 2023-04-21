%读取原始图像
wallpaper3=imread('wallpaper3.jpg');

%将图像转换为灰度图像
wallpaper3=rgb2gray(wallpaper3);

% 分别向wallpaperr1添加椒盐噪音、高斯噪声、均匀分布噪声
wallpaper3_salt_pepper=imnoise(wallpaper3,'salt & pepper',0.05);
wallpaper3_gauwallpaperian=imnoise(wallpaper3,'gaussian',0.05);
wallpaper3_speckle=imnoise(wallpaper3,'speckle',0.05);

% 对椒盐噪声图像依次用均值滤波，中值滤波、自适应中值滤波和二维自适应去噪滤波进行处理
wallpaper3_salt_pepper_mean_filtering=filter2(y11,wallpaper3_salt_pepper)/255;
wallpaper3_salt_pepper_median_filtering=medfilt2(wallpaper3_salt_pepper,[3,3]);
wallpaper3_salt_pepper_adaptive_median_filtering=adpmedian(wallpaper3_salt_pepper,15);
wallpaper3_salt_pepper_wiener2_filtering = wiener2(wallpaper3_salt_pepper,[5 5]);

% 对高斯噪声图像依次用均值滤波，中值滤波、自适应中值滤波和二维自适应去噪滤波进行处理
wallpaper3_gauwallpaperian_mean_filtering=filter2(y11,wallpaper3_salt_pepper)/255;
wallpaper3_gauwallpaperian_median_filtering=medfilt2(wallpaper3_salt_pepper,[3,3]);
wallpaper3_gauwallpaperian_adaptive_median_filtering=adpmedian(wallpaper3_salt_pepper,15);
wallpaper3_gauwallpaperian_wiener2_filtering = wiener2(wallpaper3_salt_pepper,[5 5]);

% 对均匀分布噪声图像依次用均值滤波，中值滤波、自适应中值滤波和二维自适应去噪滤波进行处理
wallpaper3_speckle_mean_filtering=filter2(y11,wallpaper3_salt_pepper)/255;
wallpaper3_speckle_median_filtering=medfilt2(wallpaper3_salt_pepper,[3,3]);
wallpaper3_speckle_adaptive_median_filtering=adpmedian(wallpaper3_salt_pepper,15);
wallpaper3_speckle_wiener2_filtering = wiener2(wallpaper3_salt_pepper,[5 5]);

subplot(5,3,1);imshow(wallpaper3_salt_pepper);title('添加椒盐噪音');
subplot(5,3,2);imshow(wallpaper3_gauwallpaperian);title('添加高斯噪声');
subplot(5,3,3);imshow(wallpaper3_speckle);title('添加均匀分布噪音');

subplot(5,3,4);imshow(wallpaper3_salt_pepper_mean_filtering);title('均值滤波');
subplot(5,3,5);imshow(wallpaper3_speckle_mean_filtering);title('均值滤波');
subplot(5,3,6);imshow(wallpaper3_salt_pepper_wiener2_filtering);title('均值滤波');

subplot(5,3,7);imshow(wallpaper3_salt_pepper_mean_filtering);title('中值滤波');
subplot(5,3,8);imshow(wallpaper3_speckle_mean_filtering);title('中值滤波');
subplot(5,3,9);imshow(wallpaper3_salt_pepper_wiener2_filtering);title('中值滤波');

subplot(5,3,10);imshow(wallpaper3_salt_pepper_mean_filtering);title('自适应中值滤波');
subplot(5,3,11);imshow(wallpaper3_speckle_mean_filtering);title('自适应中值滤波');
subplot(5,3,12);imshow(wallpaper3_salt_pepper_wiener2_filtering);title('自适应中值滤波');

subplot(5,3,13);imshow(wallpaper3_salt_pepper_mean_filtering);title('二维自适应去噪滤波');
subplot(5,3,14);imshow(wallpaper3_speckle_mean_filtering);title('二维自适应去噪滤波');
subplot(5,3,15);imshow(wallpaper3_salt_pepper_wiener2_filtering);title('二维自适应去噪滤波');
