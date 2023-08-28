function Y = kasami(n, feedback)
% Y = kasami(n) or kasami(n, feedback), generate the small set of (binary) 
% Kasami sequences.
%   Y = kasami(n, feedback) or kasami(n)
%   n: order of the sequence set, an even integer.
%   feedback: an integer specifying the feedback positions, if written in
%             binary format. See "lfsr.m" for more details.
%   Y: N-by-M, the generated small set of Kasami sequences
%      N = 2^n - 1, the period (length) of each sequence 
%      M = 2^(n/2), the number of sequences in the set
%
% All (periodic) auto- and cross-correlation sidelobes take only 
% three values: [-1 -1-2^(n/2) -1+2^(n/2)]

if mod(n,2)==1
    error('n must be an even integer');
end

if nargin<2
    feedbackSet = [nan 3 5 9 18 33 65 142 264 516 1026 2089 4109 ...
        8213 16385 32790];
    feedback = feedbackSet(n);
end

fSample = 1 + 2^(n/2); % sampler
N = 2^n - 1;
M = 2^(n/2);

% base m-sequence
a = lfsr(feedback, 1, N, 1);
b = lfsr(feedback, 1, N, fSample);

Y = zeros(N, M);
Y(:,1) = a;
for k = 0:(M-2)
    Y(:, k+2) = xor(a, circshift(b, k));
end

Y = 2 * Y - 1; % from {1,0} to {1,-1}