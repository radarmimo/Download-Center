function [ x ] = mcode( strcd , N  )
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
% Last update : 2017
% ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
if nargin < 2
    strcd   = 2;
    N       = 64;
end

L0      = N;
x       = [];
switch strcd
    % ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    % ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    % polyphase
    case 1 % frank
        N       = (fix(sqrt(N)))^2;
        chpfrnk = N;
        code    = zeros(1,chpfrnk);
        k       = 1;
        for i = 1 : sqrt(chpfrnk)
            for j = 1 : sqrt(chpfrnk)
                code(k) = exp(1i * 2 * pi /sqrt(chpfrnk) * (i-1) * (j-1) );
                k = k  + 1;
            end
        end
        x       = code(:);

    case 2 % golomb
        
        alpha = exp(1i * 2*pi /N);
        exponent = (0:(N-1))' .* (1:N)' / 2;
        x = alpha.^exponent;
        
        
    case 3 % p1
        L   = sqrt(N);
        phi = zeros(L,L);
        for k = 1 : L
            for n = 1: L
                phi(n,k) = 2*pi/L *((L+1)/2-n)*((n-1)*L+(k-1));
            end
        end
        phi = phi(:);
        x   = exp(1i * phi);
    case 4 % p2
        L   = sqrt(N);
        phi = zeros(L,L);
        for k = 1 : L
            for n = 1: L
                phi(n,k) = 2*pi/L *((L+1)/2-k)*((L+1)/2-n);
            end
        end
        phi = phi(:);
        x   = exp(1i * phi);
    case 5 % px
        L   = sqrt(N);
        phi = zeros(L,L);
        if mod(L,2) == 0
            for k = 1 : L
                for n = 1: L
                    phi(n,k) = 2*pi/L *((L+1)/2-k)*((L+1)/2-n);
                end
            end
        else
            for k = 1 : L
                for n = 1: L
                    phi(n,k) = 2*pi/L *((L)/2-k)*((L+1)/2-n);
                end
            end
        end
        phi = phi(:);
        x   = exp(1i * phi);
    case 6 % p4
        n   = (1:N)';
        phi = 2*pi/N * (n-1) .* (n-1-N)/2;
        x   = exp(1i * phi);
        
    case 7 % Zadoff-Chu
        if mod(N,2)==0
            x = exp(1i * pi * (1:N).^2 /N);
        else
            x = exp(1i * pi * (2:(N+1)) .* (1:N) /N);
        end
        
    case 8 % random
        phi    = (2*rand(N,1)-1)*pi;
        x      = exp(1i * phi);
        % ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        % binary
    case 11 % barker
        switch N
            case 2
                x = [-1 1];
            case 3
                x = [-1 -1 1];
            case 4
                x = [-1 -1 1 -1];
            case 5
                x = [-1 -1 -1 1 -1];
            case 7
                x = [-1 -1 -1 1 1 -1 1];
            case 11
                x = [-1 -1 -1 1 1 1 -1 1 1 -1 1];
            case 13
                x = [-1 -1 -1 -1 -1 1 1 -1 -1 1 -1 1 -1] ;
        end

    case 15 % random
        x      = 2 * round(rand(N,1)) - 1;
    case 16 
        x      = exp(1i * zeros(N,1));
        
        
end
if N ~= L0
    disp(['Warning ... , the length changed to ', num2str(N)]);
end
x   = x(:);

if nargout == 0
   figure; plot(abs(xcorr(x))) 
end
end
% ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
