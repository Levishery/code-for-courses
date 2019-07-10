function img = show_line(im, line)

img = im;
size_im = size(im);
for i=1:size_im(1)
    for j=1:size_im(2)
        if(line(i,j) == 0)
            img(i,j) = 0;
        end
    end
end

end
         