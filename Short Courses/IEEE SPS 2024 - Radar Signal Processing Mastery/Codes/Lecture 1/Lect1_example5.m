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
bandwidth = 1/tau;  % Bandwidth of the pulse

fs = 10*bandwidth;  % Sampling frequency (samples per second)
samplePerChip = round(tau * fs);

snr = 0;            % dB

t_start = 100e-6;   % Start time (0 ms)
t = linspace(0, t_start+nPulse*PRI, (t_start+nPulse*PRI)*fs); % Time vector 

% Simulated delay and attenuation for the received signal
delayTarget1 = 400e-6;   % Round-trip delay of target
delayTarget2 = 500e-6;   % Round-trip delay of target
attTarget1 = 0.1;        % Attenuation factor
attTarget2 = 0.2;        % Attenuation factor

pulseTx = zeros(size(t));   % Transmit pulse
pulseRxTarget1 = zeros(size(t));   % Received pulse
pulseRxTarget2 = zeros(size(t));   % Received pulse

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
received_signal = awgn(received_pulse, snr, "measured");

% Animation setup
figure('Position', [100, 100, 900, 600]);

% Initialize GIF file
filename = 'matched_filter_animation.gif';  % Output GIF file name

for k = 1:length(t)
    cla
    plot(t*1e3, pulseTx, 'r', 'LineWidth', 2, 'DisplayName', 'Transmit Pulse'); hold on;
    plot(t*1e3, received_signal, 'g', 'LineWidth', 2, 'DisplayName', 'Received Signal');

    % Calculate matched filter output up to current time
    r = abs(xcorr(received_signal(1:k), pulseTx(end:-1:1)));

    % Plot matched filter output
    plot(t*1e3, r(round(tau*fs) + 1:round(tau*fs) + length(t)), 'LineWidth', 2, 'DisplayName', 'Matched Filter Output');
    
    xlabel('Time (ms)', 'FontSize', 12);
    ylabel('Amplitude', 'FontSize', 12);
    legend();
    grid on;
    ylim([-1 3]);

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

    pause(0.01);  % Pause to create animation effect
end
