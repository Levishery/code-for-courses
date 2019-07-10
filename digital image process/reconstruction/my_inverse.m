function [im_inverse, im_inverse_b] = my_inverse(img, H, D0)

im_double = mat2gray(img,[0 255]);
im_F = fftshift(fft2(im_double)); 
[M,N] = size(im_F);% ¿ÕÓò > ÆµÓò
im_inverse_F = im_F ./ H;    % ¸´Ô­ÍË»¯
im_inverse_double = real(ifft2(ifftshift(im_inverse_F)));    % ÆµÓò > ¿ÕÓò
im_inverse = im2uint8(mat2gray(im_inverse_double));
im_inverse_Fb = im_F;
for i=1:M
    for j=1:N
        
        if abs(H(i,j)) < 1e-2
            im_inverse_Fb(i,j) = 0;
            continue
        end
        
        if sqrt((i-M/2).^2+(j-N/2).^2)<D0
            im_inverse_Fb(i,j)=im_F(i,j)./H(i,j);
            
        else im_inverse_Fb(i,j) = 0;
            
        end
    end
end
im_inverse_doubleb = real(ifft2(ifftshift(im_inverse_Fb)));    % ÆµÓò > ¿ÕÓò
im_inverse_b = im2uint8(mat2gray(im_inverse_doubleb));
%im_inverse_b = histeq(im2uint8(mat2gray(real(im_inverse_Fb))),256);


%for i=1:M
%    for j=1:N
%       H(i,j)=sin(pi* ((i-M/2)*a+(j-N/2)*b))* exp(-1i* pi* ((i-M/2)*a+(j-N/2)*b) )* T/ (pi* ((i-M/2)*a+(j-N/2)*b));
%   end
%end
