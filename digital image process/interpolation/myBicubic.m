function [img_2] = bicubic(img_1, n)

size_1 = size(img_1);
h_1 = size_1(1);
w_1 = size_1(2);
h_2 = floor(h_1 * n);
w_2 = floor(w_1 * n);
img_2 = repmat(double(0),h_2, w_2);
img_aux = padarray(img_1,[2 2],'replicate','both');
img_aux = double(img_aux);
for i = 1:h_2
  u=rem(i,n)/n;
  i1=floor(i/n)+2;
  A=[sw(1+u) sw(u) sw(1-u) sw(2-u)];
  for j = 1:w_2
    v=rem(j,n)/n;
    j1=floor(j/n)+2; 
    C=[sw(1+v);sw(v);sw(1-v);sw(2-v)]; 
    B=[  img_aux(i1-1,j1-1)     img_aux(i1-1,j1)    img_aux(i1-1,j1+1)   img_aux(i1-1,j1+2)    
         img_aux(i1  ,j1-1)     img_aux(i1,  j1)   img_aux(i1,   j1+1)  img_aux(i1,   j1+2)
         img_aux(i1+1,j1-1)     img_aux(i1+1,j1)    img_aux(i1+1,j1+1)   img_aux(i1+1,j1+2)
         img_aux(i1+2,j1-1)     img_aux(i1+2,j1)    img_aux(i1+2,j1+1)   img_aux(i1+2,j1+2)];
     x = (A*B*C);
    img_2(i,j)=x;
  end
end
img_2 = uint8(img_2);

function A=sw(w1)
w=abs(w1);
a=-0.5;
if w<1&&w>=0
  A=1-(a+3)*w^2+(a+2)*w^3;
else if w>=1&&w<2
  A=a*w^3-5*a*w^2+(8*a)*w-4*a;
else
  A=0;
    end
end
end

end
