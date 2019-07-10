function [fwt1, img] = fwt(im)

h1 = [-0.0758, -0.0296, 0.4976, 0.8037, 0.2979, -0.0992, -0.0126, 0.0322];
h2 = [-0.0322, -0.0126, 0.0992, 0.2979, -0.8037, 0.4976, 0.0296, -0.0758];

im = mat2gray(im,[0 255]);

size_1 = size(im);
h_1 = size_1(1);
w_1 = size_1(2);
im_11 = zeros(h_1, w_1+7);
im_12 = zeros(h_1, w_1+7);

for j = 1:w_1
    for i = 1:h_1
        c1 = im(i,j) *h1;
        d1 = im_11(i, j:j+7);
        d1 = d1+c1;
        im_11(i,j:j+7) = d1;
        
        c2 = im(i,j) *h2;
        d2 = im_12(i,j:j+7);
        d2 = d2+c2;
        im_12(i,j:j+7) = d2;
    end    
end
im_11 = imresize(im_11,[h_1,w_1+8]);
im_12 = imresize(im_12,[h_1,w_1+8]);
im_11 = im_crop(im_11, [0,4,h_1,w_1]);
im_12 = im_crop(im_12, [0,4,h_1,w_1]);

im_11 = downsample(im_11,2);
im_12 = downsample(im_12,2);

size_2 = size(im_11);
h_2 = size_2(1);
w_2 = size_2(2);
im_21 = zeros(h_2+7, w_2);
im_22 = zeros(h_2+7, w_2);
im_23 = zeros(h_2+7, w_2);
im_24 = zeros(h_2+7, w_2);

for i = 1:w_2
    for j = 1:h_2
        c1 = im_11(j,i) *h1;
        d1 = im_21(j:j+7,i);
        d1 = d1+c1';
        im_21(j:j+7,i) = d1;
        
        c2 = im_11(j,i) *h2;
        d2 = im_22(j:j+7,i);
        d2 = d2+c2';
        im_22(j:j+7,i) = d2;
    end    
end

for i = 1:w_2
    for j = 1:h_2
        c1 = im_12(j,i) *h1;
        d1 = im_23(j:j+7,i);
        d1 = d1+c1';
        im_23(j:j+7,i) = d1;
        
        c2 = im_12(j,i) *h2;
        d2 = im_24(j:j+7,i);
        d2 = d2+c2';
        im_24(j:j+7,i) = d2;
    end    
end

im_21 = imresize(im_21,[h_2+8,w_2]);
im_22 = imresize(im_22,[h_2+8,w_2]);
im_21 = im_crop(im_21, [4,0,h_2,w_2]);
im_22 = im_crop(im_22, [4,0,h_2,w_2]);
im_23 = imresize(im_23,[h_2+8,w_2]);
im_24 = imresize(im_24,[h_2+8,w_2]);
im_23 = im_crop(im_23, [4,0,h_2,w_2]);
im_24 = im_crop(im_24, [4,0,h_2,w_2]);

im_21 = permute(downsample(permute(im_21,[2,1,3]),2),[2,1,3]);
im_22 = permute(downsample(permute(im_22,[2,1,3]),2),[2,1,3]);
im_23 = permute(downsample(permute(im_23,[2,1,3]),2),[2,1,3]);
im_24 = permute(downsample(permute(im_24,[2,1,3]),2),[2,1,3]);

%im_21 = imresize(im_21,[h_1/2,w_1/2]);
%im_22 = imresize(im_22,[h_1/2,w_1/2]);
%im_23 = imresize(im_23,[h_1/2,w_1/2]);
%im_24 = imresize(im_24,[h_1/2,w_1/2]);

%[im_21,t] = histeq(im_21,256);
%[im_22,t] = histeq(im_22,256);
%[im_23,t] = histeq(im_23,256);
%[im_24,t] = histeq(im_24,256);

size_3 = size(im_22);
h_3 = size_3(1);
w_3 = size_3(2);
%size(im_22)

fwt1 = zeros(h_3*2, w_3*2);
fwt1(1:h_3,1:w_3) = im_21;
fwt1(h_3+1:h_3*2,1:w_3) = im_22;
fwt1(1:h_3,1+w_3:w_3*2) = im_23;
fwt1(h_3+1:h_3*2,1+w_3:w_3*2) = im_24;

img = uint8(255*im_21);




        
    