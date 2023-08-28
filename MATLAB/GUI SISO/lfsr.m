function y = lfsr(feedback, init, N, fSample)
% lfsr: generate binary m-sequences from a linear feedback shift register(LFSR)
%	y = lfsr(feedback), lfsr(feedback, init), lfsr(feeback, init, N) or 
%       lfsr(feedback, init, N, fSample)
%   feedback: an integer that specifies the feedback (XOR) positions in the
%             register when written in the binary format. For example, if
%             the register has 4 taps (a3,a2,a1,a0) and feedback=9=(1001), 
%             it means that the feedback occurs on the left of a3 and a0 
%             (the signal is fed back from the right of a0). Actually, the 
%             length of "feedback" specifies the length of the register.
%   init: an integer that specifies the initial state of the register. For
%         example, if init=8=(1000), the initial state is (a3 a2 a1 a0) = 
%         (1000). Default value is 1.
%   N: the length of the output sequence y. Usually it is chosen to be the
%      period of the sequence, which is 2^n-1 where n is the length of
%      the register. Default value is 2^n-1.
%   fSample: the register output (from a0) is re-sampled by this factor.
%            when fSample=1, unchanged; fSample=2, every second output is
%            kept, etc. It is useful for Gold or Kasami sequences. Default
%            value is 1.
%   y: N-by-1, the output binary sequence ({1,0}, NOT {1,-1})
% 06/17/2009
%
% A list of m-sequence feedback values can be found at
% http://www.ece.cmu.edu/~koopman/lfsr/index.html
% where those values must be converted from hexadecimal to decimal
% E.g., for register length n = 1:16, we can choose
% feedbacks=[nan hex2dec('3') hex2dec('5') hex2dec('9') hex2dec('12')...
%   hex2dec('21') hex2dec('41') hex2dec('8e') hex2dec('108') hex2dec('204')...
%   hex2dec('402') hex2dec('829') hex2dec('100D') hex2dec('2015')...
%   hex2dec('4001') hex2dec('8016')]
% = [nan 3 5 9 18 33 65 142 264 516 1026 2089 4109 8213 16385 32790];
%
% All (periodic) autocorrelation sidelobes are -1

n = length(dec2bin(feedback)); % length of the shift register
if nargin<2
    init = 1;
end
if nargin<3
    N = 2^n - 1;
end
if nargin<4
    fSample = 1;
end

state = uint32(init); % initial state (must be converted from double to integer)
y = zeros(N, 1);

for k = 1:N
    y(k) = bitand(state, uint32(1)); % the a0 tap is taken out as the output
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