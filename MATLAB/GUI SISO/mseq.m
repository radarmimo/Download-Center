function x = mseq(n, init, feedback)
% x = mseq(n) or mseq(n, init) or mseq(n, init, feedback), generate an
% m-sequence of length N = (2^n - 1). See "lfsr.m" for more information.
%
% all periodic auto-correlation sidelobes of x are -1

if nargin == 0
   n =  5;
    feedbackSet = [nan 3 5 9 18 33 65 142 264 516 1026 2089 4109 ...
        8213 16385 32790];
    feedback = feedbackSet(n);
    init = 1;   
end
if nargin <= 2
    feedbackSet = [nan 3 5 9 18 33 65 142 264 516 1026 2089 4109 ...
        8213 16385 32790];
    feedback = feedbackSet(n);
    if nargin == 1
        init = 1;
    end
end
N = 2^n - 1;
fSample = 1;

state = uint32(init); % initial state (must be converted from double to integer)
x = zeros(N, 1);

for k = 1:N
    x(k) = bitand(state, uint32(1)); % the a0 tap is taken out as the output
    for m = 1:fSample
        if bitand(state, uint32(1)) % if there is a "1" fed back
            % (non-cyclic) right shift the current state, 
            % and exclusive-or with the feedback
            state = bitxor(bitshift(state, -1), uint32(feedback));
        else
            state = bitshift(state, -1);
        end
    end
end

x = 2 * x - 1; % from {1,0} to {1,-1}