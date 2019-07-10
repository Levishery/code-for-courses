function dictionary = make_dictionary(p)

p = p/sum(p);
tree = cell(length(p),1);

for i  =1:length(p)
    tree{i} = uint8(i-1);
end

while(numel(tree)>2)
    %第一小
    [min_p,index1] = min(p);
    p(index1) = [];
    min_s = tree{index1};
    tree(index1) = [];
    %第二小
    [~,index2] = min(p);
    p(index2) = min_p + p(index2);
    %合并
    tree{index2} = {min_s;tree{index2}};
end
 %celldisp(tree);

global DIC
make_code(tree,[]);
dictionary = DIC;

function make_code(tree, codeword)
    
if(iscell(tree))
    make_code(tree{1},[codeword 0]); % 左子树为0
    make_code(tree{2},[codeword 1]); % 右子树为1
else
    % 到达叶子
    DIC{uint16(tree)+1} = codeword;
end
end

end

