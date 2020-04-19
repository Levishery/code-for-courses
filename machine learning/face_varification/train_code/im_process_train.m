% process image: gray + central patch + resize + histeq
clc;
clear
data_path_mis = '/Users/janechen/Desktop/课程/机器学习/大作业/LFW/mismatch pairs/';
data_path_ma = '/Users/janechen/Desktop/课程/机器学习/大作业/LFW/match pairs/';
result_path = '/Users/janechen/Desktop/coarse_test/';
NUM = 1600;
IM_SIZE = 250;
TIMES = 1;
PATCH_SIZE = 128;
RESIZE = 128;
begin_w = (IM_SIZE - PATCH_SIZE)/2;
begin_h = (IM_SIZE - PATCH_SIZE)/2;

%% mismatch
im_path_mis = dir(data_path_mis);
dirFlags = [im_path_mis.isdir];
mis = [];
% Extract only those that are directories.
im_path_mis = im_path_mis(dirFlags);
for i = 1:NUM
    folder = im_path_mis(i+2).name;
    im = dir([data_path_mis , folder]);
    im1_path = [[data_path_mis , folder], '/', im(3).name];
    im2_path = [[data_path_mis , folder], '/', im(4).name];
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
    mis = [mis sum(sum(abs(im1-im2)))];
    file_name = [result_path,'mismatch' ,num2str(i),'_',num2str(1),'.jpg'];
    %imwrite(im1, file_name, 'jpg');
    file_name = [result_path,'mismatch',num2str(i),'_',num2str(2),'.jpg'];
    %imwrite(im2, file_name, 'jpg');
end

%% match
im_path_ma = dir(data_path_ma);
dirFlags = [im_path_ma.isdir];
% Extract only those that are directories.
im_path_ma = im_path_ma(dirFlags);
ma = [];
for i = 1:NUM
    folder = im_path_ma(i+2).name;
    im = dir([data_path_ma , folder]);
    im1_path = [[data_path_ma , folder], '/', im(3).name];
    im2_path = [[data_path_ma , folder], '/', im(4).name];
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
    ma = [ma sum(sum(abs(im1-im2)))];
    file_name = [result_path,'match' ,num2str(i),'_',num2str(1),'.jpg'];
    %imwrite(im1, file_name, 'jpg');
    file_name = [result_path,'match',num2str(i),'_',num2str(2),'.jpg'];
    %imwrite(im2, file_name, 'jpg');
end