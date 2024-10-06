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
f_c = 10e9;         % Carrier frequency for radar 
lambda = c / f_c;   % Wavelength in meters

% Parameters
tau = 200e-6;       % Pulse width 
bandwidth = 1e6;    % Bandwidth of the transmit signal 
fs = 10*bandwidth;  % Sampling frequency (samples per second)

% Parameters
PRI = 1e-3;         % Pulse Repetition Interval 
PRF = 1/PRI;        % Pulse Repetition Frequency 
nPulse = 128;       % Number of pulses

nFFT = 256;
snr = 0;

timeBandwidthProduct = tau * bandwidth;
samplePerChip = round(tau * fs);
ddsRate = samplePerChip/timeBandwidthProduct;
samplePerPRI = round(PRI*fs);

unambRange = c * PRI /2;
rangeResolution = c / (2 * bandwidth);

t_start = 100e-6;   % Start time 
sampleStart = round(t_start * fs);
t = linspace(0, t_start+nPulse*PRI, (t_start+nPulse*PRI)*fs); % Time vector 

% Time vector for pulse duration
tPulse = 0:1/fs:tau-1/fs;

% Generate transmit signal
alpha = exp(1i * 2*pi /timeBandwidthProduct);
exponent = (0:(timeBandwidthProduct-1))' .* (1:timeBandwidthProduct)' / 2;
golomb_code = alpha.^exponent;

random_code = 2*randi([0 1], 1, timeBandwidthProduct) - 1; % Random binary (+1/-1)
tx_waveform = repelem(random_code, ddsRate);


% Doppler Resolution Calculation
Tcpi = nPulse * PRI;                   % Total observation time (CPI)

doppler_resolution = 1 / Tcpi;         % Doppler resolution in Hz
velocity_resolution = lambda / (2 * Tcpi);  % Velocity resolution in m/s

% Display Doppler and Velocity Resolution
fprintf('Doppler Resolution: %.2f Hz\n', doppler_resolution);
fprintf('Velocity Resolution: %.4f m/s\n', velocity_resolution);

% Simulate Two Targets with Different Doppler Shifts
v1 = 5;   % Velocity of target 
v2 = -3;   % Velocity of target 
fd1 = 2 * v1 / lambda;  % Doppler frequency shift for target 1
fd2 = 2 * v2 / lambda;  % Doppler frequency shift for target 2
dopplerTarget1 = exp(1j * 2 * pi * fd1 * t);
dopplerTarget2 = exp(1j * 2 * pi * fd2 * t);

delayTarget1 = 400e-6;   % Round-trip delay of target
delayTarget2 = 400e-6;   % Round-trip delay of target
attTarget1 = 0.1;        % Attenuation factor
attTarget2 = 0.2;        % Attenuation factor

pulseTx = zeros(size(t));   % Transmit pulse

% Simulate received signals from the two targets
pulseRxTarget1 = zeros(size(t));   % Received pulse for target 1
pulseRxTarget2 = zeros(size(t));   % Received pulse for target 2


for i = 0:nPulse-1
    tInterval = t >= t_start + i*PRI & t <= t_start + i*PRI + tau;
    pulseTx(tInterval) = tx_waveform;  % Set transmitted pulse to the intrspulse modulation

    tIntervalTarget1 = t >= t_start + i*PRI + delayTarget1 & t <= t_start + i*PRI + delayTarget1 + tau;
    tIntervalTarget2 = t >= t_start + i*PRI + delayTarget2 & t <= t_start + i*PRI + delayTarget2 + tau;

    pulseRxTarget1(tIntervalTarget1) = attTarget1 * tx_waveform;  % Set received pulse for target 1
    pulseRxTarget2(tIntervalTarget2) = attTarget2 * tx_waveform;  % Set received pulse for target 2

end


received_pulse = pulseRxTarget1 .* exp(1j * 2 * pi * fd1 * t)  + pulseRxTarget2 .* exp(1j * 2 * pi * fd2 * t);  
% Total received signal
received_signal = awgn(received_pulse, snr, "measured");

% matched filter
r = filter(conj(tx_waveform(end:-ddsRate:1)),1,received_signal(1:ddsRate:end))/timeBandwidthProduct;

% range-Doppler
dataMatrix = reshape(r(round(sampleStart/ddsRate)+1:end),round(samplePerPRI/ddsRate),nPulse);
rangeDoppler = abs(fftshift(fft(dataMatrix,nFFT,2)));

% Plot the received signal (real part)
figure('Position', [100, 100, 900, 600]);
plot(t*1e3, real(pulseTx), 'r', 'LineWidth', 2, 'DisplayName', 'Transmit Signal'); hold on;
plot(t*1e3, real(received_signal), 'b', 'LineWidth', 2, 'DisplayName', 'Received Signal');
plot(t(1:ddsRate:end)*1e3, abs(r(1:end))*4, 'LineWidth', 2, 'DisplayName', 'Matched Filter output')
axis('tight')
xlabel('Time (ms)', 'FontSize', 14);
ylabel('Amplitude', 'FontSize', 14);
legend();
grid on;


rangeDoppler_dB = 20 * log10(rangeDoppler / max(rangeDoppler(:)));  % Normalize and convert to dB

% Plot Range-Doppler map
figure('Position', [100, 100, 900, 600]);
axisfd = linspace(-PRF/2,PRF/2,nFFT);
axisVr = linspace(-PRF*lambda/4,PRF*lambda/4,nFFT);
axisRange = 0:rangeResolution:unambRange - rangeResolution;
imagesc(axisRange/1e3, axisVr, rangeDoppler_dB.');
ylabel('Radial Speed (m/s)', 'FontSize', 14);
xlabel('Range (Km)', 'FontSize', 14);
% title('Range-Doppler Map', 'FontSize', 16);
colormap(jet);
colorbar;
clim([-40 0]);  % Dynamic range in dB
axis xy;

% Optional: Add markers for the targets
hold on;
plot(fd1, delayTarget1 * c / 2, 'ro', 'MarkerSize', 10, 'LineWidth', 2, 'DisplayName', 'Target 1');
plot(fd2, delayTarget2 * c / 2, 'go', 'MarkerSize', 10, 'LineWidth', 2, 'DisplayName', 'Target 2');
legend show;