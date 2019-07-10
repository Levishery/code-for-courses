function im_wiener = my_wiener(img, H, K)

im_double = mat2gray(img,[0 255]);
im_F = fftshift(fft2(im_double)); 
[M,N] = size(im_F);% ¿ÕÓò > ÆµÓò
im_wiener_F = im_F;
for i=1:M
    for j=1:N
       im_wiener_F(i,j) = ((((abs(H(i,j)))^2)/((abs(H(i,j)))^2+K))/H(i,j))*im_F(i,j);
    end
end    % ¸´Ô­ÍË»¯

im_wiener_doubleb = real(ifft2(ifftshift(im_wiener_F)));    % ÆµÓò > ¿ÕÓò
im_wiener = im2uint8(mat2gray(im_wiener_doubleb));