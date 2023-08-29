% ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
% Copyright (c) 2020, <Mohammad Alaee>, website: https://radarmimo.com/
% All rights reserved.
% ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
% Redistribution and use in source and binary forms, with or without
% modification, are permitted provided that the following conditions are met:
% 1. Redistributions of source code must retain the above copyright
%    notice, this list of conditions and the following disclaimer.
% 2. Redistributions in binary form must reproduce the above copyright
%    notice, this list of conditions and the following disclaimer in the
%    documentation and/or other materials provided with the distribution.
% 3. All advertising materials mentioning features or use of this software
%    must display the following acknowledgement:
%    "This product includes software developed by <Mohammad Alaee>,
%    https://radarmimo.com/"
%
% THIS SOFTWARE IS PROVIDED BY <COPYRIGHT HOLDER> ''AS IS'' AND ANY
% EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
% WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
% DISCLAIMED. IN NO EVENT SHALL <COPYRIGHT HOLDER> BE LIABLE FOR ANY
% DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
% (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
% LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
% ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
% (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
% SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
% ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
% Website: https://radarmimo.com/
% Email: info@radarmimo.com, mohammad.alaee@uni.lu, mmalaee@yahoo.com
% Code written by : Mohammad Alaee
% Last update : 2017
% Paper: A Coordinate-Descent Framework to Design Low PSL/ISL Sequences
% https://ieeexplore.ieee.org/abstract/document/7967829
% ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
% ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
close all; clear ; clc
% ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
MarkerSize          = 8;
MarkerIndices       = 4;
LineWidth           = 2;
% ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
% Select figures to tun (you can have multiple selection) 
Fig1                = 1; % psl unimodular 
Fig2                = 0; % psl unimodualr 
Fig3                = 1; % psl discrete phase 
Fig4                = 1; % psl binary 
Fig5                = 1; % isl unimodular 
Fig6                = 1; % isl unimodular  
Fig7                = 1; % isl discrete phase 
Fig8                = 0; % Pareto
% ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
% Initial parameters 
thr                 = 1e-5; % stopping threshold
% P                   = (1:13); % lp-norm sweep interval in paper
P                   = (1:4); % lp-norm sweep interval
trials              = 5; % number of independet trials in paper
% ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
% ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
% ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

%% Fig. 1. The effect of constellation size on PSL values
if Fig1 == 1
    disp('Running Fig. 1. , please wait ...')
%     N                       = 400; % code length in paper
    N                       = 36; % for a quick test
    M                       = 2.^(2:9); % in paper
    LM                      = length(M);
    pDPMF1                  = zeros(LM,1);
    
    xF                      = mcode( 1 , N ); % Frank initial sequence
    xlpCPM                  = lpCPM(xF,P,thr,0); % lp-norm minimization
    xCPM                    = cpm( xlpCPM,thr,1,0); % psl minimization CPM
    pCPMaF1                 = pslisl(xCPM); % isl of optimized sequence
    for i = 1 : LM
        xlpDPM              = lpDPM(xF,P,thr,M(i),0); % lp-norm minimization
        xDPM                = dpm( xlpDPM, M(i),thr,1, 0); % psl minimization DPM
        pDPMF1(i)           = pslisl(xDPM); % psl of optimized sequence
    end

    figure; hold all
    plot(M,10*log10(pDPMF1),'ko:','MarkerSize', MarkerSize,'LineWidth',LineWidth);
    plot(M,10*log10(pCPMaF1*ones(LM,1)),'gr-','MarkerSize', MarkerSize,'LineWidth',LineWidth);
    xlabel('alphabet size (M)'); ylabel('PSL (dB)');
    set(gca, 'XLimSpec', 'Tight');
    legend('DPM', 'CPM','location','best')
    box on; grid on; drawnow
    disp('~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~')
 
end
% ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
% ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
% ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
%% Fig. 2. PSL (dB) versus sequence length
if Fig2 == 1
    disp('Running Fig. 2. , please wait ...')
    % codeLengths           = [5,7,10,12,15,18,20,25,30,32].^2; % in paper
    codeLengths             = (3:10).^2; % for a quick test
    codeLengths             = codeLengths(:);
    LcodeLengths            = length(codeLengths);
    
    pFaF2                   = zeros(LcodeLengths,1);
    pGaF2                   = zeros(LcodeLengths,1);
    pDPM64aF2               = zeros(LcodeLengths,1);
    pDPM256aF2              = zeros(LcodeLengths,1);
    pCPMaF2                 = zeros(LcodeLengths,1);
    
    for i = 1 : LcodeLengths
        N                   = codeLengths(i); % sequence length
        
        xF                  = mcode( 1 , N ); % Frank initial sequence
        xG                  = mcode( 2 , N ); % Golomb sequence
        
        pFaF2(i)            = pslisl(xF); % isl of initial sequence
        pGaF2(i)            = pslisl(xG); % isl of initial sequence

        xlpCPM              = lpCPM(xF,P,thr,0); % lp-norm minimization
        xCPM                = cpm( xlpCPM,thr,1,0); % psl minimization CPM
        
        xlpDPM64            = lpDPM(xF,P,thr,64,0); % lp-norm minimization
        xDPM64              = dpm( xlpDPM64, 64,thr,1, 0); % psl minimization DPM
        
        xlpDPM256           = lpDPM(xF,P,thr,256,0); % lp-norm minimization
        xDPM256             = dpm( xlpDPM256, 256,thr,1, 0); % psl minimization DPM
        
        pCPMaF2(i)          = pslisl(xCPM); % psl of optimized sequence
        pDPM64aF2(i)        = pslisl(xDPM64); % psl of optimized sequence
        pDPM256aF2(i)       = pslisl(xDPM256); % psl of optimized sequence
        
        
    end

    figure; hold all
    plot(codeLengths,10*log10(pFaF2),'m+-','MarkerSize', MarkerSize,'LineWidth',LineWidth);
    plot(codeLengths,10*log10(pGaF2),'r^-','MarkerSize', MarkerSize,'LineWidth',LineWidth);
    plot(codeLengths,10*log10(pDPM64aF2),'cx--','MarkerSize', MarkerSize,'LineWidth',LineWidth);
    plot(codeLengths,10*log10(pDPM256aF2),'co:','MarkerSize', MarkerSize,'LineWidth',LineWidth);
    plot(codeLengths,10*log10(pCPMaF2),'k-','MarkerSize', MarkerSize,'LineWidth',LineWidth);
    xlabel('squence length (N)'); ylabel('PSL (dB)');
    set(gca, 'XLimSpec', 'Tight');
    legend('Frank', 'Golomb', 'DPM (M=64)','DPM (M=256)', 'CPM','location','best')
    box on; grid on; drawnow
    disp('~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~')
end
% ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
% ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
% ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
%% Fig. 3. 
if Fig3 == 1
    disp('Running Fig. 3. , please wait ...')
    M                       = 8; % alphabet size; (a) M = 2, (b) M = 8, (c) M =16
    % codeLengths           = [5,7,10,12,15,18,20,25,30,32].^2; % in paper
    codeLengths             = (3:10).^2; % for a quick test
    codeLengths             = codeLengths(:);
    LcodeLengths            = length(codeLengths);
    
    pRNDaF3                 = zeros(LcodeLengths,trials);
    pDPMpaF3                = zeros(LcodeLengths,trials);
    pRNDF3                  = zeros(LcodeLengths,1);
    % PSL optimization
    for k = 1 : trials
        for i = 1 : LcodeLengths
            N               = codeLengths(i); % sequence length
            xR              = mcode( 8 , N ); % random initial sequence
            xR              = exp(1i * floor(angle(xR(1:N))/(2*pi/M))*(2*pi/M)); % quantize the initial sequence
            pRNDaF3(i,k)    = pslisl(xR); % psl of initial sequence
            xlp             = lpDPM(xR,P,thr,M,0); % lp-norm minimization
            xDPMp           = dpm( xlp, M,thr,1, 0); % psl minimization
            pDPMpaF3(i,k)   = pslisl(xDPMp); % psl of optimized sequence
        end
        disp([num2str(k/(trials)*100),' %'])
    end
    
    [pDPMpF3,indxF3]        = min(pDPMpaF3,[],2);
    for i = 1 : LcodeLengths
        pRNDF3(i)           = pRNDaF3(i,indxF3(i));
    end
    
    figure; hold all
    plot(codeLengths,10*log10(pRNDF3),'grs-','MarkerSize', MarkerSize,'LineWidth',LineWidth);
    plot(codeLengths,10*log10(pDPMpF3),'k:o','MarkerSize', MarkerSize,'LineWidth',LineWidth);
    xlabel('squence length (N)'); ylabel('PSL (dB)');
    set(gca, 'XLimSpec', 'Tight');
    legend('initial sequence',['DPM, M = ',num2str(M)] ,'location','best')
    box on; grid on; drawnow
    disp('~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~')
end
% ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
% ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
% ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
%% Fig. 4. Performance of DPM algorithm in different conditions
if Fig4 == 1
    disp('Running Fig. 4. , please wait ...')
    M                   = 2; % alphabet size , M=2, binary code design
%     codeLengths         = 2:200; % in paper
    codeLengths         = 2:105; % for a quick test
    codeLengths         = codeLengths(:);
    LcodeLengths        = length(codeLengths);
    
    pRNDaF4             = zeros(LcodeLengths,trials);
    pDPMpaF4            = zeros(LcodeLengths,trials);
    pRNDF4              = zeros(LcodeLengths,1);
    
    xopt11              = [];
    xopt126             = [];
    
    % PSL optimization, Binary PSL
    for k = 1 : trials
        for i = 1 : LcodeLengths
            N           = codeLengths(i);
            xR          = mcode( 8 , N ); % random initial sequence
            xR          = exp(1i * floor(angle(xR(1:N))/(2*pi/M))*(2*pi/M)); % quantize the initial sequence
            pRNDaF4(i,k)= pslisl(xR); % psl of initial sequence
            xlp         = lpDPM(xR,P,thr,M,0); % lp-norm minimization
            xDPMp       = dpm( xlp, M,thr,1, 0); % psl minimization
            pDPMpaF4(i,k) = pslisl(xDPMp); % psl of optimized sequence
        end
        disp([num2str(k/(trials)*100),' %'])
    end
    
    
    pMPS            = zeros(1,105);
    pMPS(1:5)       = 1; pMPS(7)        = 1; pMPS(11)       = 1;
    pMPS(13)        = 1; pMPS(6)        = 2; pMPS(8:10)     = 2;
    pMPS(12)        = 2; pMPS(14:21)    = 2; pMPS(28)       = 2;
    pMPS(22:27)     = 3; pMPS(25)       = 2; pMPS(29:48)    = 3;
    pMPS(51)        = 3; pMPS(49)       = 4; pMPS(50)       = 4;
    pMPS(52:82)     = 4; pMPS(83:105)   = 5;
    
    
    [pDPMpF4,indxF4]    = min(pDPMpaF4,[],2);
    for i = 1 : LcodeLengths
        pRNDF4(i)       = pRNDaF4(i,indxF4(i));
    end
    
    
    figure; hold all
    plot(codeLengths,pRNDF4,'c:','MarkerSize', MarkerSize,'LineWidth',LineWidth);
    plot(codeLengths,pDPMpF4,'k.-','MarkerSize', MarkerSize,'LineWidth',LineWidth);
    plot(2:105,pMPS(2:end),'r-','MarkerSize', MarkerSize,'LineWidth',LineWidth);
    xlabel('squence length (N)'); ylabel('PSL');
    set(gca, 'XLimSpec', 'Tight');
    legend('initial sequence',['DPM, M = ',num2str(M)] ,'MPS','location','best')
    box on; grid on; drawnow
    
    % Part (b)
    psl11               = inf;
    while psl11 >= 2
        xR11            = mcode( 15 , 11 );
        xlp             = lpDPM(xR11,P,thr,M,0);
        xopt11          = dpm( xlp, M,thr,1, 0);
        psl11           = pslisl(xopt11);
    end
    if ~isempty(xopt11)
        figure; hold all; 
        plot(abs(xcorr(xR11)),'gr:','MarkerSize', MarkerSize,'LineWidth',LineWidth)
        plot(abs(xcorr(xopt11)),'k','MarkerSize', MarkerSize,'LineWidth',LineWidth)
        xlabel('shift(k)'); ylabel('Correlation Level')
        legend('Random Code','DPM, M = 2','location','best')
        set(gca, 'XLimSpec', 'Tight');
        box on; grid on; drawnow
    end
    
    % Part (c)
    psl126              = inf;
    while psl126 >= 9
        xR126           = mcode( 15 , 126 );
        xlp             = lpDPM(xR126,P,thr,M,0);
        xopt126         = dpm( xlp, M,thr,1, 0);
        psl126          = pslisl(xopt126);
    end
    if ~isempty(xopt126)
        figure; hold all
        plot(abs(xcorr(xR126)),'gr:','MarkerSize', MarkerSize,'LineWidth',LineWidth)
        plot(abs(xcorr(xopt126)),'k','MarkerSize', MarkerSize,'LineWidth',LineWidth)
        xlabel('shift(k)'); ylabel('Correlation Level')
        legend('Random Code','DPM, M = 2','location','best')
        set(gca, 'XLimSpec', 'Tight');
        box on; grid on; drawnow
    end
    disp('~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~')
end
% ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
% ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
% ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
%% Fig. 5. The effect of constellation size on ISL values
if Fig5 == 1
    disp('Running Fig. 5. , please wait ...')
%     N                       = 400; % code length in paper
    N                       = 36; % for a quick test
    M                       = 2.^(2:9); % in paper
    
    LM                      = length(M);
    iDPMF5                  = zeros(LM,1);
    
    xF                      = mcode( 1 , N ); % Frank initial sequence
    [xCPM,oCPMF5]           = cpm( xF,thr,0,0); % isl minimization CPM
    [~,iCPMaF5]             = pslisl(xCPM); % isl of optimized sequence
    for i = 1 : LM
        xDPM                = dpm( xF, M(i),thr,0, 0); % isl minimization DPM
        [~,iDPMF5(i)]       = pslisl(xDPM); % isl of optimized sequence
    end

    figure; hold all
    plot(M,10*log10(iDPMF5),'ko:','MarkerSize', MarkerSize,'LineWidth',LineWidth);
    plot(M,10*log10(iCPMaF5*ones(LM,1)),'gr-','MarkerSize', MarkerSize,'LineWidth',LineWidth);
    xlabel('alphabet size (M)'); ylabel('ISL (dB)');
    set(gca, 'XLimSpec', 'Tight');
    legend('DPM', 'CPM','location','best')
    box on; grid on; drawnow
    disp('~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~')
end
% ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
% ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
% ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
%% Fig. 6. ISL (dB) versus sequence length
if Fig6 == 1
    disp('Running Fig. 6. , please wait ...')
    % codeLengths           = [5,7,10,12,15,18,20,25,30,32].^2; % in paper
    codeLengths             = (3:10).^2; % for a quick test
    codeLengths             = codeLengths(:);
    LcodeLengths            = length(codeLengths);
    
    iFaF6                   = zeros(LcodeLengths,1);
    iGaF6                   = zeros(LcodeLengths,1);
    iDPM64aF6               = zeros(LcodeLengths,1);
    iDPM256aF6              = zeros(LcodeLengths,1);
    iCPMaF6                 = zeros(LcodeLengths,1);
    
    for i = 1 : LcodeLengths
        N                   = codeLengths(i); % sequence length
        
        xF                  = mcode( 1 , N ); % Frank initial sequence
        xG                  = mcode( 2 , N ); % Golomb sequence
        
        [~,iFaF6(i)]        = pslisl(xF); % isl of initial sequence
        [~,iGaF6(i)]        = pslisl(xG); % isl of initial sequence
        
        xCPM                = cpm( xF,thr,0,0); % isl minimization CPM
        xDPM64              = dpm( xF, 64,thr,0, 0); % isl minimization DPM
        xDPM256             = dpm( xF, 256,thr,0, 0); % isl minimization DPM
        
        [~,iCPMaF6(i)]      = pslisl(xCPM); % isl of optimized sequence
        [~,iDPM64aF6(i)]    = pslisl(xDPM64); % isl of optimized sequence
        [~,iDPM256aF6(i)]   = pslisl(xDPM256); % isl of optimized sequence
        
        
    end

    figure; hold all
    plot(codeLengths,10*log10(iFaF6),'m+-','MarkerSize', MarkerSize,'LineWidth',LineWidth);
    plot(codeLengths,10*log10(iGaF6),'r^-','MarkerSize', MarkerSize,'LineWidth',LineWidth);
    plot(codeLengths,10*log10(iDPM64aF6),'cx-','MarkerSize', MarkerSize,'LineWidth',LineWidth);
    plot(codeLengths,10*log10(iDPM256aF6),'co:','MarkerSize', MarkerSize,'LineWidth',LineWidth);
    plot(codeLengths,10*log10(iCPMaF6),'k-','MarkerSize', MarkerSize,'LineWidth',LineWidth);
    xlabel('squence length (N)'); ylabel('ISL (dB)');
    set(gca, 'XLimSpec', 'Tight');
    legend('Frank', 'Golomb', 'DPM (M=64)','DPM (M=256)', 'CPM','location','best')
    box on; grid on; drawnow
    disp('~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~')
end
% ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
% ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
% ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
%% Fig. 7. ISL (dB) versus sequence length
if Fig7 == 1
    disp('Running Fig. 7. , please wait ...')
    M                       = 8; % alphabet size; (a) M = 2, (b) M = 8, (c) M =16
    % codeLengths           = [5,7,10,12,15,18,20,25,30,32].^2; % in paper
    codeLengths             = (3:10).^2; % for a quick test
    codeLengths             = codeLengths(:);
    LcodeLengths            = length(codeLengths);
    
    iRNDaF7                 = zeros(LcodeLengths,trials);
    iDPMaF7                 = zeros(LcodeLengths,trials);
    iRNDF7                  = zeros(LcodeLengths,1);
    % ISL optimization
    for k = 1 : trials
        for i = 1 : LcodeLengths
            N               = codeLengths(i); % sequence length
            xR              = mcode( 8 , N ); % random initial sequence
            xR              = exp(1i * floor(angle(xR(1:N))/(2*pi/M))*(2*pi/M)); % quantize the initial sequence
            [~,iRNDaF7(i,k)]  = pslisl(xR); % isl of initial sequence
            xDPM            = dpm( xR, M,thr,0, 0); % isl minimization
            [~,iDPMaF7(i,k)] = pslisl(xDPM); % isl of optimized sequence
        end
        disp([num2str(k/(trials)*100),' %'])
    end
    
    [iDPMF7,indxF7]         = min(iDPMaF7,[],2);
    for i = 1 : LcodeLengths
        iRNDF7(i)           = iRNDaF7(i,indxF7(i));
    end
    
    figure; hold all
    plot(codeLengths,10*log10(iRNDF7),'grs-','MarkerSize', MarkerSize,'LineWidth',LineWidth);
    plot(codeLengths,10*log10(iDPMF7),'k:o','MarkerSize', MarkerSize,'LineWidth',LineWidth);
    xlabel('squence length (N)'); ylabel('ISL (dB)');
    set(gca, 'XLimSpec', 'Tight');
    legend('initial sequence',['DPM, M = ',num2str(M)] ,'location','best')
    box on; grid on; drawnow
    disp('~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~')
end
% ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
% ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
% ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
%% Fig. 8. Pareto-optimized curves for continuous and discrete phase
if Fig8 == 1
    disp('Running Fig. 7. , please wait ...')
%     N                       = 400; % code length in paper
    N                       = 40; % for a quick test
    xR                      = mcode( 8 , N ); % random initial sequence
    Ltheta                  = 6;
    ParetoCPM               = zeros(Ltheta,1);
    ParetoDPM64             = zeros(Ltheta,1);
    ParetoDPM256            = zeros(Ltheta,1);
    
    xCPM                    = xR;
    xDPM64                  = xR;
    xDPM256                 = xR;
    
    pCPM                    = zeros(Ltheta,1);
    iCPM                    = zeros(Ltheta,1);
    pDPM64                  = zeros(Ltheta,1);
    iDPM64                  = zeros(Ltheta,1);
    pDPM256                 = zeros(Ltheta,1);
    iDPM256                 = zeros(Ltheta,1);
    
    for i = 1 : Ltheta
        theta           = 1 - (i - 1)/(Ltheta - 1);
        if theta == 1
            xCPM        = lpCPM(xCPM,P,thr,0); % lp-norm minimization
            xDPM64      = lpDPM(xDPM64,P,thr,64,0); % lp-norm minimization
            xDPM256     = lpDPM(xDPM256,P,thr,64,0); % lp-norm minimization
        end
        xCPM            = cpm( xCPM,thr,theta,0); % Pareto minimization CPM
        xDPM64          = dpm( xDPM64, 64,thr,theta, 0); % Pareto minimization
        xDPM256         = dpm( xDPM256, 256,thr,theta, 0); % Pareto minimization
        
        [pCPM(i),iCPM(i)]     = pslisl(xCPM);
        [pDPM64(i),iDPM64(i)] = pslisl(xDPM64);
        [pDPM256(i),iDPM256(i)] = pslisl(xDPM256);
    end
    
    
    figure; hold all
    plot(10*log10(iCPM),10*log10(pCPM),'gro-','MarkerSize', MarkerSize,'LineWidth',LineWidth);
    plot(10*log10(iDPM64),10*log10(pDPM64),'b:','MarkerSize', MarkerSize,'LineWidth',LineWidth);
    plot(10*log10(iDPM256),10*log10(pDPM256),'k--','MarkerSize', MarkerSize,'LineWidth',LineWidth);
    xlabel('ISL (dB)'); ylabel('PSL (dB)');
    set(gca, 'XLimSpec', 'Tight');
    legend('CPM','DPM (M=64)', 'DPM (M=256)' ,'location','best')
    box on; grid on; drawnow
    disp('~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~')
end
% ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
% ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
% ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~