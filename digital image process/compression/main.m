clc; 
clear;
close all;

p_im = zeros([1,256]);

input_path = '/Users/janechen/Desktop/�γ�/����ͼ����/ͼ��ѹ��/train/'; 
img_Dir  = dir([input_path '*.bmp']);

for i=1:length(img_Dir)
    im = rgb2gray(imread([input_path img_Dir(i).name]));
    for j=1:length(im(:))
        p_im(double(im(j))+1) = p_im(double(im(j))+1) + 1;
    end
end

figure(1)
p_im = p_im/(sum(p_im));
plot(0:255,p_im)
title('ÿ�����صĸ���ͳ��')

dictionary = make_dictionary(p_im);
celldisp(dictionary);


imgPath = '/Users/janechen/Desktop/�γ�/����ͼ����/ͼ��ѹ��/test/'; 
imgDir  = dir([imgPath '*.bmp']);

for i=5:length(imgDir)
    figure(i+1)
    im = rgb2gray(imread([imgPath imgDir(i).name]));
    size_im = size(im);
    code = encoder(im,dictionary); %%����
    
    img = decoder(code, dictionary, size_im);
    
    subplot(211)
    imshow(im);
    title('ԭͼ')
    subplot(212)
    imshow(img);
    title('���������ͼ')
    
end
