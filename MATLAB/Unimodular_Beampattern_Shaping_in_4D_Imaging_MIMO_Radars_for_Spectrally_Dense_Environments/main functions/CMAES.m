function [BestSol, BestCost, iter] = CMAES(objfcn, nVar, lb, ub, varargin)

displayFlag                 = false;
threFlag                    = false;

for i = 1:length(varargin)
    if strcmpi(varargin{i}, 'seed') && i < length(varargin)
        rng(cell2mat(varargin(i+1)));       
    end
end

for i = 1:length(varargin)
    if strcmpi(varargin{i}, 'display') && i < length(varargin)
        if strcmpi(varargin{i+1}, 'iter')
            displayFlag = true;
            break
        end
    end
end

for i = 1:length(varargin)
    if strcmpi(varargin{i}, 'Threshold') && i < length(varargin)
        threFlag = true;
        thre = cell2mat(varargin(i+1));
    end
end

VarSize                     = [1 nVar];

% - CMA-ES Settings
maxIter                     = 1e3;
for i = 1:length(varargin)
    if strcmpi(varargin{i}, 'MaxIteration') && i < length(varargin)
        maxIter = cell2mat(varargin(i+1));
    end
end

StallItMax                  = maxIter;
for i = 1:length(varargin)
    if strcmpi(varargin{i}, 'MaxStallIteration') && i < length(varargin)
        StallItMax = cell2mat(varargin(i+1));
    end
end

lambda                      = (4+round(3*log(nVar)))*3;                             % Population Size (and Number of Offsprings)
mu                          = round(lambda/2);                                      % Number of Parents
w                           = log(mu+0.5)-log(1:mu); 
w                           = w/sum(w);                                             % Parent Weights
mu_eff                      = 1/sum(w.^2);                                          % Number of Effective Solutions

sigma0                      = 0.05*(ub-lb);
cs                          = (mu_eff+2)/(nVar+mu_eff+5);
ds                          = 1+cs+2*max(sqrt((mu_eff-1)/(nVar+1))-1,0);
ENN                         = sqrt(nVar)*(1-1/(4*nVar)+1/(31*nVar^2));

cc                          = (4+mu_eff/nVar)/(4+nVar+2*mu_eff/nVar);
c1                          = 2/((nVar+1.3)^2+mu_eff);
alpha_mu                    = 2;
cmu                         = min(1-c1,alpha_mu*(mu_eff-2+1/mu_eff)/((nVar+2)^2+alpha_mu*mu_eff/2));
hth                         = (1.4+2/(nVar+1))*ENN;

% - Initial Arrays
ps                          = cell(maxIter,1);
pc                          = cell(maxIter,1);
C                           = cell(maxIter,1);
sigma                       = cell(maxIter,1);

ps{1}                       = zeros(VarSize);
pc{1}                       = zeros(VarSize);
C{1}                        = eye(nVar);
sigma{1}                    = sigma0;

empty_individual.Position   = [];
empty_individual.Step       = [];
empty_individual.Cost       = [];

M                           = repmat(empty_individual,maxIter,1);
M(1).Position               = unifrnd(lb,ub,VarSize);
M(1).Step                   = zeros(VarSize);
M(1).Cost                   = objfcn(M(1).Position);

BestSol                     = M(1);
BestCost                    = zeros(maxIter,1);

fprintf('Optimizing ... \n');
% - CMA-ES Main Loop
for iter = 1:maxIter
    
    % Generate Samples
    pop = repmat(empty_individual,lambda,1);
    for i = 1:lambda
        pop(i).Step = mvnrnd(zeros(VarSize),C{iter});
        pop(i).Position = M(iter).Position+sigma{iter}.*pop(i).Step;
        pop(i).Cost = objfcn(pop(i).Position);
        
        % Update Best Solution Ever Found
        if pop(i).Cost < BestSol.Cost
            BestSol = pop(i);
        end
    end
    
    % Sort Population
    Costs = [pop.Cost];
    [~, SortOrder] = sort(Costs);
    pop = pop(SortOrder);
  
    % Save Results
    BestCost(iter) = BestSol.Cost;

    % Display Results
    if displayFlag == true
        disp(['Iteration ' num2str(iter) ': Best Cost = ' num2str(BestCost(iter))]);
    end

    % Stopping Criterion
    if iter == maxIter || (iter >= StallItMax+1 && BestCost(iter - StallItMax) == BestCost(iter)) ...
            || (threFlag == true && BestSol.Cost <= thre)
        break
    end
        
    % Update Mean
    M(iter+1).Step = 0;
    for j = 1:mu
        M(iter+1).Step = M(iter+1).Step+w(j)*pop(j).Step;
    end
    M(iter+1).Position = M(iter).Position+sigma{iter}.*M(iter+1).Step;
    M(iter+1).Cost = objfcn(M(iter+1).Position);
    if M(iter+1).Cost < BestSol.Cost
        BestSol = M(iter+1);
    end
    
    % Update Step Size
    ps{iter+1} = (1-cs)*ps{iter}+sqrt(cs*(2-cs)*mu_eff)*M(iter+1).Step/chol(C{iter})';
    sigma{iter+1} = sigma{iter}.*exp(cs/ds*(norm(ps{iter+1})/ENN-1))^0.3;
    
    % Update Covariance Matrix
    if norm(ps{iter+1})/sqrt(1-(1-cs)^(2*(iter+1))) < hth
        hs = 1;
    else
        hs = 0;
    end
    delta = (1-hs)*cc*(2-cc);
    pc{iter+1} = (1-cc)*pc{iter}+hs*sqrt(cc*(2-cc)*mu_eff)*M(iter+1).Step;
    C{iter+1} = (1-c1-cmu)*C{iter}+c1*(pc{iter+1}'*pc{iter+1}+delta*C{iter});
    for j = 1:mu
        C{iter+1} = C{iter+1}+cmu*w(j)*pop(j).Step'*pop(j).Step;
    end
    
    % If Covariance Matrix is not Positive Defenite or Near Singular
    [V, E] = eig(C{iter+1});
    if any(diag(E) < 0)
        E = max(E, 0);
        C{iter+1} = V*E/V;
    end
    
end
fprintf('--------------------------------------------------------\n');
fprintf('Optimization Completed \n');
fprintf('--------------------------------------------------------\n');
fprintf('Iterations = %4d\n', iter);
fprintf('Objective Function Value = %g\n', BestSol.Cost);
fprintf('========================================================\n');

end