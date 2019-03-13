winsize = 30;
limit = 210;
stride = 10;
skip = ;
I = imread('/Users/janechen/Desktop/课程/人工智能/大作业/conesF/view5.tif');
J = imread('/Users/janechen/Desktop/课程/人工智能/大作业/conesF/view1.tif');
[height, width, chanel] = size(I); 
disp = ones(height,width);
hstride = floor((height-winsize)/stride);
wstride = floor((width-winsize-limit*skip)/stride);
for i = 0:hstride
    for j = 0:wstride
        result = [];
        for k= 0:limit
            I0 = I(i*stride+1:(i*stride+winsize),j*stride+1:(j*stride+winsize),:);
            J0 = J(i*stride+1:(i*stride+winsize),(j*stride+k*skip+1):(j*stride+winsize+k*skip),:);
            a=imabsdiff(I0,J0);
            a=sum(a(:));
            result = [result,a];
        end
        result0 = min(result);
        index = find(result==result0);
        index = min(index);
        disp(i*stride+1:(i*stride+stride),j*stride+1:(j*stride+stride)) = index*ones(stride,stride);
    end
end
imshow(disp,[])