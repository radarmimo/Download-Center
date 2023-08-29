function [X, obj, lp, D_X, D_grad] = WeBEST_v_1file(X0, p, w, alpha, beta, zeta, MaxItr, epsilon, MM, flg_obj)
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
%           alpha   : The parameter alpha for backtracking line search
%                     algorithm (0 < alpha < 0.5).
%           beta    : The parameter beta for backtracking line search
%                     algorithm (0 < beta < 1).
%           zeta    : The stopping threshold (scalar).
%           MaxItr  : The maximum iteration (scalar).
%           epsilon : The epsilon parameter for smoth approximation
%                     function (scalar).
%           MM      : The MM function selection (MM = {1,2,3}).
%           flg_obj : The flag for reporting the objective function 
%                     (flg_obj == 1 -> shows the obj
%                      flg_obj == 0 -> do not show the obj).
% ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
% ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
% Output:
%           X       : The optimized set of sequences (M*N matrix).
%           obj     : The objective values per iteration.
%           lp      : The lp-norm of the sequence per iteration
%           D_X     : The frobenius norm of argument per iteration.
%           D_grad  : The frobenius norm of gradient per iteration.
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
if ~exist('alpha','var')
    alpha   = 0.4;              % 0 < alpha < 0.5
end
if ~exist('beta','var')
    beta    = 0.8;              % 0 < beta < 1
end
if ~exist('zeta','var')
    zeta    = 1e-3;             % Algorithm Termination threshold
end
if ~exist('MaxItr','var')
    MaxItr  = 10000;            % Maximum number of iterations
end
if ~exist('epsilon','var')      
    epsilon = 0.05;             % The epsilon parameter for smoth approximation function.
end
if ~exist('MM','var')
    MM      = 1;                % The MM function selection.
end
if ~exist('flg_obj','var')
    flg_obj = 1;                % The flag for reporting the objective function.
end

%% WeBEST-v
if p > 0 && p <= 1
    [X, D_grad, obj, lp, D_X]   = mwLppNorm_BSUM_v(X0, p, w, alpha, beta, zeta, MaxItr, epsilon, MM, flg_obj);
elseif p >= 2
    [X, obj, D_grad, D_X]       = mwLpNorm_BSUM_v(X0, p, w, zeta, MaxItr, alpha, beta, flg_obj);
    lp                          = obj;
else
    disp('The parameter p should be, 0 < p <= 1 or p >= 2.')
    return
end

if nargout == 0
    if p == 2
        objTemp     = mPSLISL(X.', 0);
        disp(['lower bound = ' num2str(10*log10(M*(M-1))) 'dB, ISLR = ' num2str(objTemp.ISLR_AP) 'dB'])
    end   
    
    figure, plot(D_X), grid on, box on
    xlabel('Iteration'), ylabel('dX')
    
    if flg_obj == 1
        figure, plot(downsample(obj, M)), grid on, box on
        xlabel('Iteration'), ylabel('Objective Function')
        
        figure, plot(D_grad), grid on
        xlabel('Iteration'), ylabel('Gradient')
    end
    
    figure, plot(10*log10(abs(xcorr(X(1,:)))/N)), grid on, box on
    hold on, plot(10*log10(N*sqrt((M-1)/(2*M*N-M-1))/N)*ones(2*N-1,1), '--r')
    hold on, plot(10*log10(1/N)*ones(2*N-1,1), '--g')    
    legend('Auto-Correlation', 'PSL Lower bound', 'Sparsity Thershold', 'location', 'best') 
    xlabel('Lag'), ylabel('Normalized auto-correlation (dB)')
    xlim([1 2*N-1])
    
    if M > 1
        cc  = zeros(2*N-1, M);
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
    D_grad  = [];
    obj     = [];
    D_X     = [];
end
end

%% 
function [X, obj, D_grad, D_X] = mwLpNorm_BSUM_v(X0, p, w, zeta, MaxItr, alpha, beta, flg_obj)
X       = X0;
[M, N]  = size(X0);
phi0    = angle(X0); 
phi     = phi0;  

obj     = [];
D_X  = [];
D_grad    = [];
if flg_obj == 1
    itr     = 1;
    objTemp = mwLPNorm_Cost(X, p, w);
    fp      = objTemp.wLp_AP;
    obj     = (fp)^(1/p);
    
    D_Phi  = zeros(M,N);
    for t = 1:M
        d_phi           = -Grad_ut(X, p, w, t); 
        D_Phi(t,:)      = d_phi;
    end
    D_grad  = norm(D_Phi, 'fro');
end
reverseStr  = '';
for cycle = 1:MaxItr
    X_old   = X;
    for t = 1:M
        if flg_obj == 1
            fm  = Cost_wfm(X, p, w, t, fp);
        end        
        d_phi           = -Grad_ut(X, p, w, t);
        s               = 1;%1/norm(dx);
        [X, phi, ft]    = BackTracking_ut(X, p, w, t, phi, alpha, beta, d_phi, s);
        
        if flg_obj == 1
            itr             = itr +1;
            fp              = fm + ft.au + ft.cr - M*(w(N)*N)^p;
            obj(itr)        = (fp)^(1/p);
            
            D_Phi(t,:)      = d_phi;
        end
    end
    D_X(cycle)  = norm(X_old - X, 'fro');
    if flg_obj == 1
        d_obj               = obj(itr-M) - obj(itr);
        D_grad(cycle+1)     = norm(D_Phi, 'fro');
        msg                 = sprintf('WeBEST-v, p=%d, cycle:%d, d_obj = %d, D_X = %d', p, cycle, d_obj, D_X(cycle));
        fprintf([reverseStr, msg]);
        reverseStr = repmat(sprintf('\b'), 1, length(msg));
        
    else
        msg     = sprintf('WeBEST-v, p=%d, cycle:%d, D_X = %d', p, cycle, D_X(cycle));
        fprintf([reverseStr, msg]);
        reverseStr = repmat(sprintf('\b'), 1, length(msg));
    end
    if  D_X(cycle) < zeta
        break
    end
end
fprintf('\n');

end
%%

%%
function [X, D_grad, obj, lp, D_X] = mwLppNorm_BSUM_v(X0, p, w, alpha, beta, zeta, MaxItr, epsilon, MM, flg_obj)
X       = X0;
[M, N]  = size(X0);
phi0    = angle(X0); 
phi     = phi0;    

D_grad  = [];
obj     = [];
lp      = [];
reverseStr  = '';
if flg_obj == 1
    itr     = 1;
    gip     = Cost_gi(X, p, w, MM, epsilon);
    obj     = gip;
    
    objTemp = mwLPNorm_Cost(X, p, w);
    lp      = objTemp.wLp_AP;
    
    D_phi  = zeros(M,N);
    for t = 1:M
        d_phi           = -Grad_vt(X, p, w, t, MM, epsilon); 
        D_Phi(t,:)      = d_phi;
    end
    D_grad      = norm(D_Phi, 'fro');
end

for cycle = 1:MaxItr
    X_old   = X;
    for t = 1:M
        if flg_obj == 1
            gim         = Cost_gim(X, p, w, t, gip, MM, epsilon);  
        end
        
        d_phi           = -Grad_vt(X, p, w, t, MM, epsilon);  
        s               = 1;%1/norm(dx);        
        [X, phi, git]   = BackTracking_vit(X, p, w, t, phi, alpha, beta, d_phi, s, MM, epsilon);
        if flg_obj == 1
            D_phi(t,:)  = d_phi;
            
            itr         = itr +1;
            gip         = gim + git.au + git.cr;
            obj(itr)    = gip;
            
            objTemp     = mwLPNorm_Cost(X, p, w);
            lp(itr)     = objTemp.wLp_AP;
        end
    end
    D_X(cycle)   = norm(X_old - X, 'fro');
    if flg_obj == 1
        d_obj               = obj(itr-M) - obj(itr);
        D_grad(cycle+1)     = norm(D_phi, 'fro');
        msg                 = sprintf('WeBEST-v, p=%d, cycle:%d, d_obj=%d, D_X=%d', p, cycle, d_obj, D_X(cycle));
        fprintf([reverseStr, msg]);
        reverseStr = repmat(sprintf('\b'), 1, length(msg));
    else
        msg = sprintf('WeBEST-v, p=%d, cycle:%d, d_norm=%d', p, cycle, D_X(cycle));
        fprintf([reverseStr, msg]);
        reverseStr = repmat(sprintf('\b'), 1, length(msg));
    end
    if  D_X(cycle) < zeta
        break
    end
end
fprintf('\n');
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
    % auto- and cross-correlation
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
    % Output
    
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
function gi = Cost_gi(X, p, w, MM, epsilon)
    t       = 1;
    [M, N]  = size(X);
    wr_ml   = zeros((M-1)^2, 2*N-1);
    mm      = 0;
    for m = 1:M
        if m ~= t
           for l = 1:M
                if l ~= t
                    mm              = mm+1;
                    wr_ml(mm, :)    = w.*xcorr(X(m,:),X(l,:));
                end
            end 
        end        
    end
    gi_ml   = Smooth_function_f(wr_ml, MM, p, epsilon);
    gim     = sum(sum(gi_ml));
    
    git     = Cost_git(X, p, w, t, MM, epsilon);
    git_au  = git.au;
    git_cr  = git.cr;

    gi      = gim + git_au + git_cr;
end

%%
function git = Cost_git(X, p, w, t, MM, epsilon)
    [M, ~]  = size(X);
    wr_tt 	= w.*xcorr(X(t,:));
    gi_tt   = Smooth_function_f(wr_tt, MM, p, epsilon);
    git_au 	= sum(gi_tt);
    git_cr	= 0;        
    for m = 1:M
        if t ~= m
            wr_tm   = w.*xcorr(X(t,:), X(m,:));
            gi_tm   = Smooth_function_f(wr_tm, MM, p, epsilon);
            git_cr  = git_cr + 2*sum(sum(gi_tm));
        end
    end
    git.au  = git_au;
    git.cr  = git_cr;
end

%%
function gim = Cost_gim(X, p, w, t, gip, MM, epsilon)
    git     = Cost_git(X, p, w, t, MM, epsilon);
    git_au	= git.au;
    git_cr	= git.cr;
    gim  	= gip - git_au - git_cr;      
end

%%
function [Xdx, phi, ft] = BackTracking_ut(X, p, w, t, phi, alpha, beta, d_phi, s)
    ft          = Cost_wft(X, p, w, t);
    f_x         = ft.au + ft.cr;

    Xdx       	= X;
    Xdx(t,:)   	= exp(1i*(phi(t,:) + s*d_phi));
    ft          = Cost_wft(Xdx, p, w, t);
    f_xdx       = ft.au + ft.cr;

    while(f_xdx > f_x - alpha*s*d_phi.^2)
        s           = s*beta;
        if s < 1e-20
            break
        end

        Xdx(t,:)   	= exp(1i*(phi(t,:) + s*d_phi));
        ft          = Cost_wft(Xdx, p, w, t);
        f_xdx       = ft.au + ft.cr;
    end
    phi(t,:)    = phi(t,:) + s*d_phi;
end

%%
function [Xdx, phi, git] = BackTracking_vit(X, p, w, t, phi, alpha, beta, d_phi, s, MM, epsilon)
    git     = Cost_git(X, p, w, t, MM, epsilon);
    gi_x    = git.au + git.cr;

    Xdx         = X;
    Xdx(t,:)    = exp(1i*(phi(t,:) + s*d_phi));
    git         = Cost_git(Xdx, p, w, t, MM, epsilon);
    gi_xdx      = git.au + git.cr;
    while(gi_xdx > gi_x - alpha*s*d_phi.^2)
        s           = s*beta;
        Xdx(t,:)    = exp(1i*(phi(t,:) + s*d_phi));
        git         = Cost_git(Xdx, p, w, t, MM, epsilon);
        gi_xdx      = git.au + git.cr;
    end
    phi(t,:)    = phi(t,:) + s*d_phi;
end

%% 
function [dx]  = Grad_ut(X, p, w, t)
    [M, ~]  = size(X);
    r_tt    = w.*xcorr(X(t,:));
    a_tt    = Surrogate_function_ft(r_tt, p);
    dx      = gradient_wau(X(t,:), w.*sqrt(a_tt));
    
    for m = 1:M
        if t ~= m
            r_tm    = w.*xcorr(X(t,:), X(m,:));
            a_tm    = Surrogate_function_ft(r_tm, p);
            dx      = dx + 2*gradient_wcr(X(t,:), X(m,:), w.*sqrt(a_tm));
        end
    end
end

%%
function d_phi = Grad_vt(X, p, w, t, MM, epsilon)
    [M, ~]      = size(X);
    wr_tt       = w.*xcorr(X(t,:));
    gammai_tt   = Surrogate_function_vi(wr_tt, MM, p, epsilon);
    d_phi       = gradient_wau(X(t,:), w.*sqrt(gammai_tt));
    for m = 1:M
        if t ~= m
            wr_tm       = w.*xcorr(X(t,:), X(m,:));
            gammai_tm   = Surrogate_function_vi(wr_tm, MM, p, epsilon);
            d_phi       = d_phi + 2*gradient_wcr(X(t,:), X(m,:), w.*sqrt(gammai_tm));
        end
    end
end

%%
function [a]  = Surrogate_function_ft(rk, p)
%     t       = sum(abs(rk).^p, 2).^(1/p);
% 
%     a_k     = (t.^p - abs(rk).^p - p*abs(rk).^(p-1).*(t-abs(rk)))./((t - abs(rk)).^2);
%     b_k     = p*abs(rk).^(p-1) - 2*a_k.*abs(rk);
% %     b_k   	= p*abs(rk).^(p-2) - 2*a_k;
%     c_k     = a_k.*abs(rk).^2 - (p-1)*abs(rk).^p;
% 
% %     gamma_k   = 0.5*abs(rk).^(-1);
%     mu_k      = 0.5*abs(rk);
%     
%     %a2  = a_k + b_k.*gamma_k;
%     a2  = 0.5*p*abs(rk).^(p-2);
%     a0  = b_k.*mu_k + c_k;
    a   = 0.5*p*abs(rk).^(p-2);
end

%%
function [gammai]  = Surrogate_function_vi(rk, MM, p, epsilon)
    switch MM
        case 1           
            gamma1  = 0.5*p*epsilon^(p-2)*ones(size(rk));
            gamma2  = 0.5*p*abs(rk).^(p-2);
        case 2
            gamma1  = 1*ones(size(rk))./(2*epsilon*(p+epsilon)*log(1+1/p));
            gamma2  = 1./(2*log(1+1/p)*abs(rk).*(abs(rk)+p));
        case 3
            gamma1	= ones(size(rk))*exp(-epsilon/p)/(2*p*epsilon);
            gamma2	= exp(-abs(rk)/p)./(2*p*abs(rk));            
        otherwise
            disp('Choose from 1 to 3')
            return
    end    
    gamma1(abs(rk) > epsilon)  = 0;
    gamma2(abs(rk) <= epsilon)	= 0;
    gammai                      = gamma1 + gamma2;
end

%%
function [gi]  = Smooth_function_f(rk, MM, p, epsilon)
    switch MM
        case 1
            g1      = 0.5*p*epsilon^(p-2)*abs(rk).^2;        
            g2      = abs(rk).^p - (1-0.5*p)*epsilon^p;      
        case 2
            g1      = (abs(rk).^2)./(2*epsilon*(p+epsilon)*log(1+1/p));
            g2      = (log(1 + abs(rk)/p) - log(1+epsilon/p) + epsilon/(2*(p+epsilon)))./(log(1+1/p));
        case 3
            g1      = exp(-epsilon/p)*abs(rk).^2/(2*p*epsilon);
            g2      = - exp(-abs(rk)/p) + (1+epsilon/(2*p))*exp(-epsilon/p);
        otherwise
            disp('Choose from 1 to 3')
            return
    end
    g1(abs(rk) > epsilon)       = 0;
    g2(abs(rk) <= epsilon)      = 0;
    gi                          = g1 + g2;
end

%%
function    grad_an = gradient_wau(a, w)
    p           = 1;
    N           = length(a);
    fa          = fft(a,2*N-1);
    x           = fftshift(ifft(abs(fa).^2));
    g           = w.^(2*p).*x.*abs(x).^(2*p-2);
    gar         = fftshift(ifft(fft(g,2*N-1).*fa));
    grad_am     = 4*[gar(end) gar(1:N-1)];
    grad_an     = imag(conj(a).*grad_am);
end

%% 
function    grad_an = gradient_wcr(a, b, w)
    p           = 1;
    d           = 0;
    N           = length(b);
    fa          = fft(b,2*N-1);
    fb          = fft(a,2*N-1);    
    x           = fftshift(ifft(conj(fa).*fb));    
    g           = w.^(2*p).*abs(x-d).^(2*p-2).*(x-d);
    fg          = fft(g);
    gar         = fftshift(ifft(fg.*fa));
    grad_am     = 2*p*[gar(end) gar(1:N-1)];
    grad_an     = imag(conj(a).*grad_am);
end
