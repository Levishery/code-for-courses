function img = geo_expan( im, G, m, n)

img = my_expan(im, m, n);

[h,w] = size(im);
for i = 1:h
    for j = 1:w
        img(i,j) = img(i,j)&&G(i,j);
    end
end