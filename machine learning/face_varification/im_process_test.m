% process image: gray + central patch + resize + histeq

clc;
clear
data_path = '/Users/janechen/Desktop/课程/机器学习/大作业/LFW/mismatch pairs/';
result_path = '/Users/janechen/Desktop/coarse_test/';
NUM = 1600;
IM_SIZE = 250;
TIMES = 1;
PATCH_SIZE = 128;
RESIZE = 128;
begin_w = (IM_SIZE - PATCH_SIZE)/2;
begin_h = (IM_SIZE - PATCH_SIZE)/2;

%% mismatch
im_path = dir(data_path);
dirFlags = [im_path.isdir];
% Extract only those that are directories.
im_path = im_path(dirFlags);
for i = 1:NUM
    folder = im_path(i+2).name;
    im = dir([data_path , folder]);
    im1_path = [[data_path , folder], '/', im(3).name];
    im2_path = [[data_path , folder], '/', im(4).name];
    im1 = imread(im1_path);
    im1 = rgb2gray(im1);
    im1 = im1(begin_h:begin_h+PATCH_SIZE-1, begin_w:begin_w+PATCH_SIZE-1);
    im1 = histeq(im1);
    im1 = imresize(im1, [RESIZE, RESIZE]);
    im2 = imread(im2_path);
    im2 = rgb2gray(im2);
    im2 = im2(begin_h:begin_h+PATCH_SIZE-1, begin_w:begin_w+PATCH_SIZE-1);
    im2 = histeq(im2);
    im2 = imresize(im2, [RESIZE, RESIZE]);
    file_name = [result_path,'test' ,num2str(i),'_',num2str(1),'.jpg'];
    imwrite(im1, file_name, 'jpg');
    file_name = [result_path,'test',num2str(i),'_',num2str(2),'.jpg'];
    imwrite(im2, file_name, 'jpg');
end
