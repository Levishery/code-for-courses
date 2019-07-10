function img = my_open(im, m, n )

img_e = my_erode(im,m,n);
img = my_expan(img_e,m,n);