clc; 
clear;
close all;

im = imread(['Fig0929(a)(text_image)', '.tif']);

%%测试基本操作
%{
img_e = my_erode(im,3,3);
img_i = my_expan(im,3,3);
img_o = my_open(im,3,3);
img_c = my_close(im,3,3);

figure(1);
subplot(321); imshow(im); axis on
subplot(322); imshow(img_e); axis on
subplot(323); imshow(img_i); axis on
subplot(324); imshow(img_o); axis on
subplot(325); imshow(img_c); axis on
%}

%文本图像二值形态学处理
%重建开操作

img_e = my_erode(im, 51, 1);
img_o = my_open(im, 51, 1);
img_r = Re_open(im, 51, 1, 1);

figure(1);
subplot(221); imshow(im); axis on
subplot(222); imshow(img_e); axis on
subplot(223); imshow(img_o); axis on
subplot(224); imshow(img_r); axis on


%空洞填充

[h,w] = size(im);
img_F = false(h,w);
for j = 1:w
    img_F(1,j) = 1 - im(1,j);
    img_F(h,j) = 1 - im(h,j);
end
for i = 2:h-1
    img_F(i,1) = 1 - im(i,1);
    img_F(i,w) = 1 - im(i,w);
end
img_c = true(h,w) - im;
img_H = R_expan(img_F, img_c, 3, 3);
img_H = true(h,w) - img_H;
figure(2);
subplot(221); imshow(im); axis on
subplot(222); imshow(img_c); axis on
subplot(223); imshow(img_F); axis on
subplot(224); imshow(img_H); axis on   


%边界清除
[h,w] = size(im);
img_F = false(h,w);
for j = 1:w
    img_F(1,j) = im(1,j);
    img_F(h,j) = im(h,j);
end
for i = 2:h-1
    img_F(i,1) = im(i,1);
    img_F(i,w) = im(i,w);
end
img_e = R_expan(img_F, im, 3, 3);
img_x = im - img_e;
figure(3);
subplot(211); imshow(img_e); axis on
subplot(212); imshow(img_x); axis on


