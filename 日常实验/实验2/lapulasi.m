function [w]=lapulasi(num)
n=num;
w=ones(n);
x=fix(n/2)+1;
w(x,x)=-(n*n-1);
end

