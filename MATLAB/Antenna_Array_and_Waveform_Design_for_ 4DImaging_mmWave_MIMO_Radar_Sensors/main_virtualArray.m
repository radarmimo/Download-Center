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
% Transmit and receive antenna array design based on desired virtual array 
% for 4D imaging MIMO radar
% ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
clc, clear, close all
% ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

eta_vec2    = [0,0.1,0.2,0.4];

% caseStudies = {'TI', 'Vayyar', 'Bosch', 'TGRS',
% 'Uhnder', 'Micorwaves','TayloredVayyar','TayloredTI','Circular'};

caseStudy = 'Bosch';
switch caseStudy
    case 'TI'
        %% Case Study - Texas Instruments Imaging Radar
        % Design Guide: TIDEP-01012
        % https://www.ti.com/lit/ug/tiduen5a/tiduen5a.pdf?ts=1666267728378

        rng(1989)

        L_t     = 12; % desired number of Tx Antenna elements
        L_r     = 16; % desired number of Rx Antenna elements

        Nt       = L_t; % Number of Rows
        Mt       = 4 * L_r; % Number of Columns

        Nr       = 1; % Number of Rows
        Mr       = 4*L_r; % Number of Columns

        Tx      = zeros(Nt,Mt); Tx(:,1) = randn(Nt,1)>0;
        Rx      = zeros(Nr,Mr); Rx(1,:) = randn(1,Mr)>0;

        iniVAmat = conv2(Tx, Rx);
        desiredVA = desiredVAarray(7,iniVAmat,L_t,L_r,Nt,Mt,Nr,Mr); % (case 7)

    case 'Vayyar'
        %% Case Study
        rng(2012)

        L_t     = 24; % desired number of Tx Antenna elements
        L_r     = 24; % desired number of Rx Antenna elements

        Nt       =  L_t; % Number of Rows
        Mt       =  L_r; % Number of Columns

        Nr       =  L_t; % Number of Rows
        Mr       =  L_r; % Number of Columns

        Tx      = zeros(Nt,Mt); Tx(:,1) = randn(Nt,1)>0;
        Rx      = zeros(Nr,Mr); Rx(1,:) = randn(1,Mr)>0;
        iniVAmat = conv2(Tx, Rx);

        desiredVA = desiredVAarray(10,iniVAmat,L_t,L_r,Nt,Mt,Nr,Mr);
    case 'Bosch'
        rng(4244)


        L_t     = 4; % desired number of Tx Antenna elements
        L_r     = 16; % desired number of Rx Antenna elements

        Nt       = 4 * L_t; % Number of Rows
        Mt       = 3 * L_r; % Number of Columns

        Nr       = 4 * L_t; % Number of Rows
        Mr       = 2 * L_r; % Number of Columns

        Tx      = zeros(Nt,Mt); Tx(:,1) = randn(Nt,1)>0;
        Rx      = zeros(Nr,Mr); Rx(1,:) = randn(1,Mr)>0;

        iniVAmat = conv2(Tx, Rx);

        desiredVA = desiredVAarray(8,iniVAmat,L_t,L_r,Nt,Mt,Nr,Mr);

    case 'TGRS'
        %         IEEE TRANSACTIONS ON GEOSCIENCE AND REMOTE SENSING, VOL. 56,
        %         NO. 1, JANUARY 2018
        %         A Portable 3-D Imaging FMCW MIMO Radar Demonstrator With a 24 ×
        %         24 Antenna Array for Medium-Range Applications

        rng(4248)

        L_t     = 24; % desired number of Tx Antenna elements
        L_r     = 24; % desired number of Rx Antenna elements

        Nt       = 12; % Number of Rows
        Mt       = L_r; % Number of Columns

        Nr       = 12; % Number of Rows
        Mr       = L_r; % Number of Columns

        Tx      = zeros(Nt,Mt); Tx(:,1) = randn(Nt,1)>0;
        Rx      = zeros(Nr,Mr); Rx(1,:) = randn(1,Mr)>0;

        iniVAmat = conv2(Tx, Rx);

        desiredVA = desiredVAarray(9,iniVAmat,L_t,L_r,Nt,Mt,Nr,Mr);


    case 'TayloredVayyar'
        %         rng(2012)

        L_t     = 20; % desired number of Tx Antenna elements
        L_r     = 20; % desired number of Rx Antenna elements

        Nt       =  200; % Number of Rows
        Mt       =  1; % Number of Columns

        Nr       =  5; % Number of Rows
        Mr       =  200; % Number of Columns

        Tx      = zeros(Nt,Mt); Tx(:,1) = randn(Nt,1)>0;
        Rx      = zeros(Nr,Mr); Rx(1,:) = randn(1,Mr)>0;
        iniVAmat = conv2(Tx, Rx);

        desiredVA = desiredVAarray(5,iniVAmat,L_t,L_r,Nt,Mt,Nr,Mr);

    case 'TayloredTI'

        rng(91340959)

        L_t     = 12 ; % desired number of Tx Antenna elements
        L_r     = 16 ; % desired number of Rx Antenna elements

        Nt       = 10; % Number of Rows
        Mt       = 900; % Number of Columns

        Nr       = 1; % Number of Rows
        Mr       = 700; % Number of Columns

        Tx      = zeros(Nt,Mt); Tx(:,1) = randn(Nt,1)>0;
        Rx      = zeros(Nr,Mr); Rx(1,:) = randn(1,Mr)>0;

        iniVAmat = conv2(Tx, Rx);

        desiredVA = desiredVAarray(11,iniVAmat,L_t,L_r,Nt,Mt,Nr,Mr); % (case 7)

    case 'Micorwaves'
        %         IEEE Journal of Microwaves
        %         System Performance of a 79 GHz High-Resolution 4D Imaging MIMO Radar With 1728 Virtual Channels

        rng(12373)
        L_t     = 36; % desired number of Tx Antenna elements
        L_r     = 48; % desired number of Rx Antenna elements

        Nt       =  95; % Number of Rows
        Mt       = 20; % Number of Columns

        Nr       = 99; % Number of Rows
        Mr       =  25; % Number of Columns

        Tx      = zeros(Nt,Mt); Tx(:,1) = randn(Nt,1)>0;
        Rx      = zeros(Nr,Mr); Rx(1,:) = randn(1,Mr)>0;
        iniVAmat = conv2(Tx, Rx);

        desiredVA = desiredVAarray(12,iniVAmat,L_t,L_r,Nt,Mt,Nr,Mr);

    case 'Circular'


        rng(12453)

        L_t     = 20 ; % desired number of Tx Antenna elements
        L_r     = 16 ; % desired number of Rx Antenna elements


        Nt       = 20; % Number of Rows
        Mt       = 20; % Number of Columns

        Nr       = 7; % Number of Rows
        Mr       = 8; % Number of Columns

        Tx      = zeros(Nt,Mt);
        for i=1:size(Tx,1)
            for j=1:size(Tx,2)
                r = norm([i/size(Tx,1)-.5 j/size(Tx,2)-.5]);
                if abs(r)==0.3
                    Tx(i,j)=1;
                end
            end
        end
        Rx      = zeros(Nr,Mr); Rx(1,:) = randn(1,Mr)>0;

        iniVAmat = conv2(Tx, Rx);
        desiredVA = desiredVAarray(1,iniVAmat,L_t,L_r,Nt,Mt,Nr,Mr);

    case 'Filled-Circular'
        rng(80)

        L_t     = 22 ; % desired number of Tx Antenna elements
        L_r     = 13 ; % desired number of Rx Antenna elements


        Nt       = 20; % Number of Rows
        Mt       = 20; % Number of Columns

        Nr       = 13; % Number of Rows
        Mr       = 1; % Number of Columns

        Tx      = zeros(Nt,Mt);
        Rx      = zeros(Nr,Mr);Rx = randn(Nt,Nr)>0;
        for i=1:size(Tx,1)
            for j=1:size(Tx,2)
                r = norm([i/size(Tx,1)-.5 j/size(Tx,2)-.5]);
                if abs(r)<=0.35  && abs(r)>=0.29
                    Tx(i,j)=1;
                end
            end
        end

        iniVAmat = conv2(Tx, Rx);
        desiredVA = desiredVAarray(13,iniVAmat,L_t,L_r,Nt,Mt,Nr,Mr);

    otherwise

end

% ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
%% Figure Initialization

k_scaling = 4;
set(0,'defaultAxesFontName','Times New Roman');
set(0,'defaultAxesGridLineStyle',':');
set(0,'defaultAxesYGrid','on');
set(0,'defaultAxesXGrid','on');
set(0,'defaultAxesFontName','Times New Roman');
set(0,'defaultAxesFontSize',3*k_scaling);

set(0,'defaultTextFontName','Times New Roman');
set(0,'defaultTextFontSize',3*k_scaling);
set(0,'defaultLegendFontName','Times New Roman');
set(0,'defaultLegendFontSize',3*k_scaling);

set(0,'defaultAxesUnits','normalized');
set(0,'defaultAxesTickDir','out');


color = [[0 0.4470 0.7410]; [0.8500 0.3250 0.0980];[0.9290 0.6940 0.1250];[0.4940 0.1840 0.5560];[0.4660 0.6740 0.1880];[0.3010 0.7450 0.9330];[0.6350 0.0780 0.1840]];
marker = ['o', '+', '>', 'h', 's', 'd', '^', 'v', '*', 'p', '<', 'x', '.' ,'-', 'o', '+', '>', 'h', 's', 'd', '^', 'v', '*', 'p', '<', 'x', '<', 'x', 'o', '+', '>', 'h', 's', 'd', '^', 'v', '*', 'p', '<'  ];

Markersize = 12;

offset = 4;
%% Code Initialization

commentInitialPlots = true;

if ~commentInitialPlots

    figure
    mplotVA(Tx,'r','v',Markersize,'Tx')
    mplotVA(Rx,'b','s',Markersize,'Rx',offset)
    legend(legendUnq())
    box on
    xlabel('x (\lambda /2)')
    ylabel('y (\lambda /2)')
    set(gca,'TickLabelInterpreter','latex')
    grid on

    xlim([-1 max(Mt,Mr)+offset+1])
    ylim([-1 max(Nt,Nr)+1])

    figure
    mplotVA(iniVAmat,'m','.',Markersize,'initial Virtual Array')
    mplotVA(desiredVA,'b','s',Markersize,'Desired Virtual Array')
    legend(legendUnq())
    box on
    xlabel('x (\lambda /2)')
    ylabel('y (\lambda /2)')

end


%% Main Code

figure,
for t   = 1 : length(eta_vec2)

    eta = eta_vec2(t);
    [Tx,Rx,virtualArray,MSE] = mCDVAdesign(Tx, Rx, desiredVA, eta, L_t, L_r);

    disp(['eta = ', num2str(eta)])
    disp(['Number of Tx Antennas = ', num2str(sum(sum(Tx)))])
    disp(['Number of Rx Antennas = ', num2str(sum(sum(Rx)))])
    disp('~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~')

    leg{t}=['$\eta= ' num2str(eta) '$'];

    semilogy(MSE/MSE(1),'linewidth',2,'Color',color(t,:), 'Marker', marker(t),'Markersize',8)
    hold  on

    if (sum(sum(Tx))==L_t && sum(sum(Rx))==L_r)
        break
    end
end
% ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
box on
ylabel('Normalized Objective Value')
xlabel('Iteration')
set(gca,'TickLabelInterpreter','latex')
grid on
legend(leg, 'Interpreter','latex')
% ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

%% plot results
% ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
% Tx and Rx array
figure
switch caseStudy
    case 'TayloredVayyar'
        mplotVA(Tx,'r','v',Markersize,'Tx',-20,5,8)
        mplotVA(Rx,'b','s',Markersize,'Rx',offset,0,8)
        xlim([-3 26])
        ylim([-2 27])
    case 'TayloredTI'
        mplotVA(Tx.','r','v',Markersize,'Tx',-20,5,8)
        mplotVA(Rx,'b','s',Markersize,'Rx',offset,0,8)
    case 'Microwaves'
        figure
        mplotVA(Tx','r','o',Markersize,'Tx',-8,10)
        mplotVA(Rx','b','x',Markersize,'Rx', 2)
        xlim([-2 102])
        ylim([3 30])
    case 'TI'
        Tx=Tx.';
        Tx=Tx.';
        mplotVA(Tx,'r','v',Markersize,'Tx',-20,3)
        mplotVA(Rx,'b','s',Markersize,'Rx',offset)
    otherwise

        mplotVA(Tx,'r','v',Markersize,'Tx',-20,3)
        mplotVA(Rx,'b','s',Markersize,'Rx',offset)

end

legend(legendUnq())
box on
xlabel('x (\lambda /2)')
ylabel('y (\lambda /2)')
set(gca,'TickLabelInterpreter','latex')
grid on


switch caseStudy
    case 'TI'
        xlim([-1 max(Mt,Mr)+1])
        ylim([-1 max(Nt,Nr)+1])
end

% ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
% plot VA
figure
switch caseStudy
    case 'TayloredVayyar'
        mplotVA(desiredVA,'b','s',Markersize,'Desired VA',0,0,8)
        mplotVA(virtualArray,'m','.',Markersize,'Designed VA',0,0,8)
        xlim([-2 25])
        ylim([-3 30])
    case 'TayloredTI'
        mplotVA(desiredVA,'b','s',Markersize,'Desired VA',0,0,8)
        mplotVA(virtualArray,'m','.',Markersize,'Designed VA',0,0,8)

    case 'Microwaves'
        mplotVA(desiredVA,'b','s',Markersize,'Desired VA')
        mplotVA(virtualArray,'m','.',Markersize,'Designed VA')
        xlim([5 40])
        ylim([0 220])
    case 'TI'
        mplotVA(desiredVA,'b','s',Markersize,'Desired VA')
        mplotVA(virtualArray,'m','.',Markersize,'Designed VA')
        xlim([37 130])
        ylim([0.5 8.5])
    otherwise

        mplotVA(desiredVA,'b','s',Markersize,'Desired VA')
        mplotVA(virtualArray,'m','.',Markersize,'Designed VA')
        xlim([1 26])
        ylim([1 25])
end

legend(legendUnq())
box on
xlabel('x (\lambda /2)')
ylabel('y (\lambda /2)')

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

function mplotVA(Array,Color,Marker,Markersize,DisplayName,offsetx,offsety,Q)
if ~exist('offsetx','var')
    offsetx = 0;
end
if ~exist('offsety','var')
    offsety = 0;
end

if ~exist('Q','var')
    Q = 1;
end


hold on
for i = 1:size(Array,1)
    for j = 1:size(Array,2)
        if Array(i,j)>=1
            plot((j+offsetx)/Q,(i+offsety)/Q,'Marker',Marker,'Color',Color,'Markersize',Markersize,'DisplayName', DisplayName)
        end
    end
end
end

% ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
% ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
% ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~


function [Tx, Rx, virtualArray,ObjVec]=mCDVAdesign(Tx, Rx, desiredVA, eta, L_t, L_r,thr)

[Nt, Mt]        = size(Tx);
[Nr, Mr]        = size(Rx);
virtualArray = conv2(Tx, Rx);

if ~exist('thr','var')
    thr = 1e-5;
end

alpha=1;
f1 = norm(desiredVA - alpha*virtualArray, 'fro');
f2 = ( abs(( sum(sum(Rx))-L_r ))+(abs((sum(sum(Tx))-L_t ))) );

ObjVec(1) = f1+(eta)*f2;

while 1
    alpha   = (desiredVA(:).'*virtualArray(:))/(norm(virtualArray(:))^2);

    f1      = norm(desiredVA - alpha*virtualArray, 'fro');
    f2      = ( abs(( sum(sum(Rx))-L_r )) + (abs((sum(sum(Tx))-L_t ))) );

    obj     = f1 + (eta)*f2;
    if f2 ~= 0

        % Optimize Tx
        for x = 1 : Nt
            for y = 1 : Mt

                txs     = Tx(x,y);
                z       = zeros(size(virtualArray));
                z(x:(x+size(Rx,1)-1),y:(y+size(Rx,2)-1)) = Rx;

                if Tx(x,y)==0
                    virtualArrayN = virtualArray + z;
                    Tx2         = Tx;
                    Tx2(x,y)    = 1;
                else
                    virtualArrayN = virtualArray - z;
                    Tx2=Tx;
                    Tx2(x,y)=0;
                end

                f1N     = norm(desiredVA - alpha*virtualArrayN, 'fro');
                f2N     = (abs((sum(sum(Rx))-L_r))+(abs((sum(sum(Tx2))-L_t))));

                objN    = f1N + (eta)*f2N;
                if objN < obj
                    virtualArray = virtualArrayN;
                    obj     = objN;
                    Tx(x,y) = ~txs;
                end


            end
        end

        % Optimize Rx
        for x = 1 : Nr
            for y = 1 : Mr
                % ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                % Optimize Rx
                rxs=Rx(x,y);
                z=zeros(size(virtualArray));
                z(x:(x+size(Tx,1)-1),y:(y+size(Tx,2)-1))=Tx;

                if Rx(x,y)==0
                    virtualArrayN = virtualArray + z;
                    Rx2=Rx;
                    Rx2(x,y)=1;
                else
                    virtualArrayN = virtualArray - z;
                    Rx2=Rx;
                    Rx2(x,y)=0;
                end
                f1N=norm(desiredVA - alpha*virtualArrayN, 'fro');
                f2N=( abs((sum(sum(Rx2))-L_r)) +(abs(sum(sum(Tx))-L_t)) );

                objN      =f1N + (eta)*f2N;
                if objN<obj
                    virtualArray = virtualArrayN;
                    obj=objN;
                    Rx(x,y) = ~rxs;
                end
                % ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
            end
        end
    end

    ObjVec(end+1) = obj;

    if ObjVec(end-1) - ObjVec(end) < thr
        break;
    end


end
virtualArray = conv2(Tx, Rx);



end


% ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
% ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
% ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

function [desiredVA] = desiredVAarray(nArraySelection,virtualArray,L_t,L_r,Nt,Mt,Nr,Mr)

if ~exist('L_t','var')
    L_t = 0;
end
if ~exist('L_r','var')
    L_r = 0;
end
if ~exist('Nt','var')
    Nt = 0;
end

if ~exist('Mt','var')
    Mt = 0;
end

if ~exist('Nr','var')
    Nr = 0;
end

if ~exist('Mr','var')
    Mr = 0;
end


switch nArraySelection
    case 1 %'circular'
        desiredVA = zeros(size(virtualArray));
        for i=1:size(desiredVA,1)
            for j=1:size(desiredVA,2)
                r = norm([i/size(desiredVA,1)-.5 j/size(desiredVA,2)-.5]);
                if abs(r)<.35 && abs(r)>.2
                    desiredVA(i,j)=1;
                end
            end
        end

    case 2
        desiredVA = zeros(size(virtualArray));
        for i=1:size(desiredVA,1)
            for j=1:size(desiredVA,2)
                if i==1 || j==1
                    desiredVA(i,j)=1;
                end
            end
        end
    case 3
        desiredVA = zeros(size(virtualArray));
        for i=1:size(desiredVA,1)
            for j=1:size(desiredVA,2)
                if (abs(i/size(desiredVA,1)-.5)<.05) && (abs(j/size(desiredVA,2)-.5)<.05)
                    desiredVA(i,j)=1;
                end
            end
        end
    case 4 % 20 \times 20
        desiredVA = zeros(size(virtualArray));
        for i = floor(size(desiredVA,1)/2)+(-9:10)
            for j=floor(size(desiredVA,2)/2)+(-9:10)
                desiredVA(i,j)=1;
            end
        end

    case 5
        % VayyarTaylored
        desiredVA = zeros(size(virtualArray));
        NE=19;
        d = 1./taylorwin(NE);
        d=d/2;
        Q=1/16;
        p = 0;
        for i = 1:length(d)
            q = round(d(i)/Q);
            p(end+1)=p(end)+q*Q;
        end

        a = p/Q+1;
        % optArray = zeros(max(a));
        for i = 1:length(a)
            desiredVA(a(i),a)=1;
        end


    case 6 % vayyar

        Tx          = zeros(Nt,Mt);
        Rx          = zeros(Nr,Mr);
        Tx(1:L_t,1) = ones(L_t,1);
        Rx(1,1:L_r) = ones(1,L_r);
        desiredVA   = conv2(Tx, Rx);

    case 7 % TI
        % Texas Instruments Imaging Radar
        % https://www.ti.com/lit/ug/tiduen5a/tiduen5a.pdf?ts=1666267728378
        tempTx          = zeros(Nt,Mt);
        tempRx          = zeros(Nr,Mr);

        Rx = [ones(1,4) zeros(1,8) ones(1,4) zeros(1,32) ones(1,8)];

        tempRx(1,1:length(Rx)) = Rx;

        Rx = tempRx;

        Tx = [1 0 0 0 ];
        Tx = [Tx Tx Tx Tx Tx Tx Tx Tx Tx];


        Tx(2,:) = 0;
        Tx(2,10) = 1;


        Tx(5,:) = 0;
        Tx(5,11) = 1;

        Tx(7,:) = 0;
        Tx(7,12) = 1;


        tempTx(1:7,1:size(Tx,2)) = Tx;

        Tx = tempTx;


        desiredVA   = conv2(Tx, Rx);

        desiredVA = desiredVA(:,end:-1:1);

    case 8
        % Bosch
        Tx = [1 zeros(1,15) 1 zeros(1,15) 1];

        Tx(15,1) = 1;
        Tx = Tx(end:-1:1,:);
        Rx(1,14) = 1;
        Rx(3,15) = 1;
        Rx(5,16) = 1;

        k=7;
        Rx(k,1:10) = [ones(1,10)];
        Rx(k+3-1,11) = 1;
        Rx(k+5-1,12) = 1;
        Rx(k+7-1,13) = 1;

        tempTx          = zeros(Nt,Mt);
        tempTx(1:size(Tx,1),1:size(Tx,2)) = Tx;
        Tx  = tempTx;

        tempRx          = zeros(Nr,Mr);
        tempRx(1:size(Rx,1),1:size(Rx,2)) = Rx;
        Rx = tempRx;

        desiredVA   = conv2(Tx, Rx);

    case 9
        %         IEEE TRANSACTIONS ON GEOSCIENCE AND REMOTE SENSING, VOL. 56,
        %         NO. 1, JANUARY 2018
        %         A Portable 3-D Imaging FMCW MIMO Radar Demonstrator With a 24 ×
        %         24 Antenna Array for Medium-Range Applications

        Tx = zeros(12,14);
        Tx(1:12,1) = 1;
        Tx(1:12,14) = 1;

        Rx = zeros(12,14);

        Rx(1,2:13) = 1;
        Rx(12,2:13) = 1;


        tempTx          = zeros(Nt,Mt);
        tempTx(1:size(Tx,1),1:size(Tx,2)) = Tx;
        Tx  = tempTx;

        tempRx          = zeros(Nr,Mr);
        tempRx(1:size(Rx,1),1:size(Rx,2)) = Rx;
        Rx = tempRx;


        desiredVA   = conv2(Tx, Rx);


    case 10
        % Vayyar
        Tx = zeros(24,24);
        Rx = zeros(24,24);
        Tx(:,1) = 1;
        Rx(1,:) = 1;

        tempTx          = zeros(Nt,Mt);
        tempTx(1:size(Tx,1),1:size(Tx,2)) = Tx;
        Tx  = tempTx;

        tempRx          = zeros(Nr,Mr);
        tempRx(1:size(Rx,1),1:size(Rx,2)) = Rx;
        Rx = tempRx;
        desiredVA   = conv2(Tx, Rx);

    case 11
        % TI with Taylor weight


        tempVA = zeros(Nt,Mt);
        NE  = 88-1;
        d   = 1./taylorwin(NE);
        d   = d/2;
        Q=1/2;
        p = 0;
        for i = 1:length(d)
            q = round(d(i)/Q);
            p(end+1)=p(end)+q*Q;
        end

        a = p/Q+1;

        tempVA(1,a) = 1;

        rows=[2 5 7];
        cols1= (500:4:600) -100;
        cols2= (800:4:850) -100 ;
        cols3= (950:4:1000) -100 ;

        for ii = 1:length(rows)
            tempVA(rows(ii),cols1)=1;
            tempVA(rows(ii),cols2)=1;
            tempVA(rows(ii),cols3)=1;
        end

        tempTx          = zeros(Nt,Mt);
        tempRx          = zeros(Nr,Mr);

        desiredVA   = conv2(tempTx, tempRx);

        desiredVA(1:size(tempVA,1),1:size(tempVA,2)) = tempVA;


    case 12 %Micorwaves%
        %homework System Performance of a 79 GHz High-Resolution
        %4D Imaging MIMO Radar With 1728 Virtual Channels

        TXX = [76   76   76  74  74  74 46  46  46  44  44  44  16  16  16  14  14  14];
        TXX = [TXX -TXX(end:-1:1)];
        TXY = repmat([-9 0 9],1,12);

        RXX=[82 80 78 76  74 72  70  64 56 54 54 48 36 34  30  30 28 24 22 22 10 10  6  4  2   2  -2 -4 -20 -22 -24 -28 -30 -32 -38 -42 -46 -48 -54 -62 -64 -64 -66 -74 -82 -86 -100 -102];
        RXY=[9  11 4  18 -18 -16 -14 14 9 -18 11 16 -14 -21 -11 9 11 16 14 -11 -2 11 -11 9 -14 11 16 -11 14  9   11  16  -16 -14 -16  -9 -20 9   6  -18 -16  14  -14  20 -16 -16 -14 -11];


        fc = 79e9;
        Lambda = 3e8/fc;
        Q = 2;
        d = Lambda / Q *1000;
        xmin = min([TXX RXX]);
        ymin = min([TXY RXY]);

        xTX = round((TXX - xmin)/d)+1;
        xRX = round((RXX - xmin)/d)+1;

        yTX = round((TXY - ymin)/d)+1;
        yRX = round((RXY - ymin)/d)+1;

        Tx(xTX,yTX)=1;

        for i = 1:length(xRX)
            Rx(xRX(i),yRX(i))=1;
        end
        %
        tempTx          = zeros(Nt,Mt);
        tempTx(1:size(Tx,1),1:size(Tx,2)) = Tx;
        Tx  = tempTx;

        tempRx          = zeros(Nr,Mr);
        tempRx(1:size(Rx,1),1:size(Rx,2)) = Rx;
        Rx = tempRx;


        desiredVA   = conv2(Tx, Rx);

    case 13 %'filled circular'
        desiredVA = zeros(size(virtualArray));
        for i=1:size(desiredVA,1)
            for j=1:size(desiredVA,2)
                r = norm([i/size(desiredVA,1)-.5 j/size(desiredVA,2)-.5]);
                if abs(r)<.25
                    desiredVA(i,j)=1;
                end
            end
        end
    otherwise
        desiredVA = virtualArray;
end
end



% ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
% ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
% ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~


function unqLegHands = legendUnq(h, sortType)
% unqLegHands = legendUnq(h, sortType)
%   Run this function just before running 'legend()' to avoid representing duplicate or missing
% DisplayNames within the legend. This solves the problem of having a cluttered legend with 
% duplicate or generic values such as "data1" assigned by matalab's legend() function.  This 
% also makes is incredibly easy to assign one legend to a figure with multiple subplots. 
% Use the 'DisplayName' property in your plots and input the axis handle or the figure handle 
% so this code can search for all potential legend elements, find duplicate DisplayName strings, 
% and remove redundent components by setting their IconDisplayStyle to 'off'.  Then call 
% legend(unqLegHands) to display unique legend components. 
% INTPUT
%       h: (optional) either a handle to a figure, an axis, or a vector of axis handles. The code 
%           will search for plot elements in all axes belonging to h.  If h is missing, gca is used.
%       sort: (optional) can be one of the following strings that will sort the unqLeghands.
%           'alpha': alphabetical order. 
% OUTPUT
%       unqLegHands: a list of handles that have unique DisplayNames; class 'matlab.graphics.chart.primitive.Line'.
%           ie: unqLegHands = legendUnq(figHandle); legend(unqLegHands)
% EXAMPLE 1: 
%         figure; axis; hold on
%         for i=1:10
%             plot(i,rand(), 'ko', 'DisplayName', 'randVal1');        % included in legend
%             plot(i+.33, rand(), 'ro', 'DisplayName', 'randVal2');   % included in legend       
%         end
%         plot(rand(1,10), 'b-'); 	% no DisplayName so it is absent from legend
%         legend(legendUnq())
% EXAMPLE 2: 
%         fh = figure; subplot(2,2,1); hold on
%         plot(1:10, rand(1,10), 'b-o', 'DisplayName', 'plot1 val1')
%         plot(1:2:10, rand(1,5), 'r-*', 'DisplayName', 'plot1 val2')
%         subplot(2,2,2); hold on
%         plot(1:10, rand(1,10), 'm-o', 'DisplayName', 'plot2 val1')
%         plot(1:2:10, rand(1,5), 'g-*', 'DisplayName', 'plot2 val2')
%         subplot(2,2,3); hold on
%         plot(1:10, rand(1,10), 'c-o', 'DisplayName', 'plot3 val1')
%         plot(1:2:10, rand(1,5), 'k-*', 'DisplayName', 'plot3 val2')
%         lh = legend(legendUnq(fh)); 
%         lh.Position = [.6 .2 .17 .21];
%
% Danz 180515

% Change history
% 180912 fixed error when plot is empty
% 180913 adapted use of undocumented function for matlab 2018b

persistent useOldMethod

% If handle isn't specified, choose current axes
if nargin == 0
    h = gca; 
end

% If user entered a figure handle, replace with a list of children axes; preserve order of axes
if strcmp(get(h, 'type'), 'figure')
    h = flipud(findall(h, 'type', 'Axes')); 
end

% set flag to use old method of obtaining legend children
% In 2018b matlab changed an undocumented function that obtains legend handles. 
useOldMethod = verLessThan('matlab', '9.5.0'); 

% Set the correct undocumented function 
if useOldMethod
    getLegendChildren = @(x) graph2dhelper('get_legendable_children', x);
else
    getLegendChildren = @(x) matlab.graphics.illustration.internal.getLegendableChildren(x);
end

% Get all objects that will be assigned to legend.
% This uses an undocumented function that the legend() func uses to get legend componenets.
legChildren = matlab.graphics.chart.primitive.Line; %initializing class (unsure of a better way)
for i = 1:length(h)
    temp = getLegendChildren(h(i));
    if ~isempty(temp)
        legChildren(end+1:end+length(temp),1) = temp; 
    end
end
legChildren(1) = [];
% Get display names
dispNames = get(legChildren, 'DisplayName');
if isempty(dispNames)
    dispNames = {''}; 
end
if ~iscell(dispNames)
    dispNames = {dispNames}; 
end
% Find the first occurance of each name 
[~, firstIdx] = unique(dispNames, 'first'); 
% Create an index of legend items that will be hidden from legend
legRmIdx = true(size(legChildren)); 
legRmIdx(firstIdx) = false; 
% Add any elements that have no displayName to removal index (legend would assign them 'dataX')
legRmIdx = legRmIdx | cellfun(@isempty,dispNames);
% get all annotations
annot = get(legChildren, 'Annotation'); 
% Loop through all items to be hidden and turn off IconDisplayStyle
for i = 1:length(annot)
    if legRmIdx(i)
        set(get(annot{i}, 'LegendInformation'), 'IconDisplayStyle', 'off');
    end
end
% Output remaining, handles to unique legend entries
unqLegHands = legChildren(~legRmIdx); 

% Sort, if user requested
if nargin > 1 && ~isempty(sortType) && length(unqLegHands)>1
    [~, sortIdx] = sort(get(unqLegHands, 'DisplayName'));
    unqLegHands = unqLegHands(sortIdx); 
end

end