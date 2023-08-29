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

