function [X, obj, D_X] = WeBEST_d_1file(X0, p, w, zeta, MaxItr, L, flg_obj)
% ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
% Copyright (c) 2021, <Ehsan Raei>, website: https://radarmimo.com/
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
%    "This product includes software developed by <Ehsan Raei>,
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
% Email: info@radarmimo.com, ehsan.raei@uni.lu, e.raei.d@gmail.com
% Code written by : Ehsan Raei
% Update : October, 2021
% ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
% ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
% This function optimizes set of sequences with discrete phase alphabet
% ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
% Input:
%           X0      : Set of initial uni-modular sequences (M*N matrix).
%           p       : The value of p for lp-norm (scalar)
%           w       : Weight for the correlation lags (1*N vector).
%           zeta    : The stopping threshold (scalar).
%           MaxItr  : The maximum iteration (scalar).
%           L       : The alphabet size (scalar).
%           flg_obj : The flag for reporting the objective function 
%                     (flg_obj == 1 -> shows the obj
%                      flg_obj == 0 -> do not show the obj).
% ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
% ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
% Output:
%           X       : The optimized set of sequences (M*N matrix).
%           obj     : The objective values per iteration.
%           D_X     : The frobenius norm of argument per iteration.
% ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
% The input parameters can be chosed as follows:
if ~exist('X0','var')
    N   	= 64;               % Code length
    M   	= 3;                % Numbers of Antenna
    phi0    = 2*rand(M,N)*pi;   % Initial phases
    X0      = exp(1i*phi0);     % Initial sequence
    w       = ones(1,2*N-1);    % The lags weights
end
if ~exist('p','var')
    p       = 2;                % ISL minimization
end
if ~exist('zeta','var')
    zeta    = 1e-3;             % Algorithm Termination threshold
end
if ~exist('MaxItr','var')
    MaxItr  = 10000;            % Maximum number of iterations
end
if ~exist('flg_obj','var')
    L = 8;                      % The alphabet size.
end
if ~exist('flg_obj','var')
    flg_obj = 1;                % The flag for reporting the objective function.
end

%% Discrete Phase
X           = X0;
[M, N]      = size(X);
if p < 2 
    P = 1;
else
    P = p;
end

D_X          = [];
obj             = [];
if flg_obj == 1
    itr         = 1;
    objTemp     = mwLPNorm_Cost(X, p, w);
    fp          = objTemp.wLp_AP;
    obj         = (fp)^(1/P);
end
reverseStr  = '';
for cycle = 1:MaxItr
    X_old   = X;
    for t = 1:M
        if flg_obj == 1
            fm          = Cost_wfm(X, p, w, t, fp);
        end
        for d = 1:N            
            coeff   = mwLpNorm_coeffe(X, w, t, d);
            a_tldk  = coeff.a_tldk;
            c_tldk  = coeff.c_tldk;
            a_ttdk  = coeff.a_ttdk;
            b_ttdk  = coeff.b_ttdk;
            c_ttdk  = coeff.c_ttdk;            
            
            r_tldk_l    = fft(cat(3, a_tldk, c_tldk), L, 3);                
            if L > 2
                r_ttdk_l	= fft(cat(2, a_ttdk.', c_ttdk.', b_ttdk.'), L, 2);       
            else
                r_ttdk_l	= fft(cat(2, a_ttdk.' +  b_ttdk.', c_ttdk.'), L, 2);       
            end
            
            if flg_obj == 1
                itr                 = itr + 1;
                fo                  = (sum(abs(r_ttdk_l).^p).' + squeeze(2*sum(sum(abs(r_tldk_l).^p, 1), 2)) + fm - (M-1)*(w(N)*N)^p).^(1/P);
                [obj(itr), indx]    = min(fo);
                X(t,d)              = exp(1i*2*pi*(indx-1)/L);

                r_ttdk      = c_ttdk + a_ttdk.*X(t,d) + b_ttdk.*conj(X(t,d));
                r_tldk      = c_tldk + a_tldk.*X(t,d);
                ft_au       = sum(abs(r_ttdk).^p) + (w(N)*N)^p;
                ft_cr       = 2*sum(sum(abs(r_tldk).^p));

                fp          = fm + ft_au + ft_cr - M*(w(N)*N)^p;
            else
                fo          = (sum(abs(r_ttdk_l).^p).' + squeeze(2*sum(sum(abs(r_tldk_l).^p, 1), 2))).^(1/P);
                [~, indx]	= min(fo);
                X(t,d)      = exp(1i*2*pi*(indx-1)/L);
            end
        end        
    end
    D_X(cycle)   = norm(X_old - X, 'fro');
    if flg_obj == 1
        d_obj   = obj(itr-N*M) - obj(itr);
        msg = sprintf('WeBEST-d, p=%d, cycle:%d, d_obj = %d, D_X = %d', p, cycle, d_obj, D_X(cycle));
        fprintf([reverseStr, msg]);
        reverseStr = repmat(sprintf('\b'), 1, length(msg));
    else
        msg = sprintf('WeBEST-d, dp=%d, cycle:%d, D_X = %d', p, cycle, D_X(cycle));
        fprintf([reverseStr, msg]);
        reverseStr = repmat(sprintf('\b'), 1, length(msg));
    end
    if  D_X(cycle) < zeta
        break
    end
end
fprintf('\n');

if nargout == 0
    if p == 2 && norm(w - ones(1, 2*N-1)) == 0
        temp    = mPSLISL(X.',0);
        ISLR    = temp.ISLR_AP;
        disp(['Obtained ISLR = ' num2str(ISLR), 'dB, Lower bound ISLR = ' num2str(10*log10(M*(M-1))) 'dB'])
    end
    
    figure, plot(D_X), grid on, box on
    xlabel('Iteration'), ylabel('dX')
    
    if flg_obj == 1
        figure, plot(downsample(obj, M*N)), grid on, box on
        xlabel('Iteration'), ylabel('Objective Function')
    end
    
    figure, plot(10*log10(abs(xcorr(X(1,:)))/N)), grid on, box on
    hold on, plot(10*log10(N*sqrt((M-1)/(2*M*N-M-1))/N)*ones(2*N-1,1), '--r')
    hold on, plot(10*log10(1/N)*ones(2*N-1,1), '--g')    
    legend('Auto-Correlation', 'PSL Lower bound', 'Sparsity Thershold', 'location', 'best') 
    xlabel('Lag'), ylabel('Normalized auto-correlation (dB)')
    xlim([1 2*N-1])
    
    if M > 1
        for m = 1:M
            cc(:,m)     = 20*log10(abs(xcorr(X(round(M/2),:),X(m,:))/N));
        end
        figure, surf(cc); 
        xlabel('Sequences'), ylabel('Lags')
        xlim([1 M]), ylim([1 2*N])
        az = 180-37.5; el = 30;
        view([az,el])
    end
    
    X       = [];
    obj     = [];
    D_X  = [];
end

end

%%
function [out] = mwLPNorm_Cost(X, p, w)
if ~exist('X','var')
    M       = 4;
    N       = 64;
    phase0  = 2*pi*(rand(M, N));
    X       = exp(1i*phase0);
    w       = ones(1, 2*N-1);
end
if ~exist('p','var')
    p   = 2;
end

[M, N]    	= size(X);

Lp_AP_Au    = 0;
Lp_AP_Cr	= 0;
ISL_AP_Au   = 0;
ISL_AP_Cr   = 0;
PSL_AP_Au   = 0;
PSL_AP_Cr 	= 0;
L00_AP      = 0;
L0_AP       = 0;

wLp_AP_Au   = 0;
wLp_AP_Cr	= 0;
wISL_AP_Au  = 0;
wISL_AP_Cr  = 0;
wPSL_AP_Au  = 0;
wPSL_AP_Cr 	= 0;
% ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
% auto- and cross-correlation
for m = 1 : M
    for l = 1 : M
        % aperiodic
        rk      = xcorr(X(m,:),X(l,:));
        wrk     = w.*(xcorr(X(m,:),X(l,:)));
        if m == l
            Lp_AP_Au	= Lp_AP_Au + sum(abs(rk(1:N-1)).^p) + sum(abs(rk(N+1:end)).^p);
            ISL_AP_Au	= ISL_AP_Au + sum(abs(rk(1:N-1)).^2) + sum(abs(rk(N+1:end)).^2);
            PSL_AP_Au   = max(PSL_AP_Au , max(max(abs(rk(1:N-1))) , max(abs(rk(N+1:end)))));
            
            wLp_AP_Au	= wLp_AP_Au + sum(abs(wrk(1:N-1)).^p) + sum(abs(wrk(N+1:end)).^p);
            wISL_AP_Au  = wISL_AP_Au + sum(abs(wrk(1:N-1)).^2) + sum(abs(wrk(N+1:end)).^2);
            wPSL_AP_Au  = max(wPSL_AP_Au , max(max(abs(wrk(1:N-1))) , max(abs(wrk(N+1:end)))));
        else
            Lp_AP_Cr 	= Lp_AP_Cr + sum(abs(rk).^p);
            ISL_AP_Cr 	= ISL_AP_Cr + sum(abs(rk).^2);
            PSL_AP_Cr   = max(PSL_AP_Cr , max(abs(rk)));
            
            wLp_AP_Cr 	= wLp_AP_Cr + sum(abs(wrk).^p);
            wISL_AP_Cr 	= wISL_AP_Cr + sum(abs(wrk).^2);
            wPSL_AP_Cr  = max(wPSL_AP_Cr , max(abs(wrk)));
        end
        
        L00_AP  = L00_AP + length(rk(abs(rk)<1));
        L0_AP   = L0_AP + length(rk(abs(rk)<N*sqrt((M-1)/(2*M*N-M-1))));
    end
end
% ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
% Output
out.Lp_AP           = Lp_AP_Au + Lp_AP_Cr;
out.Lp_AP_Auto      = Lp_AP_Au;
out.Lp_AP_Cross     = Lp_AP_Cr;
out.ISL_AP          = ISL_AP_Au + ISL_AP_Cr;
out.ISL_AP_Auto     = ISL_AP_Au;
out.ISL_AP_Cross    = ISL_AP_Cr;
out.PSL_AP          = max(PSL_AP_Au, PSL_AP_Cr);
out.PSL_AP_Auto     = PSL_AP_Au;
out.PSL_AP_Cross    = PSL_AP_Cr;

out.wLp_AP          = wLp_AP_Au + wLp_AP_Cr;
out.wLp_AP_Auto     = wLp_AP_Au;
out.wLp_AP_Cross    = wLp_AP_Cr;
out.wISL_AP         = wISL_AP_Au + wISL_AP_Cr;
out.wISL_AP_Auto    = wISL_AP_Au;
out.wISL_AP_Cross   = wISL_AP_Cr;
out.wPSL_AP         = max(wPSL_AP_Au, wPSL_AP_Cr);
out.wPSL_AP_Auto    = wPSL_AP_Au;
out.wPSL_AP_Cross   = wPSL_AP_Cr;

out.L00_AP          = L00_AP;
out.L0_AP           = L0_AP;

if nargout == 0
%    if M > 1
%        figure; plot(abs(w.*xcorr(X(2,:))));
%        figure; plot(abs(w.*xcorr(X(1,:),X(2,:))));
%    else
%        figure; plot(abs(w.*xcorr(X(1,:))));      
%    end
end
end

%%
function fm = Cost_wfm(X, p, w, t, fp)
    [M, N]  = size(X);
    ft      = Cost_wft(X, p, w, t);
    ft_au 	= ft.au;
    ft_cr  	= ft.cr;
    fm     	= fp - ft_au - ft_cr + M*(w(N)*N)^p;
end

%%
function [ft]  = Cost_wft(X, p, w, t)
    [M, ~]	= size(X);
    r_tt	= w.*xcorr(X(t,:));
%     r_tt(N) = 0;
    ft_au   = sum(abs(r_tt).^p);
    ft_cr   = 0;
    for m = 1:M
        if t ~= m
            r_tm            = w.*xcorr(X(t,:), X(m,:));
            ft_cr           = ft_cr + 2*sum(abs(r_tm).^p);
        end
    end
    ft.au   = ft_au;
    ft.cr   = ft_cr;
end

%%
function [out] = mwLpNorm_coeffe(X, w, t, d)
    [M, N]  = size(X);    
    c_tldk  = zeros(M,2*N-1);
    a_tldk  = zeros(M,2*N-1);
    x_td    = X(t,:);
    x_td(d) = 0;
    for l = 1:M
        if l ~= t
            c_tldk(l,:) = w.*xcorr(x_td,X(l,:));
            for k = -N+1:N-1
                if (1 <= d + k ) && (d + k <= N)
                    a_tldk(l,N-k)     = conj(X(l,d+k));
                end
            end
            a_tldk(l,:) = w.*a_tldk(l,:);
        end
    end
    c_tldk(t,:) = [];
    a_tldk(t,:) = [];
    c_mtdk      = conj(flip(c_tldk, 2));
    b_mtdk      = conj(flip(a_tldk, 2));

    c_ttdk      = w.*xcorr(x_td);
    c_ttdk(N)   = [];%0;
    a_ttdk      = zeros(1,2*N-1);
    for k = -N+1:N-1
        if (1 <= d + k) && (d + k <= N)
            a_ttdk(1,N-k)   = conj(X(t,d+k));
        end
    end
    a_ttdk      = w.*a_ttdk;
    a_ttdk(N)   = [];%0;
    b_ttdk      = conj(flip(a_ttdk, 2));
    
%     out.s_ptd   = s_ptd;
    out.a_tldk  = a_tldk;
    out.c_tldk  = c_tldk;
    out.b_mtdk  = b_mtdk;
    out.c_mtdk  = c_mtdk;
    out.a_ttdk  = a_ttdk;
    out.b_ttdk  = b_ttdk;
    out.c_ttdk  = c_ttdk;
end

%%
function [out] = mPSLISL(X,theta)
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
if ~exist('X','var')
    X           = mrandmat(63,4,8);
end
if ~exist('theta','var')
    theta       = 0;
end

[N,N_T]         = size(X);
ISL_AP_Au       = 0;
ISL_AP_Cr       = 0;
ISL_P_Au        = 0;
ISL_P_Cr        = 0;
PSL_AP_Au       = 0;
PSL_AP_Cr       = 0;
PSL_P_Au        = 0;
PSL_P_Cr        = 0;
% ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
%% auto- and cross-correlation
for i           = 1 : N_T
    for j       = 1 : N_T
        % aperiodic
        rk      = (xcorr(X(:,i),X(:,j)));
        if i == j
            ISL_AP_Au   = ISL_AP_Au + sum(abs(rk(1:N-1)).^2) + sum(abs(rk(N+1:end)).^2);
            PSL_AP_Au   = max(PSL_AP_Au , max(max(abs(rk(1:N-1))) , max(abs(rk(N+1:end)))));
        else
            ISL_AP_Cr   = ISL_AP_Cr + sum(abs(rk).^2);
            PSL_AP_Cr   = max(PSL_AP_Cr , max(abs(rk)));
        end
    
        % periodic
        ck              = (pcorr(X(:,i),X(:,j)));
        if i == j
            ISL_P_Au    = ISL_P_Au + sum(abs(ck(1:N-1)).^2) + sum(abs(ck(N+1:end)).^2);
            PSL_P_Au    = max(PSL_P_Au , max(max(abs(ck(1:N-1))) , max(abs(ck(N+1:end)))));        
        else
            ISL_P_Cr    = ISL_P_Cr + sum(abs(ck).^2);
            PSL_P_Cr    = max(PSL_P_Cr , max(abs(ck)));
        end
    end
end
% ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
%% Output

ISLR_AP         = 10 * log10 ((ISL_AP_Au + ISL_AP_Cr)/N^2);
PSLR_AP         = 10 * log10 ((max(PSL_AP_Au,PSL_AP_Cr))^2/N^2);

ISLR_P          = 10 * log10 ((ISL_P_Au + ISL_P_Cr)/N^2);
PSLR_P          = 10 * log10 ((max(PSL_P_Au,PSL_P_Cr))^2/N^2);

Pareto_AP       = theta * (max(PSL_AP_Au,PSL_AP_Cr))^2 + (1 - theta) * (ISL_AP_Au + ISL_AP_Cr);
ParetoR_AP      = 10 * log10(Pareto_AP / N^2);

Pareto_P        = theta * (max(PSL_P_Au,PSL_P_Cr))^2 + (1 - theta) * (ISL_P_Au + ISL_P_Cr);
ParetoR_P       = 10 * log10(Pareto_P / N^2);


out.PSL_AP      = (max(PSL_AP_Au,PSL_AP_Cr));
out.ISL_AP      = (ISL_AP_Au + ISL_AP_Cr) ;
out.PSL_P       = (max(PSL_P_Au,PSL_P_Cr));
out.ISL_P       = (ISL_P_Au + ISL_P_Cr) ;
out.PSLR_AP     = PSLR_AP;
out.ISLR_AP     = ISLR_AP;
out.PSLR_P      = PSLR_P;
out.ISLR_P      = ISLR_P ;
out.Pareto_AP   = Pareto_AP;
out.ParetoR_AP  = ParetoR_AP;
out.Pareto_P    = Pareto_P;
out.ParetoR_P   = ParetoR_P;
out.PSL_AP_Auto = PSL_AP_Au;
out.PSL_AP_Cross = PSL_AP_Cr;
out.ISL_AP_Auto = ISL_AP_Au;
out.ISL_AP_Cross = ISL_AP_Cr;

if nargout == 0
   if N_T > 1
       figure; plot(abs(xcorr(X(:,2))));
       figure; plot(abs(pcorr(X(:,2))));
       figure; plot(abs(xcorr(X(:,1),X(:,2))));
       figure; plot(abs(pcorr(X(:,1),X(:,2))));
   else
       figure; plot(abs(xcorr(X(:,1))));
       figure; plot(abs(pcorr(X(:,1))));
       
   end
end
end

%%
function [ r ] = pcorr( x , y)
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
if ~exist('x','var')
    N           = 50; % sequence length
    phi         = (2*rand(N,1)-1)*pi;
    x           = exp(1i * phi);
end
if ~exist('y','var')
    y           = x;
end

x               = x(:);
N               = length(x);
r               = zeros(2*N-1,1);
pc1             = ifft(fft(x).*conj(fft(y)));
r(N:end)        = pc1;
r(1:N-1)        = pc1(end:-1:2);
    
if nargout == 0
    figure;
    hold all;
    plot(abs(r))
    r = [];
end
end


