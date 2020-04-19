close all;  
clear all;
clc;  
test=load('/Users/janechen/Desktop/课程/机器学习/HW3/hw3_lr/test_imgs.mat');
test_label=load('/Users/janechen/Desktop/课程/机器学习/HW3/hw3_lr/test_labels.mat');
img = full(test.test_img);
label = full(test_label.test_label);
n = 2167;
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

%% test
tp = 0;
tn = 0;
fp = 0;
fn = 0;
load /Users/janechen/Desktop/课程/机器学习/HW3/hw3_lr/w.mat w
for i = 1:n
    result = ft(i,:)*w;
    if result > 0
        if label(1,i)>0.5
            tp = tp + 1;
        else
            fp = fp + 1;
        end
    else
        if label(1,i)>0.5
            fn = fn + 1;
        else
            tn = tn + 1;
        end      
    end
end
