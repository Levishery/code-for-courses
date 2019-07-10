function code = encoder(im,dictionary)
code = [];


for i = 1:length(im(:))
    code = [code, dictionary{uint16(im(i))+1}];
end

%{
k = 7;
for i = 1:length(im(:))
    for j = 1:length(code{im(i)+1})
        temp = temp + uint8(code{im(i)+1}(j) * 2^(k));
        k = k - 1;
        if k < 0
            compression = [compression, temp];
            temp = 0;
            k = 7;
        end
    end
end

%}


end

