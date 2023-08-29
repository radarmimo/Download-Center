function [ mu,kappa,xi,eta ,rho] = coef( ak, bk , ck )
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

akr     = real(ak);
aki     = imag(ak);
bkr     = real(bk);
bki     = imag(bk);
ckr     = real(ck);
cki     = imag(ck);

mu1     = (akr+bkr).^2 - 2*ckr.*(akr+bkr)+ckr.^2;
kappa1  = -4*(akr+bkr).*(bki-aki)+4*ckr.*(bki-aki);
xi1     = -2*(akr+bkr).^2 + 2*ckr.^2+4*(bki-aki).^2;
eta1    = 4*(akr+bkr).*(bki-aki)+4*ckr.*(bki-aki);
rho1    = (akr+bkr).^2+2*(akr+bkr).*ckr+ckr.^2;


mu2     = (aki+bki).^2 - 2*cki.*(aki+bki)+cki.^2;
kappa2  = -4*(aki+bki).*(akr-bkr)+4*cki.*(akr-bkr);
xi2     = -2*(aki+bki).^2 + 2*cki.^2+4*(akr-bkr).^2;
eta2    = 4*(aki+bki).*(akr-bkr)+4*cki.*(akr-bkr);
rho2    = (aki+bki).^2+2*(aki+bki).*cki+cki.^2;


mu      = (mu1+mu2);
kappa   = (kappa1+kappa2);
xi      = (xi1+xi2);
eta     = (eta1+eta2);
rho     = (rho1+rho2) ;

end

