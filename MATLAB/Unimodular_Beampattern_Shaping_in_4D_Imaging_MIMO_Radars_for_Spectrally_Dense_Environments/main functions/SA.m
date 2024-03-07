function [BestSol, BestCost, iter] = SA(objfcn, nVar, lb, ub, varargin)

displayFlag                 = false;
threFlag                    = false;

for i = 1:length(varargin)
    if strcmpi(varargin{i}, 'seed') && i < length(varargin)
        rng(cell2mat(varargin(i+1)));       
    end
end

for i = 1:length(varargin)-1
    if strcmpi(varargin{i}, 'Display') && i < length(varargin)
        if strcmpi(varargin{i+1}, 'iter')
            displayFlag = true;
            break
        end
    end
end

for i = 1:length(varargin)-1
    if strcmpi(varargin{i}, 'Threshold') && i < length(varargin)
        threFlag = true;
        thre = cell2mat(varargin(i+1));
    end
end

VarSize                     = [1 nVar];

% - SA Parameters
maxIter                     = 1e3;
for i = 1:length(varargin)-1
    if strcmpi(varargin{i}, 'MaxIteration') && i < length(varargin)
        maxIter = cell2mat(varargin(i+1));
    end
end

maxSubIter                     = 20;
for i = 1:length(varargin)-1
    if strcmpi(varargin{i}, 'MaxSubIter') && i < length(varargin)
        maxSubIter = cell2mat(varargin(i+1));
    end
end

StallItMax                  = maxIter;
for i = 1:length(varargin)-1
    if strcmpi(varargin{i}, 'MaxStallIteration') && i < length(varargin)
        StallItMax = cell2mat(varargin(i+1));
    end
end

nPop                        = 100;
for i = 1:length(varargin)-1
    if strcmpi(varargin{i}, 'PopulationSize') && i < length(varargin)
        nPop = cell2mat(varargin(i+1));
    end
end

nMove                       = 5;
for i = 1:length(varargin)-1
    if strcmpi(varargin{i}, 'NeighborsSize') && i < length(varargin)
        nMove = cell2mat(varargin(i+1));
    end
end

mu                          = 0.5;
for i = 1:length(varargin)-1
    if strcmpi(varargin{i}, 'MutationRate') && i < length(varargin)
        mu = cell2mat(varargin(i+1));
    end
end

T0                          = 0.1;
alpha                       = 0.95;
sigma                       = 0.1*(ub-lb);

% - Initialization
empty_individual.Position   = [];
empty_individual.Cost       = [];

pop                         = repmat(empty_individual,nPop,1);

BestSol.Cost                = inf;

% Initialize Population
for i = 1:nPop
    
    % Initialize Position
    pop(i).Position = unifrnd(lb, ub, VarSize);
    
    % Evaluation
    pop(i).Cost = objfcn(pop(i).Position);
    
    % Update Best Solution
    if pop(i).Cost <= BestSol.Cost
        BestSol = pop(i);
    end
    
end

% Array to Hold Best Cost Values
BestCost                    = zeros(maxIter,1);

% Intialize Temp.
T                           = T0;

fprintf('Optimizing ... \n');
% - SA Main Loop
for iter = 1:maxIter
    
    for subit = 1:maxSubIter
        
        % Create and Evaluate New Solutions
        newpop = repmat(empty_individual,nPop,nMove);
        for i = 1:nPop
            for j = 1:nMove
                
                % Create Neighbor
                newpop(i,j).Position = MutateSA(pop(i).Position,mu,sigma,lb,ub);
                
                % Evaluation
                newpop(i,j).Cost = objfcn(newpop(i,j).Position);
                
            end
        end
        newpop = newpop(:);
        
        % Sort Neighbors
        [~, SortOrder] = sort([newpop.Cost]);
        newpop = newpop(SortOrder);
        
        for i = 1:nPop
            
            if newpop(i).Cost <= pop(i).Cost
                pop(i) = newpop(i);
                
            else
                DELTA = (newpop(i).Cost-pop(i).Cost)/pop(i).Cost;
                P = exp(-DELTA/T);
                if rand <= P
                    pop(i) = newpop(i);
                end
            end
            
            % Update Best Solution Ever Found
            if pop(i).Cost <= BestSol.Cost
                BestSol = pop(i);
            end
        
        end

    end
    
    % Store Best Cost Ever Found
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
    
    % Update Temp.
    T = alpha*T;
    
    sigma = 0.98*sigma;
    
end

fprintf('--------------------------------------------------------\n');
fprintf('Optimization Completed \n');
fprintf('--------------------------------------------------------\n');
fprintf('Iterations = %4d\n', iter);
fprintf('Objective Function Value = %g\n', BestSol.Cost);
fprintf('========================================================\n');

end                 