function [img_2] = mySharpen(img_1)

size_1 = size(img_1);
h = size_1(1);
w = size_1(2);
img_2 = repmat(uint8(0),h-2, w-2);

for i = 1:h-2
    for j = 1:w-2
        x = img_1(i:i+2, j:j+2);
        a = sum(x(:));
        a_1 = int16(img_1(i+1,j+1));
        a_1 = 10*a_1;
        a_2 = -a+a_1;
        img_2(i,j) = a_2;
    end
end

end


