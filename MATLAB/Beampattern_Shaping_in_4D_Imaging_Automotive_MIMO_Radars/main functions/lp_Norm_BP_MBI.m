% LP_NORM_BP_MBI - Beampattern Shaping for MIMO Radars Using BSUM Method
%
% This function designs a beampattern for MIMO radars aiming to match a
% desired beampattern shape by iteratively minimizing the distance between
% the designed and desired beampatterns. It emplys the Block Successive
% Upper0bound Minimization (BSUM) method and accomodates both discrete and
% continuous phase constraints. The optimization leverages the l_p-norm
% criteria for p >= 2 and 0 < p <= 1.
%
% Usage:
% [POpt, mu, objfunVal, solConv, S] = lp_Norm_BP_MBI(Mt, Nc, p, L, theta, thetaDes, varargin)
%
% Inputs:
%   Mt       - Number of transmitters.
%   Nc       - Number of chirps (time slots).
%   p        - l_p norm parameter.
%   L        - Length of modulation (positive integer for MPSK, inf for continuous phase).
%   theta    - Array of angles from -90 to 90 degrees.
%   thetaDes - Vector specifying the beginning and end of the desired beampattern (e.g., [-60 -30; 30 60]).
%   varargin - Name-value pairs for 'draw', 'result', 'mu', 'iter', 'seed', 'InitialPoint'.
%
% Outputs:
%   POpt       - Optimized beampattern vector.
%   mu         - Final optimized mu parameter.
%   objfunVal  - Objective function values for all iterations.
%   solConv    - Solution convergence over iterations.
%   S          - Final optimized code.
%
% Example:
%   POpt = lp_Norm_BP(16, 16, 2, inf, -90:90, [-20, 20])
%
% This function draws the optimized beampattern, compares it with the
% desired one, and displays optimization results including MSE, ILS, and
% PSL when applicable. Options 'draw' and 'result' control these features.
%
% Author:
%   Masoud DORVASH (masoud.dorvash@gmail.com) and
%   Mohammad ALAEE (mohammad.alaee@uni.lu)
%
% Reference:
%   "Beampattern Shaping in 4D-Imaging Automotive MIMO Radars" by 
%   Masoud DORVASH, Mahmoud MODARRES-HASHEMI, and Mohammad ALAEE-KERAHROODI.
%
% Version:
%   2.0, dated 05/25/2024

function [POpt, mu, objfunVal, solConv, S] = lp_Norm_BP_MBI(Mt,Nc,p,L,theta,thetaDes,varargin)

plotResult      = true;
tableResult     = true;
muFlag          = true;
threFlag        = true;
setInitial      = false;

for i = 1:length(varargin)
    if strcmpi(varargin{i}, 'draw') && i < length(varargin)
        if strcmpi(varargin{i+1}, 'off')
            plotResult = false;
            break
        end
    end
end

for i = 1:length(varargin)
    if strcmpi(varargin{i}, 'result') && i < length(varargin)
        if strcmpi(varargin{i+1}, 'off')
            tableResult = false;
            break
        end
    end
end

for i = 1:length(varargin)
    if strcmpi(varargin{i}, 'mu') && i < length(varargin)
        muFlag = false;
        mu = cell2mat(varargin(i+1));
        break
    end
end

for i = 1:length(varargin)
    if strcmpi(varargin{i}, 'iter') && i < length(varargin)
        threFlag = false;
        maxIter = cell2mat(varargin(i+1));
        break
    end
end

for i = 1:length(varargin)
    if strcmpi(varargin{i}, 'seed') && i < length(varargin)
        rng(cell2mat(varargin(i+1)))
        break
    end
end

for i = 1:length(varargin)
    if strcmpi(varargin{i}, 'InitialPoint') && i < length(varargin)
        setInitial = true;
        S = cell2mat(varargin(i+1));
        if L ~= inf
            phi = 2*pi*(0:L-1)/L;
        end
        break
    end
end

varNo           = Mt*Nc;
MtVec           = 1:Mt;

A               = exp(-1i*pi*(MtVec-1)'*sind(theta));

PDes            = designPDes(theta, thetaDes);

if threFlag == true
    maxIter     = 1e4;
end
objfunVal       = zeros(maxIter,1);
POpt            = zeros(length(theta),1);
solConv         = zeros(maxIter,1);
cellS           = cell(maxIter,1);

if ~setInitial
    S               = exp(1i*(2*pi*rand(Mt,Nc)));
    if L ~= inf
        phi             = 2*pi*(0:L-1)/L;
        pos             = randi([1, L], [Mt, Nc]);
        S               = exp(1i*phi(pos));
    end
end

if muFlag == true
    if p <= 2
        mu = 10;
    elseif p >= 3
        mu = 0.25;
    end
end
epsilon         = 1e-6;
threshold       = 1e-3;

GS              = @(mu,S)(sum(mu*1/(varNo)*abs(A'*S).^2,2) - PDes);
objFun          = @(eta,psi,nou,X)(sum(eta .* X.^2 + psi .* X + nou));

tic

% - Coordinate Descent Algorithm
for iter = 1:maxIter

    if p <= 1 && p > 0

        epsilonFlag = abs(GS(mu,S)) <= epsilon;

        eta = (p/2 * epsilon^(p-2) .* epsilonFlag) + (p/2*(abs(GS(mu,S))).^(p-2) .* ~epsilonFlag);
        psi = 0;
        nou = (abs(GS(mu,S).^p - p/2 * epsilon^(p-2) * abs(GS(mu,S)).^2) .* epsilonFlag) + ...
            ((1-p/2)*(abs(GS(mu,S))).^p .* ~epsilonFlag);

    elseif p >= 2

        t = norm(GS(mu,S),p);

        eta = (t^p + (p-1) * abs(GS(mu,S)).^p - p * t * abs(GS(mu,S)).^(p-1)) ./ (t - abs(GS(mu,S))).^2;
        psi = (p * abs(GS(mu,S)).^(p-2) - 2 * eta) .* GS(mu,S);
        nou = eta .* abs(GS(mu,S)).^2 - (p-1) * abs(GS(mu,S)).^p;

    else

        errordlg('Choose p in the defined range','Error')
        return

    end

    if muFlag == true

        mu = sum(2*eta.*sum(1/(varNo)*abs(A'*S).^2,2).*PDes - psi.*sum(1/(varNo)*abs(A'*S).^2,2)) / ...
            sum(2*eta.*sum(1/(varNo)*abs(A'*S).^2,2).^2);

    end

    objfunVal(iter) = objFun(eta,psi,nou,GS(mu,S));
    cellS{iter} = S;
    SOldPrime = S;

    CR = zeros(Mt,Nc);
    for mPrime = 1:Mt

        for nPrime = 1:Nc

            SCell = cell(Mt,Nc);
            objValPrime = inf*ones(Mt*Nc,1);

            for mP = 1:Mt
                MtVec = 1:Mt;
                MtVec(mP) = [];
                for nP = 1:Nc

                    if CR(mP,nP)

                        continue

                    end

                    NcVec = 1:Nc;
                    NcVec(nP) = [];

                    alpha = sum(abs(A' * S(:,NcVec)).^2,2);
                    beta = (S(MtVec,nP)' * A(MtVec,:)).';
                    gamma = conj(A(mP,:)).' .* beta;
                    delta = abs(beta).^2 + alpha + 1;

                    b0 = sum(mu^2*eta./((Nc*Mt)^2) .* conj(gamma).^2);
                    b1 = sum(mu^2*2*eta./((Nc*Mt)^2) .* conj(gamma) .* delta - (2*eta.*PDes)*mu/(Nc*Mt) .* conj(gamma) + psi *mu ./(Nc*Mt) .* conj(gamma));
                    b2 = sum(mu^2*eta./((Nc*Mt)^2) .* (delta.^2 + 2*abs(gamma).^2) - 2*eta.*PDes*mu/(Nc*Mt) .* delta + eta .*PDes.^2+psi*mu/(Nc*Mt).*delta-psi .*PDes+nou);
                    b3 = conj(b1);
                    b4 = conj(b0);

                    if L == inf

                        G = [b4 b3 b2 b1 b0];
                        Gp = [2*b4 b3 0 -b1 -2*b0];

                        SolP = roots(Gp);
                        Gpol = polyval(G,SolP).*SolP.^(-2);

                        gIdx = abs(abs(SolP) - 1) <= 1e-6;

                        if sum(gIdx) >= 1
                            [~, idx] = min(Gpol(gIdx));
                            solG = SolP(gIdx);
                            S(mP, nP) = solG(idx);
                        end

                    else

                        B = [b0 b1 b2 b3 b4];

                        if L < length(B)

                            bPad = padarray(B,[0 L-mod(length(B),L)], 0, 'post');
                            Y = fft(sum(reshape(bPad,L,[]),2).');

                        else

                            Y = fft(B,L);

                        end

                        [~, idx] = min(circshift(flip(abs(Y)),1));
                        S(mP,nP) = exp(1i*phi(idx));

                    end

                    objValPrime((mP-1)*Nc+nP) = objFun(eta,psi,nou,GS(mu,S));
                    SCell{mP,nP} = S;
                    S = SOldPrime;

                end
            end

            [~, idxPrime] = min(objValPrime);
            [column, row] = ind2sub([Nc, Mt], idxPrime);

            S = SCell{row, column};

            SOldPrime = S;

            CR(row,column) = 1;

        end
    end

    if threFlag && iter >= 2 && objfunVal(iter) / objfunVal(iter-1) > (1-threshold)
        break
    end

end

elapsedTime     = toc;

% - Solution Convergence
for i = 2:iter
    solConv(i-1) = norm(cellS{i} - cellS{i-1},'fro');
end

% - Optimized Set of Sequence Beampattern
POpt        = sum(1/varNo*abs((A'*S)).^2,2);

if plotResult == true

    %%  Plot Results

    ScreenSize  = get(0,'ScreenSize');
    figure('Name','Normalized Beampattern','NumberTitle','off',...
        'Position', [0 0 floor(ScreenSize(3)/3) floor(ScreenSize(4)/2.5)]);
    movegui('center')
    plot(theta,20*log10(POpt/max(POpt)),'LineWidth',1.5), hold on
    PDesP = PDes;
    PDesP(PDesP == 0) = -100;
    PDesP = PDesP - max(PDesP);
    plot(theta,PDesP,'--k','LineWidth',1.5)
    ylim([1.05*min(min(20*log10(POpt/ max(POpt)))) 0])
    xlim([min(theta) max(theta)])
    xticks(-90:30:90)
    legend('Optimized Beampattern', 'Desired Beampattern','Interpreter','latex','Location','Best','FontSize',12)
    xlabel('Angle ($^\circ$)','Interpreter','latex','FontSize',12')
    ylabel('Normalized Beampattern (dB)','Interpreter','latex','FontSize',12')
    grid minor

end

if tableResult == true

    %%  MSE, ISL, and PSL Calculations

    MSE                     = immse(PDes,mu*POpt);

    ISLrange                = POpt;
    ISLrange(PDes ~= 0)     = [];
    ISL                     = 20*log10(sum(ISLrange/max(POpt)));

    PSLs                    = sort(findpeaks(ISLrange));
    PSL                     = 20*log10(PSLs(end-1)/max(POpt));

    % - Display Results
    fprintf('==================== Simulation Results ====================\n');
    fprintf('Mt = %d, Nc = %d, L = Infinity, and p = %d\n', Mt, Nc, p);
    fprintf('------------------------------------------------------------\n');
    fprintf('Number of Iterations = %d\n', iter);
    fprintf('Run Time = %.2f seconds\n', elapsedTime);
    fprintf('------------------------------------------------------------\n');
    fprintf('MSE = %.3f\n', MSE);
    fprintf('ISL = %.2f dB\n', ISL);
    fprintf('PSL = %.2f dB\n', PSL);
    fprintf('==================== Simulation Results ====================\n');

end

end