function z = SpatialFcn(M,data,A,p,PDes)

alpha = data(:,1);

phiCol = flip(data(:,2:M+1).',1);

z = sum(abs((alpha.*squeeze(1/(M) * abs(pagemtimes(A,exp(1i*phiCol))).^2) - ...
    permute(PDes,[1+(size(phiCol,2)==1) 2-(size(phiCol,2)==1)]))).^p,1+(size(phiCol,2)>1)).^(1/p);

end