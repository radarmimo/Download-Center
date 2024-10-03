% SPS Short Course: Radar Signal Processing Mastery
% Theory and Hands-On Applications with mmWave MIMO Radar Sensors
% Date: 7-11 October 2024
% Time: 9:00AM-11:00AM ET (New York Time)
% Presenter: Mohammad Alaee-Kerahroodi

close all
clear
clc

% Constants
c = 3e8;            % Speed of light in m/s
fc = 150e6;           % Carrier frequency in Hz
lambda = c / fc;    % Wavelength in meters
vrTarget1 = 100;           % Radial speed of the target in m/s
vrTarget2 = 70;           % Radial speed of the target in m/s

% Doppler frequency calculation
fdTarget1 = 2 * vrTarget1 / lambda;  % Doppler frequency in Hz
fdTarget2 = 2 * vrTarget2 / lambda;  % Doppler frequency in Hz

% Parameters
PRI = 1e-3;            % Pulse Repetition Interval 
PRF = 1/PRI;           % Pulse Repetition Frequency 
nPulse = 1;           % Number of pulses
nFFT = 4096;
tau = 200e-6;          % Pulse width 
bandwidth = 1/tau;    % Bandwidth of the pulse

fs = 10*bandwidth;    % Sampling frequency (samples per second)

snr = 10;           % dB

t_start = 100e-6;      % Start time (0 ms)
t = linspace(0, t_start+nPulse*PRI, (t_start+nPulse*PRI)*fs); % Time vector 

% Simulated delay and attenuation for the received signal
delayTarget1 = 400e-6;   % Round-trip delay of target
delayTarget2 = 650e-6;   % Round-trip delay of target
attTarget1 = 0.1;     % Attenuation factor
attTarget2 = 0.2;     % Attenuation factor

numRangeBins = round(PRI * fs);
indexStart = round(t_start/PRI * numRangeBins);
indexTarget = round((delayTarget1+tau/2)/PRI * numRangeBins);

pulseTx = zeros(size(t));   % Transmit pulse
pulseRxTarget1 = zeros(size(t));   % Received pulse
pulseRxTarget2 = zeros(size(t));   % Received pulse

% doppler_signal = zeros(size(t));    % Doppler signal
dopplerSignalTarget1 = cos(2 * pi * fdTarget1 * t);
dopplerSignalTarget2 = cos(2 * pi * fdTarget2 * t);

for i = 0:nPulse-1
    tInterval = t >= t_start + i*PRI & t <= t_start + i*PRI + tau; % Time interval for each pulse
    pulseTx(tInterval) = 1;  % Set transmitted pulse to 1

    tIntervalTarget1 = t >= t_start + i*PRI + delayTarget1 & t <= t_start + i*PRI + delayTarget1 + tau;
    tIntervalTarget2 = t >= t_start + i*PRI + delayTarget2 & t <= t_start + i*PRI + delayTarget2 + tau;

    pulseRxTarget1(tIntervalTarget1) = attTarget1;  % Set received pulse
    pulseRxTarget2(tIntervalTarget2) = attTarget2;  % Set received pulse
end

received_pulse = pulseRxTarget1 .* dopplerSignalTarget1 + pulseRxTarget2 .* dopplerSignalTarget2;  % Received pulse (Delayed and attenuated)
received_signal = awgn(received_pulse,snr,"measured");
% data_cube_noiseless = reshape(received_pulse(indexStart+1:end),[numRangeBins,nPulse]);
% data_cube = reshape(received_signal(indexStart+1:end),[numRangeBins,nPulse]);


figure('Position', [100, 100, 900, 600]);
plot(t*1e3, pulseTx, 'r', 'LineWidth', 2,'DisplayName','Transmit Pulse'); hold on;  % Transmit pulse
plot(t*1e3, pulseRxTarget1, 'm', 'LineWidth', 2,'DisplayName','Received Pulse Target #1');          % Received pulse
plot(t*1e3, pulseRxTarget2, 'c', 'LineWidth', 2,'DisplayName','Received Pulse Target #2');          % Received pulse
plot(t*1e3, received_signal, 'g', 'LineWidth', 2,'DisplayName','Received Signal');          % Received pulse

legend()
xlabel('Time (ms)', 'FontSize', 12);
ylabel('Amplitude', 'FontSize', 12);
% legend('Transmit Pulse', 'Received Pulse', 'Doppler Signal', 'FontSize', 12);
grid on;
set(gca, 'FontSize', 12);
box on;
axis('tight');
ylim([-1 1]);

r = abs(xcorr(received_signal,pulseTx(end:-1:1)));
% figure; 
plot(t*1e3, r(round(tau*fs) + 1:round(tau*fs) + length(t)));