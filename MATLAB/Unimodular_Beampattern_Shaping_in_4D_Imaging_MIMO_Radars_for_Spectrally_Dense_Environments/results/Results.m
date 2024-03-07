%%  PreProcessing
clear, close all
clc
%%  Initializing

seed                        = 3;
ScreenSize                  = get(0,'ScreenSize');

addpath('../comparison data/')
addpath('../main functions/')

% - Radar Parameters
fc                          = 77e9;
c                           = 3e8;
lambda                      = c/fc;
mX                          = 4;
mY                          = 4;
Nt                          = mX * mY;
N                           = 64;
dt                          = lambda/2;
txX                         = ((1:mX) - (mX+1)/2) * dt;
txY                         = ((1:mY) - (mY+1)/2) * dt;
[pX, pY]                    = meshgrid(txX,txY);
pZ                          = zeros(size(pX));

% - Fast Time Domain
nHat                        = 5*N;                                                  % Zero Padded Fast Time Domain Sequence Length

kVec                        = 0:nHat-1;
nVec                        = (0:nHat-1)';

F                           = exp(-1i*2*pi*kVec.*nVec/nHat);                        % DFT Matrix

Ud                          = [0.7 0.9];                                            % Undesired Normalized Frequency
kTotal                      = 0:nHat-1;
kUd                         = kTotal(any(round(nHat*Ud(:,1)) <= kTotal ...
    & round(nHat*Ud(:,2)) >= kTotal,1)) + 1;

G                           = F(kUd,:);                                             % Undesired Normalized Frequency Correspoiding DFT Matrix

gamma                       = 0.01*sqrt(nHat);                                      % Suppression Threshold

% - Steering Vector
thetaVec                    = (-90:90)';
phiVec                      = -90:90;
R                           = cat(3,sind(thetaVec).*cosd(phiVec), sind(thetaVec).*sind(phiVec), cosd(thetaVec)+phiVec-phiVec);
P                           = cat(3,pX,pY,pZ);
tau                         = -1/c .* sum(permute(P,[4,5,3,1,2]) .* R,3);
APrime                      = reshape(permute(exp(1i*2*pi/lambda*c.*tau),[1 2 3 4 5]),length(thetaVec),length(phiVec),[]);
A                           = permute(reshape(APrime,[],Nt),[3, 2, 4, 1]);
A                           = conj(A);

% - 2D Desired Beampattern
PDesPrime                   = zeros(length(thetaVec),length(phiVec));
thetaDes                    = [15 45];
phiDes                      = [-25 25];

for i = 1:length(thetaVec)

    for j = 1:length(phiVec)

        if any((thetaDes(:,1) <= thetaVec(i) & thetaVec(i) <= thetaDes(:,2)) & ...
                (phiDes(:,1) <= phiVec(j) & phiVec(j) <= phiDes(:,2)))

            PDesPrime(i,j) = 1;

        end

    end

end

PDes                        = reshape(PDesPrime,1,[]);

%%  Problem Definition

% - Fast Time Domain
nVarFT                      = N;
lbFT                        = 0;
ubFT                        = 2*pi;
objfcnFT                    = @(data)(FastTimeFcn(data,G,gamma));
thre                        = 0;
load FFTSpectralDeng
load FFTSpectralALAEE

% - Spatial Domain
nVarSpatial                 = 1 + Nt;
lbSpatial                   = [0 zeros(1,Nt)];
ubSpatial                   = [1 2*pi*ones(1,Nt)];
MaxStallIter                = 100;
pVec                        = [2 4 8 16];

%%  Fast Time Domain Optimization

fprintf('=============== Fast Time Domain (CMAES) ===============\n');
[BestSolFT, BestCostFT]     = CMAES(objfcnFT, nVarFT, lbFT, ubFT,'MaxIteration',1e3+2,'seed',seed);
sTildeStar                  = exp(1i*mod(BestSolFT.Position, 2*pi));

%%  Spatial Domain Optimization

alphaStar                   = zeros(1,length(pVec));
sBarStar                    = cell(length(pVec),1);
IterSpatial                 = zeros(1,length(pVec));
BestCostSpatialCell         = cell(1,length(pVec));

for i = 1:length(pVec)

    p = pVec(i);
    objfcnSpatial = @(data)(SpatialFcn(Nt,data,A,p,PDes));
    
    fprintf('\n================ Spatial Domain (p = %2d) ===============\n', p);
    [BestSolSpatial, BestCostSpatial, iterSpatial] = CMAES(objfcnSpatial, nVarSpatial, lbSpatial, ubSpatial, ...
        'MaxStallIteration',MaxStallIter,'seed',seed);

    alphaStar(i) = BestSolSpatial.Position(1);
    sBarStar{i, :} = exp(1i*mod(BestSolSpatial.Position(2:end), 2*pi));
    IterSpatial(i) = iterSpatial;
    BestCostSpatialCell{:,i} = BestCostSpatial;

end

%%  GA, PSO, and SA Fast Time Domain Optimization

fprintf('\n================ Fast Time Domain (GA) =================\n');
[~, BestCostFTGA, iterFTGA] = GA(objfcnFT, nVarFT, lbFT, ubFT,'PopulationSize',500, ...
    'CrossoverFraction',0.6,'MutationFraction',0.4,'SelectionMethod','Tournament', ...
    'MaxIteration',1e3+2,'Threshold',thre,'seed',seed);

fprintf('\n=============== Fast Time Domain (PSO) =================\n');
[~, BestCostFTPSO, iterFTPSO] = PSO(objfcnFT, nVarFT, lbFT, ubFT,'PopulationSize',500, ...
    'MaxIteration',1e3+2,'Threshold',thre,'seed',seed);

fprintf('\n================ Fast Time Domain (SA) =================\n');
[~, BestCostFTSA, iterFTSA] = SA(objfcnFT, nVarFT, lbFT, ubFT,'PopulationSize',20, ...
    'MaxIteration',1e3+2,'MutationRate', 0.75, ...
    'Threshold',thre,'seed',seed);

%%  Plot Results

colors                      = ['b', 'r', 'g', 'm'];

% - Fast Time Domain Convergence Curves
fhdl(1)                     = figure('Name','Fast Time Convergence Curve','NumberTitle','off',...
    'Position', [0 0 floor(ScreenSize(3)/4) floor(ScreenSize(4)/3)]);
movegui('northwest')
iterFT = find(BestCostFT > 0, 1, 'last' );
plot(0:iterFT-2,10*log10(BestCostFT(1:iterFT-1)), 'LineWidth', 2, 'color', 'blue'), hold on
plot(0:iterFTGA-2,10*log10(BestCostFTGA(1:iterFTGA-1)), 'LineWidth', 2, 'color', 'red')
plot(0:iterFTPSO-2,10*log10(BestCostFTPSO(1:iterFTPSO-1)), 'LineWidth', 2, 'color', 'green')
plot(0:iterFTSA-2,10*log10(BestCostFTSA(1:iterFTSA-1)), 'LineWidth', 2, 'color', 'magenta')
xlabel('Iteration','FontSize',11,'Interpreter','Latex')
ylabel('Objective Function (dB)','FontSize',11,'Interpreter','Latex')
legend('CMA-ES', 'GA', 'PSO', 'SA', 'Interpreter','Latex', 'FontSize', 11, 'location', 'ne')
grid minor
box on

pointStart                  = [iterFT-2, 10*log10(BestCostFT(iterFT-1))];
pointEnd                    = [iterFT-2+100, 10*log10(BestCostFT(iterFT-1))+5];
ax                          = gca;
xLimits                     = ax.XLim;
yLimits                     = ax.YLim;
axesPos                     = ax.Position;
normPointStart              = [(pointStart(1) - xLimits(1)) / diff(xLimits), ...
    (pointStart(2) - yLimits(1)) / diff(yLimits)];
normPointEnd                = [(pointEnd(1) - xLimits(1)) / diff(xLimits), ...
    (pointEnd(2) - yLimits(1)) / diff(yLimits)];
figPointStart               = [axesPos(1) + normPointStart(1) * axesPos(3), axesPos(2) + normPointStart(2) * axesPos(4)];
figPointEnd                 = [axesPos(1) + normPointEnd(1) * axesPos(3), axesPos(2) + normPointEnd(2) * axesPos(4)];
annotation('arrow', [figPointStart(1), figPointEnd(1)], [figPointStart(2), figPointEnd(2)], 'LineWidth', 1.5);
textStr                     = 'Feasible Point';
textOffsetY                 = -0.3 / yLimits(end);
textPositionX               = figPointEnd(1);
textPositionY               = figPointEnd(2) - textOffsetY;
textPositionDataX           = xLimits(1) + (textPositionX - axesPos(1)) / axesPos(3) * diff(xLimits);
textPositionDataY           = yLimits(1) + (textPositionY - axesPos(2)) / axesPos(4) * diff(yLimits);
text(textPositionDataX, textPositionDataY, textStr, 'FontSize', 11, 'Interpreter', 'latex', 'HorizontalAlignment', 'center')

% - Spatial Domain Convergence Curves
fhdl(2)                     = figure('Name','Spatial Domain Convergence Curve','NumberTitle','off',...
    'Position', [0 0 floor(ScreenSize(3)/4) floor(ScreenSize(4)/3)]);
hold on
movegui('northeast')
for i = 1:length(pVec)

    iterSpatial = IterSpatial(i);
    BestCostSpatial = cell2mat(BestCostSpatialCell(:,i));


    if mean(BestCostSpatial(iterSpatial:-1:iterSpatial-MaxStallIter)) == BestCostSpatial(iterSpatial)
        plot(0:iterSpatial-(MaxStallIter + 1), ...
            10*log10(BestCostSpatial(1:iterSpatial-MaxStallIter)/max(BestCostSpatial(1:iterSpatial-MaxStallIter))), ...
            'LineWidth', 2, 'color', colors(i))
        IterSpatial(i) = iterSpatial-MaxStallIter;
    else
        plot(0:iterSpatial-2, ...
            10*log10(BestCostSpatial(1:iterSpatial-1)/max(BestCostSpatial(1:iterSpatial-1))), ...
            'LineWidth', 2, 'color', colors(i))
        IterSpatial(i) = iterSpatial;
    end

end
xlim([0 max(IterSpatial)-1])
xlabel('Iteration','FontSize',11,'Interpreter','Latex')
ylabel('Normalized Objective Function (dB)','FontSize',11,'Interpreter','Latex')
legend(['$p = $ ' num2str(pVec(1))], ['$p = $ ' num2str(pVec(2))], ...
    ['$p = $ ' num2str(pVec(3))], ['$p = $ ' num2str(pVec(4))], ...
    'Interpreter','Latex', 'FontSize', 11, 'location', 'ne')
grid minor
box on

% - 2D Beampattern Map
for i = 1:length(pVec)

    SStar = repmat(flip(cell2mat(sBarStar(i,:))).',1,N) .* sTildeStar/(sTildeStar(1));
    pOpt2D = 1/(Nt*N)*abs(squeeze(sum(conj(APrime).*permute(SStar,[3,4,1,2]),3))).^2;
    POpt2D = sum(pOpt2D,3);
    fhdl(i+2) = figure('Name','2D Beampattern','NumberTitle','off',...
        'Position', [(i-1)*floor(ScreenSize(3)/4) floor(ScreenSize(4)/3.75) floor(ScreenSize(3)/4) floor(ScreenSize(4)/3.5)]);
    imagesc(thetaVec,phiVec,POpt2D)
    xlim([-90 90])
    ylim([-90 90])
    xticks(-90:30:90)
    yticks(-90:30:90)
    xlabel('Azimuth ($\theta_{\mathrm{az}}$, degree $^\circ$)','Interpreter','latex','FontSize',11)
    ylabel('Elevation ($\theta_{\mathrm{el}}$, degree $^\circ$)','Interpreter','latex','FontSize',11)
    colormap(jet)
    colorbar
    set(gca,'YDir','normal')

end

% - Azimuth Cut
fhdl(7) = figure('Name','Azimuth Cut at 0','NumberTitle','off',...
    'Position', [0 floor(ScreenSize(4)/20) floor(ScreenSize(3)/4) floor(ScreenSize(4)/3)]);
hold on
for i = 1:length(pVec)

    SStar = repmat(flip(cell2mat(sBarStar(i,:))).',1,N) .* sTildeStar/(sTildeStar(1));
    pOpt2D = 1/(Nt*N)*abs(squeeze(sum(conj(APrime).*permute(SStar,[3,4,1,2]),3))).^2;
    POpt2D = sum(pOpt2D,3);
    elCut = POpt2D(:, thetaVec == 0);
    PDesEl = PDesPrime(:, thetaVec == 0);
    PDesEl( PDesEl == 0) = 1e-10;
    plot(thetaVec,10*log10(elCut/max(elCut)),'LineWidth',2, 'color', colors(i))

end
plot(phiVec,10*log10(PDesEl)/max(PDesEl(:)), '--k', 'LineWidth', 2);
xlabel('Elevation (degree $^\circ$)', 'FontSize', 11, 'Interpreter', 'Latex')
ylabel('Normalized Magnitude (dB)', 'FontSize', 11, 'Interpreter', 'Latex')
xlim([-90 90])
ylim([-50 0])
xticks(-90:30:90)
legend(['$p = $ ' num2str(pVec(1))], ['$p = $ ' num2str(pVec(2))], ...
    ['$p = $ ' num2str(pVec(3))], ['$p = $ ' num2str(pVec(4))], ...
    'Desired Beampattern', 'Interpreter','Latex', 'FontSize', 11, 'location', 's')
grid minor
box on

% - Elevation Cut
fhdl(8) = figure('Name','Elevation Cut at 40','NumberTitle','off',...
    'Position', [3*floor(ScreenSize(3)/4) floor(ScreenSize(4)/20) floor(ScreenSize(3)/4) floor(ScreenSize(4)/3)]);
hold on
for i = 1:length(pVec)

    SStar = repmat(flip(cell2mat(sBarStar(i,:))).',1,N) .* sTildeStar/(sTildeStar(1));
    pOpt2D = 1/(Nt*N)*abs(squeeze(sum(conj(APrime).*permute(SStar,[3,4,1,2]),3))).^2;
    POpt2D = sum(pOpt2D,3);
    azCut = POpt2D(phiVec == 40,:);
    PDesAz = PDesPrime(phiVec == 40, :);
    PDesAz( PDesAz == 0) = 1e-10;
    plot(thetaVec,10*log10(azCut/max(azCut)),'LineWidth',2, 'color', colors(i))

end
plot(phiVec,10*log10(PDesAz)/max(PDesAz(:)), '--k', 'LineWidth', 2);
xlabel('Azimuth (degree $^\circ$)', 'FontSize', 11, 'Interpreter', 'Latex')
ylabel('Normalized Magnitude (dB)', 'FontSize', 11, 'Interpreter', 'Latex')
xlim([-90 90])
ylim([-40 0])
xticks(-90:30:90)
legend(['$p = $ ' num2str(pVec(1))], ['$p = $ ' num2str(pVec(2))], ...
    ['$p = $ ' num2str(pVec(3))], ['$p = $ ' num2str(pVec(4))], ...
    'Desired Beampattern', 'Interpreter','Latex', 'FontSize', 11, 'location', 's')
grid minor
box on

% - Spatial Domain Spectral Result
SStar                       = repmat(flip(cell2mat(sBarStar(1,:))).',1,N) .* sTildeStar/(sTildeStar(1));
FFTs                        = F*padarray(SStar,[0 nHat-N], 0,'post').';
FFTsAmp                     = abs(FFTs);

fhdl(9)                     = figure('Name','Spectral Result','NumberTitle','off',...
    'Position', [0 0 floor(ScreenSize(3)/3) floor(ScreenSize(4)/3.5)]);
movegui('north')

idxStop = sum(linspace(0,1,nHat) <= Ud.',2);
idxPass = setdiff(1:nHat,idxStop(1):idxStop(2));

plot(linspace(0,1,nHat),mean(20*log10(FFTsAmp),2), 'LineWidth',2, 'color', 'blue'),hold on
plot(linspace(0,1,nHat),20*log10(FFTSpectralDeng * mean(FFTsAmp(idxPass)) / mean(FFTSpectralDeng(idxPass))), 'LineWidth',2, 'color', 'red')
plot(linspace(0,1,nHat),20*log10(FFTSpectralALAEE * mean(FFTsAmp(idxPass)) / mean(FFTSpectralALAEE(idxPass))), 'LineWidth',2, 'color', 'green')
yline(20*log10(gamma) ,'--','LineWidth',2.5, 'color', 'magenta')
xline(Ud(1),':k','LineWidth',2.5)
xline(Ud(2),':k','LineWidth',2.5)
xlabel('Normalized Frequency (Hz)','FontSize',11,'Interpreter','Latex')
ylabel('Spectrum (dB)','FontSize',11,'Interpreter','Latex')
legend('Proposed Spectral Response', 'DENG [19]', 'ALAEE [20]', '$\gamma$', 'Interpreter','Latex', 'FontSize', 11, 'location', 'sw')
grid minor

%%  MSE, ISL, and PSL Results

PSL                         = zeros(1,length(pVec));
ISL                         = zeros(1,length(pVec));
MSE                         = zeros(1,length(pVec));

fprintf('\n=============== MSE, ISL, and PSL Result ===============\n');
for i = 1:length(pVec)

    fprintf('------------------------ p = %2d ------------------------\n', pVec(i));
    SStar = repmat(flip(cell2mat(sBarStar(i,:))).',1,N) .* sTildeStar/(sTildeStar(1));
    pOpt2D = 1/(Nt*N)*abs(squeeze(sum(conj(APrime).*permute(SStar,[3,4,1,2]),3))).^2;
    POpt2D = sum(pOpt2D,3);
    [Peaks, locX, locY] = peaks2(POpt2D);
    PSL(i) = 10*log10(max(Peaks .* (PDesPrime(sub2ind(size(PDesPrime),locX,locY)) ~= 1)) / max(POpt2D(:)));
    ISL(i) = 10*log10(sum(POpt2D .* (1-PDesPrime), [1 2])/ max(POpt2D(:)));
    MSE(i) = immse(alphaStar(i) * POpt2D(:), PDesPrime(:));

    fprintf('MSE = %.4f, ISL = %.2f dB, and PSL = %.2f dB\n', MSE(i), ISL(i), PSL(i));

end
fprintf('========================================================\n');

%%  Saving the Figures

folderName = 'figs';
if ~exist(folderName, 'dir')
    mkdir(folderName);
end

figureNames = {'ConvCurveFT', 'ConvCurveSpatial', 'BPR2', 'BPR4', 'BPR8', 'BPR16', ...
    'AzCut', 'ElCut', 'SpectralResponse'};

for i = 1:length(fhdl)
    figure(fhdl(i));
    filename = sprintf('%s.pdf', figureNames{i});
    figsFilename = fullfile(folderName, filename);
    exportgraphics(fhdl(i), figsFilename);
end