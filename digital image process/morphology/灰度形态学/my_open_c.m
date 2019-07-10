function img = my_open_c(im, r)

img_i = my_erode_c(im, r);
img = my_expan_c(img_i, r);