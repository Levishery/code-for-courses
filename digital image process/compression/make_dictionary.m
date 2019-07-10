function dictionary = make_dictionary(p)

p = p/sum(p);
tree = cell(length(p),1);

for i  =1:length(p)
    tree{i} = uint8(i-1);
end

while(numel(tree)>2)
    %��һС
    [min_p,index1] = min(p);
    p(index1) = [];
    min_s = tree{index1};
    tree(index1) = [];
    %�ڶ�С
    [~,index2] = min(p);
    p(index2) = min_p + p(index2);
    %�ϲ�
    tree{index2} = {min_s;tree{index2}};
end
 %celldisp(tree);

global DIC
make_code(tree,[]);
dictionary = DIC;

function make_code(tree, codeword)
    
if(iscell(tree))
    make_code(tree{1},[codeword 0]); % ������Ϊ0
    make_code(tree{2},[codeword 1]); % ������Ϊ1
else
    % ����Ҷ��
    DIC{uint16(tree)+1} = codeword;
end
end

end

