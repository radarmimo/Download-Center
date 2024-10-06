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
fc = 150e6;         % Carrier frequency in Hz
lambda = c / fc;    % Wavelength in meters
vrTarget1 = 100;    % Radial speed of the target in m/s
vrTarget2 = 70;     % Radial speed of the target in m/s

% Doppler frequency calculation
fdTarget1 = 2 * vrTarget1 / lambda;  % Doppler frequency in Hz
fdTarget2 = 2 * vrTarget2 / lambda;  % Doppler frequency in Hz

% Parameters
PRI = 1e-3;         % Pulse Repetition Interval 
PRF = 1/PRI;        % Pulse Repetition Frequency 
nPulse = 1;         % Number of pulses
nFFT = 4096;
tau = 200e-6;       % Pulse width 
bandwidth = 1e6;   % Bandwidth of the LFM signal (10 MHz)

fs = 10*bandwidth;  % Sampling frequency (samples per second)
timeBandwidthProduct = tau * bandwidth;
samplePerChip = round(tau * fs);
ddsRate = samplePerChip/timeBandwidthProduct;

snr = 0;            % dB

t_start = 100e-6;   % Start time (0 ms)
t = linspace(0, t_start+nPulse*PRI, (t_start+nPulse*PRI)*fs); % Time vector 

% Simulated delay and attenuation for the received signal
delayTarget1 = 400e-6;   % Round-trip delay of target
delayTarget2 = 410e-6;   % Round-trip delay of target
attTarget1 = 0.1;        % Attenuation factor
attTarget2 = 0.2;        % Attenuation factor

% Generate LFM chirp signal
pulseTx = zeros(size(t));   % Transmit pulse
tPulse = 0:1/fs:tau-1/fs;        % Time vector for pulse duration
lfm_chirp = chirp(tPulse, 0, tau, bandwidth, 'linear');  % Up LFM chirp

% Insert LFM chirp in the transmit signal
for i = 0:nPulse-1
    tInterval = t >= t_start + i*PRI & t <= t_start + i*PRI + tau; % Time interval for each pulse
    pulseTx(tInterval) = lfm_chirp;  % Set transmitted pulse to the LFM chirp
end

pulseRxTarget1 = zeros(size(t));   % Received pulse for target 1
pulseRxTarget2 = zeros(size(t));   % Received pulse for target 2

dopplerSignalTarget1 = cos(2 * pi * fdTarget1 * t);
dopplerSignalTarget2 = cos(2 * pi * fdTarget2 * t);

% Apply delay and attenuation for the received signals
for i = 0:nPulse-1
    tIntervalTarget1 = t >= t_start + i*PRI + delayTarget1 & t <= t_start + i*PRI + delayTarget1 + tau;
    tIntervalTarget2 = t >= t_start + i*PRI + delayTarget2 & t <= t_start + i*PRI + delayTarget2 + tau;

    pulseRxTarget1(tIntervalTarget1) = attTarget1 * lfm_chirp;  % Set received pulse for target 1
    pulseRxTarget2(tIntervalTarget2) = attTarget2 * lfm_chirp;  % Set received pulse for target 2
end

% Combine received pulses with Doppler shift
received_pulse = (pulseRxTarget1 .* dopplerSignalTarget1) + (pulseRxTarget2 .* dopplerSignalTarget2);  
received_signal = awgn(received_pulse, snr, "measured");

% Animation setup
figure('Position', [100, 100, 900, 600]);

% Initialize GIF file
filename = 'matched_filter_LFM_animation.gif';  % Output GIF file name

for k = 1:ddsRate*10:length(t)
    cla
    plot(t*1e3, pulseTx, 'r', 'LineWidth', 2, 'DisplayName', 'Transmit Pulse (LFM)'); hold on;
    plot(t*1e3, received_signal, 'g', 'LineWidth', 2, 'DisplayName', 'Received Signal');

    % Calculate matched filter output up to current time
    r = abs(xcorr(received_signal(1:ddsRate:k), pulseTx(end:-ddsRate:1)))/timeBandwidthProduct*ddsRate;
    tr = t(1:ddsRate:end);
    % Plot matched filter output
    plot(tr*1e3, r(timeBandwidthProduct + 1:timeBandwidthProduct + length(tr)), 'LineWidth', 2, 'DisplayName', 'Matched Filter Output');
    axis('tight')
    xlabel('Time (ms)', 'FontSize', 12);
    ylabel('Amplitude', 'FontSize', 12);
    legend();
    grid on;
    ylim([-1 1]);
    axis('tight')

    % Capture frame and convert it to an image
    frame = getframe(gcf);
    img = frame2im(frame);
    [imgIndexed, cmap] = rgb2ind(img, 256);  % Convert image to indexed color map

    % Write the frame to the GIF file
    if k == 1
        imwrite(imgIndexed, cmap, filename, 'gif', 'LoopCount', Inf, 'DelayTime', 0.01);
    else
        imwrite(imgIndexed, cmap, filename, 'gif', 'WriteMode', 'append', 'DelayTime', 0.01);
    end
    
    drawnow
    
    % pause(0.01);  % Pause to create animation effect
end
% spectrogram(lfm_chirp)