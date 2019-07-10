function img = my_close_c(im, r)

img_i = my_expan_c(im, r);
img = my_erode_c(img_i, r);