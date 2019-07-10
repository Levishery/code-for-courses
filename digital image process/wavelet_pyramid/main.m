clc;
clear;
close all;

% ∂¡»°Õº∆¨
im = imread('demo-1.jpg');
[py_si1, py_si2, py_si3, py_re1, py_re2, py_re3] = pyramid(im);

im2 = imread('demo-2.tif');
%im2 = imresize(im2, [64,64]);
[fwt1,im3] = fwt(im2);
[fwt2,im4] = fwt(im3);
[fwt3,im5] = fwt(im4);

im_rec = reverse_fwt(fwt1);

PSNR = psnr(im2, im_rec)

size_2 = size(fwt1);
h_2 = size_2(1)/2;
w_2 = size_2(2)/2;
fwt_ = fwt1;
fwt_(1:h_2,1:w_2) = zeros(h_2, w_2);

im_edge = histeq(reverse_fwt(fwt_),256);
%im_edge1 = reverse_fwt(fwt_);



%figure(1);
%subplot(241); imshow(im); title('im'); axis on
%subplot(242); imshow(py_si1); axis on
%imshow(im);
figure(1);
imshow(im);
hold on;
imshow(histeq(py_re1,256));
imshow(histeq(py_re2,256));
imshow(histeq(py_re3,256));

figure(2)
imshow(histeq(fwt1,256));
hold on;
imshow(histeq(fwt2,256));
imshow(histeq(fwt3,256));

figure(3)
subplot(131); imshow(im2); title('im'); axis on
subplot(132); imshow(im_rec); title('im_rec'); axis on
subplot(133); imshow(im_edge); title('im_edge1'); axis on
