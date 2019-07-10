function [img_2] = myAverage(img_1,n)

size_1 = size(img_1);
h = size_1(1);
w = size_1(2);
img_2 = img_1;
for k = 1:n
    img_2 = padarray(img_1,[2 2],'replicate','both');
    for i = 1:h-2
        for j = 1:w-2
            x = img_1(i:i+2, j:j+2);
            img_2(i,j) = sum(x(:))/9;
        end
    end
end

end

