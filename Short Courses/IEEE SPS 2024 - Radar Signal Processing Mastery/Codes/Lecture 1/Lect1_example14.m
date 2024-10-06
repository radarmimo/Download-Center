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

% Parameters for FMCW
chirpTime = 40e-6;       % Sweep duration (chirp time) for FMCW
bandwidth = 4e9;    % Bandwidth of the FMCW signal (sweep bandwidth)
simSamplingRate = 10*bandwidth;  % Sampling frequency (samples per second)

f_start = 0;     % Starting frequency of the FMCW chirp (e.g., 78 GHz)
f_end = f_start + bandwidth; % Ending frequency of the FMCW chirp
f_c = 79e9;         % Carrier frequency for radar 
lambda = c / f_c;   % Wavelength in meters
snr = 20;
% FMCW chirp parameters
nSamples = round(chirpTime * simSamplingRate);  % Number of samples per chirp
nChirps = 2;                % Number of chirps
PRI = chirpTime + 10e-6;          % Time between chirps (PRI in FMCW is related to sweep time)
PRF = 1 / PRI;               % Pulse repetition frequency
t_total = PRI * nChirps;     % Total time for all chirps
t_start = 10e-6;   % Start time 
% Time vectors
t_chirp = linspace(0, chirpTime, nSamples);    % Time vector for one chirp
t_gap = linspace(0, PRI - chirpTime, round((PRI - chirpTime) * simSamplingRate));  % Time vector for gap between chirps

% Generate FMCW signal (linear frequency modulation)
fmcw_chirp = exp(-1i * 2 * pi * (f_start * t_chirp + (bandwidth / (2*chirpTime)) * t_chirp.^2));

t = linspace(0, t_start+nChirps*PRI, (t_start+nChirps*PRI)*simSamplingRate); % Time vector 

% Simulate Two Targets with Different Doppler Shifts
v1 = 0;   % Velocity of target 
v2 = -8;   % Velocity of target 
fd1 = 2 * v1 / lambda;  % Doppler frequency shift for target 1
fd2 = 2 * v2 / lambda;  % Doppler frequency shift for target 2
dopplerTarget1 = exp(1j * 2 * pi * fd1 * t);
dopplerTarget2 = exp(1j * 2 * pi * fd2 * t);

delayTarget1 = 100e-9;   % Round-trip delay of target
delayTarget2 = 35e-9;   % Round-trip delay of target
attTarget1 = 0.1;        % Attenuation factor
attTarget2 = 0.2;        % Attenuation factor
slope = bandwidth/chirpTime;
f_IF1 = slope * delayTarget1;
f_IF2 = slope * delayTarget2;

maxIF = max(f_IF1, f_IF2);
adcSamplingRate = max(40e6,2 * maxIF);
ddsRate = round(simSamplingRate / adcSamplingRate);

signalTx = zeros(size(t));   % Transmit pulse

% Simulate received signals from the two targets
pulseRxTarget1 = zeros(size(t));   % Received pulse for target 1
pulseRxTarget2 = zeros(size(t));   % Received pulse for target 2

for i = 0:nChirps-1
    tInterval = t >= t_start + i*PRI & t <= t_start + i*PRI + chirpTime;
    signalTx(tInterval) = fmcw_chirp;  % Set transmitted pulse to the intrspulse modulation

    tIntervalTarget1 = t >= t_start + i*PRI + delayTarget1 & t <= t_start + i*PRI + delayTarget1 + chirpTime;
    tIntervalTarget2 = t >= t_start + i*PRI + delayTarget2 & t <= t_start + i*PRI + delayTarget2 + chirpTime;

    pulseRxTarget1(tIntervalTarget1) = attTarget1 * fmcw_chirp;  % Set received pulse for target 1
    pulseRxTarget2(tIntervalTarget2) = attTarget2 * fmcw_chirp;  % Set received pulse for target 2

end


received_pulse = pulseRxTarget1 .* exp(1j * 2 * pi * fd1 * t)  + pulseRxTarget2 .* exp(1j * 2 * pi * fd2 * t);  
% Total received signal
signalRx = awgn(received_pulse, snr, "measured");


% Plot the transmitted FMCW signal (real part)
figure('Position', [100, 100, 900, 600]);
plot(t * 1e6, real(signalTx), 'r', 'LineWidth', 2, 'DisplayName', 'Transmit FMCW Signal');
hold on
plot(t * 1e6, real(signalRx), 'b', 'LineWidth', 2, 'DisplayName', 'Received FMCW Signal');
xlabel('Time (\mus)', 'FontSize', 14);
ylabel('Amplitude', 'FontSize', 14);
legend()
% title('Transmit FMCW Signal with Zero Padding');
grid on;


%% De-chirp (mix received signal with transmitted signal)
IF_signal = signalRx .* conj(signalTx);  % Perform de-chirping
IF_signal = IF_signal(1:ddsRate:end);

% Plot the de-chirped IF signal (real part)
figure('Position', [100, 100, 900, 600]);
plot(t(1:ddsRate:end) * 1e6, real(IF_signal), 'b', 'LineWidth', 2, 'DisplayName', 'IF Signal (De-chirped)');
xlabel('Time (\mus)', 'FontSize', 14);
ylabel('Amplitude', 'FontSize', 14);
% title('IF Signal after De-chirping');
grid on;
% axis('tight')

%% Compute and plot the frequency spectrum of the IF signal
figure('Position', [100, 100, 900, 600]);
nFFT = 1024;  % Number of points in FFT
freq_axis = linspace(-adcSamplingRate / 2, adcSamplingRate / 2, nFFT) /1e6;  % Frequency axis in MHz
IF_spectrum = fftshift(abs(fft(IF_signal, nFFT)));  % FFT of IF signal

% Plot the IF signal spectrum
plot(freq_axis, 20 * log10(IF_spectrum / max(IF_spectrum)), 'LineWidth', 2);
xlabel('Frequency (MHz)', 'FontSize', 14);
ylabel('Magnitude (dB)', 'FontSize', 14);
grid on;
xlim([0, adcSamplingRate/2/1e6]);

% Annotate the IF frequencies of the two targets
hold on;

% IF frequencies in MHz
f_IF1_MHz = f_IF1 / 1e6;
f_IF2_MHz = f_IF2 / 1e6;

% Add vertical lines and text labels at f_IF1 and f_IF2
line([f_IF1_MHz, f_IF1_MHz], ylim, 'Color', 'r', 'LineStyle', '--', 'LineWidth', 2, 'DisplayName', 'Target 1 IF');
text(f_IF1_MHz, -10, sprintf('f_{IF1} = %.2f MHz', f_IF1_MHz), 'FontSize', 12, 'Color', 'r', 'VerticalAlignment', 'bottom');

line([f_IF2_MHz, f_IF2_MHz], ylim, 'Color', 'g', 'LineStyle', '--', 'LineWidth', 2, 'DisplayName', 'Target 2 IF');
text(f_IF2_MHz, -10, sprintf('f_{IF2} = %.2f MHz', f_IF2_MHz), 'FontSize', 12, 'Color', 'g', 'VerticalAlignment', 'bottom');

legend({'IF Signal Spectrum', 'Target 1 IF Frequency', 'Target 2 IF Frequency'});
