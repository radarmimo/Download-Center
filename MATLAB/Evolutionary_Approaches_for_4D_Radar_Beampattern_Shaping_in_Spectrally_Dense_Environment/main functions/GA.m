function [BestSol, BestCost, iter] = GA(objfcn, nVar, lb, ub, varargin)

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

% - GA Parameters
maxIter                     = 1e3;
for i = 1:length(varargin)-1
    if strcmpi(varargin{i}, 'MaxIteration') && i < length(varargin)
        maxIter = cell2mat(varargin(i+1));
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

pc                          = 0.7;
for i = 1:length(varargin)-1
    if strcmpi(varargin{i}, 'CrossoverFraction') && i < length(varargin)
        pc = cell2mat(varargin(i+1));
    end
end
nc                          = 2*round(pc*nPop/2);
gamma                       = 0.4;

pm                          = 0.3;
for i = 1:length(varargin)-1
    if strcmpi(varargin{i}, 'MutationFraction') && i < length(varargin)
        pm = cell2mat(varargin(i+1));
    end
end

nm                          = round(pm*nPop);
mu                          = 0.1;

UseTournamentSelection      = 1;
UseRouletteWheelSelection   = 0;
UseRandomSelection          = 0;
for i = 1:length(varargin)-1
    if strcmpi(varargin{i}, 'SelectionMethod')
        UseTournamentSelection = 0;
        if strcmpi(varargin{i+1}, 'RouletteWheel')
            UseRouletteWheelSelection = 1;
        elseif strcmpi(varargin{i+1}, 'Tournament')
            UseTournamentSelection = 1;
        elseif strcmpi(varargin{i+1}, 'Random')
            UseRandomSelection = 1;
        end
    end
end

if UseRouletteWheelSelection
    beta = 8;
end

if UseTournamentSelection
    TournamentSize = 3;
end

% - Initialization
empty_individual.Position   = [];
empty_individual.Cost       = [];

pop                         = repmat(empty_individual,nPop,1);

for i = 1:nPop
    
    pop(i).Position = unifrnd(lb,ub,VarSize);
    pop(i).Cost = objfcn(pop(i).Position);
    
end

Costs                       = [pop.Cost];
[Costs, SortOrder]          = sort(Costs);
pop                         = pop(SortOrder);
BestSol                     = pop(1);
BestCost                    = zeros(maxIter,1);
WorstCost                   = pop(end).Cost;

fprintf('Optimizing ... \n');
% - Main GA Loop
for iter = 1:maxIter
    
    % Calculate Selection Probabilities
    if UseRouletteWheelSelection
        P = exp(-beta*Costs/WorstCost);
        P = P/sum(P);
    end
    
    % Crossover
    popc = repmat(empty_individual,nc/2,2);
    for k = 1:nc/2
        
        % Select Parents Indices
        if UseRouletteWheelSelection
            i1 = RouletteWheelSelection(P);
            i2 = RouletteWheelSelection(P);
        end
        if UseTournamentSelection
            i1 = TournamentSelection(pop,TournamentSize);
            i2 = TournamentSelection(pop,TournamentSize);
        end
        if UseRandomSelection
            i1 = randi([1 nPop]);
            i2 = randi([1 nPop]);
        end

        % Select Parents
        p1 = pop(i1);
        p2 = pop(i2);
        
        % Apply Crossover
        [popc(k,1).Position, popc(k,2).Position] = Crossover(p1.Position,p2.Position,gamma,lb,ub);
        
        % Evaluate Offsprings
        popc(k,1).Cost = objfcn(popc(k,1).Position);
        popc(k,2).Cost = objfcn(popc(k,2).Position);
        
    end
    popc = popc(:);
    
    
    % Mutation
    popm = repmat(empty_individual,nm,1);
    for k = 1:nm
        
        % Select Parent
        i = randi([1 nPop]);
        p = pop(i);
        
        % Apply Mutation
        popm(k).Position = Mutate(p.Position,mu,lb,ub);
        
        % Evaluate Mutant
        popm(k).Cost = objfcn(popm(k).Position);
        
    end
    
    % Create Merged Population
    pop = [pop
         popc
         popm]; %#ok
     
    % Sort Population
    Costs = [pop.Cost];
    [Costs, SortOrder] = sort(Costs);
    pop = pop(SortOrder);
    
    % Update Worst Cost
    WorstCost = max(WorstCost,pop(end).Cost);
    
    % Truncation
    pop = pop(1:nPop);
    Costs = Costs(1:nPop);
    
    % Store Best Solution Ever Found
    BestSol = pop(1);
    
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
    
end

fprintf('--------------------------------------------------------\n');
fprintf('Optimization Completed \n');
fprintf('--------------------------------------------------------\n');
fprintf('Iterations = %4d\n', iter);
fprintf('Objective Function Value = %g\n', BestSol.Cost);
fprintf('========================================================\n');

end