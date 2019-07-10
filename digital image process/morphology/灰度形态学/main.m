

%%²âÊÔ»ù±¾²Ù×÷
%{
im = imread(['_circuit_m', '.jpg']);
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

%{
im = imread(['Fig0940(a)(rice_image_with_intensity_gradient)', '.tif']);
img_b = im2bw(im, 0.5);
img_o = my_open(im, 69, 69);
img_t = top_hat(im, 69, 69);
img_tb = im2bw(img_t, 0.2);

figure(1);
subplot(231); imshow(im); axis on
subplot(232); imshow(img_b); axis on
subplot(234); imshow(img_o); axis on
subplot(235); imshow(img_t); axis on
subplot(236); imshow(img_tb); axis on
%}


im = imread(['Fig0941(a)(wood_dowels)', '.tif']);
[w,h] = size(im);
img_s = my_open_c(im, 5);
img_s = my_close_c(img_s, 5);
img_10 = my_open_c(img_s, 10);
img_20 = my_open_c(img_s, 20);
img_25 = my_open_c(img_s, 25);
img_30 = my_open_c(img_s, 30);
r = [1:1:35];
sum = zeros(1, 35);
for i = 1:35
    img_o = my_open_c(img_s, r(i));
    for j = 1:w
        for k = 1:h
            sum(i) = sum(i) + double(img_o(j,k));
        end
    end
end
dis = zeros(1, 35);
dis(1) = 0;
for i = 2:35
    dis(i) = sum(i-1) - sum(i);
end
plot(r,dis);
figure(2);
subplot(231); imshow(im); axis on
subplot(232); imshow(img_s); axis on
subplot(233); imshow(img_10); axis on
subplot(234); imshow(img_20); axis on
subplot(235); imshow(img_25); axis on
subplot(236); imshow(img_30); axis on


im = imread(['Fig0943(a)(dark_blobs_on_light_background)', '.tif']);
img_b = my_close_c(im, 30);
img_d = my_open_c(img_b, 70);
[w,h] = size(im);
X = zeros(1,h);

for i = 1:h
    for j = 1:w-1
        if(img_d(i,j)-img_d(i,j+1) > 0)
            X(i) = j;
            break;
        end
    end
end

img = im;
for i = 1:h
    img(i, X(i)) = 255;
    img(i, X(i)-1) = 255;
    img(i, X(i)+1) = 255;
    img(i, X(i)-2) = 255;
    img(i, X(i)+2) = 255;
end
    
figure(3);
subplot(231); imshow(im); axis on
subplot(232); imshow(img_b); axis on
subplot(233); imshow(img_d); axis on
subplot(234); imshow(img); axis on

