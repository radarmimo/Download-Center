function [ x , o , t] = dpm( x0, L,thr,theta, pF)
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
% Last update : 2016
% ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
% ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
% This function obtains optimized discrete phase sequence
% ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
% Input:
%           x0      : initial sequence (discrete phase)
%           L       : alphabet size (M-ary PSK design)
%           thr     : stopping threshold
%           theta   : Pareto weight , 0 <= theta  <= 1
%                       theta = 1 -> minimizing PSL,
%                       theta = 0 -> minimizing ISL,
%           pF      : pF = 1 -> minimizing "Periodic" auto-correlation,
%                     otherwise, minimizing "Aperiodic" auto-correlation
% ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
% ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
% Output:
%           x       : optimized sequence (discrete phase, M-ary PSK)
%           o       : objective values per iteration
%                       (theta * PSL + (1-theta)*ISL)
%           t       : run-time (second)
% ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
% The input parameters can be chosed as follows:
% Some examples are below, they can be specified when calling the function
if ~exist('x0','var')
    rng(2)
    N               = 250; % code length
    phi             = (2*rand(N,1)-1)*pi; % initial phase
    x0              = exp(1i * phi); % initial sequence
end
if ~exist('L','var') % alphabet size
   L                = 16;
end
if ~exist('thr','var')
    thr             = 1e-5; % stopping threshold 
end
if ~exist('theta','var')
    theta           = 0; % pareto weight 
end
if ~exist('pF','var')
    pF              = 0; % periodic auto-correlation optimization flag
end
% ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
x0                  = x0(:);
N                   = length(x0);
x0                  = exp(1i * floor(angle(x0(1:N))/(2*pi/L))*(2*pi/L)); % Quantize, to make sure the initial sequence has appropriate alphabet size
x                   = x0;
if L <= 2
    x               = real(ceil(x0)); x(find(real(x)==0,N)) = -1;
end
N                   = length(x);

if pF == 1
    [p1,i1,~,~ ]    = pslisl( x , 0 , 1);
else
    [p1,i1,~,~ ]    = pslisl( x );
end
o(1)                = theta * p1^2 + (1-theta) * i1;

cnt                 = 1;
cnd                 = 1;
tic
while (cnd > 0 && cnt < 20*N)
    for d = 1 : N
        if pF == 1
            [ a_dk,b_dk,c_dk ]      = mabcp( x,d );
        else
            [ a_dk,b_dk,c_dk ]      = mabc( x,d );
        end
        if L <= 2
            X1          = [a_dk+b_dk,c_dk];
        else
            X1          = [a_dk,c_dk,b_dk];
        end
        Y               = (fft(X1.',L));
        Y1              = abs(Y).^2;
        Ytemp           = sum(Y1,2);
        Y2              = repmat(Ytemp,1,N-1);
        Omega           = theta * Y1 + (1 - theta) * Y2;
        mYobj           = max(Omega,[],2);
        [~,iy]          = min(mYobj);
        phf1est         = 2*pi*(iy-1)/L;
        if phf1est > pi
            phf1est     = phf1est - 2*pi;
        end
        x(d)            = exp(1i * phf1est);
        
    end
    if pF == 1
        [p2,i2,~,~ ]    = pslisl( x , 0 , 1);
    else
        [p2,i2,~,~ ]    = pslisl( x );
    end
    o(end+1)            = theta * p2^2 + (1-theta) * i2;

    cnt       = cnt + 1;
    if (o(end-1) - o(end)) <= thr
        break
    end
end
t = toc;
if L <= 2
    x = real(x);
end

if nargout == 0

    disp(['run-time : ', num2str(t),' second'])
%     close all
    MarkerSize = 20;
    
    figure;
    plot(10*log10((o)),'gr*-','MarkerSize',MarkerSize);
    xlabel('iteration')
    ylabel('objective (dB)')
    grid on
    box on
    
    
    figure; hold on
    if pF == 1
        plot(10*log10(abs(pcorr(x0))/N),'b.-','MarkerSize',MarkerSize,'MarkerIndices',1:5:2*N-1);
        plot(10*log10(abs(pcorr(x))/N),'gr*-','MarkerSize',MarkerSize,'MarkerIndices',1:5:2*N-1);
%         title('Periodic auto-correlation')
    else
        plot(10*log10(abs(xcorr(x0))/N),'k:','MarkerSize',MarkerSize,'MarkerIndices',1:5:2*N-1);
        plot(10*log10(abs(xcorr(x))/N),'gr*-','MarkerSize',MarkerSize,'MarkerIndices',1:5:2*N-1);
%         title('Aperiodic auto-correlation')
        ylim([-20*log10(2*sqrt(N)),0])
    end
    box on
    grid on
    legend('Initial Sequence','Obtained Sequence','location','best')
    xlabel('shift (k)')
    ylabel('Correlation Level (dB)')
    
    
    figure; hold on
    if pF == 1
        plot((abs(pcorr(x0))),'b.-','MarkerSize',MarkerSize,'MarkerIndices',1:5:2*N-1);
        plot(abs(pcorr(x)),'gr*-','MarkerSize',MarkerSize,'MarkerIndices',1:5:2*N-1);
        title('Periodic auto-correlation')
    else
        plot((abs(xcorr(x0))),'b.-','MarkerSize',MarkerSize,'MarkerIndices',1:5:2*N-1);
        plot((abs(xcorr(x))),'gr*-','MarkerSize',MarkerSize,'MarkerIndices',1:5:2*N-1);
        title('Aperiodic auto-correlation')
    end
    box on
    grid on
    legend('Initial Sequence','Obtained Sequence','location','best')
    xlabel('shift (k)')
    ylabel('Correlation Level')
    
    figure; plot(real(x),imag(x),'o')
    x = [];
end