function [img_2] = bilinear(img_1, n)

size_1 = size(img_1);
h_1 = size_1(1);
w_1 = size_1(2);
h_2 = floor(h_1 * n);
w_2 = floor(w_1 * n);
img_2 = repmat(uint8(0),h_2, w_2);
e = 1e-4;
for i = 1:h_2
    for j = 1:w_2
        if (i/n<1&&j/n<1) x = img_1(1,1);
        elseif (i/n<1) x = (ceil(j/n+e)-j/n)*img_1(1,ceil(j/n))+(j/n-floor(j/n+e))*img_1(1,floor(j/n));
        elseif (j/n<1) x = (ceil(i/n+e)-i/n)*img_1(ceil(i/n),1)+(i/n-floor(i/n+e))*img_1(floor(i/n),1);
        else x = abs(ceil(i/n+e)-i/n)*abs(ceil(j/n+e)-j/n)*img_1(ceil(i/n),ceil(j/n)) + ...
            abs(ceil(i/n+e)-i/n)*abs(j/n-floor(j/n+e))*img_1(ceil(i/n),floor(j/n)) + ...
            abs(i/n-floor(i/n+e))*abs(ceil(j/n+e)-j/n)*img_1(floor(i/n),ceil(j/n)) + ...
            abs(i/n-floor(i/n+e))*abs(j/n-floor(j/n+e))*img_1(floor(i/n),floor(j/n));
        end
        img_2(i,j) = x;
    end
end
end

