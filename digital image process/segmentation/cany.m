function img = cany(im,sigma,T_L,T_H)

size_im = size(im);

% 平滑
gauss_filter = fspecial('gaussian', [13,13], sigma);
im = double(imfilter(im, gauss_filter, 'replicate'));

% 梯度
g_x = [im(2:end,:)-im(1:(end-1),:);zeros(1,size_im(2))];
g_y = [im(:,2:end)-im(:,1:(end-1)),zeros(size_im(1),1)];

M = sqrt(g_x.*g_x+g_y.*g_y);

alpha = zeros(size_im);
for i=1:size_im(1)
    for j=1:size_im(2)
        if g_x(i,j)==0
            if g_y(i,j)>=0
                alpha(i,j) = pi/2;
            else
                alpha(i,j) = -pi/2;
            end
        else
            alpha(i,j) = atan(g_y(i,j)/g_x(i,j));
        end
    end
end

alpha = round(alpha/pi*4)+3;
dire = {[0,-1],[1,-1],[1,0],[1,1],[0,1]};
g_N = zeros(size_im);

%非极大值抑制
for i=1:size_im(1)
    for j=1:size_im(2)
        if((i+dire{alpha(i,j)}(1) <= 0) || (j+dire{alpha(i,j)}(2)<=0) || (i+dire{alpha(i,j)}(1) > size_im(1)) || (j+dire{alpha(i,j)}(2) > size_im(2)))
            if((i-dire{alpha(i,j)}(1) > 0) && (j-dire{alpha(i,j)}(2)>0) && (i+dire{alpha(i,j)}(1) <= size_im(1)) || (j+dire{alpha(i,j)}(2) <= size_im(2)))
                temp = im(i-dire{alpha(i,j)}(1),j-dire{alpha(i,j)}(2));
            else
                temp = 0;
            end
        else
            if((i-dire{alpha(i,j)}(1) <= 0) || (j-dire{alpha(i,j)}(2)<=0) || (i-dire{alpha(i,j)}(1) > size_im(1)) || (j-dire{alpha(i,j)}(2) > size_im(2)))
                temp = im(i+dire{alpha(i,j)}(1),j+dire{alpha(i,j)}(2));
            else
                temp = max(M(i+dire{alpha(i,j)}(1),j+dire{alpha(i,j)}(2)),M(i-dire{alpha(i,j)}(1),j-dire{alpha(i,j)}(2)));
            end
        end
        if(temp<M(i,j))
            g_N(i,j) = M(i,j);
        end
    end
end

%双阈值处理
g_NL = zeros(size_im, 'logical');
g_NH = zeros(size_im, 'logical');

g_NH(g_N>=T_H) = 1;
g_NL(g_N>=T_L) = 1;

B = ones([2,2],'logical');

g_NL = (dilation(g_NL,B) & g_NH);
img = (dilation(g_NL,B) & g_NH);

temp = xor(g_NL,img);
index = find(temp,1);
if(isempty(index))
    return
end

while(1)
    g_NL = (dilation(img,B) & g_NH);
    img = (dilation(g_NL,B) & g_NH);
    if(g_NL(index) == img(index))
        temp = xor(g_NL,img);
        index = find(temp,1);
        if(isempty(index))
            break
        end
    end
end

end

