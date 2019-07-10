function psnr_ = psnr(im, im_rec)

im = mat2gray(im,[0 255]);
im_rec = mat2gray(im_rec,[0 255]);
im_x = im - im_rec;

MSE = 0;
size_ = size(im);
h = size_(1);
w = size_(2);

for i = 1:h
    for j = 1:w
        MSE = MSE + (im_x(i,j))^2;
    end
end

MSE = MSE/(h*w);
psnr_ = 10* log(1/MSE);