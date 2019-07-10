function [img_2] = nearest(img_1, n)

size_1 = size(img_1);
h_1 = size_1(1);
w_1 = size_1(2);
h_2 = floor(h_1 * n);
w_2 = floor(w_1 * n);
img_2 = repmat(uint8(0),h_2, w_2);
for i = 1:h_2
    for j = 1:w_2
        i_ = max(min(round(i/n),h_1),1);
        j_ = max(min(round(j/n),w_1),1);
        img_2(i,j) = img_1(i_,j_);
    end
end


end


