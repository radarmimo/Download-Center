function [ mur2,kappar2,xir2,etar2 ,rhor2] = coeflp( ak, bk , ck, rkl)
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
akr         = real(ak);
aki         = imag(ak);
bkr         = real(bk);
bki         = imag(bk);
ckr         = real(ck);
cki         = imag(ck);


arkl        = abs(rkl);
G           = rkl./arkl;
Gr          = real(G);
Gi          = imag(G);


uu2         = (ckr - akr - bkr) .* Gr;
uu1         = 2*(bki - aki) .* Gr;
uu0         = (akr + bkr + ckr) .* Gr;


vv2         = (aki + bki - cki) .* (Gi);
vv1         = 2*(bkr - akr) .* (Gi);
vv0         = -(aki + bki + cki) .* (Gi);

mu2         = uu2 + vv2;
kappa2      = uu1 + vv1;
xi2         = uu0 + vv0;

mur2        = mu2;
kappar2     = kappa2;
xir2        = mu2 + xi2;
etar2       = kappa2;
rhor2       = xi2;


end

