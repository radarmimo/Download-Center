function c = FastTimeFcn(data,G,gamma)

phiRow      = data;
N           = size(phiRow,2);
c           = max(abs(pagemtimes(exp(1i*phiRow), G(:,1:N).')),[],2) - gamma;

end