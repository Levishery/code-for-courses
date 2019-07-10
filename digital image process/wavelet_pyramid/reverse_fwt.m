function im_rec = reverse_fwt(im)

h2 = [-0.0758, 0.0296, 0.4976, -0.8037, 0.2979, 0.0992, -0.0126, -0.0322];
h1 = [0.0322, -0.0126, -0.0992, 0.2979, 0.8037, 0.4976, -0.0296, -0.0758];

im = mat2gray(im,[0 255]);

size_3 = size(im);
h_3 = size_3(1)/2;
w_3 = size_3(2)/2;

im_21 = im(1:h_3,1:w_3);
im_22 = im(h_3+1:h_3*2,1:w_3);
im_23 = im(1:h_3,1+w_3:w_3*2);
im_24 = im(h_3+1:h_3*2,1+w_3:w_3*2);

im_21 = upsample(im_21,2);
im_22 = upsample(im_22,2);
im_23 = upsample(im_23,2);
im_24 = upsample(im_24,2);
%%im_23 = permute(upsample(permute(im_23,[2,1,3]),2),[2,1,3]);
%%im_24 = permute(upsample(permute(im_24,[2,1,3]),2),[2,1,3]);

size_2 = size(im_21);
h_2 = size_2(1);
w_2 = size_2(2);

im_11 = zeros(h_2+7, w_2);
im_12 = zeros(h_2+7, w_2);

for i = 1:w_2
    for j = 1:h_2
        c1 = im_21(j,i) *h1;
        c2 = im_22(j,i) *h2;
        d1 = im_11(j:j+7,i);
        d1 = d1+c1'+c2';
        im_11(j:j+7,i) = d1;
    end    
end

for i = 1:w_2
    for j = 1:h_2
        c1 = im_23(j,i) *h1;
        c2 = im_24(j,i) *h2;
        d1 = im_12(j:j+7,i);
        d1 = d1+c1'+c2';
        im_12(j:j+7,i) = d1;
    end    
end

%im_11 = upsample(im_11,2,0);
%im_12 = upsample(im_12,2,1);

im_11 = imresize(im_11,[h_2+8,w_2]);
im_12 = imresize(im_12,[h_2+8,w_2]);
im_11 = im_crop(im_11, [4,0,h_2,w_2]);
im_12 = im_crop(im_12, [4,0,h_2,w_2]);


im_11 = permute(upsample(permute(im_11,[2,1,3]),2),[2,1,3]);
im_12 = permute(upsample(permute(im_12,[2,1,3]),2),[2,1,3]);

size_1 = size(im_11);
h_1 = size_1(1);
w_1 = size_1(2);

im_rec = zeros(h_1, w_1+7);

for j = 1:w_1
    for i = 1:h_1
        c1 = im_11(i,j) *h1;
        c2 = im_12(i,j) *h2;
        d1 = im_rec(i, j:j+7);
        d1 = d1+c1+c2;
        im_rec(i,j:j+7) = d1;
    end    
end

im_rec = imresize(im_rec,[h_1,w_1+8]);
im_rec = im_crop(im_rec, [0,4,h_1,w_1]);

im_rec = uint8(255*255*im_rec);
%im_rec = histeq(im_rec);

