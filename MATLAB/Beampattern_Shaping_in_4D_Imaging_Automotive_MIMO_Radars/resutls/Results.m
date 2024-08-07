% BEAMPATTERN_SHAPING_FIGURES - Interactive Beampattern Shaping Demonstrations
%
% This script demonstrates the application of the lp_Norm_BP function for
% beampattern shaping across various scenarios, as presented in figures
% within the Beampattern Shaping in 4D-Imaging Automotive MIMO Radars. You
% can interactively select the figure/scenario they wish to visualize and
% have the option to adjust parameters to explore the proposed method's
% performance under different conditions.
%
% Upon execution, the script prompts the user to select a figure number
% corresponding to the results they wish to see. Each figure number is
% associated with a specific beampattern shaping scenario in the associated
% paper.
%
% Usage:
%   - Run the script in MATLAB.
%   - Follow the prompt to select the desired figure number.
%
% Features:
%   - Interactive selection of beampattern shaping scenarios.
%   - Customizable parameters for in-depth analysis.
%   - Visualization of optimized beampatterns and comparison with desired outcomes.
%
% Author:
%   Masoud DORVASH (masoud.dorvash@gmail.com) and
%   Mohammad ALAEE (mohammad.alaee@uni.lu)
%
% Reference:
%   "Beampattern Shaping in 4D-Imaging Automotive MIMO Radars" by
%   Masoud DORVASH, Mahmoud MODARRES-HASHEMI, and Mohammad ALAEE-KERAHROODI.

%%  PreProcessing
clear, close all
clc
%%  Initializing

scriptDir       = fileparts(mfilename('fullpath'));
cd(scriptDir);
parentDir       = fullfile(pwd, '..');
mainFcn         = fullfile(parentDir, 'main functions');
compData        = fullfile(parentDir, 'comparision data');
addpath(mainFcn, compData);

figSelector, uiwait()

if isempty(whos('figureNum'))
    return
end

%% Figure 3

if any(3 == figureNum)

    fprintf(' Figure 3 ...\n');

    %  Initializing

    Mt                      = 8;
    Nc                      = 32;
    theta                   = -90:90;
    thetaDes                = [-20 20];
    pVec                    = [0.25 3];
    lVec                    = [8 inf];
    maxIter                 = 100;

    % - Pre Allocation
    solConvCyclic           = zeros(length(pVec),length(lVec),maxIter);
    solConvMBI              = zeros(length(pVec),length(lVec),maxIter);

    %  Main Code

    % - MBI Selection Rule
    for i = 1:length(pVec)

        p = pVec(i);

        for j = 1:length(lVec)

            L = lVec(j);
            [~, ~, ~, solConvMBI(i,j,:)] = lp_Norm_BP_MBI(Mt,Nc,p,L,theta,thetaDes,'seed',6,'iter',maxIter,'draw','off','result','off');

        end

    end

    % - Cyclic Selection Rule
    for i = 1:length(pVec)

        p = pVec(i);

        for j = 1:length(lVec)

            L = lVec(j);
            [~, ~, ~, solConvCyclic(i,j,:)] = lp_Norm_BP(Mt,Nc,p,L,theta,thetaDes,'seed',6,'iter',maxIter,'draw','off','result','off');

        end

    end

    %  Plot Resutls

    ScreenSize              = get(0,'ScreenSize');
    markers                 = ['d', 'o', 's', 'v'];

    fhdl(1)                 = figure('Name','Figure 3a (Solution Convergence Curve - MBI)','NumberTitle','off',...
        'Position', [0 0 floor(ScreenSize(3)/3) floor(ScreenSize(4)/3)]);
    movegui('west')

    grid on
    xlabel('Iteration','Interpreter','latex','FontSize',12')
    ylabel('Normalized $\Delta \mathbf{S}$','Interpreter','latex','FontSize',12')
    xlim([1 inf])
    hold on

    counter = 0;

    for i = 1:length(lVec)

        for j = 1:length(pVec)

            counter = counter + 1;

            columnData = squeeze(solConvMBI(j,i,:));

            plot(1:length(columnData),columnData/max(columnData), ...
                ['-', markers(counter)], 'LineWidth', 2, 'MarkerSize', 8,'MarkerIndices',[1 5:5:maxIter])

        end

    end
    legend('$L = 8$, $p = 0.75$', '$L = 8$, $p = 3$',...
        '$L = \infty$, $p = 0.75$', '$L = \infty$, $p = 3$','Interpreter','latex','Location','Best','FontSize',12)
    box on

    fhdl(2)                 = figure('Name','Figure 3b (Solution Convergence Curve - Cyclic)','NumberTitle','off',...
        'Position', [0 0 floor(ScreenSize(3)/3) floor(ScreenSize(4)/3)]);
    movegui('east')

    grid on
    xlabel('Iteration','Interpreter','latex','FontSize',12')
    ylabel('Normalized $\Delta \mathbf{S}$','Interpreter','latex','FontSize',12')
    xlim([1 inf])
    hold on

    counter = 0;

    for i = 1:length(lVec)

        for j = 1:length(pVec)

            counter = counter + 1;

            columnData = squeeze(solConvCyclic(j,i,:));

            plot(1:length(columnData),columnData/max(columnData), ...
                ['-', markers(counter)], 'LineWidth', 2, 'MarkerSize', 8,'MarkerIndices',[1 5:5:maxIter])

        end

    end
    legend('$L = 8$, $p = 0.75$', '$L = 8$, $p = 3$',...
        '$L = \infty$, $p = 0.75$', '$L = \infty$, $p = 3$','Interpreter','latex','Location','Best','FontSize',12)
    box on

    drawnow
    clearvars -except figureNum

end

%%  Figure 4

if any(4 == figureNum)

    fprintf(' Figure 4 ...\n');

    %  Initializing

    Mt                      = 16;
    Nc                      = 128;
    theta                   = -90:90;
    thetaDes                = [-60 -20];
    pVec                    = [0.75 3];
    lVec                    = [2 4 8 inf];

    % - Pre Allocation
    objfunVal               = zeros(length(pVec),1e4,length(lVec));

    %  Main Code

    for i = 1:length(pVec)

        p = pVec(i);

        for j = 1:length(lVec)

            L = lVec(j);
            [~, ~, objfunVal(i,:,j)] = lp_Norm_BP(Mt,Nc,p,L,theta,thetaDes,'seed',4,'draw','off','result','off');

        end

    end

    %  Plot Restults

    ScreenSize              = get(0,'ScreenSize');
    markers                 = ['d', 'o', 's', 'v'];

    % - Objective Function Convergence for p = 0.75
    fhdl(1)                 = figure('Name','Figure 4a (Convergence Curve, p = 0.75)','NumberTitle','off',...
        'Position', [0 0 floor(ScreenSize(3)/3) floor(ScreenSize(4)/3)]);
    hold on
    movegui('west')
    grid minor
    xlabel('Iteration','Interpreter','latex','FontSize',12)
    ylabel('Normalized Objective Function (dB)','Interpreter','latex','FontSize',12)

    for j = 1:length(lVec)

        columnData = objfunVal(1,:,j);
        nonZeroObjfunVal = columnData(columnData ~= 0);

        plot(0:length(nonZeroObjfunVal)-2,20*log10(nonZeroObjfunVal(1:end-1)/max(nonZeroObjfunVal(1:end-1))), ...
            ['-', markers(j)], 'LineWidth', 2, 'MarkerSize', 8)

    end
    legend('Discrete Phase: $L = 2$','Discrete Phase: $L = 4$','Discrete Phase: $L = 8$','Continuous Phase', ...
        'Interpreter','latex','FontSize',11)
    box on

    % - Objective Function Convergence for p = 3
    fhdl(2)     = figure('Name','Figure 4b (Convergence Curve, p = 3)','NumberTitle','off',...
        'Position', [0 0 floor(ScreenSize(3)/3) floor(ScreenSize(4)/3)]);
    hold on
    movegui('east')
    grid minor
    xlabel('Iteration','Interpreter','latex','FontSize',12)
    ylabel('Normalized Objective Function (dB)','Interpreter','latex','FontSize',12)

    for j = 1:length(lVec)

        columnData = objfunVal(2,:,j);
        nonZeroObjfunVal = columnData(columnData ~= 0);

        plot(0:length(nonZeroObjfunVal)-2,20*log10(nonZeroObjfunVal(1:end-1)/max(nonZeroObjfunVal(1:end-1))), ...
            ['-', markers(j)], 'LineWidth', 2, 'MarkerSize', 8, 'MarkerIndices', [1:5:length(nonZeroObjfunVal)-1 length(nonZeroObjfunVal)-1])

    end
    legend('Discrete Phase: $L = 2$','Discrete Phase: $L = 4$','Discrete Phase: $L = 8$','Continuous Phase', ...
        'Interpreter','latex','FontSize',11)
    box on

    drawnow
    clearvars -except figureNum

end

%%  Figure 5

if any(5 == figureNum)

    fprintf(' Figure 5 ...\n');

    %  Initializing

    Mt                      = 16;
    Nc                      = 128;
    L                       = inf;
    theta                   = -90:90;
    thetaDes                = [-20 20];
    pVec                    = [0.25 0.75 2 3 8];

    % - Pre Allocating
    POpt                    = zeros(length(theta),length(pVec));
    mu                      = zeros(1,length(pVec));
    MSE                     = zeros(1,length(pVec));
    ISL                     = zeros(1,length(pVec));
    PSL                     = zeros(1,length(pVec));

    %  Main Code

    for i = 1:length(pVec)

        p = pVec(i);
        [POpt(:,i), mu(i)] = lp_Norm_BP(Mt,Nc,p,L,theta,thetaDes,'seed',2,'draw','off','result','off');

    end

    %  Plot Results

    PDes                    = designPDes(theta, thetaDes);
    PDesP                   = PDes;
    PDesP(PDesP == 0)       = -100;
    PDesP                   = PDesP - max(PDesP);

    ScreenSize              = get(0,'ScreenSize');
    markers                 = ['d', 'o', 's', 'v', 'pentagram'];
    fhdl(1)                 = figure('Name','Figure 5 (p Effect)','NumberTitle','off',...
        'Position', [0 0 floor(ScreenSize(3)/3) floor(ScreenSize(4)/2.5)]);
    movegui('center')
    hold on
    xlim([-90 90])
    ylim([-60 0])
    xticks(-90:30:90)
    xlabel('Angle (degree$^\circ$)','Interpreter','latex','FontSize',12')
    ylabel('Normalized Beampattern (dB)','Interpreter','latex','FontSize',12')
    grid minor
    for i = 1:length(pVec)

        plot(theta,20*log10(POpt(:,i)/max(POpt(:,i))), ...
            ['-', markers(i)], 'LineWidth', 2, 'MarkerSize', 8, 'MarkerIndices',1:10:length(theta))

    end
    plot(theta,PDesP,'--k','LineWidth',2)
    legend('Optimized Beampattern $p = 0.25$', 'Optimized Beampattern $p = 0.75$', 'Optimized Beampattern $p = 2$', ...
        'Optimized Beampattern $p = 3$', 'Optimized Beampattern $p = 8$', ' Desired Beampattern', ...
        'Interpreter','latex','Location','northoutside','FontSize',12')
    box on

    %  MSE, ISL, and PSL Calculation

    for i = 1:length(pVec)
        % - MSE
        MSE(i) = immse(PDes,mu(i)*POpt(:,i));
        % - ISL
        POptISL            = POpt(:,i);
        POptISL(find(theta == thetaDes(1)):find(theta == thetaDes(2))) = [];
        ISL(i) = 20*log10(sum(POptISL/max(POpt(:,i))));
        % - PSL
        PSLs = sort(findpeaks(POptISL));
        PSL(i) = 20*log10(PSLs(end-1)/max(POpt(:,i)));
    end

    %  Display Results

    fprintf('================ Figure 4 Simulation Results ================\n');
    for i = 1:length(pVec)
        fprintf('MSE (p = %.2f) = %.3f\n', pVec(i), MSE(i));
    end
    fprintf('-------------------------------------------------------------\n');
    for i = 1:length(pVec)
        fprintf('ISL (p = %.2f) = %.2f dB\n', pVec(i), ISL(i));
    end
    fprintf('-------------------------------------------------------------\n');
    for i = 1:length(pVec)
        fprintf('PSL (p = %.2f) = %.2f dB\n', pVec(i), PSL(i));
    end
    fprintf('=============================================================\n');

    drawnow
    clearvars -except figureNum

end

%%  Figure 6 & 7

if any([6 7] == figureNum,'all')

    fprintf(' Figures 6 & 7 ...\n');

    %  Initializing

    Mt              = 16;
    Nc              = 16;

    p               = 3;
    L               = 8;

    theta           = -90:0.5:90;

    thetaDes        = [-20 0];
    PDes            = designPDes(theta, thetaDes);

    simCnt          = 1000;

    % - Pre Allocating
    MSE             = zeros(simCnt,1);
    ISL             = zeros(simCnt,1);
    PSL             = zeros(simCnt,1);
    POpt            = zeros(length(theta),simCnt);

    %  Main Code

    rng(4)

    for i = 1:simCnt

        Sinitial = exp(1i*(2*pi*rand(Mt,Nc)));

        [POpt(:,i), mu] = lp_Norm_BP(Mt,Nc,p,L,theta,thetaDes, ...
            'draw','off','result','off','InitialPoint',Sinitial);

        MSE(i) = immse(PDes,mu*POpt(:,i));

        ISLrange = POpt(:,i);
        ISLrange(PDes ~= 0) = [];
        ISL(i) = 20*log10(sum(ISLrange/max(POpt(:,i))));

        PSLs = sort(findpeaks(ISLrange));
        PSL(i) = 20*log10(PSLs(end-1)/max(POpt(:,i)));

    end

    %  Plot Results

    ScreenSize      = get(0,'ScreenSize');

    % - Criteria
    fhdl(1)         = figure('Name','Figure 6a (MSE Box Plot)','NumberTitle','off',...
        'Position', [0 0 floor(ScreenSize(3)/4) floor(ScreenSize(4)/3)]);
    movegui('northwest')
    boxplot(MSE)
    ax              = gca;
    ax.XTickLabel   = [];
    xlabel('MSE','Interpreter', 'Latex','FontSize',12)

    fhdl(2)         = figure('Name','Figure 6b (ISL Box Plot)','NumberTitle','off',...
        'Position', [0 0 floor(ScreenSize(3)/4) floor(ScreenSize(4)/3)]);
    movegui('north')
    boxplot(ISL)
    ax              = gca;
    ax.XTickLabel   = [];
    xlabel('ISL','Interpreter', 'Latex','FontSize',12)

    fhdl(3)         = figure('Name','Figure 6c (PSL Box Plot)','NumberTitle','off',...
        'Position', [0 0 floor(ScreenSize(3)/4) floor(ScreenSize(4)/3)]);
    movegui('northeast')
    boxplot(PSL)
    ax              = gca;
    ax.XTickLabel   = [];
    xlabel('PSL','Interpreter', 'Latex','FontSize',12)

    % - Beampattern
    Q25             = quantile(20*log10(POpt/max(POpt(:))),0.25,2);
    Q75             = quantile(20*log10(POpt/max(POpt(:))),0.75,2);

    fhdl(4)         = figure('Name','Figure 7a (Median, 25-th and 75-th Percentile)','NumberTitle','off',...
        'Position', [0 0 floor(ScreenSize(3)/3) floor(ScreenSize(4)/3)]);
    movegui('center')

    h(1)            = plot(theta,Q75,'LineWidth',2,'LineStyle',':','Color', [0.8500 0.3250 0.0980]);
    hold on
    h(2)            = plot(theta,Q25,'LineWidth',2,'LineStyle',':','Color', [0.9290 0.6940 0.1250]);
    h(3)            = plot(theta,median(20*log10(POpt/max(POpt(:))),2),'LineStyle','--','LineWidth',2,'Color',[0 0.4470 0.7410]);
    legend(flip(h), 'Median', '$25$-th Percentile', '$75$-th Percentile','Interpreter', 'Latex','FontSize',11)
    xlim([-90 90])
    xticks(-90:30:90)
    ylim([-35 0])
    xlim([-90 90])
    grid minor
    ylabel('Normalized Beampattern (dB)','Interpreter', 'Latex','FontSize',12)

    % - Dleta Q
    fhdl(5)         = figure('Name','Figure 7b (Dleta Q)','NumberTitle','off',...
        'Position', [floor(ScreenSize(3)/2)-floor(ScreenSize(3)/6)  floor(ScreenSize(4)/9) ...
        floor(ScreenSize(3)/3) floor(ScreenSize(4)/10)]);
    plot(theta,Q75-Q25,'LineWidth',2)
    xlim([-90 90])
    ylim([0 3])
    xticks(-90:30:90)
    grid minor
    ylabel('$\Delta Q$ (dB)','Interpreter','Latex','FontSize',12)
    xlabel('Angles (degree $^\circ$)','Interpreter','Latex','FontSize',12)

    drawnow
    clearvars -except figureNum

end

%%  Figure 8 & 9

if any([8 9] == figureNum,'all')

    fprintf(' Figures 8 & 9 ...\n');

    %  Initializing

    Mt                      = 16;
    Nc                      = 128;
    theta                   = -90:90;
    thetaDes                = [30 60];
    p                       = 3;
    lVec                    = [2 4 8 inf];

    % - Pre Allocating
    POpt                    = zeros(length(theta),length(lVec));
    mu                      = zeros(1,length(lVec));
    MSE                     = zeros(1,length(lVec));
    ISL                     = zeros(1,length(lVec));
    PSL                     = zeros(1,length(lVec));

    %  Main Code

    for i = 1:length(lVec)

        L = lVec(i);
        [POpt(:,i), mu(i)] = lp_Norm_BP(Mt,Nc,p,L,theta,thetaDes,'seed',4,'draw','off','result','off');

    end

    %  MSE, ISL, and PSL Calculation

    PDes                    = designPDes(theta, thetaDes);

    for i = 1:length(lVec)
        % - MSE
        MSE(i) = immse(PDes,mu(i)*POpt(:,i));
        % - ISL
        POptISL = POpt(:,i);
        POptISL(find(theta == thetaDes(1)):find(theta == thetaDes(2))) = [];
        ISL(i) = 20*log10(sum(POptISL/max(POpt(:,i))));
        % - PSL
        PSLs = sort(findpeaks(POptISL));
        PSL(i) = 20*log10(PSLs(end-1)/max(POpt(:,i)));
    end

    PSL(1)                  = 0;

    %  Plot Results

    PDesP                   = PDes;
    PDesP(PDesP == 0)       = -100;
    PDesP                   = PDesP - max(PDesP);

    ScreenSize              = get(0,'ScreenSize');
    fhdl(1)                 = figure('Name','Figure 8 (L Effect on Beampattern)','NumberTitle','off',...
        'Position', [0 0 floor(ScreenSize(3)/3) floor(ScreenSize(4)/2.5)]);
    movegui('west')
    plot(theta,20*log10(POpt(:,1)/max(POpt(:,1))),'-d','MarkerIndices',1:10:length(theta),'markersize',8,'LineWidth',2), hold on
    plot(theta,20*log10(POpt(:,2)/max(POpt(:,2))),'-o','MarkerIndices',1:10:length(theta),'markersize',8,'LineWidth',2)
    plot(theta,20*log10(POpt(:,3)/max(POpt(:,3))),'-s','MarkerIndices',1:10:length(theta),'markersize',8,'LineWidth',2)
    plot(theta,20*log10(POpt(:,4)/max(POpt(:,4))),'-v','MarkerIndices',1:10:length(theta),'markersize',8,'LineWidth',2)
    plot(theta,PDesP,'--k','LineWidth',2)
    grid minor
    xlim([-90 90])
    ylim([-60 0])
    xticks(-90:30:90)
    xlabel('Angle (degree$^\circ$)','Interpreter','latex','FontSize',12')
    ylabel('Normalized Beampattern (dB)','Interpreter','latex','FontSize',12')
    legend('Optimized Beampattern $L = 2$', 'Optimized Beampattern $L = 4$', 'Optimized Beampattern $L = 8$', ...
        'Optimized Beampattern $L = \infty$', ' Desired Beampattern', ...
        'Interpreter','latex','Location','northoutside','FontSize',12')
    box on


    fhdl(2)             = figure('Name','Figure 9 (L Effect on MSE, ISL, and PSL)','NumberTitle','off',...
        'Position', [0 0 floor(ScreenSize(3)/3) floor(ScreenSize(4)/3)]);
    movegui('east')
    plot([2 4 8 32],20*log10(MSE/max(MSE)),'-d','LineWidth',2,'markersize',8), hold on
    plot([2 4 8 32],20*log10(ISL/max(ISL)),'-o','LineWidth',2,'markersize',8)
    plot([2 4 8 32],PSL,'-s','LineWidth',2,'markersize',8)
    legend('MSE','ISL','PSL', 'Interpreter','latex','Location','best','FontSize',11)
    xlabel('$L$','Interpreter','latex','FontSize',12')
    ylabel('Normalized Magnitude (dB)','Interpreter','latex','FontSize',12')
    grid minor
    xticks([2 4 8 32])
    xticklabels({'2','4','8','\infty'})
    box on

    drawnow
    clearvars -except figureNum

end

%%  Figure 10

if any(10 == figureNum)

    fprintf(' Figure 10 ...\n');

    %  Initializing

    MtVec                       = 2.^(1:7);
    Mt                          = 16;
    NcVec                       = 2.^(1:7);
    Nc                          = 16;
    theta                       = -90:90;
    thetaDes                    = [30 60];
    p                           = 0.75;
    L                           = inf;
    Nmc                         = 48;

    % - parfor Pre Initialization
    poolobj = gcp('nocreate');
    if isempty(poolobj)
        c = parcluster;
        c.NumWorkers = 6;
        parpool(c)
    end

    % - Pre Allicating
    POpt                        = zeros(length(theta),length(MtVec));
    PDes                        = designPDes(theta, thetaDes);

    MSEmT                       = zeros(size(MtVec));
    MSEnC                       = zeros(size(NcVec));

    %  Main Code

    % - Fixed Nc
    for i = 1:length(MtVec)

        mT = MtVec(i);

        parfor j = 1:Nmc

            [POpt, mu] = lp_Norm_BP(mT,Nc,p,L,theta,thetaDes,'draw','off','result','off');

            MSEmT(j,i) = immse(mu*POpt,PDes);

        end

    end

    % - Fixed Mt
    for i = 1:length(NcVec)

        nC = NcVec(i);

        parfor j = 1:Nmc

            [POpt, mu] = lp_Norm_BP(Mt,nC,p,L,theta,thetaDes,'draw','off','result','off');

            MSEnC(j,i) = immse(mu*POpt,PDes);

        end

    end

    %  Plot Results

    ScreenSize  = get(0,'ScreenSize');
    fhdl(1)     = figure('Name','Figure 10 (Sequence Length Effect)','NumberTitle','off',...
        'Position', [0 0 floor(ScreenSize(3)/3) floor(ScreenSize(4)/3)]);
    movegui('center')
    semilogy(Nc*MtVec,mean(MSEmT,1),'-d','LineWidth',2,'MarkerSize', 8), hold on
    semilogy(Mt*NcVec,mean(MSEnC,1),'-o','LineWidth',2,'MarkerSize', 8)
    grid on
    xlabel('Sequence Length ($M_t \times N_c$)','Interpreter','latex','FontSize',12')
    ylabel('Mean Square Error (MSE)','Interpreter','latex','FontSize',12')
    legend('Fixed $N_c$', 'Fixed $M_t$','Interpreter','latex','Location','Best','FontSize',12)
    xticks([32 256 512 1024 2048])
    xlim([32 2048])

    drawnow
    clearvars -except figureNum

end

%%  Figure 11 (Results Only)

if any(11 == figureNum)

    fprintf(' Figure 11 ...\n');

    %  Initialization

    theta                       = -90:90;
    load PDesComp
    load POptProposed
    load POptUniqueC3
    load POptADMM
    load POptDrone
    load POptPseudoCM

    %  MSE Calculations

    MSEProposed                 = immse(POptProposed,PDesComp);
    MSEUniqueC3                 = immse(POptUniqueC3,PDesComp);
    MSEADMM                     = immse(POptADMM,PDesComp);
    MSEDrone                    = immse(POptDrone,PDesComp);
    MSEPseudoCM                 = immse(POptPseudoCM,PDesComp);

    %  ISL Calculations

    ISLrangeProposed            = POptProposed;
    ISLrangeProposed(71:111)    = [];
    ISLProposed                 = 20*log10(sum(ISLrangeProposed/max(POptProposed)));

    ISLrangeUniqueC3            = POptUniqueC3;
    ISLrangeUniqueC3(71:111)    = [];
    ISLUniqueC3                 = 20*log10(sum(ISLrangeUniqueC3/max(POptUniqueC3)));

    ISLrangeADMM                = POptADMM;
    ISLrangeADMM(71:111)        = [];
    ISLADMM                     = 20*log10(sum(ISLrangeADMM/max(POptADMM)));

    ISLrangeDrone               = POptDrone;
    ISLrangeDrone(71:111)       = [];
    ISLDrone                    = 20*log10(sum(ISLrangeDrone/max(POptDrone)));

    ISLrangePseudoCM            = POptPseudoCM;
    ISLrangePseudoCM(71:111)    = [];
    ISLPseudoCM                 = 20*log10(sum(ISLrangePseudoCM/max(POptPseudoCM)));


    %  PSL Calculations

    PSLs                        = sort(findpeaks(ISLrangeProposed));
    PSLProposed                 = 20*log10(PSLs(end-1)/max(POptProposed));

    PSLs                        = sort(findpeaks(ISLrangeUniqueC3));
    PSLUniqueC3                 = 20*log10(PSLs(end-1)/max(POptUniqueC3));

    PSLs                        = sort(findpeaks(ISLrangeADMM));
    PSLADMM                     = 20*log10(PSLs(end-1)/max(POptADMM));

    PSLs                        = sort(findpeaks(ISLrangeDrone));
    PSLDrone                    = 20*log10(PSLs(end-1)/max(POptADMM));

    PSLs                        = sort(findpeaks(ISLrangePseudoCM));
    PSLPseudoCM                 = 20*log10(PSLs(end-1)/max(POptPseudoCM));

    %  Plot Results

    PDesP                       = PDesComp;
    PDesP(PDesP == 0)           = -100;
    PDesP                       = PDesP - max(PDesP);

    ScreenSize                  = get(0,'ScreenSize');
    fhdl(1)                     = figure('Name','Figure 11 (Comparison)','NumberTitle','off',...
        'Position', [0 0 floor(ScreenSize(3)/3) floor(ScreenSize(4)/2.5)]);
    movegui('center')
    plot(theta,(20*log10(POptProposed/max(POptProposed))),'-d','MarkerIndices',1:10:length(theta),'markersize',8,'LineWidth',2), hold on
    plot(theta,(20*log10(POptUniqueC3/max(POptUniqueC3))),'-o','MarkerIndices',1:10:length(theta),'markersize',8,'LineWidth',2)
    plot(theta,(20*log10(POptADMM/max(POptADMM))),'-s','MarkerIndices',1:10:length(theta),'markersize',8,'LineWidth',2)
    plot(theta,(20*log10(POptDrone/max(POptDrone))),'-v','MarkerIndices',1:10:length(theta),'markersize',8,'LineWidth',2)
    plot(theta,(20*log10(POptPseudoCM/max(POptPseudoCM))),'-+','MarkerIndices',1:10:length(theta),'markersize',8,'LineWidth',2)
    plot(theta,PDesP,'--k','LineWidth',2)
    grid minor
    xlim([-90 90])
    ylim([-50 0])
    xticks(-90:30:90)
    xlabel('Angle (degree$^\circ$)','Interpreter','latex','FontSize',12)
    ylabel('Normalized Beampattern (dB)','Interpreter','latex','FontSize',12)
    legend('Proposed Method', 'UNIQUE $C3$ [21]', 'ADMM [8]', 'Drone Swarm [20]', 'Pseudo-CM [15]', ...
        'Desired Beampattern','Interpreter','latex','Location','northoutside','FontSize', 12,'NumColumns',2)

    %  Display Results

    fprintf('=================== Figure 11 Comparision ===================\n');
    fprintf('MSE Proposed = %.2f\n', MSEProposed);
    fprintf('MSE UNIQUE C3 = %.2f\n', MSEUniqueC3);
    fprintf('MSE ADMM = %.2f\n', MSEADMM);
    fprintf('MSE Drone Swarm = %.2f\n', MSEDrone);
    fprintf('MSE Pseudo-CM = %.2f\n', MSEPseudoCM);
    fprintf('-------------------------------------------------------------\n');
    fprintf('ISL Proposed = %.2f dB\n', ISLProposed);
    fprintf('ISL UNIQUE C3 = %.2f dB\n', ISLUniqueC3);
    fprintf('ISL ADMM = %.2f dB\n', ISLADMM);
    fprintf('ISL Drone Swarm = %.2f dB\n', ISLDrone);
    fprintf('ISL Pseudo-CM = %.2f dB\n', ISLPseudoCM);
    fprintf('-------------------------------------------------------------\n');
    fprintf('PSL Proposed = %.2f dB\n', PSLProposed);
    fprintf('PSL UNIQUE C3 = %.2f dB\n', PSLUniqueC3);
    fprintf('PSL ADMM = %.2f dB\n', PSLADMM);
    fprintf('PSL Drone Swarm = %.2f dB\n', PSLDrone);
    fprintf('PSL Pseudo-CM = %.2f dB\n', PSLPseudoCM);
    fprintf('=============================================================\n');

    drawnow
    clearvars -except figureNum

end

%%  Figure 12 & 13

if any([12 13] == figureNum,'all')

    fprintf(' Figures 12 & 13 ...\n');

    %  Initializing

    Mt                  = 16;
    mtVec               = 1:Mt;
    c                   = 3e8;
    fc                  = 77e9;
    lambda              = c/fc;
    d                   = lambda/2;
    steeringTheta       = -50:-30;
    theta               = -90:90;
    thetaDes            = [30 60];
    Nc                  = 128;
    L                   = inf;
    p                   = 2;

    % - Tylor Windowing
    Fc                  = 1/2*sind(1.05*max(15));
    flag                = 'scale';
    Nbar                = 4;
    SidelobeLevel       = -30;

    win                 = taylorwin(Mt, Nbar, SidelobeLevel);
    b                   = fir1(Mt-1, Fc, 'low', win, flag).';

    % - rx Steering Vector
    steeringVec         = 1 .* permute(exp(-1i*2*pi*d/lambda*sin(deg2rad(steeringTheta)).'*(0:Mt-1)),[2,3,1]);

    AF                  = abs(sum(exp(1i*2*pi*d/lambda*(mtVec-1)'.*sind(theta)) .* steeringVec));
    AFamp               = squeeze(sum(AF,3));
    AFmag               = (AFamp/max(AFamp));

    %  Main Code

    POptTx              = lp_Norm_BP(Mt,Nc,p,L,theta,thetaDes,'seed',4,'draw','off','result','off');

    %  Plot Results

    POptTx2D            = repmat(POptTx/max(POptTx),1,size(AF,2));

    ScreenSize          = get(0,'ScreenSize');

    % - Transmitting 2D Beampattern
    fhdl(1)             = figure('Name','Figure 12a (tx Beampattern)','NumberTitle','off',...
        'Position', [0 0 floor(ScreenSize(3)/3) floor(ScreenSize(4)/2.5)]);
    movegui('west')
    imagesc(-90:90,-90:90,POptTx2D')
    colorbar
    set(gca,'YDir','normal')
    xlabel('Azimuth ($\theta_{\mathrm{az}}$, degree $^\circ$)','Interpreter','latex','FontSize',12)
    ylabel('Elevation ($\theta_{\mathrm{el}}$, degree $^\circ$)','Interpreter','latex','FontSize',12)
    xlim([-90 90])
    ylim([-90 90])
    xticks(-90:30:90)
    yticks(-90:30:90)

    % - Receiving 2D Beampattern
    AFRx2D              = repmat(AFmag,size(POptTx,1),1);
    fhdl(2)             = figure('Name','Figure 12b (rx Beampattern)','NumberTitle','off',...
        'Position', [0 0 floor(ScreenSize(3)/3) floor(ScreenSize(4)/2.5)]);
    movegui('east')
    imagesc(-90:90,-90:90,AFRx2D')
    colorbar
    set(gca,'YDir','normal')
    xlabel('Azimuth ($\theta_{\mathrm{az}}$, degree $^\circ$)','Interpreter','latex','FontSize',12)
    ylabel('Elevation ($\theta_{\mathrm{el}}$, degree $^\circ$)','Interpreter','latex','FontSize',12)
    xlim([-90 90])
    ylim([-90 90])
    xticks(-90:30:90)
    yticks(-90:30:90)

    % - tx rx 2D Beampattern
    fhdl(3)             = figure('Name','Figure 13 (tx rx Beampattern)','NumberTitle','off',...
        'Position', [0 0 floor(ScreenSize(3)/3) floor(ScreenSize(4)/2.5)]);
    movegui('center')
    txrxBP = POptTx2D'.*AFRx2D';
    imagesc(-90:90,-90:90,(txrxBP/max(txrxBP(:))))
    colorbar
    set(gca,'YDir','normal')
    xlabel('Azimuth (degree $^\circ$)','Interpreter','latex','FontSize',12)
    ylabel('Elevation (degree $^\circ$)','Interpreter','latex','FontSize',12)
    xlim([-90 90])
    ylim([-90 90])
    xticks(-90:30:90)
    yticks(-90:30:90)

    drawnow
    clearvars -except figureNum

end

%%  Figure 14 & 15

if any([14 15] == figureNum,'all')

    fprintf(' Figures 14 & 15 ...\n');

    %  Initializing

    MtX         = 8;
    MtY         = 8;
    Nc          = 8;
    p           = 2;
    L           = inf;

    thetaAz     = (-90:0.5:90)';
    thetaEl     = -90:0.5:90;
    thetaAzDes  = [-60 -31 ; 31 60];
    thetaElDes  = [-60 -31 ; 31 60];

    POpt = lp_Norm_BP_URA(MtX,MtY,Nc,p,L, ...
        thetaAz,thetaAzDes,thetaEl,thetaElDes,'seed',4,'result','off','draw','off');

    %  Plot Results

    ScreenSize              = get(0,'ScreenSize');

    % - 2D Beampattern
    fhdl(1)                 = figure('Name','Figure 14 (2D Beampattern)','NumberTitle','off',...
        'Position', [0 0 floor(ScreenSize(3)/3) floor(ScreenSize(4)/2.5)]);
    movegui('center')
    imagesc(thetaAz,thetaEl,POpt/max(POpt(:)))
    xlim([-90 90])
    ylim([-90 90])
    xticks(-90:30:90)
    yticks(-90:30:90)
    xlabel('Azimuth ($\theta_{\mathrm{az}}$, degree $^\circ$)','Interpreter','latex','FontSize',12)
    ylabel('Elevation ($\theta_{\mathrm{el}}$, degree $^\circ$)','Interpreter','latex','FontSize',12)
    colorbar
    set(gca,'YDir','normal')

    % - Azimuth Cut
    PDesAz                  = designPDes(thetaAz, [-60 -30]);
    PDesPAz                 = PDesAz;
    PDesPAz(PDesPAz == 0)   = -100;
    PDesPAz                 = PDesPAz - max(PDesPAz);
    AzCut                   = POpt(:,thetaAz == -44);

    fhdl(2)                 = figure('Name','Figure 15a (Azimuth Cut at -44 degree)','NumberTitle','off',...
        'Position', [0 0 floor(ScreenSize(3)/4) floor(ScreenSize(4)/2.5)]);
    movegui('east')
    plot(thetaEl,20*log10(AzCut/max(AzCut(:))),'LineWidth',2), hold on
    plot(thetaEl,PDesPAz,'--k','LineWidth',2)
    xlabel('Elevation ($\theta_{\mathrm{el}}$, degree $^\circ$)','Interpreter','latex','FontSize',12)
    ylabel('Normalized Beampattern (dB)','Interpreter','latex','FontSize',12)
    grid minor
    xlim([-90 90])
    ylim([-62 0])
    xticks(-90:30:90)
    legend('Optimized Beampattern ($\theta_{\mathrm{az}} = -44^\circ$)', 'Desired Beampattern', ...
        'Interpreter','latex','Location','south','FontSize',12')
    box on

    % - Elevation Cut
    PDesEl                  = designPDes(thetaEl, [30 60]);
    PDesPEl                 = PDesEl;
    PDesPEl(PDesPEl == 0)   = -100;
    PDesPEl                 = PDesPEl - max(PDesPEl);
    ElCut                   = POpt(:,thetaEl == 50);

    fhdl(3)                 = figure('Name','Figure 15b (Elevation Cut at 50 degree)','NumberTitle','off',...
        'Position', [0 0 floor(ScreenSize(3)/4) floor(ScreenSize(4)/2.5)]);
    movegui('west')
    plot(thetaAz,20*log10(ElCut/max(ElCut(:))),'LineWidth',2), hold on
    plot(thetaAz,PDesPEl,'--k','LineWidth',2)
    xlabel('Azimuth ($\theta_{\mathrm{az}}$, degree $^\circ$)','Interpreter','latex','FontSize',12)
    ylabel('Normalized Beampattern (dB)','Interpreter','latex','FontSize',12)
    grid minor
    xlim([-90 90])
    ylim([-62 0])
    xticks(-90:30:90)
    legend('Optimized Beampattern ($\theta_{\mathrm{el}} = 50^\circ$)', 'Desired Beampattern', ...
        'Interpreter','latex','Location','south','FontSize',12')
    box on

    drawnow
    clearvars -except figureNum

end

%%  Figure 17

if any(17 == figureNum)

    fprintf(' Figure 17 ...\n');

    %  Initializing

    ScreenSize          = get(0,'ScreenSize');
    theta               = -90:90;
    Mt                  = 16;
    Nc                  = 128;
    rMax                = 150;
    fc                  = 77e9;
    c                   = 3e8;
    lambda              = c/fc;
    vMax                = 16;
    Tc                  = lambda/(4*vMax);
    d                   = lambda/2;
    p                   = 2;
    L                   = inf;
    thetaDes            = [-15 15];
    B                   = 150e6;
    carRange            = 120;
    carVelocity         = 0;
    carAngle            = -10;

    % - Data Loading
    load BPcruiseUniqueC3
    load BPcruiseADMM
    load BPcruisePseudoCM

    %  Main Code

    [POpt, ~, ~, ~, S]  = lp_Norm_BP(Mt,Nc,p,L,theta,thetaDes,'seed',4,'draw','off','result','off');

    %  SNR Calculation (Angle Velocity)

    % - all Angles and Velocities Signal Pre ProcessingPt
    mtVec               = permute(1:Mt,[1,3,2]);
    range               = carRange;
    NcVec               = 0:Nc-1;
    velocityVec         = permute(-vMax:vMax,[1,3,4,5,6,2]);
    angleVec            = permute(-90:90,[1,3,4,5,6,7,2]);
    nVrVec              = (mtVec-1);

    % - Power Parameters
    KBoltz              = physconst('Boltzmann');
    PtdBm               = 12;
    Pt                  = 10^(PtdBm/10 - 3);
    Gt                  = 10;
    Gr                  = 10;
    RCS                 = 10;
    Rt                  = range;
    N0                  = KBoltz*(23+273);
    NoiseFiguredB       = 15;

    Pr                  = Pt*Gt*Gr*lambda^2*RCS/((4*pi)^3.*Rt.^4);

    % - Received Signal for all Angles and Velocities
    rxSig               = permute(S,[3,2,1]) .* sqrt(Pr) .* exp(-1i .* 4.*pi.*velocityVec.*Tc./lambda.*NcVec) ...
        .* exp(1i * 2*pi*d.*nVrVec.*sind(angleVec)/lambda);
    rxSigAntenna        = abs(squeeze(sum(rxSig,[3 , 4]))).^2;

    % - SNR
    DoppGain            = 10*log10(Nc);
    TBPGain             = 10*log10(B*Tc);
    NoisedB             = 10*log10(B*N0);
    LossdB              = 6;
    rxSNRdB             = 10*log10(squeeze(mean(rxSigAntenna(:,:,:)))) ...
        - NoiseFiguredB - NoisedB - LossdB ...
        + DoppGain + TBPGain;

    % - Angle Velocity SNR Map
    fhdl(1)             = figure('Name','Figure 17b (Scenario 1 - Angle Velocity SNR Map)','NumberTitle','off',...
        'Position', [0 0 floor(ScreenSize(3)/3) floor(ScreenSize(4)/2.5)]);
    movegui('center')
    imagesc(-90:90,-vMax:vMax,rxSNRdB), hold on
    plot(carAngle,carVelocity,'rx','MarkerSize',10,'LineWidth',2)
    [~, velocityIdx] = min(abs(diff(-vMax:vMax - carVelocity)));
    angleIdx = -90:90 == carAngle;
    text(carAngle + 5, carVelocity, sprintf('\\bf{%.1f dB}', rxSNRdB(velocityIdx,angleIdx)), 'Color', 'red', 'Interpreter', 'latex', 'FontSize', 12)
    colorbar
    set(gca,'YDir','normal')
    xlabel('Angle (degree $^\circ$)','Interpreter','latex','FontSize',12')
    ylabel('Velocity (m/s)','Interpreter','latex','FontSize',12')
    xlim([-90 90])
    ylim([-vMax vMax])

    %  SNR Calculation (Range Angle)

    % - all Ranges and Velocities Signal Pre Processing
    rVec                = permute(1:rMax,[1,3,4,5,2]);
    velocity            = carVelocity;

    % - Power Parameters
    Rt                  = rVec;
    Pr                  = Pt*Gt*Gr*lambda^2*RCS/((4*pi)^3.*Rt.^4);

    % - Received Signal Power for all Angles and Ranges
    rxSig               = permute(S,[3,2,1]) .* sqrt(Pr) .* exp(-1i .* 4.*pi.*velocity.*Tc./lambda.*NcVec) ...
        .* exp(1i * 2*pi*d.*nVrVec.*sind(angleVec)/lambda);
    rxSigAntenna        = abs(squeeze(sum(rxSig,[3 , 4]))).^2;

    % - SNR
    DoppGain            = 10*log10(Nc);
    TBPGain             = 10*log10(B*Tc);
    NoisedB             = 10*log10(B*N0);
    LossdB              = 6;
    rxSNRdB             = 10*log10(squeeze(mean(rxSigAntenna(:,:,:)))) ...
        - NoiseFiguredB - NoisedB - LossdB ...
        + DoppGain + TBPGain;

    % - Angle Range SNR Map
    fhdl(2)             = figure('Name','Figure 17a (Scenario 1 - Angle Range SNR Map)','NumberTitle','off',...
        'Position', [0 0 floor(ScreenSize(3)/3) floor(ScreenSize(4)/2.5)]);
    movegui('west')
    imagesc(-90:90,1:rMax,rxSNRdB), hold on
    plot(carAngle,carRange,'rx','MarkerSize',10,'LineWidth',2)
    rangeIdx = 1:200 == carRange;
    text(carAngle + 5, carRange, sprintf('\\bf{%.1f dB}', rxSNRdB(rangeIdx,angleIdx)), 'Color', 'red', 'Interpreter', 'latex', 'FontSize', 12)
    colorbar
    set(gca,'YDir','normal')
    xlabel('Angle (degree $^\circ$)','Interpreter','latex','FontSize',12')
    ylabel('Range (m)','Interpreter','latex','FontSize',12')
    xlim([-90 90])
    ylim([0 rMax])

    %  Beampattern

    % - Omnidirectional Corresponding Code
    SOmni               = repmat(hadamard(Mt),1,Nc/Mt);

    rxSigOmni           = permute(SOmni,[3,2,1]) .* sqrt(Pr) .* exp(-1i .* 4.*pi.*velocity.*Tc./lambda.*NcVec) ...
        .* exp(-1i * 2*pi*d.*nVrVec.*sind(angleVec)/lambda);
    rxSigAntennaOmni    = abs(squeeze(sum(rxSigOmni,[3 , 4]))).^2;

    % - SNR
    DoppGain            = 10*log10(Nc);
    TBPGain             = 10*log10(B*Tc);
    NoisedB             = 10*log10(B*N0);
    LossdB              = 6;
    rxSNRdBOmni             = 10*log10(squeeze(mean(rxSigAntennaOmni(:,:,:)))) ...
        - NoiseFiguredB - NoisedB - LossdB ...
        + DoppGain + TBPGain;

    % - Target SNR
    tarSNROmni          = rxSNRdBOmni(rangeIdx,angleIdx);
    tarSNR              = rxSNRdB(rangeIdx,angleIdx);


    fhdl(3)             = figure('Name','Figure 17c (Scenario 1 - Beampatterns)','NumberTitle','off',...
        'Position', [0 0 floor(ScreenSize(3)/3) floor(ScreenSize(4)/2.5)]);
    movegui('east')

    % - Polar Plot
    polarplot(deg2rad(-90:90),20*log10(POpt),'-d','MarkerIndices',1:10:length(theta),'markersize',7,'LineWidth',1.5), hold on
    polarplot(deg2rad(-90:90),20*log10(BPcruiseUniqueC3),'-o','MarkerIndices',1:10:length(theta),'markersize',7,'LineWidth',1.5)
    polarplot(deg2rad(-90:90),20*log10(BPcruiseADMM),'-s','MarkerIndices',1:10:length(theta),'markersize',7,'LineWidth',1.5)
    polarplot(deg2rad(-90:90),20*log10(BPcruisePseudoCM),'-v','MarkerIndices',1:10:length(theta),'markersize',7,'LineWidth',1.5)
    polarplot(deg2rad(-90:90),zeros(size(theta)),'--k','LineWidth',1.5)
    legend('Proposed Method', 'UNIQUE $C3$ [21]', 'ADMM [8]', ...
        'Pseudo-CM [15]', 'Orthogonal','Interpreter','latex', ...
        'Location','northoutside','FontSize',11)
    axis tight
    ax = gca;
    ax.ThetaLim = [-90 90];
    ax.ThetaZeroLocation = 'top';
    ax.ThetaDir = 'clockwise';

    % Comparison SNR

    diffSNRC3 = 20*log10(POpt(theta == carAngle)) ...
        - 20*log10(BPcruiseUniqueC3(theta == carAngle));
    SNRC3 = tarSNR - diffSNRC3;

    diffSNRADMM = 20*log10(POpt(theta == carAngle)) ...
        - 20*log10(BPcruiseADMM(theta == carAngle));
    SNRADMM = tarSNR - diffSNRADMM;

    diffSNRPseudoCM = 20*log10(POpt(theta == carAngle)) ...
        - 20*log10(BPcruisePseudoCM(theta == carAngle));
    SNRPseudoCM = tarSNR - diffSNRPseudoCM;

    %  Display Results

    fprintf('==================== Figure 17 Cruise Control Scenario ====================\n');
    fprintf('Range = %d m, Angle = %d degree, and Velocity = %d m/s\n', carRange, carAngle, carVelocity);
    fprintf('---------------------------------------------------------------------------\n');
    fprintf('Proposed Method Coding SNR = %.1f dB\n', tarSNR);
    fprintf('UNIQUE C3 Method Coding SNR = %.1f dB\n', SNRC3);
    fprintf('ADMM Method Coding SNR = %.1f dB\n', SNRADMM)
    fprintf('Pseudo-CM Method Coding SNR = %.1f dB\n', SNRPseudoCM)
    fprintf('Orthogonal Coding Method SNR = %.1f dB\n', tarSNROmni);
    fprintf('===========================================================================\n');

    drawnow
    clearvars -except figureNum

end

%%  Figure 18

if any(18 == figureNum)

    fprintf(' Figure 18 ...\n');

    %  Initializing

    ScreenSize          = get(0,'ScreenSize');
    theta               = -90:90;
    Mt                  = 16;
    Nc                  = 128;
    rMax                = 150;
    fc                  = 77e9;
    c                   = 3e8;
    lambda              = c/fc;
    vMax                = 16;
    Tc                  = lambda/(4*vMax);
    d                   = lambda/2;
    p                   = 2;
    L                   = inf;
    thetaDes            = [-90 -70; 70 90];
    B                   = 150e6;
    carRange            = 6;
    carVelocity         = 2;
    carAngle            = 80;

    % - Data Loading
    load BPblindUniqueC3
    load BPblindADMM
    load BPblindPseudoCM

    %  Main Code

    [POpt, ~, ~, ~, S]  = lp_Norm_BP(Mt,Nc,p,L,theta,thetaDes,'seed',4,'draw','off','result','off');

    %  SNR Calculation (Angle Velocity)

    % - all Angles and Velocities Signal Pre Processing
    mtVec               = permute(1:Mt,[1,3,2]);
    range               = carRange;
    NcVec               = 0:Nc-1;
    velocityVec         = permute(-vMax:vMax,[1,3,4,5,6,2]);
    angleVec            = permute(-90:90,[1,3,4,5,6,7,2]);
    nVrVec              = (mtVec-1);

    % - Power Parameters
    KBoltz              = physconst('Boltzmann');
    PtdBm               = 12;
    Pt                  = 10^(PtdBm/10 - 3);
    Gt                  = 10;
    Gr                  = 10;
    RCS                 = 10;
    Rt                  = range;
    N0                  = KBoltz*(23+273);
    NoiseFiguredB       = 15;

    Pr                  = Pt*Gt*Gr*lambda^2*RCS/((4*pi)^3.*Rt.^4);

    % - Received Signal for all Angles and Velocities
    rxSig               = permute(S,[3,2,1]) .* sqrt(Pr) .* exp(-1i .* 4.*pi.*velocityVec.*Tc./lambda.*NcVec) ...
        .* exp(1i * 2*pi*d.*nVrVec.*sind(angleVec)/lambda);
    rxSigAntenna        = abs(squeeze(sum(rxSig,[3 , 4]))).^2;

    % - SNR
    DoppGain            = 10*log10(Nc);
    TBPGain             = 10*log10(B*Tc);
    NoisedB             = 10*log10(B*N0);
    LossdB              = 6;
    rxSNRdB             = 10*log10(squeeze(mean(rxSigAntenna(:,:,:)))) ...
        - NoiseFiguredB - NoisedB - LossdB ...
        + DoppGain + TBPGain;

    % - Angle Velocity SNR Map
    fhdl(1)             = figure('Name','Figure 18b (Scenario 2 - Angle Velocity SNR Map)','NumberTitle','off',...
        'Position', [0 0 floor(ScreenSize(3)/3) floor(ScreenSize(4)/2.5)]);
    movegui('center')
    imagesc(-90:90,-vMax:vMax,rxSNRdB), hold on
    plot(carAngle,carVelocity,'rx','MarkerSize',10,'LineWidth',2)
    [~, velocityIdx] = min(abs(diff(-vMax:vMax - carVelocity)));
    angleIdx = -90:90 == carAngle;
    text(carAngle - 35, carVelocity, sprintf('\\bf{%.1f dB}', rxSNRdB(velocityIdx,angleIdx)), 'Color', 'red', 'Interpreter', 'latex', 'FontSize', 12)
    colorbar
    set(gca,'YDir','normal')
    xlabel('Angle (degree $^\circ$)','Interpreter','latex','FontSize',12')
    ylabel('Velocity (m/s)','Interpreter','latex','FontSize',12')
    xlim([-90 90])
    ylim([-vMax vMax])

    %  SNR Calculation (Range Angle)

    % - all Ranges and Velocities Signal Pre Processing
    rVec                = permute(1:rMax,[1,3,4,5,2]);
    velocity            = carVelocity;

    % - Power Parameters
    Rt                  = rVec;
    Pr                  = Pt*Gt*Gr*lambda^2*RCS/((4*pi)^3.*Rt.^4);

    % - Received Signal Power for all Angles and Ranges
    rxSig               = permute(S,[3,2,1]) .* sqrt(Pr) .* exp(-1i .* 4.*pi.*velocity.*Tc./lambda.*NcVec) ...
        .* exp(1i * 2*pi*d.*nVrVec.*sind(angleVec)/lambda);
    rxSigAntenna        = abs(squeeze(sum(rxSig,[3 , 4]))).^2;

    % - SNR
    DoppGain            = 10*log10(Nc);
    TBPGain             = 10*log10(B*Tc);
    NoisedB             = 10*log10(B*N0);
    LossdB              = 6;
    rxSNRdB             = 10*log10(squeeze(mean(rxSigAntenna(:,:,:)))) ...
        - NoiseFiguredB - NoisedB - LossdB ...
        + DoppGain + TBPGain;

    % - Angle Range SNR Map
    fhdl(2)             = figure('Name','Figure 18a (Scenario 2 - Angle Range SNR Map)','NumberTitle','off',...
        'Position', [0 0 floor(ScreenSize(3)/3) floor(ScreenSize(4)/2.5)]);
    movegui('west')
    imagesc(-90:90,1:rMax,rxSNRdB), hold on
    plot(carAngle,carRange,'rx','MarkerSize',10,'LineWidth',2)
    rangeIdx = 1:200 == carRange;
    text(carAngle - 32, carRange + 7, sprintf('\\bf{%.1f dB}', rxSNRdB(rangeIdx,angleIdx)), 'Color', 'red', 'Interpreter', 'latex', 'FontSize', 12)
    colorbar
    set(gca,'YDir','normal')
    xlabel('Angle (degree $^\circ$)','Interpreter','latex','FontSize',12')
    ylabel('Range (m)','Interpreter','latex','FontSize',12')
    xlim([-90 90])
    ylim([0 rMax])

    %  Beampattern

    % - Omnidirectional Corresponding Code
    SOmni               = repmat(hadamard(Mt),1,Nc/Mt);

    rxSigOmni           = permute(SOmni,[3,2,1]) .* sqrt(Pr) .* exp(-1i .* 4.*pi.*velocity.*Tc./lambda.*NcVec) ...
        .* exp(-1i * 2*pi*d.*nVrVec.*sind(angleVec)/lambda);
    rxSigAntennaOmni    = abs(squeeze(sum(rxSigOmni,[3 , 4]))).^2;

    % - SNR
    DoppGain            = 10*log10(Nc);
    TBPGain             = 10*log10(B*Tc);
    NoisedB             = 10*log10(B*N0);
    LossdB              = 6;
    rxSNRdBOmni             = 10*log10(squeeze(mean(rxSigAntennaOmni(:,:,:)))) ...
        - NoiseFiguredB - NoisedB - LossdB ...
        + DoppGain + TBPGain;

    % - Target SNR
    tarSNROmni          = rxSNRdBOmni(rangeIdx,angleIdx);
    tarSNR              = rxSNRdB(rangeIdx,angleIdx);


    fhdl(3)             = figure('Name','Figure 18c (Scenario 2 - Beampattern)','NumberTitle','off',...
        'Position', [0 0 floor(ScreenSize(3)/3) floor(ScreenSize(4)/2.5)]);
    movegui('east')

    % - Polar Plot
    polarplot(deg2rad(-90:90),20*log10(POpt),'-d','MarkerIndices',1:10:length(theta),'markersize',7,'LineWidth',1.5), hold on
    polarplot(deg2rad(-90:90),20*log10(BPblindUniqueC3),'-o','MarkerIndices',1:10:length(theta),'markersize',7,'LineWidth',1.5)
    polarplot(deg2rad(-90:90),20*log10(BPblindADMM),'-s','MarkerIndices',1:10:length(theta),'markersize',7,'LineWidth',1.5)
    polarplot(deg2rad(-90:90),20*log10(BPblindPseudoCM),'-v','MarkerIndices',1:10:length(theta),'markersize',7,'LineWidth',1.5)
    polarplot(deg2rad(-90:90),zeros(size(theta)),'--k','LineWidth',1.5)
    legend('Proposed Method', 'UNIQUE $C3$ [21]', 'ADMM [8]', ...
        'Pseudo-CM [15]', 'Orthogonal','Interpreter','latex', ...
        'Location','northoutside','FontSize',11)
    axis tight
    ax = gca;
    ax.ThetaLim = [-90 90];
    ax.ThetaZeroLocation = 'top';
    ax.ThetaDir = 'clockwise';
    ax.RLim = [-60 inf];

    % Comparison SNR

    diffSNRC3 = 20*log10(POpt(theta == carAngle)) ...
        - 20*log10(BPblindUniqueC3(theta == carAngle));
    SNRC3 = tarSNR - diffSNRC3;

    diffSNRADMM = 20*log10(POpt(theta == carAngle)) ...
        - 20*log10(BPblindADMM(theta == carAngle));
    SNRADMM = tarSNR - diffSNRADMM;

    diffSNRPseudoCM = 20*log10(POpt(theta == carAngle)) ...
        - 20*log10(BPblindPseudoCM(theta == carAngle));
    SNRPseudoCM = tarSNR - diffSNRPseudoCM;

    %  Display Results

    fprintf('===================== Figure 18 Blind Spot Detection =====================\n');
    fprintf('Range = %d m, Angle = %d degree, and Velocity = %d m/s\n', carRange, carAngle, carVelocity);
    fprintf('--------------------------------------------------------------------------\n');
    fprintf('Proposed Method Coding SNR = %.1f dB\n', tarSNR);
    fprintf('UNIQUE C3 Method Coding SNR = %.1f dB\n', SNRC3);
    fprintf('ADMM Method Coding SNR = %.1f dB\n', SNRADMM)
    fprintf('Pseudo-CM Method Coding SNR = %.1f dB\n', SNRPseudoCM)
    fprintf('Orthogonal Coding Method SNR = %.1f dB\n', tarSNROmni);
    fprintf('===========================================================================\n');

    drawnow
    clearvars -except figureNum

end

%%  Figure 19

if any(19 == figureNum)

    fprintf(' Figure 19 ...\n');

    %  Initializing

    ScreenSize          = get(0,'ScreenSize');
    theta               = -90:90;
    Mt                  = 16;
    Nc                  = 128;
    rMax                = 150;
    fc                  = 77e9;
    c                   = 3e8;
    lambda              = c/fc;
    vMax                = 16;
    Tc                  = lambda/(4*vMax);
    d                   = lambda/2;
    p                   = 2;
    L                   = inf;
    thetaDes            = [-90 0];
    B                   = 150e6;
    carRange            = 30;
    carVelocity         = -1;
    carAngle            = -30;

    % - Data Loading
    load BPlaneChangeADMM
    load BPlaneChangeUniqueC3
    load BPlaneChangePseudoCM

    %  Main Code

    [POpt, ~, ~, ~, S]  = lp_Norm_BP(Mt,Nc,p,L,theta,thetaDes,'seed',4,'draw','off','result','off');

    %  SNR Calculation (Angle Velocity)

    % - all Angles and Velocities Signal Pre Processing
    mtVec               = permute(1:Mt,[1,3,2]);
    range               = carRange;
    NcVec               = 0:Nc-1;
    velocityVec         = permute(-vMax:vMax,[1,3,4,5,6,2]);
    angleVec            = permute(-90:90,[1,3,4,5,6,7,2]);
    nVrVec              = (mtVec-1);

    % - Power Parameters
    KBoltz              = physconst('Boltzmann');
    PtdBm               = 12;
    Pt                  = 10^(PtdBm/10 - 3);
    Gt                  = 10;
    Gr                  = 10;
    RCS                 = 10;
    Rt                  = range;
    N0                  = KBoltz*(23+273);
    NoiseFiguredB       = 15;

    Pr                  = Pt*Gt*Gr*lambda^2*RCS/((4*pi)^3.*Rt.^2);

    % - Received Signal for all Angles and Velocities
    rxSig               = permute(S,[3,2,1]) .* sqrt(Pr) .* exp(-1i .* 4.*pi.*velocityVec.*Tc./lambda.*NcVec) ...
        .* exp(1i * 2*pi*d.*nVrVec.*sind(angleVec)/lambda);
    rxSigAntenna        = abs(squeeze(sum(rxSig,[3 , 4]))).^2;

    % - SNR
    DoppGain            = 10*log10(Nc);
    TBPGain             = 10*log10(B*Tc);
    NoisedB             = 10*log10(B*N0);
    LossdB              = 6;
    rxSNRdB             = 10*log10(squeeze(mean(rxSigAntenna(:,:,:)))) ...
        - NoiseFiguredB - NoisedB - LossdB ...
        + DoppGain + TBPGain;

    % - Angle Velocity SNR Map
    fhdl(1)             = figure('Name','Figure 19b (Scenario 3 - Angle Velocity SNR Map)','NumberTitle','off',...
        'Position', [0 0 floor(ScreenSize(3)/3) floor(ScreenSize(4)/2.5)]);
    movegui('center')
    imagesc(-90:90,-vMax:vMax,rxSNRdB), hold on
    plot(carAngle,carVelocity,'rx','MarkerSize',10,'LineWidth',2)
    [~, velocityIdx] = min(abs(diff(-vMax:vMax - carVelocity)));
    angleIdx = -90:90 == carAngle;
    text(carAngle - 30, carVelocity, sprintf('\\bf{%.1f dB}', rxSNRdB(velocityIdx,angleIdx)), 'Color', 'red', 'Interpreter', 'latex', 'FontSize', 12)
    colorbar
    set(gca,'YDir','normal')
    xlabel('Angle (degree $^\circ$)','Interpreter','latex','FontSize',12')
    ylabel('Velocity (m/s)','Interpreter','latex','FontSize',12')
    xlim([-90 90])
    ylim([-vMax vMax])

    %  SNR Calculation (Range Angle)

    % - all Ranges and Velocities Signal Pre Processing
    rVec                = permute(1:rMax,[1,3,4,5,2]);
    velocity            = carVelocity;

    % - Power Parameters
    Rt                  = rVec;
    Pr                  = Pt*Gt*Gr*lambda^2*RCS/((4*pi)^3.*Rt.^2);

    % - Received Signal Power for all Angles and Ranges
    rxSig               = permute(S,[3,2,1]) .* sqrt(Pr) .* exp(-1i .* 4.*pi.*velocity.*Tc./lambda.*NcVec) ...
        .* exp(1i * 2*pi*d.*nVrVec.*sind(angleVec)/lambda);
    rxSigAntenna        = abs(squeeze(sum(rxSig,[3 , 4]))).^2;

    % - SNR
    DoppGain            = 10*log10(Nc);
    TBPGain             = 10*log10(B*Tc);
    NoisedB             = 10*log10(B*N0);
    LossdB              = 6;
    rxSNRdB             = 10*log10(squeeze(mean(rxSigAntenna(:,:,:)))) ...
        - NoiseFiguredB - NoisedB - LossdB ...
        + DoppGain + TBPGain;

    % - Angle Range SNR Map
    fhdl(2)             = figure('Name','Figure 19a (Scenario 3 - Angle Range SNR Map)','NumberTitle','off',...
        'Position', [0 0 floor(ScreenSize(3)/3) floor(ScreenSize(4)/2.5)]);
    movegui('west')
    imagesc(-90:90,1:rMax,rxSNRdB), hold on
    plot(carAngle,carRange,'rx','MarkerSize',10,'LineWidth',2)
    rangeIdx = 1:200 == carRange;
    text(carAngle - 30, carRange + 7, sprintf('\\bf{%.1f dB}', rxSNRdB(rangeIdx,angleIdx)), 'Color', 'red', 'Interpreter', 'latex', 'FontSize', 12)
    colorbar
    set(gca,'YDir','normal')
    xlabel('Angle (degree $^\circ$)','Interpreter','latex','FontSize',12')
    ylabel('Range (m)','Interpreter','latex','FontSize',12')
    xlim([-90 90])
    ylim([0 rMax])

    %  Beampattern

    % - Omnidirectional Corresponding Code
    SOmni               = repmat(hadamard(Mt),1,Nc/Mt);

    rxSigOmni           = permute(SOmni,[3,2,1]) .* sqrt(Pr) .* exp(-1i .* 4.*pi.*velocity.*Tc./lambda.*NcVec) ...
        .* exp(-1i * 2*pi*d.*nVrVec.*sind(angleVec)/lambda);
    rxSigAntennaOmni    = abs(squeeze(sum(rxSigOmni,[3 , 4]))).^2;

    % - SNR
    DoppGain            = 10*log10(Nc);
    TBPGain             = 10*log10(B*Tc);
    NoisedB             = 10*log10(B*N0);
    LossdB              = 6;
    rxSNRdBOmni             = 10*log10(squeeze(mean(rxSigAntennaOmni(:,:,:)))) ...
        - NoiseFiguredB - NoisedB - LossdB ...
        + DoppGain + TBPGain;

    % - Target SNR
    tarSNROmni          = rxSNRdBOmni(rangeIdx,angleIdx);
    tarSNR              = rxSNRdB(rangeIdx,angleIdx);


    fhdl(3)             = figure('Name','Figure 19c (Scenario 3 - Beampattern)','NumberTitle','off',...
        'Position', [0 0 floor(ScreenSize(3)/3) floor(ScreenSize(4)/2.5)]);
    movegui('east')

    % - Polar Plot
    polarplot(deg2rad(-90:90),20*log10(POpt),'-d','MarkerIndices',1:10:length(theta),'markersize',7,'LineWidth',1.5), hold on
    polarplot(deg2rad(-90:90),20*log10(BPlaneChangeUniqueC3),'-o','MarkerIndices',1:10:length(theta),'markersize',7,'LineWidth',1.5)
    polarplot(deg2rad(-90:90),20*log10(BPlaneChangeADMM),'-s','MarkerIndices',1:10:length(theta),'markersize',7,'LineWidth',1.5)
    polarplot(deg2rad(-90:90),20*log10(BPlaneChangePseudoCM),'-v','MarkerIndices',1:10:length(theta),'markersize',7,'LineWidth',1.5)
    polarplot(deg2rad(-90:90),zeros(size(theta)),'--k','LineWidth',1.5)
    legend('Proposed Method', 'UNIQUE $C3$ [21]', 'ADMM [8]', ...
        'Pseudo-CM [15]', 'Orthogonal','Interpreter','latex', ...
        'Location','northoutside','FontSize',11)
    axis tight
    ax = gca;
    ax.ThetaLim = [-90 90];
    ax.ThetaZeroLocation = 'top';
    ax.ThetaDir = 'clockwise';
    ax.RLim = [-60 inf];

    % Comparison SNR

    diffSNRC3 = 20*log10(POpt(theta == carAngle)) ...
        - 20*log10(BPlaneChangeUniqueC3(theta == carAngle));
    SNRC3 = tarSNR - diffSNRC3;

    diffSNRADMM = 20*log10(POpt(theta == carAngle)) ...
        - 20*log10(BPlaneChangeADMM(theta == carAngle));
    SNRADMM = tarSNR - diffSNRADMM;

    diffSNRPseudoCM = 20*log10(POpt(theta == carAngle)) ...
        - 20*log10(BPlaneChangePseudoCM(theta == carAngle));
    SNRPseudoCM = tarSNR - diffSNRPseudoCM;

    %  Display Results

    fprintf('==================== Figure 19 Lane Change Assistance ====================\n');
    fprintf('Range = %d m, Angle = %d degree, and Velocity = %d m/s\n', carRange, carAngle, carVelocity);
    fprintf('--------------------------------------------------------------------------\n');
    fprintf('Proposed Method Coding SNR = %.1f dB\n', tarSNR);
    fprintf('UNIQUE C3 Method Coding SNR = %.1f dB\n', SNRC3);
    fprintf('ADMM Method Coding SNR = %.1f dB\n', SNRADMM)
    fprintf('Pseudo-CM Method Coding SNR = %.1f dB\n', SNRPseudoCM)
    fprintf('Orthogonal Coding Method SNR = %.1f dB\n', tarSNROmni);
    fprintf('===========================================================================\n');

    drawnow
    clearvars -except figureNum

end

%%  Figure 20

if any(20 == figureNum)

    fprintf(' Figure 20 ...\n');

    %  Initializing

    Mt                  = 16;
    Nc                  = 128;
    p                   = 2;
    L                   = inf;
    theta               = -90:90;
    c                   = 3e8;
    fc                  = 77e9;
    lambda              = c/fc;

    RCS                 = 1;
    vMax                = 16;
    Tc                  = lambda/(4*vMax);
    d                   = lambda/2;
    B                   = 150e6;

    % - Vehicle
    roadLength          = 50;
    step                = 0.5;
    roadVec             = 0:step:roadLength;
    xCar                = zeros(size(roadVec));
    carSpeed            = 10;
    tTotalCar           = roadLength/carSpeed;
    tVecCar             = linspace(0,tTotalCar,length(roadVec));
    yCar                = carSpeed * tVecCar;

    % - Pedesrtian
    crossLength         = 6;
    crossVec            = linspace(0,crossLength,length(roadVec));
    yPed                = (roadLength + 2) * ones(size(roadVec));
    pedSpeed            = 1.2;
    tTotalPed           = crossLength / pedSpeed;
    tVecPed             = linspace(0,tTotalPed,length(crossVec));
    x0Ped               = -3;
    xPed                = pedSpeed * tVecPed + x0Ped;

    % - Relative Distances, Angles, and Velocities
    distCarPed          = sqrt((yPed - yCar).^2 + (xPed - xCar).^2);
    angleCarPed         = atan2d((xPed - xCar),(yPed - yCar));
    velocityCarPed      = diff(distCarPed)/0.05;
    velocityCarPed      = [velocityCarPed(1) velocityCarPed];

    % - parfor Initialization
    poolobj = gcp('nocreate');
    if isempty(poolobj)
        c = parcluster;
        c.NumWorkers = 6;
        parpool(c)
    end

    % - Pre Allocation
    S = cell(size(angleCarPed));

    % - Data Loading
    load trackSNRdBC3
    load trackSNRdBADMM
    load trackSNRdBPseudoCM

    %  Main Code

    parfor i = 1:length(angleCarPed)

        thetaDes = [-10 10] + angleCarPed(i);
        [POpt{i}, ~, ~, ~, S{i}] = lp_Norm_BP(Mt,Nc,p,L,theta,thetaDes,'seed',4,'draw','off','result','off');

    end

    %  Results

    % - all Ranges and Velocities Signal Pre Processing
    rVec                = distCarPed;

    % - Power Parameters
    KBoltz              = physconst('Boltzmann');
    PtdBm               = 12;
    Pt                  = 10^(PtdBm/10 - 3);
    Gt                  = 10;
    Gr                  = 10;
    N0                  = KBoltz*(23+273);
    Rt                  = rVec;
    Pr                  = Pt*Gt*Gr*lambda^2*RCS./((4*pi)^3.*Rt.^4);
    NoiseFiguredB = 15;

    % - Power Processing
    NcVec               = 0:Nc-1;
    mtVec               = permute(1:Mt,[1,3,2]);
    nVrVec              = (mtVec-1);

    % - Received Signal Power for all Angles and Ranges
    rxSig               = cellfun(@(S,Pr,velocity,angle)mean(permute(S,[3,2,1]) .* sqrt(Pr) .* exp(-1i .* 4.*pi.*velocity.*Tc./lambda.*NcVec) ...
        .* exp(1i * 2*pi*d.*nVrVec.*sind(angle)/lambda), 5),S,num2cell(Pr),num2cell(velocityCarPed),arrayfun(@(x)permute(linspace(x-9, x+9), [1,5,4,3,2]),angleCarPed,'UniformOutput',false),'UniformOutput',false);

    rxSigAntenna        = cellfun(@(rxSigPower)abs(squeeze(sum(rxSigPower,[3 , 4]))).^2,rxSig,'UniformOutput',false);

    % - SNR
    DoppGain            = 10*log10(Nc);
    TBPGain             = 10*log10(B*Tc);
    NoisedB             = 10*log10(B*N0);
    LossdB              = 6;

    rxSNRdB             = cell2mat(cellfun(@(SNRvar)flip(10*log10(squeeze(mean(SNRvar,2))),2),rxSigAntenna,'UniformOutput',false)) ...
        - NoiseFiguredB - NoisedB - LossdB ...
        + DoppGain + TBPGain;

    % - Omnidirectional Beampattern Power
    SOmni               = repmat(hadamard(Mt),1,Nc/Mt);

    rxSigOmni           = cellfun(@(Pr,velocity,angle)mean(permute(SOmni,[3,2,1]) .* sqrt(Pr) .* exp(-1i .* 4.*pi.*velocity.*Tc./lambda.*NcVec) ...
        .* exp(1i * 2*pi*d.*nVrVec.*sind(angle)/lambda), 5),num2cell(Pr),num2cell(velocityCarPed),arrayfun(@(x)permute(linspace(x-9, x+9), [1,5,4,3,2]),angleCarPed,'UniformOutput',false),'UniformOutput',false);
    rxSigAntennaOmni    = cellfun(@(rxSigPower)abs(squeeze(sum(rxSigPower,[3 , 4]))).^2,rxSigOmni,'UniformOutput',false);

    % - SNR
    rxSNRdBOmni             = cell2mat(cellfun(@(SNRvar)flip(10*log10(squeeze(mean(SNRvar,2))),2),rxSigAntennaOmni,'UniformOutput',false)) ...
        - NoiseFiguredB - NoisedB - LossdB ...
        + DoppGain + TBPGain;

    %  Plot Resutls

    ScreenSize          = get(0,'ScreenSize');
    fhdl(1)             = figure('Name','Figure 20 (Pedestrian SNR)','NumberTitle','off',...
        'Position', [0 0 floor(ScreenSize(3)/3) floor(ScreenSize(4)/2.5)]);
    movegui('center')
    h1 = subplot(1,4,1:3);
    spS = 55;
    spE = 59;
    plot(distCarPed,rxSNRdB,'LineWidth',2), hold on
    plot(distCarPed,trackSNRdBC3,'LineWidth',2)
    plot(distCarPed,trackSNRdBADMM,'LineWidth',2)
    plot(distCarPed,trackSNRdBPseudoCM,'LineWidth',2)
    plot(distCarPed,rxSNRdBOmni,'--k','LineWidth',2)
    rectPos = [round(distCarPed(spE)), trackSNRdBC3(spS), round(distCarPed(spS)) - round(distCarPed(spE)), rxSNRdB(spE) - trackSNRdBC3(spS)];
    rectangle('Position', ...
        rectPos, ...
        'EdgeColor', '#77AC30', 'LineWidth', 2);
    set (gca, 'xdir', 'reverse' )
    grid minor
    axis tight
    xlim([-inf 50])
    y_limits = ylim;
    ylabel('SNR (dB)','Interpreter','latex','FontSize',12')
    legend('Proposed Method', 'UNIQUE $C3$ [21]', 'ADMM [8]', ...
        'Pseudo-CM [15]', 'Orthogonal','Interpreter','latex', ...
        'Location','nw','FontSize',11)
    drawnow

    h2 = subplot(1,4,4);
    plot(rxSNRdB(spS:spE),'LineWidth',2), hold on
    plot(trackSNRdBC3(spS:spE),'LineWidth',2)
    plot(trackSNRdBADMM(spS:spE),'LineWidth',2)
    plot(trackSNRdBPseudoCM(spS:spE),'LineWidth',2)
    xticks([1,3,5])
    xticklabels(flip(round(2*[distCarPed(spE),distCarPed((spS+spE)/2),distCarPed(spS)])/2));
    grid minor
    axis('tight')
    han = axes(fhdl(1),'visible','off');
    han.XLabel.Visible = 'on';
    xlabel(han,'Relative Distance (m)','Interpreter','latex','FontSize',12')

    subplotPos1 = h1.Position;
    subplotPos2 = h2.Position;
    arrowStartX = subplotPos1(1) + (rectPos(1) + rectPos(3))/(50 - distCarPed(end)) * subplotPos1(3);
    arrowStartY1 = subplotPos1(2) + (rectPos(2) - y_limits(1))/(y_limits(2) - y_limits(1)) * subplotPos1(4);
    arrowStartY2 = subplotPos1(2) + (rectPos(2) + rectPos(4) - y_limits(1))/(y_limits(2) - y_limits(1)) * subplotPos1(4);
    arrowEndX = subplotPos2(1);
    arrowEndY1 = subplotPos2(2);
    arrowEndY2 = subplotPos2(4) + subplotPos2(2);
    annotation('arrow', [arrowStartX, arrowEndX], [arrowStartY1, arrowEndY1], 'Color', '#77AC30', 'LineWidth', 2);
    annotation('arrow', [arrowStartX, arrowEndX], [arrowStartY2, arrowEndY2], 'Color', '#77AC30', 'LineWidth', 2);

    %  Display Results

    fprintf('====================== Figure 20 Pedestrian Tracking ======================\n');
    fprintf('Proposed Method Coding Average SNR = %.1f dB\n', mean(rxSNRdB));
    fprintf('UNIQUE C3 Method Coding Average SNR = %.1f dB\n', mean(trackSNRdBC3));
    fprintf('ADMM Method Coding Average SNR = %.1f dB\n', mean(trackSNRdBADMM));
    fprintf('Pseudo-CM Method Coding Average SNR = %.1f dB\n', mean(trackSNRdBPseudoCM));
    fprintf('Orthogonal Coding Method SNR = %.1f dB\n', mean(rxSNRdBOmni));
    fprintf('===========================================================================\n');

    drawnow
    clearvars -except figureNum

end

%%  Saving Figures

folderName = 'figs';
if ~exist(folderName, 'dir')
    mkdir(folderName);
end

fhdl = findobj('Type', 'figure');

for i = 1:length(fhdl)
    fig = fhdl(i);
    figureName = get(fig, 'Name');

    if isempty(figureName)
        figureName = sprintf('Figure%d', i);
    end

    filename = sprintf('%s.pdf', figureName);
    figsFilename = fullfile(folderName, filename);

    exportgraphics(fig, figsFilename);
end

clearvars -except figureNum