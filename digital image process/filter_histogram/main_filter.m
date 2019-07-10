%% ����������������˲��㷨���� myAverage.m��myMedian.m��Ȼ�󽫱��������еı���
%% filename����Ϊ'circuit'������main_filter.m�����ɵõ��˲�����
%%
clc; 
clear;
close all;

%% ��ȡͼ��
filename = 'circuit'; % �ܵ�����������Ⱦ�ĵ�·��X����ͼ��
im = imread([filename, '.jpg']);

%% ��ͼ����о�ֵ�˲�
im_a = myAverage(im,1);
im_a100 = myAverage(im,100);

%% ��ͼ�������ֵ�˲�
im_m = myMedian(im,1);
im_m100 = myMedian(im,100);

%% ��������浽��ǰĿ¼�µ�result�ļ�����
%imwrite(im_a, sprintf('result/_%s_a.jpg', filename));
%imwrite(im_m, sprintf('result/_%s_m.jpg', filename));

%% ��ʾ���
figure(1); 
subplot(231); imshow(im); title('ԭͼ'); axis on
subplot(232); imshow(im_a); title('��ֵ�˲�'); axis on
subplot(233); imshow(im_a100); title('��ֵ�˲�100'); axis on
subplot(234); imshow(im); title('ԭͼ'); axis on
subplot(235); imshow(im_m); title('��ֵ�˲�'); axis on
subplot(236); imshow(im_m100); title('��ֵ�˲�100'); axis on

