function [img_2] = myHisteq(img_1, n)

size_1 = size(img_1);
h = size_1(1);
w = size_1(2);
img_2 = repmat(uint8(0),h_2, w_2);
for i = 1:h
    for j = 1:w
        his(int8(img_1(i,j))+1) = his(int8(img_1(i,j))+1)+1;
    end
end

for i = 2:256
    his(i) = his(i)+his(i-1);
end

for i = 1:h
    for j = 1:w
        x = round((n-1)*(his(int8(img_1(i,j))+1)/(h*w)));
        img_2(i,j) = x*255/(n-1);
    end
end

end
