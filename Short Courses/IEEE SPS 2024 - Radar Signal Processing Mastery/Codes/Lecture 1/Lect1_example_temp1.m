% SPS Short Course: Radar Signal Processing Mastery
% Theory and Hands-On Applications with mmWave MIMO Radar Sensors
% Date: 7-11 October 2024
% Time: 9:00AM-11:00AM ET (New York Time)
% Presenter: Mohammad Alaee-Kerahroodi

close all
clear
clc

rng(2024)
% Constants
c = 3e8;            % Speed of light in m/s

% Parameters
tau = 200e-6;       % Pulse width (200 µs)
bandwidth = 1e6;    % Bandwidth of the LFM signal (10 MHz)
fs = 10*bandwidth;  % Sampling frequency (samples per second)
timeBandwidthProduct = tau * bandwidth;
samplePerChip = round(tau * fs);
ddsRate = samplePerChip/timeBandwidthProduct;

% Parameters
PRI = 1e-3;         % Pulse Repetition Interval 
PRF = 1/PRI;        % Pulse Repetition Frequency 
nPulse = 2;         % Number of pulses

t_start = 100e-6;   % Start time (0 ms)
t = linspace(0, t_start+nPulse*PRI, (t_start+nPulse*PRI)*fs); % Time vector 

% Time vector for pulse duration
tPulse = 0:1/fs:tau-1/fs;

% Generate Up LFM chirp signal (frequency increases from -B/2 to B/2)
lfm_chirp = chirp(tPulse, 0, tau, bandwidth, 'linear','complex');  % Up LFM chirp

pulseTx = zeros(size(t));   % Transmit pulse
% Insert LFM chirp in the transmit signal
for i = 0:nPulse-1
    tInterval = t >= t_start + i*PRI & t <= t_start + i*PRI + tau; % Time interval for each pulse
    pulseTx(tInterval) = lfm_chirp;  % Set transmitted pulse to the LFM chirp
end

figure('Position', [100, 100, 900, 600]);
plot(t*1e3, real(pulseTx), 'r', 'LineWidth', 2, 'DisplayName', 'Transmit Pulse (LFM)'); hold on;
% plot(t*1e3, imag(pulseTx), 'b', 'LineWidth', 2, 'DisplayName', 'Transmit Pulse (LFM)'); hold on;


xlabel('Time (ms)', 'FontSize', 14);
ylabel('Amplitude', 'FontSize', 14);
legend();
grid on;
axis('tight')
ylim([-1 1]);
% xlim([0.05,0.4])

