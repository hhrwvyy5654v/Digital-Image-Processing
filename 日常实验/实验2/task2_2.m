num=input('请输入数字n：');
n=num;
W=ones(n,n);

for i =1:n
    for j=1:n
        if(i==fix(n/2)+1&&j==fix(n/2)+1)
            W(i,j)=n*n-1;
        end
    end
end

display(W)