function img = my_erode(im,m,n)

[h,w] = size(im);
img = false(h,w);

for i=1+(m-1)/2:h-(m-1)/2
    for j =1+(n-1)/2:w-(n-1)/2
        count = 0;

        for k = 0:m-1
            for l = 0:n-1
                count = count+im(i-(m-1)/2+k,j-(n-1)/2+l);
            end
        end

        if(count == m*n)
            img(i,j) = 1;
        end
    
    end
end
