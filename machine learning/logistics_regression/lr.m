close all;  
clear all;
clc;  
train=load('/Users/janechen/Desktop/课程/机器学习/HW3/hw3_lr/train_imgs.mat');
train_label=load('/Users/janechen/Desktop/课程/机器学习/HW3/hw3_lr/train_labels.mat');
img = full(train.train_img);
label = full(train_label.train_label);
n = 12700;
d = 784;

%% norm img, label
for i = 1:size(img,1)
    max_ = max(img(i,:));
    for j = 1:size(img,2)
        if img(i,j) >= 0.5*max_
            img(i,j) = 1;
        else
            img(i,j) = 0;
        end 
    end
end
x1 = ones(n,1);
ft= [x1 img];

max_ = 0.5*max(label);
for i = 1:size(label,2)
    if label(1,i) > max_
        label(1,i) = 1;
    else
        label(1,i) = 0;
    end
end

%%梯度下降求参数
w = zeros(d+1, 1);
a = 0.0005;
loss = 100;
loss_total = [];
exp_ = 0; % 辅助计算
step = 0;
while loss>0.1
    g_w = zeros(d+1, 1);
    loss = 0;
    for i = 1:n
        exp_ = exp(ft(i,:)*w);
        g_w = g_w+(label(1,i)-exp_/(1+exp_))*ft(i,:)';
        loss = loss + (label(1,i)*log(exp_/(1+exp_))+(1-label(1,i))*log(1/(1+exp_)));
    end
    g_w = -g_w/n;
    loss = -loss/n;
    w = w - a*g_w;
    step = step + 1;
    loss_total = [loss_total loss];
end