function img = my_erode(im,m,n)

[h,w] = size(im);
im = padarray(im,[(m-1)/2 (n-1)/2],'replicate','both');
img = repmat(double(0),h, w);

for i=1:h
    for j =1:w
        min = 255;
        for k = 0:m-1
            for l = 0:n-1
                if im(i+k, j+l) < min
                    min = im(i+k, j+l);
                end
            end
        end
        img(i,j) = min;
    end
end
img = uint8(img);
