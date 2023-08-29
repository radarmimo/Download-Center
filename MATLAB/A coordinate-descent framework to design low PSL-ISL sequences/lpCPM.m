function [ x , o , t] = lpCPM( x0,P,thr,pF)
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
% This function obtains optimized constant modulus sequence by lp-norm
% minimization of auto-correlation lags
% ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
% Input:
%           x0      : initial sequence (uni-modular)
%           P       : is an array which its entry will be multiplied by 2 
%                       and then  used for Lp-Norm minimization, using the 
%                       increasing scheme, 
%                       i.e., ||x||_{2P(1)} = (|x_1|^{P(1)} + ... +
%                       |x_N|^{P(1)})^{1/P}
%           thr     : stopping threshold
%           pF      : pF = 1 -> minimizing "Periodic" auto-correlation,
%                     otherwise, minimizing "Aperiodic" auto-correlation
% ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
% ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
% Output:
%           x       : optimized sequence (continuous phase)
%           o       : PSL values per Lp-Norm minimization for every P entry
%           t       : run-time (second)
% ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
% The input parameters can be chosed as follows:
% Initial values if the fucntion was called internally  

if ~exist('x0','var')
    rng(1)
    N           = 50; % code length
    phi         = (2*rand(N,1)-1)*pi; % initial phase
    x0          = exp(1i * phi); % initial sequence
end
if ~exist('thr','var')
    thr         = 1e-5; % stopping threshold 
end 
if ~exist('P','var')
    P           = 1 : 6; % p values for lp-Norm minimization (we use 2P)
end
if ~exist('pF','var')
    pF          = 1; % periodic auto-correlation optimization flag
end
% ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
x               = x0(:);
N               = length(x);
L               = length(P);
if pF == 1
    o           = pslisl(x,0,1);
    rkln        = abs(pcorr(x));
else
    o           = pslisl(x);
    rkln        = abs(xcorr(x));
end

rkl             = rkln(1:N-1);
tn              = norm(rkl,2);
lpnorm(1)       = tn;

cnt             = 1;
tic
for l = 1 : L
    cnd         = 1;
    p           = 2^(P(l));
    
    if pF == 1
        rkln    = abs(pcorr(x));
    else
        rkln    = abs(xcorr(x));
    end
    rkl         = rkln(1:N-1);
    tn          = norm(rkl,p);
    if tn^p == inf || tn^p < thr
        continue
    end
    cnt2        = 1;
    while (cnd > 0 && cnt2 < 20*N)
        %
        for d = 1 : N
            
            if pF == 1
                [ ak,bk,ck ] = mabcp( x,d );
            else
                [ ak,bk,ck ] = mabc( x,d );
            end
            
            rkl             = conj(ak * x(d) + bk * conj(x(d)) + ck);
            
            arkl            = abs(rkl);
            tn              = norm(arkl,p);
            tau_k           = (tn^p - arkl.^p - p * arkl.^(p-1).*(tn - arkl)) ./ (tn - arkl).^(2);
            
            lambda_k        = (p * arkl.^(p-1) - 2 * tau_k .* arkl);
            
            [ mu,kappa,xi,eta ,rho] = coef( ak, bk , ck );
            [ mur2,kappar2,xir2,etar2 ,rhor2] = coeflp( ak, bk , ck,rkl );
            mu_tilde        = sum(tau_k .* mu + lambda_k .* mur2 );
            kappa_tilde     = sum(tau_k .* kappa + lambda_k .* kappar2 );
            xi_tilde        = sum(tau_k .* xi + lambda_k .* xir2 );
            eta_tilde       = sum(tau_k .* eta + lambda_k .* etar2 );
            rho_tilde       = sum(tau_k .* rho + lambda_k .* rhor2 );
            
            a1              = -real(kappa_tilde);
            a2              = real(4 * mu_tilde - 2 * xi_tilde);
            a3              = real(2 * kappa_tilde - 3 * eta_tilde);
            a4              = real(4 * mu_tilde - 4 * rho_tilde);
            a5              = real(3 * kappa_tilde - 2 *eta_tilde);
            a6              = real(2 * xi_tilde - 4 * rho_tilde);
            a7              = real(eta_tilde);

            pr1             = ([a1 , a2 , a3 , a4, a5, a6 , a7]);
            if isnan(pr1)
                continue
            end
            
            root_tmp        = roots(pr1);
            if isnan(root_tmp)
                continue
            end
            roots1          = real(root_tmp(find(imag(root_tmp)==0,7)));
            betaVec         = (mu_tilde * roots1.^4 + kappa_tilde * roots1.^3 + ...
                xi_tilde * roots1.^2 + eta_tilde * roots1 + rho_tilde) ./ (1 + roots1.^2).^2;
            
            [~, indx]       = min(betaVec);
            beta_d          = roots1(indx);
            
            if ~isempty(beta_d)
                phi_d       = 2*atan(beta_d);
                x(d)        = exp(1i*phi_d);
            end
        end

        
        if pF == 1
            rkln            = pcorr(x);
        else
            rkln            = xcorr(x);
        end
        
        rkl                 = rkln(N+1:end);
        arkl                = abs(rkl);
        
        lpnorm(end+1)       = norm(arkl,p);
        if (lpnorm(end-1) - lpnorm(end))/lpnorm(end) <= thr/p
            cnd             = 0;
        end
        cnt2                = cnt2 + 1;
        
    end
    disp(num2str(cnt))
    cnt                     = cnt + 1;
    
    if pF == 1
        o(end+1)            = pslisl(x,0,1);
    else
        o(end+1)            = pslisl(x);

    end
end

t = toc;

if nargout == 0
    disp(['run-time : ', num2str(t),' second'])
    close all
    MarkerSize = 20;
    
    figure;
    plot(10*log10((o)),'gr*-','MarkerSize',MarkerSize);
    xlabel('p')
    ylabel('PSL (dB)')
    grid on
    box on

    figure; hold on
    if pF == 1
        plot(10*log10(abs(pcorr(x0))/N),'b.-','MarkerSize',MarkerSize,'MarkerIndices',1:5:2*N-1);
        plot(10*log10(abs(pcorr(x))/N),'gr*-','MarkerSize',MarkerSize,'MarkerIndices',1:5:2*N-1);
        title('Periodic auto-correlation')
    else
        plot(10*log10(abs(xcorr(x0))/N),'b.-','MarkerSize',MarkerSize,'MarkerIndices',1:5:2*N-1);
        plot(10*log10(abs(xcorr(x))/N),'gr*-','MarkerSize',MarkerSize,'MarkerIndices',1:5:2*N-1);
        title('Aperiodic auto-correlation')
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
    
    x = [];
end
