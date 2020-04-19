% compute PCA matrix from images in path, save G as G.mat
% save the Projection Matrix which can preserve 100%/98%/95%/90%
% information of the original feature.

clear;
clc;
path = '/Users/janechen/Desktop/feature_1/';
feature_num = 256;
sample_num = 3200;
sample_matrix = [];
data = dir(path);
for i=1:sample_num
    name_1 = data(2*i+2).name;
    path_1 = [path name_1];
    name_2 = data(2*i+3).name;
    path_2 = [path name_2];
    data_1 = load(path_1);
    data_1 = data_1.x;
    data_2 = load(path_2);
    data_2 = data_2.x;
    sample_matrix = [sample_matrix data_1' data_2'];
end

img_mean= mean(sample_matrix,2);  

for i = 1:sample_num
    sample_matrix(:,i) = sample_matrix(:,i) - img_mean;   % centralize
end


covMat = sample_matrix*sample_matrix';  % compute convoriance matrix
disp('begin computing eig');
[U,sigma] = eig(covMat);    % compute eig value and vector(left singular vector)
disp('end computing eig');

total_var = 0;
for i=1:feature_num 
    total_var = total_var+sigma(i,i);
end
%% 100%
tmp_var = 0;
k=100;
for i=0:feature_num-1
    tmp_var = tmp_var+sigma(feature_num-i,feature_num-i);
    if tmp_var/total_var > k/100
        break;
    end
end
reduced_feature_100 = i;
disp('reduced_feature_100 number is ');
disp(reduced_feature_100+1);
%% 98%
tmp_var = 0;
k=98;
for i=0:feature_num-1
    tmp_var = tmp_var+sigma(feature_num-i,feature_num-i);
    if tmp_var/total_var > k/100
        break;
    end
end
reduced_feature_98 = i;
disp('reduced_feature_98 number is ');
disp(reduced_feature_98+1);

%% 95%
tmp_var = 0;
k=95;
for i=0:feature_num-1
    tmp_var = tmp_var+sigma(feature_num-i,feature_num-i);
    if tmp_var/total_var > k/100
        break;
    end
end
reduced_feature_95 = i;
disp('reduced_feature_95 number is ');
disp(reduced_feature_95+1);

%% 90%
tmp_var = 0;
k=90;
for i=0:feature_num-1
    tmp_var = tmp_var+sigma(feature_num-i,feature_num-i);
    if tmp_var/total_var > k/100
        break;
    end
end
reduced_feature_90 = i;
disp('reduced_feature_90 number is ');
disp(reduced_feature_90+1);

%%
tmp_var = 0;
k=70;
for i=0:feature_num-1
    tmp_var = tmp_var+sigma(feature_num-i,feature_num-i);
    if tmp_var/total_var > k/100
        break;
    end
end
reduced_feature_70 = i;
disp('reduced_feature_70 number is ');
disp(reduced_feature_70+1);


%%
G=[];
for i=0:0
    uk = U(:, feature_num-i);
    G = [G uk];
end

save('G_1.mat','G');

%%
G=[];
for i=0:reduced_feature_98
    uk = U(:, feature_num-i);
    G = [G uk];
end

save('G_98.mat','G');

%%
G=[];
for i=0:reduced_feature_95
    uk = U(:, feature_num-i);
    G = [G uk];
end

save('G_95.mat','G');

%%
G=[];
for i=0:reduced_feature_90
    uk = U(:, feature_num-i);
    G = [G uk];
end

save('G_90.mat','G');
   
%%
G=[];
for i=0:reduced_feature_70
    uk = U(:, feature_num-i);
    G = [G uk];
end

save('G_70.mat','G');