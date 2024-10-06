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
tau = 200e-6;       % Pulse width 
bandwidth = 1e6;    % Bandwidth of the signal 
fs = 10*bandwidth;  % Sampling frequency (samples per second)
timeBandwidthProduct = tau * bandwidth;
samplePerChip = round(tau * fs);
ddsRate = samplePerChip/timeBandwidthProduct;

% Parameters
PRI = 1e-3;         % Pulse Repetition Interval 
PRF = 1/PRI;        % Pulse Repetition Frequency 
nPulse = 1;         % Number of pulses

t_start = 100e-6;   % Start time 
t = linspace(0, t_start+nPulse*PRI, (t_start+nPulse*PRI)*fs); % Time vector 

% Time vector for pulse duration
tPulse = 0:1/fs:tau-1/fs;

% Generate random binary code signal
random_code = 2*randi([0 1], 1, timeBandwidthProduct) - 1; % Random binary (+1/-1)
random_code_resampled = repelem(random_code, ddsRate);               % Repeat each entry ddsRate times

pulseTx = zeros(size(t));   % Transmit pulse
% Insert random binary code in the transmit signal
for i = 0:nPulse-1
    tInterval = t >= t_start + i*PRI & t <= t_start + i*PRI + tau; % Time interval for each pulse
    pulseTx(tInterval) = random_code_resampled;  % Set transmitted pulse to the random binary code
end

figure('Position', [100, 100, 900, 600]);
plot(t*1e3, real(pulseTx), 'r', 'LineWidth', 2, 'DisplayName', 'Transmit Pulse (Random Binary)'); hold on;

xlabel('Time (ms)', 'FontSize', 14);
ylabel('Amplitude', 'FontSize', 14);
legend();
grid on;
ylim([-1.5 1.5]);
xlim([0.05,0.4])

figure('Position', [100, 100, 900, 600]);
r = abs(xcorr(random_code_resampled(1:ddsRate:end)))/timeBandwidthProduct;
lags = linspace(-tau/2,tau/2,2*timeBandwidthProduct-1);
plot(lags/1e-6,20*log10(r), 'LineWidth', 2, 'DisplayName', 'Autocorrelation (Random Binary)')
xlabel('Time (us)', 'FontSize', 14);
ylabel('Amplitude (dB)', 'FontSize', 14);
legend();
axis('tight')
ylim([-60,0])
grid on;

% Plot the spectrogram of the random binary code
figure('Position', [100, 100, 900, 600]);
nFFT = length(random_code_resampled)/5;
spectrogram(random_code_resampled, nFFT, round(nFFT-nFFT/20), nFFT, fs, 'yaxis');

xlabel('Time (µs)', 'FontSize', 14);
ylabel('Frequency (MHz)', 'FontSize', 14);
colormap('jet');
colorbar;

% Adjust axes for better visualization
ylim([0 bandwidth/1e6]);   % Show frequency from 0 to the bandwidth in MHz

figure('Position', [100, 100, 900, 600]);
[afmag, delay, doppler] = ambgfun(random_code_resampled(1:ddsRate:end), 1, 1);

% Use 'surf' for better visibility
surf(delay, doppler * bandwidth / 1e6, afmag, 'EdgeColor', 'none');

% Improve view and appearance
view(2); % Top-down view for a clear 2D plot
colormap jet; % High-contrast colormap
colorbar; % Add a colorbar to indicate magnitude levels

% Use 'shading interp' for smooth color transitions
shading interp;

% Add axis labels and title
xlabel("Delay (\mu seconds)", 'FontSize', 12, 'FontWeight', 'bold');
ylabel("Doppler Shift (MHz)", 'FontSize', 12, 'FontWeight', 'bold');

% Set font size for axes
set(gca, 'FontSize', 12);