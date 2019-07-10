function [A,img] = my_hogh(im)
size_im = size(im);
dtheta = 1;
dr = 1;
D = sqrt((size_im(1)*size_im(1)+size_im(2)*size_im(2)));
index_max_D = ceil(D/dr);
A = zeros(2*index_max_D,ceil(180/dtheta));

theta = ((1:dtheta:180)-91);
cos_theta = cos(theta/180*pi);
sin_theta = sin(theta/180*pi);

for i=1:size_im(1)
    for j=1:size_im(2)
        if(im(i,j)==1)
            rho = round((i*cos_theta+j*sin_theta)/dr);
            for k = 1:length(rho)
                A(rho(k)+index_max_D+1,theta(k)+91) = A(rho(k)+index_max_D+1,theta(k)+91)+1;
            end
        end
    end
end

img = ones(size_im);
[x,y]=find(A>=120);

for i=1:length(x)
    for j=1:size_im(1)
        for k=1:size_im(2)
            if abs(j*cos_theta(y(i)) + k*sin_theta(y(i))-x(i)+index_max_D+1)<=2
                img(j,k) = 0;
            end
        end
    end
    
end

end

