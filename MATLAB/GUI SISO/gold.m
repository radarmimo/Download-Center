function Y = gold(n, feedback)
% Y = gold(n) or gold(n, feedback), generate the Gold sequence set
%   n: order of the sequence set, satisfying mod(n,2)=1 or mod(n,4)=2
%   feedback: an integer specifying the feedback positions, if written in
%             binary format. See "lfsr.m" for more details.
%   Y: N-by-M, the generated Gold sequence set, N = 2^n - 1, M = N + 2

% All (periodic) correlation sidelobes only take three values:
% -1, -1+t(n) and -1-t(n)
% where t(n) = 2^[(n+1)/2] for odd n
%            = 2^[(n+2)/2] for mod(n,4)=2

if nargin<2
    feedbackSet = [nan 3 5 9 18 33 65 142 264 516 1026 2089 4109 ...
        8213 16385 32790];
    feedback = feedbackSet(n);
end

if(mod(n,2)==1)
    fSample = 1 + 2^((n+1)/2);
elseif(mod(n,4)==2)
    fSample = 1 + 2^((n+2)/2);
else
    error('mod(n,2)=1 or mod(n,4)=2');
end

N = 2^n - 1;
a = lfsr(feedback, 1, N, 1);
b = lfsr(feedback, 1, N, fSample);

Y = zeros(N,N+2);
Y(:,1) = a;
Y(:,2) = b;

for k = 0:(N-1)
    Y(:,k+3) = xor(a, circshift(b, k));
end

Y = 2 * Y - 1; % from {1,0} to {1,-1}