function img = Re_open(im, m, n, k)

img = im;
for i = 1:k
    img = my_erode(img, m, n);
end
img = R_expan(img, im, 3, 3);