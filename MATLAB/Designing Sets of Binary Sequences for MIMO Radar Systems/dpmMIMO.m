function [ X , o , t] = dpmMIMO( X0, L,thr,theta,pF)
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
% Update : 2016
% ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
% ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
% This function optimizes set of sequences with discrete phase alphabet
% ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
% Input:
%           X0      : set of initial sequences (uni-modular)
%           L       : alphabet size, L = 2 -> binary , L = 4 -> QPSK, ...
%           thr     : stopping threshold
%           pF      : pF = 1 -> minimizing "Periodic" correlation functions,
%                   otherwise, minimizing "Aperiodic" correlation functions
%           theta   : Pareto weight , 0 <= theta  <= 1
%                       theta = 1 -> minimizing PSL,
%                       theta = 0 -> minimizing ISL,
% ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
% ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
% Output:
%           X       : optimized set of sequences
%           o       : objective values per iteration
%                       (theta * PSL + (1-theta)*ISL)
%           t       : run-time (second)
% ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
% The input parameters can be chosed as follows:

if ~exist('X0','var')
    rng(1)
    NT              = 2; % number of transmit waveforms
    N               = 100; % sequence length
    phi             = (2*rand(N,NT)-1)*pi;
    X0              = exp(1i * phi);
end
if ~exist('L','var')
    L                = 8; % alphabet size
    for m = 1 : NT % Quantize, to make sure the initial sequence has appropriate alphabet size
        x0          = X0(:,m);
        x0          = exp(1i * floor(angle(x0(1:N))/(2*pi/L))*(2*pi/L));
        X0(:,m)     = x0;
    end
end
if ~exist('thr','var')
    thr             = 1e-5; % stopping threshold
end
if ~exist('theta','var')
    theta           = 1; % pareto weight
    % theta = 1 --> PSL minimization
    % theta = 0 --> ISL minimization 
end
if ~exist('pF','var')
    pF              = 0; % periodic auto-correlation optimization flag
    % pf = 1 --> periodic
    % pf = 0 --> aperiodic
end
% ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
[N,NT]              = size(X0);
Xi                  = X0;
out                 = mPSLISL(Xi,theta);
if pF == 1
    o               = out.Pareto_P;
    PSLval          = out.PSL_P;
else
    o               = out.Pareto_AP;
    PSLval          = out.PSL_AP;
end
cnt                 = 1;
cnd                 = 1;
tic
while (cnd > 0 && cnt < 20*N*NT)
    for t = 1 : NT
        xt          = Xi(:,t);      % Select t-th transmitter
        for d = 1 : N
            if pF == 1
                [ a_mm,b_mm,c_mm ]  = mabcp( xt,d );
            else
                [ a_mm,b_mm,c_mm ]  = mabc( xt,d );
            end
            
            a_dkm                   = zeros(2*N-1,1);
            c_dkm                   = zeros(2*N-1,1);
            a_dkm(N+1:end)          = a_mm;
            
            b_dkm                   = zeros(2*N-1,1);
            b_dkm(N+1:end)          = b_mm;
            b_dkm(N-1:-1:1)         = b_mm;
            
            c_dkm(N+1:end)          = c_mm;
            a_dkm(N-1:-1:1)         = a_mm;
            c_dkm(N-1:-1:1)         = c_mm;
            
            if L == 2
                X1mm                = [a_dkm+b_dkm,c_dkm];
            else
                X1mm                = [a_dkm,c_dkm,b_dkm];
            end
            Ymm                     = abs(fft(X1mm,L,2)).'; % for PSL
            Y1mm                    = (Ymm).^2;
            Y2mm                    = sum(Y1mm,2);          % for ISL
            Y1ml2                   = zeros(L,1);
            Ytempml                 = zeros(L,1);
            
            for l = 1 : NT
                if l ~= t
                    xl  = Xi(:,l);
                    if pF == 1
                        [ a_dkl,c_dkl ] = mabccp( xt,xl,d );
                    else
                        [ a_dkl,c_dkl ] = mabcc( xt,xl,d);
                    end
                    
                    X1ml            = [a_dkl,c_dkl];
                    Yml             = abs(fft(X1ml,L,2)).';
                    Y1ml            = (Yml).^2;
                    max_Y1ml        = max(Y1ml.').';
                    Y1ml2           = max(Y1ml2 , max_Y1ml); % PSL
                    Ytempml         = Ytempml + sum(Y1ml,2); % ISL
                end
            end
            Y2ml            = Ytempml;
            Omega           = theta * max( max(Y1mm.').',  Y1ml2) + (1-theta)*( Y2mm + 2* Y2ml) ;
            mYobj           = Omega;
            [~,iy]          = min(mYobj);
            
            phf1est         = 2*pi*(iy-1)/L;
            xt(d)           = exp(1i * phf1est);
            
        end
        Xi(:,t)             = xt;
        out                 = mPSLISL(Xi,theta);
        if pF == 1
            o(end+1)        = out.Pareto_P;
            PSLval(end+1)   = out.PSL_P;
        else
            o(end+1)        = out.Pareto_AP;
            PSLval(end+1)   = out.PSL_AP;
        end

    end
    cnt                     = cnt + 1;
    if (o(end-1) - o(end)) < thr
        break
    end
end
X = Xi;
t = toc;
if nargout == 0

    disp(['run-time : ', num2str(t),' second'])
    close all
    MarkerSize = 20;
    
    figure;
    plot(10*log10((o/N^2)),'gr*-','MarkerSize',MarkerSize);
    xlabel('iteration')
    ylabel('objective (dB)')
    grid on
    box on
    
    if theta == 1
        figure;
        plot(PSLval,'gr*-','MarkerSize',MarkerSize);
        xlabel('iteration')
        ylabel('PSL')
        grid on
        box on
    end

    
    if pF == 1
        figure; hold all;
        plot(abs(pcorr(X0(:,1))),':k');
        plot(abs(pcorr(X(:,1))),'-or')
        axis('tight')
        xlabel('k')
        ylabel('Correlation Level')
        grid on
        box on
        legend('Initial Sequence','Obtained Sequence','Location','Best')
        
        figure; hold all; plot(abs(pcorr(X0(:,1),X0(:,2))));
        plot(abs(pcorr(X(:,1),X(:,2))))
        grid on
        box on       
    else
        figure; hold all;
        plot(abs(xcorr(X0(:,1))),':k');
        
        plot(abs(xcorr(X(:,1))),'-vb')
        
        axis('tight')
        xlabel('k')
        ylabel('Correlation Level')
        grid on
        box on
        legend('Initial Sequence','Obtained Sequence','Location','Best')

        figure; hold all;
        plot(abs(xcorr(X0(:,1),X0(:,2))));
        plot(abs(xcorr(X(:,1),X(:,2))))
        grid on
        box on        
    end
    X = [];
    
end
end
