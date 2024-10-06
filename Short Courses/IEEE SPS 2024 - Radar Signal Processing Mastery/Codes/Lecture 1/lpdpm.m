function [ x , lpnorm , t] = lpdpm( x0,P,thr,L,pF)
% ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
% Copyright (c) 2021, <Mohammad Alaee>, website: https://radarmimo.com/
% All rights reserved.
% Website: https://radarmimo.com/
% Email: info@radarmimo.com, mohammad.alaee@uni.lu, mmalaee@yahoo.com
% Code written by : Mohammad Alaee-Kerahroodi
% Update : December 2021
% ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
% ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
% This function obtains optimized constant modulus sequence by lp-norm
% minimization of auto-correlation lags
% ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
% Input:
%           x0      : initial sequence (uni-modular)
%           P       : is an array with minimum value of 2, using the
%                       increasing scheme,
%                       i.e., ||x||_{2P(1)} = (|x_1|^{P(1)} + ... +
%                       |x_N|^{P(1)})^{1/P}
%           thr     : stopping threshold
%           L       : alphabet size (M-ary PSK design)
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
    N = 200;
    alpha = exp(1i * 2*pi /N);
    exponent = (0:(N-1))' .* (1:N)' / 2;
    x0 = alpha.^exponent;
end
if ~exist('L','var') % alphabet size
    L           = 2;
end
if ~exist('thr','var')
    thr         = 1e-5; % stopping threshold
end
if ~exist('P','var')
    P           = 1:6; % p values for lp-Norm minimization (we use 2P)
end
if ~exist('pF','var')
    pF          = 0; % periodic auto-correlation optimization flag
end
% ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
x0              = x0(:);
N               = length(x0);
% Quantize, to make sure the initial sequence has appropriate alphabet size
x0              = exp(1i * floor(angle(x0(1:N))/(2*pi/L))*(2*pi/L));
x               = x0;

LnthP           = length(P);
if pF == 1
    arkln       = abs(pcorr(x));
else
    arkln       = abs(xcorr(x));
end
arkl            = arkln(1:N-1);
tn              = norm(arkl,P(1));
lpnorm(1)       = tn;


tic
for l = 1 : LnthP
    p           = P(l);

    while 1

        for d = 1 : N
            if pF == 1
                [ak,bk,ck]  = mabcp( x,d );
            else
                [ak,bk,ck]  = mabc( x,d );
            end
            if L == 2
                X1          = [ak+bk,ck];
            else
                X1          = [ak,ck,bk];
            end
            Y               = (fft(X1,L,2)).';

            % normalize by t^p to avoid numerical issue
            Y1_1n           = abs(Y)./tn;
            Y1_2n           = Y1_1n.^2;

            % simplified weight
            lambdaNew_k     = p/2 * Y1_1n.^(p-2);

            Omega           = real(lambdaNew_k .* Y1_2n );

            mYobj           = (sum(Omega.')).^(1/p);
            [~,iy]          = min(mYobj);
            phf1est         = 2*pi*(iy-1)/L;
            if phf1est > pi
                phf1est     = phf1est - 2*pi;
            end
            x(d)           = exp(1i * phf1est);
        end

        arkln               = abs(xcorr(x));
        arkl                = arkln(1:N-1);
        tn                  = norm(arkl,p);
        lpnorm(end+1)       = tn;

        if (lpnorm(end-1) - lpnorm(end))/lpnorm(end) <= thr/p
            break
        end

    end
end

t = toc;
if L == 2
    x = real(x);
end

if nargout == 0
    disp(['run-time : ', num2str(t),' second'])
    close all
    MarkerSize = 20;

    figure;
    plot(10*log10(lpnorm),'gr*-','MarkerSize',MarkerSize);
    xlabel('p')
    ylabel('Objective (dB)')
    grid on
    box on
    axis tight

    figure; hold on
    if pF == 1
        plot(-N+1:N-1,20*log10(abs(pcorr(x0))/N),'b-','MarkerSize',MarkerSize,'MarkerIndices',1:5:2*N-1);
        plot(-N+1:N-1,20*log10(abs(pcorr(x))/N),'gr-','MarkerSize',MarkerSize,'MarkerIndices',1:5:2*N-1);
        title('Periodic auto-correlation')
    else
        plot(-N+1:N-1,20*log10(abs(xcorr(x0))/N),'b-','MarkerSize',MarkerSize,'MarkerIndices',1:5:2*N-1);
        plot(-N+1:N-1,20*log10(abs(xcorr(x))/N),'gr-','MarkerSize',MarkerSize,'MarkerIndices',1:5:2*N-1);
        title('Aperiodic auto-correlation')
        ropt = abs(xcorr(x));
        max(ropt(1:N-1))
    end
    box on
    grid on
    legend('Initial Sequence','Optimized Sequence','location','best')
    xlabel('shift (k)')
    ylabel('Correlation Level (dB)')
    axis tight

    figure; hold on
    if pF == 1
        plot(-N+1:N-1,(abs(pcorr(x0))),'b-','MarkerSize',MarkerSize,'MarkerIndices',1:5:2*N-1);
        plot(-N+1:N-1,abs(pcorr(x)),'gr-','MarkerSize',MarkerSize,'MarkerIndices',1:5:2*N-1);
        title('Periodic auto-correlation')
    else
        plot(-N+1:N-1,(abs(xcorr(x0))),'b-','MarkerSize',MarkerSize,'MarkerIndices',1:5:2*N-1);
        plot(-N+1:N-1,(abs(xcorr(x))),'gr-','MarkerSize',MarkerSize,'MarkerIndices',1:5:2*N-1);
        title('Aperiodic auto-correlation')
    end
    box on
    grid on
    legend('Initial Sequence','Optimized Sequence','location','best')
    xlabel('shift (k)')
    ylabel('Correlation Level')
    axis tight

    x = [];
end
end

function [ r ] = pcorr( x , y)
% ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
% Copyright (c) 2020, <Mohammad Alaee>, website: https://radarmimo.com/
% All rights reserved.
% ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
if ~exist('x','var')
    N           = 50; % sequence length
    phi         = (2*rand(N,1)-1)*pi;
    x           = exp(1i * phi);
end
if ~exist('y','var')
    y           = x(:);
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


function [ a_dk,b_dk,c_dk ] = mabc( x,d )
% ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
% Copyright (c) 2020, <Mohammad Alaee>, website: https://radarmimo.com/
% All rights reserved.
% ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
x           = x(:);
N           = length(x);
x(d)        = 0;
c_dk        = xcorr(conj(x));
c_dk(1:N)   = [];

b_dk        = circshift(x(end:-1:1),d-1);
b_dk(d:end) = 0;
b_dk(end)   = [];

a_dk        = conj(circshift(x,-d));
a_dk(end-d+1:end) = 0;
a_dk(end)   = [];
end

function [ a_dk,b_dk,c_dk ] = mabcp( x,d )
% ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
% Copyright (c) 2020, <Mohammad Alaee>, website: https://radarmimo.com/
% All rights reserved.
% ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
x           = x(:);
N           = length(x);

x(d)        = 0;
c_dk        = pcorr(conj(x));
c_dk(1:N)   = [];

b_dk        = circshift(x(end:-1:1),d-1);
b_dk(end)   = [];

a_dk        = conj(circshift(x,-d));
a_dk(end)   = [];

end