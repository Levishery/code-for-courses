function img = my_erode_c(im, r)

[h,w] = size(im);
im = padarray(im,[r r],'replicate','both');
img = repmat(double(0),h, w);

for i=1:h
    for j =1:w
        min = 255;
        for k = 0:2*r
            for l = 0:2*r
                if((k-r)^2+(l-r)^2 < r^2)
                    if im(i+k, j+l) < min
                        min = im(i+k, j+l);
                    end
                end
            end
        end
        img(i,j) = min;
    end
end
img = uint8(img);