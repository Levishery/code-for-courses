function img = my_expan(im,m,n)

[h,w] = size(im);
im = padarray(im,[(m-1)/2 (n-1)/2],'replicate','both');
img = zeros(h,w);

for i=1:h
    for j =1:w
        max = 0;
        for k = 0:m-1
            for l = 0:n-1
                if im(i+k, j+l) > max
                    max = im(i+k, j+l);
                end
            end
        end
        img(i,j) = max;
    end
end
img = uint8(img);
