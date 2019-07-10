clc; 
clear;
close all;

im = imread(['Fig1034(a)(marion_airport)', '.tif']);

%%�����Ե���
img_edge = cany(im,0.5,10,25);
[A, img_hough] = my_hogh(img_edge);
img_line = show_line(im, img_hough);

figure(1)
subplot(231)
imshow(im)
title('ԭͼ')

subplot(232)
imshow(img_edge)
title('canny��Ե')


subplot(233)
imshow(A)
title('hough�ռ���')

subplot(234)
imshow(img_hough)
title('�ҵ�����')

subplot(235)
imshow(img_line)
title('���ӵ�ԭͼ')

%%������ֵ
im = imread('Fig1038(a)(noisy_fingerprint).tif');

figure(2)
subplot(131)
imshow(im)
title('ԭͼ')

subplot(132)
imhist(im);
title('ֱ��ͼ')

subplot(133)
T = global_threshold(im);
img = zeros(size(im),'logical');
img(im>T) = 1;
imshow(img)
title('ȫ����ֵ����')

%%Otsu
im = imread('Fig1039(a)(polymersomes).tif');

figure(3)
subplot(221)
imshow(im)
title('ԭͼ')

subplot(222)
imhist(im)
title('ֱ��ͼ')

subplot(223)
T = global_threshold(im);
img = zeros(size(im),'logical');
img(im>T) = 1;
imshow(img)
title('ȫ����ֵ')

subplot(224)
img = Otsu(im);
imshow(img)
title('Otsu��ֵ')

%%�ֿ�
im = imread('Fig1046(a)(septagon_noisy_shaded).tif');

figure(4)
subplot(231)
imshow(im)
title('ԭͼ')

subplot(232)
imhist(im)
title('ֱ��ͼ')

subplot(233)
T = global_threshold(im);
img = zeros(size(im),'logical');
img(im>T) = 1;
imshow(img)
title('ȫ����ֵ')

subplot(234)
img = Otsu(im);
imshow(img)
title('Ostu��ֵ')

subplot(235)
size_im = size(im);
img = im;
img(ceil(size_im(1)/2)-5:ceil(size_im(1)/2)+5,:) = 255;
img(:,ceil(size_im(2)/3)-5:ceil(size_im(2)/3)+5) = 255;
img(:,ceil(size_im(2)/3*2)-5:ceil(size_im(2)/3*2)+5) = 255;
imshow(img)
title('�ֳ�6��')

subplot(236)
im1 = Otsu(im(1:ceil(size_im(1)/2),1:ceil(size_im(2)/3)));
im2 = Otsu(im(1:ceil(size_im(1)/2),ceil(size_im(2)/3)+1:ceil(size_im(2)/3*2)));
im3 = Otsu(im(1:ceil(size_im(1)/2),ceil(size_im(2)/3*2)+1:end));
im4 = Otsu(im(ceil(size_im(1)/2)+1:end,1:ceil(size_im(2)/3)));
im5 = Otsu(im(ceil(size_im(1)/2)+1:end,ceil(size_im(2)/3)+1:ceil(size_im(2)/3*2)));
im6 = Otsu(im(ceil(size_im(1)/2)+1:end,ceil(size_im(2)/3*2)+1:end));
imshow([im1,im2,im3;im4,im5,im6])
title('�ֿ�Otsu')










