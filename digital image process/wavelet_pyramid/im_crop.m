function im_ = im_crop(im, a)
y = a(1);
x = a(2);
h = a(3);
w = a(4);
im_ = zeros(h,w);
for i = 1:h
    for j = 1:w
        im_(i,j) = im(i+y,j+x);
    end
end

