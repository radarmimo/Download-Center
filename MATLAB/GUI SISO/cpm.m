function [ x , o, t] = cpm( x0,thr,theta,pF)
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
% This function obtains optimized constant modulus sequence
% ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
% Input:
%           x0      : initial sequence (uni-modular)
%           thr     : stopping threshold
%           theta   : Pareto weight , 0 <= theta  <= 1
%                       theta = 1 -> minimizing PSL,
%                       theta = 0 -> minimizing ISL,
%           pF      : pF = 1 -> minimizing "Periodic" auto-correlation,
%                     otherwise, minimizing "Aperiodic" auto-correlation
% ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
% ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
% Output:
%           x       : optimized sequence (continuous phase)
%           o       : objective values per iteration
%                       (theta * PSL + (1-theta)*ISL)
%           t       : run-time (second)
% ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
% The input parameters can be chosed as follows:
% Initial values if the fucntion was called internally  
if ~exist('x0','var')
    rng(1)
    N               = 100; % code length
    phi             = (2*rand(N,1)-1)*pi; % random initial phase
    x0              = exp(1i * phi); % random initial sequence
end
if ~exist('thr','var')
    thr             = 1e-3; % stopping threshold 
end
if ~exist('theta','var')
    theta           = 0; % pareto weight 
end
if ~exist('pF','var')
    pF              = 0; % periodic auto-correlation optimization flag
end
% ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
tic
x0                  = x0(:); % column wise initial sequence 
N                   = length(x0); % code length 
x                   = x0; 

if pF == 1
    [p1,i1,~,~ ]    = pslisl( x , 0 , 1);
else
    [p1,i1,~,~ ]    = pslisl( x );
end
o(1)                = theta * p1^2 + (1-theta) * i1;

cnt                 = 1;
cnd                 = 1;
while (cnd > 0 && cnt < 20*N)
    for d = 1 : N
        if pF == 1
            [ a_dk,b_dk,c_dk ]      = mabcp( x,d );
        else
            [ a_dk,b_dk,c_dk ]      = mabc( x,d );
        end
        
        [ mu,kappa,xi,eta ,rho]     = coef( a_dk, b_dk , c_dk );
        mu_tilde                    = sum(mu);
        kappa_tilde                 = sum(kappa);
        xi_tilde                    = sum(xi);
        eta_tilde                   = sum(eta);
        rho_tilde                   = sum(rho);
        
        if theta ~= 0 % bisection
            
            cnd_bisection           = 1;
            
            if pF == 1
                [p2,i2,~,~ ]        = pslisl( x , 0 , 1);
            else
                [p2,i2,~,~ ]        = pslisl( x );
            end

            q                       = theta * p2^2 + (1-theta) * i2;
            w                       = 0;
            beta_d                  = [];
            CNT_ITR                 = 0;
            while cnd_bisection && CNT_ITR < 10 
                CNT_ITR             = CNT_ITR + 1;
                barAk = [];
                bar_gamma           = (q + w) /2 ;
                for k = 1 : N - 1
                    mu_bar          = theta * mu(k) + (1 - theta) * mu_tilde;
                    kappa_bar       = theta * kappa(k) + (1 - theta) * kappa_tilde;
                    xi_bar          = theta * xi(k) + (1 - theta) * xi_tilde;
                    eta_bar         = theta * eta(k) + (1 - theta) * eta_tilde;
                    rho_bar         = theta * rho(k) + (1 - theta) * rho_tilde;
                    barAk           = mfeas_u3( mu_bar,kappa_bar, xi_bar,eta_bar ,rho_bar,bar_gamma ,barAk);
                    if ~isempty(barAk)
                        if barAk(1,1) == -inf && barAk(1,2) == inf
                            % problem is infeasible
                            break
                        end
                    end
                    
                end
                if isempty(barAk)
                    % feasible everywhere
                    break;
                else
                    if barAk(1,1) == -inf && barAk(1,2) == inf
                        % infeasible
                        w           = bar_gamma;
                    else
                        % feasible
                        q           = bar_gamma;
                        %                 w
                        if size(barAk,1) > 1
                            beta_d = (barAk(1,2)+barAk(2,1))/2;
                        else
                            Ak      = [-inf, barAk(1);
                                barAk(2), inf];
                            if Ak(1) == -inf
                                Ak(1) = Ak(1,2) - 1e8 * rand(1);
                            end
                            if Ak(end,2) == +inf
                                Ak(end,2) = Ak(end,1) + 1e8 * rand(1);
                            end
                            
                            beta_d = (Ak(1,1)+barAk(1,2))/2;
                        end
                    end
                end
                if (q - w < thr)
                    cnd_bisection = 0;
                end
            end
        else % use the derivative of the objective to find optimal code entry
            
            a1          = -kappa_tilde;
            a2          = (4 * mu_tilde - 2 * xi_tilde);
            a3          = (2 * kappa_tilde - 3 * eta_tilde);
            a4          = (4 * mu_tilde - 4 * rho_tilde);
            a5          = (3 * kappa_tilde - 2 *eta_tilde);
            a6          = (2 * xi_tilde - 4 * rho_tilde);
            a7          = eta_tilde;
            p           = ([a1 , a2 , a3 , a4, a5, a6 , a7]);
            root_tmp    = roots(p);
            
            roots1      = real(root_tmp(find(imag(root_tmp)==0,7)));
            
            betaVec     = (mu_tilde * roots1.^4 + kappa_tilde * roots1.^3 + ...
                xi_tilde * roots1.^2 + eta_tilde * roots1 + rho_tilde) ./ (1 + roots1.^2).^2;
            
            [~, indx]   = min(betaVec);
            beta_d      = roots1(indx);
            
        end
        if ~isempty(beta_d)
            phi_d       = 2*atan(beta_d);
            x(d)        = exp(1i*phi_d);
        end
    end
    disp(num2str(cnt))
    cnt                 = cnt + 1;
    if pF == 1
        [p2,i2,~,~ ]    = pslisl( x , 0 , 1);
    else
        [p2,i2,~,~ ]    = pslisl( x );
    end
    o(end+1)            = theta * p2^2 + (1-theta) * i2;

    
    if (o(end-1) - o(end)) <= thr % stopping criterion 
        cnd = 0;
    end
    
end
t = toc;
if nargout == 0 % plot the outputs if the fucntion was called internally  
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
        plot(20*log10(abs(pcorr(x0))/N),'b.-','MarkerSize',MarkerSize,'MarkerIndices',1:5:2*N-1);
        plot(20*log10(abs(pcorr(x))/N),'gr*-','MarkerSize',MarkerSize,'MarkerIndices',1:5:2*N-1);
        title('Periodic auto-correlation')
    else
        plot(20*log10(abs(xcorr(x0))/N),'b.-','MarkerSize',MarkerSize,'MarkerIndices',1:5:2*N-1);
        plot(20*log10(abs(xcorr(x))/N),'gr*-','MarkerSize',MarkerSize,'MarkerIndices',1:5:2*N-1);
        title('Aperiodic auto-correlation')
        ylim([-20*log10(4*sqrt(N)),0])
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
    
    x = [];
end
