% ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
% Copyright (c) 2023, <Nazila Karimian>, university of luxembourg
% website: https://radarmimo.com/
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
% Email: info@radarmimo.com, nazila.karimian@gmail.com
% Code written by : Nazila Karmiyan
% Update : 2023
% ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
% ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
% Reference:
% ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
% N. K. Sichani, M. Alaee-Kerahroodi, B. Shankar M. R., E. Mehrshahi and 
% S. A. Ghorashi, "Antenna Array and Waveform Design for 
% 4D-Imaging mmWave MIMO Radar Sensors," in 
% IEEE Transactions on Aerospace and Electronic Systems, 
% doi: 10.1109/TAES.2023.3343688.
% ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
% Waveform Design for 4D imaging MIMO radars with continuous phase
% constraint
% ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
clc, clear, close all
% ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
rng(20)
maxITR = 100;

M       = 2; %number of transmit antennas
N       = 512; %code_length

X       = zeros(M,N);
for m = 1:M
    X(m,:)= exp(1i*2*pi*rand(1,N));
end

%% objective function
W_ISL       = zeros(1,2*N-1);
W_ISL(N-100:N+100) = 1; %ROI
W_SPEC      = ones(1,2*N-1); %spectrum-shaping
W_SPEC(255:511) = 10;

%% CD approach

obj_value(1)    = objfunction(X,M,N,W_SPEC,W_ISL);
eps             = 1e-2;
it              = 0;
X_new           = zeros(size(X));

while 1

    it      = it+1;
    F       = dftmtx(2*N-1);
    Finv    = conj(F)/(2*N-1);
    perc    = 0;
    for m0=1:M
        for n0=1:N
            perc0=(m0-1)/M+(n0-1)/N/M;
            if perc0>perc
                perc=perc+0.0001;
                clc
                disp(['Progress = '  num2str(100*perc) ' , Iteration = ' num2str(it)])
            end
            %initialization for funcmultipliers

            [K, D]=funcmultipliers2(m0,n0,X,M,N,W_SPEC,W_ISL,F,Finv);
 
            poly=[2*K D 0 -D' -2*K'];
            r=roots(poly);
            phiroots=-1i*log(r);
            i=0;
            phiroots(abs(imag(phiroots))>1e-5) = [];
            phireal = real(phiroots);
                       
            for i =1:length(phireal)
                X1=X;
                X1(m0,n0)=exp(1i*phireal(i));
                objvalue(i)=objfunction(X1,M,N,W_SPEC,W_ISL);
            end
            % objvalue
            [obj_val,k]=(min(objvalue));
            
            X(m0,n0)=exp(1i*phireal(k));
           
        end
        
    end
    
    obj_value(end+1)=obj_val;
    if (obj_value(end-1)-obj_value(end))/norm(obj_value(end))<eps || (it > maxITR)
        break
    end
end

%% plots

m=2;
figure,semilogx(10*log10(abs(obj_value(1,2:end))))
title('obj value')

figure,plot(20*log10(abs(fft(X(m,:),2*N-1))/N))
title('fftx')
% ylim([-50, 0])

figure,plot(20*log10(abs(xcorr(X(m,:),X(m,:)))/N))
title('autocorrelation')
figure,plot(20*log10(abs(xcorr(X(1,:),X(2,:)))/N))
title('cross correlation')

ISL1    = 10*log10((obj_value(end)-M*N^2)/N^2)%correct value for ISL

ISL     = 10*log10(obj_value(end)-M*N^2)

ISL     = 10*log10(obj_value(end))

Lower_bound = 10*log10(M*(M-1)*N^2+M*N^2)

pxx=pwelch(X(m,:));
figure,plot(10*log10(pxx))

xlabel('Frequency (Hz)')
ylabel('PSD (dB/Hz)')

pxx=periodogram(X(m,:),[],250);
figure,plot(((1:250)./250).', 10*log10(pxx))
ylim([-40, 0])


fs      = fft(X(m,:));
figure,
hold on, plot( (1:1:length(X(m,:)))./length(X(m,:)).', 10*log10((abs(fs).^2)/N))
grid on, box on

xlabel('Frequency (Hz)')
ylabel('PSD (dB/Hz)')


% ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
% ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
% ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
% ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
% ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
% ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
% ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
% additional functions
% ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
% ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
% ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~


%% obj1
function[obj]=objfunction(X,M,N,W_SPEC,W_ISL)
obj=0;
for m=1:M
    for l=1:M
        
        x1=X(m,:);
        x2=X(l,:);
        wfx1=W_SPEC.*fft(x1,2*N-1);
        wfx2=fft(x2,2*N-1);
        wcross=fftshift(ifft(conj(wfx1).*wfx2));
        obj1=W_ISL.*conj(wcross(end:-1:1));
        obj=obj+sum(abs(obj1).^2);           
   
    end
end
end

% ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
% ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
% ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

function[K, D]=funcmultipliers2(m0,n0,X,M,N,W_SPEC,W_ISL,F,Finv)
%%
%initials
% x=X(m0,n0);
K=0; K1=0;K2=0;
d1=0;d2=0; d3=0; d4=0; d5=0; d6=0; d7=0; d8=0; d9=0; d10=0; d11=0; d12=0; d13=0; d14=0; d15=0;

X1=X(m0,:);
X2=X1(end:-1:1);

F2=F(:,1:N);
F3=F2;
F2(:,n0)=[];
F3(:,N+1-n0)=[];

FN=F(:,N+1-n0);
Fn0=F(:,n0);
%%
X_padm0=[X1 zeros(1,N-1)];
FX_padm0=fft(X_padm0).';
F2X3prim=FX_padm0-Fn0*X(m0,n0);

X_padm0=[X2 zeros(1,N-1)];
FX_padm0=fft(conj(X_padm0)).';
F2X2hermit=(FX_padm0-Fn0*conj(X(m0,N+1-n0)));

F3X2hermit=(FX_padm0-FN*conj(X(m0,N+1-n0)));


F3X21hermit=(FX_padm0-FN*conj(X(m0,n0)));

A1=W_ISL'.*(ifft(W_SPEC'.*(F2X3prim.*FN)));
B2=A1;
A2=W_ISL'.*(ifft(W_SPEC'.*Fn0.*F2X2hermit));
A=A1'*A2;

K=A;


A1=B2;
A2=W_ISL'.*(ifft(W_SPEC'.*Fn0.*FN));
B3=A2;
A=A1'*A2;

d1=M*A;

%d3
d3A=0; d3B=0;

A1=B3;
A2=W_ISL'.*(ifft(W_SPEC'.*Fn0.*F3X2hermit));
A=A1'*A2;

d3A=A;


d15C=0;
for m=1:M
    if m~=m0

        X4=X(m,:);

        X_padm0=[X4 zeros(1,N-1)];
        FX_padm0=fft(X_padm0).';
        F2X4prim=FX_padm0-Fn0*X(m,n0);
        A1=B3;
        A2=W_ISL'.*(ifft(W_SPEC'.*F2X4prim.*F3X21hermit));
        A=A1'*A2;

        d3B=d3B+(X(m,n0)'*(A));

        A1=W_ISL'.*(ifft(W_SPEC'.*(F2X4prim.*FN)));
        A=A1'*A2;
        d15C=d15C+A;
    end
end

d3=M*d3A+d3B;
d12A=0; d12B=0;
d15A=0; d15B=0; %d15C=0;
%d5
for l=1:M
    if l~=m0

        X4=X(l,:);
        X5=X4(end:-1:1);
        X_padm0=[X5 zeros(1,N-1)];
        FX_padm0=fft(conj(X_padm0)).';
        F3X5hermit=FX_padm0-Fn0*conj(X(m,n0));


        A1=B2;
        A2=W_ISL'.*(ifft(W_SPEC'.*Fn0.*F3X5hermit));
        A=A1'*A2;

        d5=d5+X(l,n0)*A;
        d15B=d15B+X(l,n0)*A;

        A12=W_ISL'.*(ifft(W_SPEC'.*(F2X3prim.*F3X5hermit)));
        A=A12'*A2;
        d12A=d12A+A;

        A24=B3;
        A=A1'*A24;
        d14=d14+X(l,n0)'*A;

    end
end



A1=W_ISL'.*(ifft(W_SPEC'.*(F2X3prim.*F3X21hermit)));
B4=A1;
A2=W_ISL'.*(ifft(W_SPEC'.*Fn0.*F3X21hermit));
A=A1'*A2;
d12B=d12B+A;

d12=d12A+d12B;


%d15A

A1=B2;
A2=B4;
A=A1'*A2;
d15A=d15A+A;

d15=d15A+d15B+d15C;

%~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
%computing objective function
D=d1+d3+d5+d12+d14+d15;


end
