function img = my_close(im, m, n )

img_i = my_expan(im,m,n);
img = my_erode(img_i,m,n);