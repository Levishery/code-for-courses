function [py_si1, py_si2, py_si3, py_re1, py_re2, py_re3] = pyramid(img)

im = img;

w = fspecial('gaussian',[5,5],1);
im_gauss = imfilter(im,w,'replicate');
im2 = downsample(im_gauss,2);
im2 = permute(downsample(permute(im2,[2,1,3]),2),[2,1,3]);
py_si1 = im2; 
im_predict = myBilinear(im2, 2);
py_re1 = im - im_predict;
im = im2;

w = fspecial('gaussian',[5,5],1);
im_gauss = imfilter(im,w,'replicate');
im2 = downsample(im_gauss,2);
im2 = permute(downsample(permute(im2,[2,1,3]),2),[2,1,3]);
py_si2 = im2; 
im_predict = myBilinear(im2, 2);
py_re2 = im - im_predict;
im = im2;

w = fspecial('gaussian',[5,5],1);
im_gauss = imfilter(im,w,'replicate');
im2 = downsample(im_gauss,2);
im2 = permute(downsample(permute(im2,[2,1,3]),2),[2,1,3]);
py_si3 = im2; 
im_predict = myBilinear(im2, 2);
py_re3 = im - im_predict;
im = im2;

    
    
    