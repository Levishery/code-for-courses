function result = dilation(A,B)

size_A = size(A);
size_B = size(B);
result = zeros(size_A,'logical');

i_low = ceil(size_B(1)/2);
i_high = floor(size_B(1)/2);
j_low = ceil(size_B(2)/2);
j_high = floor(size_B(2)/2);

B = ~B;

for i = i_low : size_A(1)-i_high
    for j = j_low : size_A(2)-j_high
        temp = A(i-i_low+1:i+i_high,j-j_low+1:j+j_high) | B;
        result(i,j) = all(temp(:));
    end
end

end

