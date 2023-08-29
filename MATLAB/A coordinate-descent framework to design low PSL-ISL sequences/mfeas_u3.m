function [ Ak_bar ] = mfeas_u3( mu,kappa, xi,eta ,rho,gamma ,Ak_bar )
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

a           =  mu - gamma;
b           = kappa;
c           = xi - 2*gamma;
d           = eta;
e           = rho - gamma;

p           = ([a , b , c , d, e]);
EPSILON     = 0.00001;

root_tmp    = roots(p);

ind1        = find(imag(root_tmp)== 0,7);
roots1      = real(root_tmp(ind1));


L           = length(roots1);

if L==0 && e <= 0
    return;
elseif L==0 && e > 0
    Ak_bar  = [-inf,inf];
    return
end

roots1      = sort(roots1);
for i = 1 : L 
   beta =  roots1(i);
   [ Pi, Pi1, Pi2, Pi3, Pi4 ] = mderiv2( a,b,c,d,e,beta );
   if i == 1
       xi_1     = -inf;
   else
       xi_1     = roots1(i-1);
   end
   if i == L
       xip1     = +inf;
   else
       xip1     = roots1(i+1);
   end
   xi   = roots1(i);
       
   if Pi1 > EPSILON 
       Ak_bar = muniuon2(  Ak_bar,[xi-eps, xip1+eps;]  );
   elseif Pi1 < -EPSILON 
       Ak_bar = muniuon2(  Ak_bar,[xi_1-eps, xi+eps;]  );
   else
       if Pi2 > EPSILON
           Ak_bar = muniuon2(  Ak_bar,[xi_1-eps, xi+eps;]  );
           Ak_bar = muniuon2(  Ak_bar,[xi-eps, xip1+eps;]  );
       elseif Pi2 < -EPSILON
       else
           if (Pi3 > EPSILON)
               Ak_bar = muniuon2(  Ak_bar,[xi-eps, xip1+eps;]  );
           elseif (Pi3 < -EPSILON)
               Ak_bar = muniuon2(  Ak_bar,[xi_1-eps, xi+eps;]  );
           else
               if Pi4 > EPSILON
                  Ak_bar = muniuon2(  Ak_bar,[xi_1-eps, xi+eps;]  );
                  Ak_bar = muniuon2(  Ak_bar,[xi-eps, xip1+eps;]  );                   
               else
                   continue
               end
           end
       end
   end
   
end

end