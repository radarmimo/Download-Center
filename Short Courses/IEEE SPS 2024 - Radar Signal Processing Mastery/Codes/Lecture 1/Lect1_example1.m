% SPS Short Course: Radar Signal Processing Mastery
% Theory and Hands-On Applications with mmWave MIMO Radar Sensors
% Date: 7-11 October 2024
% Time: 9:00AM-11:00AM ET (New York Time)
% Presenter: Mohammad Alaee-Kerahroodi

close all
clear
clc

% Parameters
PRF = 1000;               % Pulse Repetition Frequency 
PRI = 1 / PRF;            % Pulse Repetition Interval 
nPulse = 5;               % Number of pulses


tau = 200e-6;             % Pulse width 
fc = 20e3;                % Pulse carrier frequency

samplePerPulse = 1000;     % Number of samples per pulse 
fs = 20*fc; % Sampling frequency (samples per second)

t_start = 0;              % Start time (0 ms)
t = linspace(t_start, 1.5e-3, 1.5e-3*fs); % Time vector 

% Simulated delay and attenuation for the received signal
delay_time = 400e-6;      % Round-trip delay 
attenuation = 0.1;        % Attenuation factor

% Transmit Pulse (Sinusoidal pulse for each PRI)
pulse = zeros(size(t));
timing = zeros(size(t));

% Received Signal (Delayed and attenuated version of the transmitted pulse)
received_pulse = zeros(size(t));

for i = 0:nPulse-1
    tInterval = t >= t_start + i*PRI & t <= t_start + i*PRI + tau; % Time interval for each pulse
    pulse(tInterval) = sin(2*pi*fc*(t(tInterval)-(t_start + i*PRI))); % Sinusoidal pulse
    timing(tInterval) = 1;

    tInterval_received = t >= t_start + i*PRI + delay_time & t <= t_start + i*PRI + delay_time + tau; % Time interval for received pulse
    received_pulse(tInterval_received) = attenuation * sin(2*pi*fc*(t(tInterval_received)-(t_start + i*PRI + delay_time))); % Delayed and attenuated pulse
end

% Plot timing
figure('Position', [100, 100, 900, 600]);
plot(t*1e3, timing, 'r', 'LineWidth', 4); % Plotting time in milliseconds
xlabel('Time (ms)', 'FontSize', 12);
ylabel('Amplitude', 'FontSize', 12);
grid on;
set(gca, 'FontSize', 12);

% Plot the transmit pulse
figure('Position', [100, 100, 900, 600]);
plot(t*1e3, pulse, 'r', 'LineWidth', 2); % Plotting time in milliseconds
xlabel('Time (ms)', 'FontSize', 12);
ylabel('Amplitude', 'FontSize', 12);
grid on;
set(gca, 'FontSize', 12);

% Plot the transmit and received pulses together for comparison
figure('Position', [100, 100, 900, 600]);
plot(t*1e3, pulse, 'r', 'LineWidth', 2); hold on;
plot(t*1e3, received_pulse, 'b', 'LineWidth', 2); % Plotting time in milliseconds
xlabel('Time (ms)', 'FontSize', 12);
ylabel('Amplitude', 'FontSize', 12);
legend('Transmit Pulse', 'Received Pulse', 'FontSize', 12);
grid on;
set(gca, 'FontSize', 12);
