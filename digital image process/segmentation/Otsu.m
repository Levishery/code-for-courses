function result = Otsu(im)
size_im = size(im);
p = imhist( im );
p = p / (size_im(1)*size_im(2));

P1 = zeros(255,1);
P1(1) = p(1);
for k=2:255
    P1(k) = p(k) + P1(k-1);
end
P2 = 1-P1;
m = zeros(255,1);
m(1) = 0;
for k=2:255
    m(k) = m(k-1) + (k-1)*p(k);
end
m_g = m(255);

sigma = ((m_g*P1-m).^2)./(P1.*P2);
M = max(sigma);
index = find(sigma==M);

T = ceil(mean(index));

result = zeros(size(im),'logical');
result(im>T) = 1;
end

