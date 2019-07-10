function id = find_array(dictionary, len, array)
index = false(1, numel(dictionary));
for k = 1:numel(dictionary)
    size_ = size(dictionary{k});
    if(size_(2) ==  len)
        index(k) = (all(dictionary{k} == array));
    end
end
id = find(index);
