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
fc = 79e9;          % Carrier frequency
lambda = c / fc;    % Wavelength

% Parameters
tSim = 1e-3;              % Total simulation time (0.3 us)
fs = 1e6;                  % Sampling frequency (samples per second)
nFFT = 1024;                % Number of FFT points

% Doppler shifts based on target velocities
v1 = 20;         % Velocity of target 1 in m/s
v2 = -35;         % Velocity of target 2 in m/s
fd1 = 2 * v1 / lambda;  % Doppler shift for target 1
fd2 = 2 * v2 / lambda;  % Doppler shift for target 2

% Simulated delays and attenuations for the received signals
delay1 = 400e-6;      % Round-trip delay for target 1
delay2 = 450e-6;      % Round-trip delay for target 2
att1 = 0.5;           % Attenuation factor for target 1
att2 = 0.2;           % Attenuation factor for target 2
snr = 10;             % Signal-to-noise ratio for AWGN
max_speed = 100;
max_fd = 2 * max_speed/lambda;

t = linspace(0, tSim, round(tSim * fs));

% Received signals (with Doppler shifts, delays, attenuations, and noise)
signalRx1 = att1 * exp(1i*2*pi*(fd1)*(t - delay1)); % Target 1 with Doppler shift fd1
signalRx2 = att2 * exp(1i*2*pi*(fd2)*(t - delay2)); % Target 2 with Doppler shift fd2

% Combine the received signals from both targets
signalRx = signalRx1 + signalRx2;
signalRx = awgn(signalRx, snr, "measured");

% Initialize figure
figure('Position', [100, 100, 900, 600]);
plot(t*1e6, real(signalRx1), 'r', 'LineWidth', 2, 'DisplayName', 'Received Signal (Targets 1)'); 
hold all;
plot(t*1e6, real(signalRx2), 'm', 'LineWidth', 2, 'DisplayName', 'Received Signal (Targets 2)'); 
plot(t*1e6, real(signalRx), 'b', 'LineWidth', 2, 'DisplayName', 'Received Signal (Targets 1 and 2)');

% Label axes
xlabel('Time (us)', 'FontSize', 14);
ylabel('Amplitude', 'FontSize', 14);

% Add legend and grid
legend();
grid on;

% Tighten axis limits
axis('tight');
ylim([-1 1]);

% Perform Doppler FFT to estimate frequencies
dopplerSpectrum = fftshift(fft(hann(length(signalRx)).' .* signalRx, nFFT));  % Doppler FFT
frequencies = linspace(-fs/2, fs/2, nFFT);        % Frequency axis

% Plot the Doppler spectrum
figure('Position', [100, 100, 900, 600]);
plot(frequencies*lambda/2, 20*log10(abs(dopplerSpectrum)/nFFT), 'LineWidth', 2);
xlabel('Velocity (m/s)', 'FontSize', 14);
ylabel('Amplitude (dB)', 'FontSize', 14);
grid on;
xlim([-max_speed,max_speed])

