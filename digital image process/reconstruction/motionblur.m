function [H, im_blured] = motionblur(img, sigma)

[M,N] = size(img);

a = 0.1;
b = 0.1;
T = 1;
im_double = mat2gray(img,[0 255]);
im_F = fftshift(fft2(im_double));      % ¿ÕÓò > ÆµÓò
[u,v]=meshgrid(1:M,1:N);
H =sinc (((u-M/2)*a+(v-N/2)*b)).* exp(-1i* pi* ((u-M/2)*a+(v-N/2)*b) )* T;
%H2 =sinc (pi*((u)*a+(v)*b)).* exp(-1i* pi* ((u)*a+(v)*b) )* T;

im_blured_F = im_F.* H; 
%{
K = 0.01
for i=1:M
    for j=1:N
       im_blured_F(i,j) = ((((abs(H(i,j)))^2)/((abs(H(i,j)))^2+K))/H(i,j))*im_F(i,j);
    end
end    % ¸´Ô­ÍË»¯
%}
im_blured_double = real(ifft2(ifftshift(im_blured_F)));    % ÆµÓò > ¿ÕÓò
im_blured = im2uint8(mat2gray(im_blured_double));

im_blured = imnoise(im_blured,'gaussian',0,sigma);

%conj_H = conj(H);
%H = (H + conj_H(M:-1:1,N:-1:1))/2;
%H = sqrt(2)*H;

