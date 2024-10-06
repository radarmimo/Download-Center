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
tSim = 0.05e-6;              % Total simulation time (0.3 us)
fs = 10*fc;                  % Sampling frequency (samples per second)
displayInterval = 0.1e-9;    % Display Interval 

% Doppler shifts based on target velocities
v1 = 20;         % Velocity of target 1 in m/s
v2 = 40;         % Velocity of target 2 in m/s
fd1 = 2 * v1 / lambda;  % Doppler shift for target 1
fd2 = 2 * v2 / lambda;  % Doppler shift for target 2

% Simulated delays and attenuations for the received signals
delay1 = 400e-6;      % Round-trip delay for target 1
delay2 = 450e-6;      % Round-trip delay for target 2
att1 = 0.1;           % Attenuation factor for target 1
att2 = 0.2;           % Attenuation factor for target 2
snr = 10;             % Signal-to-noise ratio for AWGN

% Initialize figure
figure('Position', [100, 100, 900, 600]);

% Filename for the GIF
gif_filename = 'cw_animation_two_targets.gif';

% Loop through each time step to animate the signal
for i = 1:round(tSim/displayInterval)
    % Time vector for the current window
    t = linspace((i-1)*displayInterval, i*displayInterval, round(displayInterval * fs)); 
    
    % Transmitted signal (sine wave)
    signalTx = sin(2*pi*fc*t); 

    % Received signals (with Doppler shifts, delays, attenuations, and noise)
    signalRx1 = att1 * sin(2*pi*(fc + fd1)*(t - delay1)); % Target 1 with Doppler shift fd1
    signalRx2 = att2 * sin(2*pi*(fc + fd2)*(t - delay2)); % Target 2 with Doppler shift fd2
    
    % Combine the received signals from both targets
    signalRx = signalRx1 + signalRx2;
    signalRx = awgn(signalRx, snr, "measured");

    % Clear previous plot and plot the current signals
    cla
    plot(t*1e6, real(signalTx), 'r', 'LineWidth', 2, 'DisplayName', 'Transmit Signal'); hold on;
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

    % Capture the current frame
    frame = getframe(gcf);
    img = frame2im(frame);
    [imind, cm] = rgb2ind(img, 256);

    % Write to the GIF file
    if i == 1
        imwrite(imind, cm, gif_filename, 'gif', 'Loopcount', inf, 'DelayTime', 0.1);
    else
        imwrite(imind, cm, gif_filename, 'gif', 'WriteMode', 'append', 'DelayTime', 0.1);
    end

    % Update the plot dynamically
    drawnow limitrate;
end
