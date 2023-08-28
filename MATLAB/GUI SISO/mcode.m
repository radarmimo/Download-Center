function [ x ] = mcode( strcd , N ,init )
% m.alaee@ec.iut.ac.ir
% mmalaee@yahoo.com

if nargin < 2
    strcd   = 12;
    N       = 64;
    init    = 1;
elseif nargin == 2
    init = 1;
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
    case 12 % m-seq

        x   = mseq(nextpow2(N),init);
    case 13 % gold
        if  mod(nextpow2(N),2)~= 1 && mod(nextpow2(N),4)~=2
            disp('order of the sequence set must satisfying mod(n,2)=1 or mod(n,4)=2');
            return;
        end
        Y   = gold(nextpow2(N));
        x   = Y(:,1);
        
    case 14 % kasami
        if  mod(nextpow2(N),2)~= 0
            disp('order of the sequence set, an even integer.');
            return;
        end
        
        Y   = kasami(nextpow2(N));
        x   = Y(:,1);
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
