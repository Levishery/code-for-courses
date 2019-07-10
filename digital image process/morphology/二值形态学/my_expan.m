function img = my_expan(im,m,n)

[h,w] = size(im);
img = false(h+m-1,w+n-1);

for i=1:h
    for j =1:w
        
        if(im(i,j))
            for k = 0:m-1
                for l = 0:n-1
                img(i+k, j+l) = 1;
                end
            end
        end
        
    end
end

img = img(1+(m-1)/2:h+(m-1)/2, 1+(n-1)/2:w+(n-1)/2);
