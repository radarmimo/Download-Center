% ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
% Copyright (c) 2022, <Robin Amar>,
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
%    This product includes software developed by the <organization>.
% 4. Neither the name of the <organization> nor the
%    names of its contributors may be used to endorse or promote products
%    derived from this software without specific prior written permission.
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
% Email: robin.amar@uni.lu, amar.robin.2020@gmail.com
% Code written by : Robin Amar
% Last update : 2022
% ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~


clc;clear;close all;

% Parmeters
MaxIter = 1e4;
tol = 1e-4;

% Initialization
N = 300;
M = 10;
L = round(N/M);
Q = 3;
fprintf('sequence length N = %d\n',N);
FLG_RNDM_SUBSQNCE_LEN = false;

p_init = 2;

M_min = M;
[x_seed, refVec, a] = rndmSqnce_phaseEstmt(N,L,M_min, Q, FLG_RNDM_SUBSQNCE_LEN);
pStruct.refVec = refVec; pStruct.aQL = a; pStruct.N = N; pStruct.L = L; 
pStruct.Q = Q; pStruct.p = p_init; 
pStruct.tol = 1e-2; pStruct.MaxIter = MaxIter; pStruct.tol = tol;
[x_PSL, obj_hist, PSL_hist, ISL_hist,infm] = MPSL_PECS(x_seed, pStruct);
% ----------------------- PSL Convergence Plot --------------------------
figure(21);box on; hold all
plot(0:2:length(PSL_hist)-1,PSL_hist(1:2:end),'linewidth',2);
% grid on
% set(gca,'FontSize', 12, 'FontWeight', 'bold','GridAlpha',0.5, 'MinorGridAlpha',0.5);
xlabel('iteration')
ylabel('PSL [dB]')
% title('PSL - Convergence Curve')
% ----------------------- ISL Convergence Plot --------------------------
figure;box on; hold all
plot(0:2:length(ISL_hist)-1,ISL_hist(1:2:end),'linewidth',2);
% grid on
% set(gca,'FontSize', 12, 'FontWeight', 'bold','GridAlpha',0.5, 'MinorGridAlpha',0.5);
xlabel('iteration')
ylabel('ISL [dB]')
% title('ISL - Convergence Curve')
% ------------------- Objective Convergence Plot --------------------------------
figure(22);box on; hold all
plot(0:2:length(obj_hist)-1,obj_hist(1:2:end),'linewidth',2);
% grid on
% set(gca,'FontSize', 12, 'FontWeight', 'bold','GridAlpha',0.5, 'MinorGridAlpha',0.5);
xlabel('iteration')
ylabel('pth Norm - rk')
% title('Objective - Convergence Curve')

% ------------------- Correlation Plot ----------------------------
chk = xcorr(x_seed);
chkPly = 20*log10(abs(chk./chk(N)));

ac_MM_ply = xcorr(x_PSL);
corrPS = 20*log10(abs(ac_MM_ply./ac_MM_ply(N)));

figure(23); hold all;
plot(1-N:N-1,chkPly, 'linewidth',1.5);
plot(1-N:N-1,corrPS,  'LineWidth',1.5);
% grid on
% set(gca,'FontSize', 12, 'FontWeight', 'bold','GridAlpha',0.5, 'MinorGridAlpha',0.5);
ylim([-60, 1]);
xlabel('k')
ylabel('correlation level (dB)')
legend('Seed Sqnce','PECS - PS')

% --------------------- Phase Plot -------------------------------
argX_ply = unwrap(atan2(imag(x_seed),real(x_seed)));
argPly_PS = unwrap(atan2(imag(x_PSL),real(x_PSL)));

% figure(24); box on; hold all; % grid on;
% indx_e = 0;
% for l = 1:L
%     indx_s = indx_e + 1;
%     indx_e = indx_s + refVec(l)-1;
%     plot(indx_s:indx_e, argX_ply(indx_s:indx_e),'--sk');
%     plot(indx_s:indx_e, argPly_PS(indx_s:indx_e), '-.o', 'linewidth', 1.5);
% %     set(gca,'FontSize', 12, 'FontWeight', 'bold','GridAlpha',0.5, 'MinorGridAlpha',0.5);
% end
% xlabel('Code length');ylabel('Phase');
% legend('PECS - PS', 'Seed Sqnce');
% hold off;
figure(24); box on; hold all; % grid on;
indx = 1:N;
plot(indx, argPly_PS, '-.o', 'linewidth', 1.5);
xlabel('Code length');ylabel('Phase');
hold off;

% ------------------- Bandwidth Plot ---------------------------
figure; 
hold all
nFFT = 256;fIndx = linspace(-0.5,0.5,nFFT);
plot(fIndx, fftshift(20*log10(abs(fft(x_PSL,nFFT))/nFFT)),'linewidth',2);
xlabel('Normalized Frequency'); ylabel('Power [dB]');

x_glmb = mcode(2,N);
[~,isl_glmb] = pslisl(x_glmb);
fprintf('ISL of Golomb sequence for length N -> %d : %f\n',N, 10*log10(isl_glmb));
[~,isl_x_PSL] = pslisl(x_PSL);
fprintf('ISL of the optimized sequence for length N -> %d : %f\n',N, 10*log10(isl_x_PSL));

% ------------------- Ambig Fn Plot ---------------------------
AmbigFn_heat(x_PSL);


%% ========================= * ==========================
% Lp Norm increment with increasing iterations
function [x_PSL,obj_PSL,PSL, ISL, infm] = MPSL_PECS(x0, pStruct)
%%%%%%%% Output %%%%%%%%%%%
% x_PSL : output sequence
% num_iter: number of iterations
% obj_PSL: objective values (p-norm) at each iteration
% PSL: PSL value at each iteration
N = pStruct.N;
p = pStruct.p;
MaxIter = pStruct.MaxIter; 
tol = pStruct.tol;
x = x0;
obj = [];
PSL = [];
ISL = [];
f = fft(x,2*N);             % 2N point FFT of x
r = ifft(abs(f).^2);        % r = [r0,r1,...,r_N-1,0,r_1-N,...,r_-1]
r_abs = abs(r(2:N));
obj(end+1) = norm(r_abs,p);
PSL(end+1) = 20*log10(max(r_abs));

% ------------------------------------
iter = 1; 
while 1
    xU = MPSL_update(x,p,N);
    % ------------------ PECS start ----------------------------
    [yF, pStruct] = PECS_PerfSqr(xU, pStruct);
    argY = unwrap(atan2(imag(yF),real(yF)));
    x1 = exp(1j*argY);
    % ------------------ PECS end ----------------------------
    x_fft = fft(x1,2*N); rk = ifft(abs(x_fft).^2); r_abs = abs(rk(2:N)); obj3 = norm(r_abs,p);
    x = x1;

%     if (abs(obj(end) - obj3) < tol ) || iter >= MaxIter
    if iter >= MaxIter
        break;
    end
    
    obj(end+1) = obj3;
    PSL(end+1) = 20*log10(max(r_abs));
    [~,isl] = pslisl(x); ISL(end+1)=20*log10(isl);
    iter = iter+1;
end
x_PSL = x;
obj_PSL = obj;

infm.actlItrns = iter;
end

%% PSL Minimization
function [x_update] = MPSL_update(x,p,N)
% One step update of MPSL_eig
f = fft(x,2*N);
r = ifft(abs(f).^2); % r = [r0,r1,...,r_N-1,0,r_1-N,...,r_-1]
r_abs = abs(r(2:N));
t = norm(r_abs,p)+1e-5;
% normalized version (normalize by t^p to avoid numerical issue)
r_t_ratio = r_abs/t;
a = (1 + (p-1)*r_t_ratio.^p - p*r_t_ratio.^(p-1))./(t-r_abs).^2;
w = 0.5*p/t^2*r_t_ratio.^(p-2);

lambda_max_L = max([N-1:-1:1]'.*a); % the maximum eigenvalue of L

c = [0;w;0;w(N-1:-1:1)].*r;
mu = real(fft(c));
lambda_u = 0.5*(max(mu(1:2:end))+max(mu(2:2:end)));

y = ifft(mu.*f); % the fator 1/2N is implicitly included

x_update = (N*lambda_max_L + lambda_u)*x - y(1:N);
end

%% PECS - Perfect Square Implementation
function [z, pStruct] = PECS_PerfSqr(y, pStruct)
if false
    z = y;
else

    refVec = pStruct.refVec;
    L = pStruct.L;
    Q = pStruct.Q;

    z = [];
    psi = unwrap(atan2(imag(y),real(y)));
    r = abs(y);

    % ------------- For ----------------
    indx_e = 0;
    for l = 1:L
        indx_s = indx_e+1;
        indx_e = indx_s + refVec(l)-1;

        psi_M = psi(indx_s:indx_e);
        r_M   = r(indx_s:indx_e);

        M = refVec(l);
        m = 1:M; m = m(:);

        arg_init = 0;
        for q = 1:Q
            arg_init = arg_init + pStruct.aQL(q,l).*(m.^(q-1));
        end

        theta = arg_init - psi_M;

        % =========== Taylor subroutine starts ================

        am = r_M / 2 .* cos(theta);
        bm = r_M .* sin(theta);
        beta = - 2 * am .* psi_M - 2 * am .* theta + bm;
        alpha = [];
        for q = 0 : Q-1
            alpha = [alpha, 2 *  am .* ((1:M).').^q];
        end

        [pStruct.aQL(:,l),flag] = lsqr(alpha,-beta, 1e-3);

        % =========== Taylor subroutine ends ===============

        arg_opt = 0;
        for q = 1:Q
            arg_opt =  arg_opt + pStruct.aQL(q,l).*(m.^(q-1));
        end
        x_j = exp(1j*arg_opt);

        z = [z; x_j];
        x_j = [];
    end
end
end



function [ psl,isl,PSLRdB,ISLRdB ] = pslisl( x , nF , pF )
% This function calculates PSL and ISL for a radar transmit sequence 
% ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
% Input: 
%           x       : sequence
%           nF      : normalization flag, default n = 0 
%           pF      : pF = 1 -> calculating "Periodic" PSL and ISL,
%                     otherwise, calculating "Aperiodic" PSL and ISL,
% ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
% ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
% Output: 
%           psl     : calculated PSL value
%           isl     : calculated ISL value
%           PSLRdB  : calculated PSLR (dB) value
%           ISLRdB  : calculated ISLR (dB) value
% ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
% The input parameters can be chosed as follows:
if nargin == 1
    nF      = 0;
    pF      = 0; 
elseif nargin <= 2
   pF       = 0; 
end
% ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
x           = x(:);
N           = length(x);   
if pF == 0
    r       = abs(xcorr(x));
else
    r       = abs(pcorr(x));
end
if nF == 1
    r       = r / max(r);
end
psl         = max(r(1:N-1));
isl         = sum(r(1:N-1).^2);

PSLRdB      = 10*log10(psl^2/N^2);
ISLRdB      = 10*log10(isl/N^2);
end



function [x, refVec, a_ql] = rndmSqnce_phaseEstmt(N,L,M_min, Q, FLG_RNDM_SUBSQNCE_LEN)
% This function is designed to keep variable sub-sequence length - M
% only choice required is No of sub-sequences - L, minimum sub-sequence length - M_min, Q, sequence length - N
if nargin < 1
    clc; clear; close all;
    N = 200;
    L = 5;
    M_min = 20;
    Q = 3;
    PLT_ACTVE = true;
    DBG = true;
else
    PLT_ACTVE = false;
    DBG = false;
end

rng 'shuffle'

if FLG_RNDM_SUBSQNCE_LEN
    [refVec] = sqnce_len_gnrtr(N, L, M_min);
else
    refVec = M_min*ones(L,1);
end
z = [];

RNDM = 8; y = mcode(RNDM,N);

psi = unwrap(atan2(imag(y),real(y)));
r = abs(y);
a = 10*rand(Q,L);
indx_e = 0;
for l = 1:L
    
    M = refVec(l);
    m = 1:M; m = m(:);
    indx_s = indx_e+1;
    indx_e = indx_s + refVec(l)-1;
    
    psi_M = psi(indx_s:indx_e);
    r_M   = r(indx_s:indx_e);
    arg_init = 0;
    m_s = [ones(size(m))];
    for q = 1:Q
        arg_init = arg_init + a(q,l)*m.^(q-1);
    end
    
    for q = 2:Q
        m_s = [m.^(q-1), m_s];
    end
    
    A_ls = m_s;
    [vrbl,flag] = lsqr(A_ls, psi_M);
    
    for q =1:Q
        a(Q+1-q,l) = vrbl(q);
    end
    
    arg_opt = 0;
    for q = 1:Q
        arg_opt =  arg_opt + a(q,l)*m.^(q-1);
    end
    x_j = exp(1j*arg_opt);
    z = [z; x_j];
end
x = z; 
a_ql = a;
end

function [refVec] = sqnce_len_gnrtr(N, L, M)
w = randi([M, 4*M],L,1);
mul = round(N/sum(w),1);
w = round(w*mul);
if sum(w) > N
    fct = round(abs(sum(w) - N)/L);
    if fct == 0
        fct = 1;
    end
    cmpnst = fct*ones(L,1);
    w = w - cmpnst;
    if sum(w) < N
        w(end) = w(end) + abs(sum(w) - N);
    elseif sum(w) > N
       [~,indx] = max(w);
       w(indx) = w(indx) - abs(sum(w) - N); 
    end
else
    rmndr = mod(N, sum(w));
    w(end) = w(end)+ rmndr;
end
refVec = w;
end

function [ x ] = mcode( strcd , N ,init )
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
    case 16 % all one
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



function AmbigFn_heat(uinput)
% Compute and plot the ambiguity function for a any code sequence
% Compute the ambiguity function 
% by utilizing the FFT through combining multiple range cuts 
if isrow(uinput)
    code_seq = uinput; 
else
    code_seq = uinput'; 
    fprintf(1, 'Note: Input should be a Row Vector!!\n');
end
% code_seq = uinput(:);
N = size(code_seq,2); 
tau = N; 
stp = 1;                                 % Oversampling Ratio - stp = 1: Normal sampling / stp > 1: oversampling
samp_num = size(code_seq,2) *stp;
n = ceil(log(samp_num) / log(2)); 
nfft = 2^n; 
u(1:nfft) = 0; 
j = 0; 

for index = 1:stp:samp_num 
    j = j+1; 
    u(index:index+stp-1) = code_seq(j);
end
v = u; 
delay = linspace(-tau, tau, nfft); 
% Options: freq_del = 12 / tau /100;               % Why 12/tau/100    % freq_del = 2 / tau / 10;     
freq_del = 1 / tau / 100;   
j = 0; 
vfft = fft(v,nfft); 
% Options: for freq = -6/tau:freq_del:6/tau % for freq = -1/tau:freq_del:1/tau % for freq = -0.5:freq_del:0.5
for freq = -0.1:freq_del:0.1
    j = j+1; 
    exf = exp(sqrt(-1) * 2. * pi * freq .* delay); 
    u_times_exf = u .* exf; 
    ufft = fft(u_times_exf,nfft); 
    prod = ufft .* conj(vfft); 
    ambig(:,j) = fftshift(abs(ifft(prod))');
end

norm_ambig = ambig ./ max(max(ambig));  % Normalization of the ambig function
PWR_CNVRSN = false;
if PWR_CNVRSN
    norm_ambig = 10*log10(abs(norm_ambig).^2);    % Conversion to Log Scale
    norm_ambig(norm_ambig < -50) = -50;
end
% Options: freq = -6/tau:freq_del:6/tau; % freq = -1/tau:freq_del:1/tau; % freq = -0.5:freq_del:0.5;
freq = -0.1:freq_del:0.1; 

% delay = linspace(-N,N,nfft); 
delay = linspace(-1,1,nfft); 

figure;
surf(freq, delay, norm_ambig);
xlabel('frequency') 
ylabel('delay') 
axis tight;
shading interp
% colormap hot;
% brighten(colormap,0.7)
colorbar;
box on
end

