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
vr = 100;           % Radial speed of the target in m/s

% Doppler frequency calculation
fd = 2 * vr / lambda;  % Doppler frequency in Hz

% Parameters
PRI = 1e-3;            % Pulse Repetition Interval 
PRF = 1/PRI;           % Pulse Repetition Frequency 
nPulse = 50;           % Number of pulses
nFFT = 4096;
tau = 200e-6;          % Pulse width 
bandwidth = 1/tau;    % Bandwidth of the pulse

fs = 10*bandwidth;    % Sampling frequency (samples per second)

snr = 0;           % dB

t_start = 100e-6;      % Start time (0 ms)
t = linspace(0, t_start+nPulse*PRI, (t_start+nPulse*PRI)*fs); % Time vector 

% Simulated delay and attenuation for the received signal
delay_time = 400e-6;   % Round-trip delay of target
attenuation = 0.1;     % Attenuation factor

numRangeBins = round(PRI * fs);
indexStart = round(t_start/PRI * numRangeBins);
indexTarget = round((delay_time+tau/2)/PRI * numRangeBins);

pulseTx = zeros(size(t));   % Transmit pulse
pulseRx = zeros(size(t));   % Received pulse

% doppler_signal = zeros(size(t));    % Doppler signal
doppler_signal = cos(2 * pi * fd * t);

for i = 0:nPulse-1
    tInterval = t >= t_start + i*PRI & t <= t_start + i*PRI + tau; % Time interval for each pulse
    pulseTx(tInterval) = 1;  % Set transmitted pulse to 1

    tInterval_received = t >= t_start + i*PRI + delay_time & t <= t_start + i*PRI + delay_time + tau; % Time interval for received pulse
    pulseRx(tInterval_received) = attenuation;  % Set received pulse
end

received_pulse = pulseRx .* doppler_signal;  % Received pulse (Delayed and attenuated)
received_signal = awgn(received_pulse,snr,"measured");
data_cube_noiseless = reshape(received_pulse(indexStart+1:end),[numRangeBins,nPulse]);
data_cube = reshape(received_signal(indexStart+1:end),[numRangeBins,nPulse]);

% Plot the transmit, received, and Doppler signals
figure('Position', [100, 100, 900, 600]);
plot(t*1e3, pulseTx, 'r', 'LineWidth', 2); hold on;  % Transmit pulse
plot(t*1e3, pulseRx, 'b', 'LineWidth', 2);          % Received pulse
plot(t*1e3, attenuation * doppler_signal, 'g', 'LineWidth', 2); 

xlabel('Time (ms)', 'FontSize', 12);
ylabel('Amplitude', 'FontSize', 12);
legend('Transmit Pulse', 'Received Pulse', 'Doppler Signal', 'FontSize', 12);
grid on;
set(gca, 'FontSize', 12);
box on;
axis('tight');
ylim([-1 1]);


figure('Position', [100, 100, 900, 600]);
plot(t*1e3, pulseTx, 'r', 'LineWidth', 2,'DisplayName','Transmit Pulse'); hold on;  % Transmit pulse
plot(t*1e3, received_pulse, 'g', 'LineWidth', 2,'DisplayName','Received Pulse');          % Received pulse

legend()
xlabel('Time (ms)', 'FontSize', 12);
ylabel('Amplitude', 'FontSize', 12);
% legend('Transmit Pulse', 'Received Pulse', 'Doppler Signal', 'FontSize', 12);
grid on;
set(gca, 'FontSize', 12);
box on;
axis('tight');
ylim([-1 1]);



P1 = 20*log10(fftshift(abs(fft(data_cube_noiseless(indexTarget,:),nFFT))));
f = linspace(-PRF/2,PRF/2,nFFT);
% Plot the FFT magnitude spectrum
figure('Position', [100, 100, 900, 600]);
plot(f, P1, 'k', 'LineWidth', 2);  % Frequency in MHz
xlabel('Doppler Frequency (Hz)', 'FontSize', 12);
ylabel('|P1(f)|', 'FontSize', 12);
% title('Magnitude Spectrum of Doppler Signal', 'FontSize', 14);
grid on;
set(gca, 'FontSize', 12);
box on;
hold on
xlim([0,PRF/2])
% Find the peak frequency and estimate vr
[peakMagnitude, peakIndex] = max(P1(round(nFFT/2)+1:end));    % Find the peak magnitude and its index
estimated_fd = f(peakIndex+round(nFFT/2)+1);               % Estimate Doppler frequency in Hz
estimated_vr = estimated_fd * lambda / 2; % Estimate radial speed in m/s
plot(estimated_fd,peakMagnitude,'ro',MarkerSize=8,LineWidth=2)
% Display estimated values on the plot
text(estimated_fd+10, 0, sprintf('  Peak: %.2f Hz\n  v_r: %.2f m/s', estimated_fd, estimated_vr), ...
     'VerticalAlignment', 'bottom', 'HorizontalAlignment', 'left', 'FontSize', 12, 'Color', 'blue');


% Plot the data at the target range bin (indexTarget)
figure('Position', [100, 100, 900, 600]);  % Set the figure size
plot(data_cube_noiseless(indexTarget,:), 'LineWidth', 2, 'Marker', 'o', 'MarkerFaceColor', 'b', 'MarkerEdgeColor', 'r'); 

% Enhance the plot with labels and title
xlabel('Pulse Index', 'FontSize', 12);  % Label for x-axis
ylabel('Amplitude', 'FontSize', 12);    % Label for y-axis
% title('Signal at Target Range Bin', 'FontSize', 14);  % Plot title

% Add grid lines for better visibility
grid on;

% Add a legend to describe the plotted data
legend(sprintf('Target Range Bin (Index: %d)', indexTarget), 'FontSize', 12);

% Adjust plot limits for a tighter fit
axis tight;
set(gca, 'FontSize', 12);  % Set the font size for axes
box on;  % Add a box around the plot for a cleaner look


figure('Position', [100, 100, 900, 600]);
plot(t*1e3, pulseTx, 'r', 'LineWidth', 2,'DisplayName','Transmit Pulse'); hold on;  % Transmit pulse
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

% Plot the data at the target range bin (indexTarget)
figure('Position', [100, 100, 900, 600]);  % Set the figure size
plot(data_cube(indexTarget,:), 'LineWidth', 2, 'Marker', 'o', 'MarkerFaceColor', 'b', 'MarkerEdgeColor', 'r'); 

% Enhance the plot with labels and title
xlabel('Pulse Index', 'FontSize', 12);  % Label for x-axis
ylabel('Amplitude', 'FontSize', 12);    % Label for y-axis
% title('Signal at Target Range Bin', 'FontSize', 14);  % Plot title

% Add grid lines for better visibility
grid on;

% Add a legend to describe the plotted data
legend(sprintf('Target Range Bin (Index: %d)', indexTarget), 'FontSize', 12);

% Adjust plot limits for a tighter fit
axis tight;
set(gca, 'FontSize', 12);  % Set the font size for axes
box on;  % Add a box around the plot for a cleaner look


P2 = 20*log10(fftshift(abs(fft(data_cube(indexTarget,:),nFFT))));
% Plot the FFT magnitude spectrum
figure('Position', [100, 100, 900, 600]);
plot(f, P2, 'k', 'LineWidth', 2);  % Frequency in MHz
xlabel('Doppler Frequency (Hz)', 'FontSize', 12);
ylabel('|P2(f)|', 'FontSize', 12);
% title('Magnitude Spectrum of Doppler Signal', 'FontSize', 14);
grid on;
set(gca, 'FontSize', 12);
box on;
hold on
xlim([0,PRF/2])
% Find the peak frequency and estimate vr
[peakMagnitude, peakIndex] = max(P2(round(nFFT/2)+1:end));    % Find the peak magnitude and its index
estimated_fd = f(peakIndex+round(nFFT/2)+1);               % Estimate Doppler frequency in Hz
estimated_vr = estimated_fd * lambda / 2; % Estimate radial speed in m/s
plot(estimated_fd,peakMagnitude,'ro',MarkerSize=8,LineWidth=2)
% Display estimated values on the plot
text(estimated_fd+10, 0, sprintf('  Peak: %.2f Hz\n  v_r: %.2f m/s', estimated_fd, estimated_vr), ...
     'VerticalAlignment', 'bottom', 'HorizontalAlignment', 'left', 'FontSize', 12, 'Color', 'blue');


