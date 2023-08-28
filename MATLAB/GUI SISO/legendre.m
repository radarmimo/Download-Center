function x = legendre(N)
% x = legendre(N), generate a Legendre sequence of length N

x=zeros(N,1);
x1=zeros(N,1);
x(1)=1;

for i=2:N
    r=i-1;
    t=mod(r^2,N);
    x(t)=1;
end
x=2*x-1;

r=1/4;
rn=floor(r*N);
x1(1:(N-rn+1))=x(rn:N);
x1((N-rn+2):N)=x(1:(rn-1));
x=x1;