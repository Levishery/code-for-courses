% compute PCA feature of the images in 'path' and save to feature.mat
% every column is a sample

clc;
clear
path = '/Users/janechen/Desktop/feature_test/';
G_path = 'G/';
result_path = '/Users/janechen/Desktop/2/sumabs/';
data = dir(path);
feature_num = 256;
Gfile = matfile([G_path 'G_95_65.mat']);
G = Gfile.G;
sample_num = 600;
data_result = [];
for i=1:sample_num
    name_1 = data(2*i+1).name;
    path_1 = [path name_1];
    name_2 = data(2*i+2).name;
    n_1 = split(name_1,'_');
    n_2 = split(name_2,'_');
    if(char(n_1(1)) ~= char(n_2(1)))
        disp('data not match');
        return
    end
    path_2 = [path name_2];
    data_1 = load(path_1);
    data_1 = data_1.x;
    data_2 = load(path_2);
    data_2 = data_2.x;
    reduced_data1 = G'* data_1';
    reduced_data2 = G'* data_2';
    data_result = [data_result, abs(reduced_data1 - reduced_data2)];
end
test = data_result;
save([result_path 'test.mat'], 'test');
