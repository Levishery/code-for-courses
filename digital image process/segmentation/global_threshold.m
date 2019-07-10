function T = global_threshold(im)
    
T = mean(im(:));
index = (im<=T);

m1 = mean(im(index));
m2 = mean(im(~index));
dT = (m1+m2)/2 - T;
T = (m1+m2)/2;

while(dT > 0)
    index = (im<=T);
    m1 = mean(im(index));
    m2 = mean(im(~index));
    dT = (m1+m2)/2 - T;
    T = (m1+m2)/2;
end

end