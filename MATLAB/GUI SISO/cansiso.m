function x = cansiso(N, x0,thr,L ,w,plt)
% x = cansiso(N) or x = cansiso(N, x0), CAN SISO
%   N: length of the sequence
%   x0: N-by-1, the initialization sequence
%   x: N-by-1, the generated sequence
if nargin == 0
    N       = 16;
    x0      =  mcode(8,N);
    thr     = 1e-5;
    L       = inf;
    w       = 0;
    plt     = 1;
end
x           = x0(:);

if L > 0 && L ~= inf
    % quantization to L levels, e.g. L = 256
    x       = exp(1i * floor(angle(x(1:N))/(2*pi/L))*(2*pi/L)); % if phase
end

if plt  == 1
    %     hold all
    plot(abs(xcorr(x)));
end
cnt         = 0;
cnd         = 1;
while (cnd == 1 && cnt < 1e5)
    cnt     = cnt + 1;
    xPre    = x;
    % step 2
    z       = [x; zeros(N, 1)]; % 2N-by-1
    f       = 1/sqrt(2*N) * fft(z); % 2N-by-1
    v       = sqrt(1/2) * exp(1i * angle(f)); % 2N-by-1
    % step 1
    g       = sqrt(2*N) * ifft(v); % 2N-by-1
    x       = exp(1i * angle(g(1:N))); % N-by-1

    if (rem(cnt,100)== 0 && plt  == 1)
        plot(abs(xcorr(x))); drawnow
    end
    [~, islx]   = pslisl(x);
    obj(cnt)    = islx;
    if norm(x - xPre) < thr
        cnd = 0;
    end
end
if L > 0 && L ~= inf
    % quantization to L levels, e.g. L = 256
    x   = exp(1i * floor(angle(g(1:N))/(2*pi/L))*(2*pi/L)); % if phase
    if L == 2
        x = real(x);
    end
end

if plt  == 1
    hold off
    plot(abs(xcorr(x)));
    if nargout == 0
        figure; plot(obj);
        [psl_x,isl_x] = pslisl(x)
    end
end
end