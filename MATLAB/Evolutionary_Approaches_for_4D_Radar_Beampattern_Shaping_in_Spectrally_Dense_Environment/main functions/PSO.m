function [BestSol, BestCost, iter] = PSO(objfcn, nVar, lb, ub, varargin)

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

% - PSO Parameters
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

% - Constriction Coefficients
phi1                        = 2.05;
phi2                        = 2.05;
phi                         = phi1 + phi2;
chi                         = 2 / (phi - 2 + sqrt(phi^2 - 4*phi));

w                           = chi;
c1                          = chi * phi1;
c2                          = chi * phi2;

% - Velocity Limits
VelMax                      = 0.1*(ub-lb);
VelMin                      = -VelMax;

% - Initialization
empty_particle.Position     =[];
empty_particle.Cost         =[];
empty_particle.Velocity     =[];
empty_particle.Best.Position=[];
empty_particle.Best.Cost    =[];

particle                    = repmat(empty_particle,nPop,1);

GlobalBest.Cost             = inf;

for i = 1:nPop
    
    particle(i).Position = unifrnd(lb,ub,VarSize);

    particle(i).Velocity = zeros(VarSize);
    
    particle(i).Cost = objfcn(particle(i).Position);

    particle(i).Best.Position = particle(i).Position;
    particle(i).Best.Cost = particle(i).Cost;

    if particle(i).Best.Cost < GlobalBest.Cost
        GlobalBest = particle(i).Best;
    end
    
end

BestCost                    = zeros(maxIter,1);

fprintf('Optimizing ... \n');
% - PSO Main Loop
for iter = 1:maxIter
    
    for i = 1:nPop
        
        % Update Velocity
        particle(i).Velocity = w*particle(i).Velocity ...
            +c1*rand(VarSize).*(particle(i).Best.Position-particle(i).Position) ...
            +c2*rand(VarSize).*(GlobalBest.Position-particle(i).Position);
        
        % Apply Velocity Limits
        particle(i).Velocity = max(particle(i).Velocity,VelMin);
        particle(i).Velocity = min(particle(i).Velocity,VelMax);
        
        % Update Position
        particle(i).Position = particle(i).Position + particle(i).Velocity;
        
        % Velocity Mirror Effect
        IsOutside=(particle(i).Position<lb | particle(i).Position>ub);
        particle(i).Velocity(IsOutside)=-particle(i).Velocity(IsOutside);
        
        % Apply Position Limits
        particle(i).Position = max(particle(i).Position,lb);
        particle(i).Position = min(particle(i).Position,ub);
        
        % Evaluation
        particle(i).Cost = objfcn(particle(i).Position);
        
        % Update Personal Best
        if particle(i).Cost < particle(i).Best.Cost
            
            particle(i).Best.Position = particle(i).Position;
            particle(i).Best.Cost = particle(i).Cost;
            
            % Update Global Best
            if particle(i).Best.Cost < GlobalBest.Cost

                GlobalBest = particle(i).Best;

            end
            
        end
        
    end
    
    BestCost(iter) = GlobalBest.Cost;
    
    % Display Results
    if displayFlag == true
        disp(['Iteration ' num2str(iter) ': Best Cost = ' num2str(BestCost(iter))]);
    end
    
    % Stopping Criterion
    if iter == maxIter || (iter >= StallItMax+1 && BestCost(iter - StallItMax) == BestCost(iter)) ...
            || (threFlag == true && BestCost(iter) <= thre)
        break
    end
    
end

BestSol = GlobalBest;

fprintf('--------------------------------------------------------\n');
fprintf('Optimization Completed \n');
fprintf('--------------------------------------------------------\n');
fprintf('Iterations = %4d\n', iter);
fprintf('Objective Function Value = %g\n', BestSol.Cost);
fprintf('========================================================\n');

end