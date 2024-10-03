% SPS Short Course: Radar Signal Processing Mastery
% Theory and Hands-On Applications with mmWave MIMO Radar Sensors
% Date: 7-11 October 2024
% Time: 9:00AM-11:00AM ET (New York Time)
% Presenter: Mohammad Alaee-Kerahroodi

close all
clear
clc

% Parameters

PRI = 1e-3;            % Pulse Repetition Interval 
PRF = 1/PRI;               % Pulse Repetition Frequency 
nPulse = 10;               % Number of pulses

tau = 200e-6;             % Pulse width 
bandwidth = 1/tau;

fs = 100*bandwidth; % Sampling frequency (samples per second)

t_start = 100e-6;              % Start time (0 ms)
t = linspace(0, t_start+nPulse*PRI, (t_start+nPulse*PRI)*fs); % Time vector 

% Simulated delay and attenuation for the received signal
delay_time = 400e-6;      % Round-trip delay 
attenuation = 0.1;        % Attenuation factor

pulseTx = zeros(size(t));
pulseRx = zeros(size(t));
% Received Signal (Delayed and attenuated version of the transmitted pulse)
received_pulse = zeros(size(t));

for i = 0:nPulse-1
    tInterval = t >= t_start + i*PRI & t <= t_start + i*PRI + tau; % Time interval for each pulse
    pulseTx(tInterval) = 1;

    tInterval_received = t >= t_start + i*PRI + delay_time & t <= t_start + i*PRI + delay_time + tau; % Time interval for received pulse
    pulseRx(tInterval_received) = attenuation;
end

% Plot the transmit and received pulses together for comparison
figure('Position', [100, 100, 900, 600]);
plot(t*1e3, pulseTx, 'r', 'LineWidth', 2); hold on;
plot(t*1e3, pulseRx, 'b', 'LineWidth', 2); % Plotting time in milliseconds
xlabel('Time (ms)', 'FontSize', 12);
ylabel('Amplitude', 'FontSize', 12);
legend('Transmit Pulse', 'Received Pulse', 'FontSize', 12);
grid on;
set(gca, 'FontSize', 12);
box on
axis('tight')
ylim([-1 1])

% Spectrum of single pulse
% Parameters
nFFT = 1024;  % Number of points for FFT
f = linspace(-fs/2, fs/2, nFFT); % Frequency axis
% Find the 3 dB bandwidth
threshold_dB = -3;

% Compute FFT of the transmit pulse
spectrumTx = fftshift(abs(fft(pulseTx(1:round(PRI*fs)), nFFT)));
spectrumTx = spectrumTx / max(spectrumTx);  % Normalize the spectrum

% Convert to dB scale
spectrumTx_dB = 20 * log10(spectrumTx);

% Plot the magnitude spectrum in dB
figure('Position', [100, 100, 900, 600]);
plot(f/1e3, spectrumTx_dB, 'b', 'LineWidth', 2);  % Frequency in kHz
xlabel('Frequency (kHz)', 'FontSize', 14, 'FontWeight', 'bold');
ylabel('Magnitude (dB)', 'FontSize', 14, 'FontWeight', 'bold');
% title('Spectrum of Transmitted Pulse with 3 dB Bandwidth', 'FontSize', 16, 'FontWeight', 'bold');
grid on;
set(gca, 'FontSize', 12, 'GridAlpha', 0.3);
box on;
xlim([-5*bandwidth/2/1e3, 5*bandwidth/2/1e3])
hold on;
% Add dashed line for -3 dB threshold
plot([-5*bandwidth/2, 5*bandwidth/2]/1e3, [threshold_dB threshold_dB], 'k--', 'LineWidth', 1.5);
% Final adjustments for visual clarity
set(gca, 'FontSize', 14, 'FontWeight', 'bold', 'LineWidth', 1.2);
ylim([-35 5]) 

% Spectrum of pulse train with PRF spikes highlighted

% Compute FFT of the transmit pulse train
window = hamming(length(pulseTx))';  % Apply Hamming window to reduce spectral leakage
spectrumTxPulseTrain = fftshift(abs(fft(pulseTx .* window, nFFT)));
spectrumTxPulseTrain = spectrumTxPulseTrain / max(spectrumTxPulseTrain);  % Normalize the spectrum

% Convert to dB scale
spectrumTxPulseTrain_dB = 20 * log10(spectrumTxPulseTrain);

min_dB = min(spectrumTxPulseTrain_dB);  % Set the floor value for the bars

% Plot the magnitude spectrum in dB
figure('Position', [100, 100, 900, 600]);
plot(f/1e3, spectrumTx_dB, 'b--', 'LineWidth', 2); 
hold on
% bar(f/1e3, spectrumTxPulseTrain_dB, 'b', 'BaseValue', min_dB); 
bar(f/1e3, spectrumTxPulseTrain_dB, 'b', 'LineWidth', 2, 'BaseValue', min_dB);  % Frequency in kHz
xlabel('Frequency (kHz)', 'FontSize', 14, 'FontWeight', 'bold');
ylabel('Magnitude (dB)', 'FontSize', 14, 'FontWeight', 'bold');
% title('Spectrum of Pulse Train Showing PRF Spacing', 'FontSize', 16, 'FontWeight', 'bold');
grid on;
set(gca, 'FontSize', 12, 'GridAlpha', 0.3);
box on;
xlim([-5*bandwidth/2/1e3, 5*bandwidth/2/1e3])

% Highlight spikes corresponding to PRF multiples
% hold on;
PRF_spacing = PRF / (fs / nFFT);  % Convert PRF to bin spacing
spike_indices = 1:round(PRF_spacing):nFFT;  % Indices where frequency is a multiple of PRF
spike_frequencies = f(spike_indices);       % Frequencies corresponding to PRF multiples

% Highlight the spikes
for k = 1:length(spike_frequencies)
    plot(spike_frequencies(k)/1e3, spectrumTxPulseTrain_dB(spike_indices(k)), 'ro', 'MarkerSize', 8, 'LineWidth', 2);
end

% Annotate the PRF and the distance between spikes
PRF_kHz = PRF / 1e3;
% for k = 1:5:length(spike_frequencies)
%     text(spike_frequencies(k)/1e3, spectrumTxPulseTrain_dB(spike_indices(k)) + 5, ...
%         sprintf('%.1f kHz', spike_frequencies(k)/1e3), ...
%         'FontSize', 12, 'FontWeight', 'bold', 'HorizontalAlignment', 'center');
% end
% text(mean(spike_frequencies(1:2))/1e3, -40, sprintf('PRF = %.1f kHz', PRF_kHz), ...
%     'FontSize', 12, 'FontWeight', 'bold', 'HorizontalAlignment', 'center', 'BackgroundColor', 'w');

% Add dashed line for -3 dB threshold
plot([-5*bandwidth/2, 5*bandwidth/2]/1e3, [threshold_dB threshold_dB], 'k--', 'LineWidth', 1.5);

% Final adjustments for visual clarity
set(gca, 'FontSize', 14, 'FontWeight', 'bold', 'LineWidth', 1.2);
ylim([-35 5])  % Adjust y-axis for better visualization of spikes
