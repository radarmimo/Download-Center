function y = Mutate(x,mu,VarMin,VarMax)

nVar = numel(x);

nmu = ceil(mu* nVar);

j = randsample(nVar,nmu);

sigma = 0.1 * (VarMax - VarMin);

y = x;
y(j) = x(j) + sigma * randn(size(j.'));

y = min(max(y, VarMin), VarMax);

end