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
fc = 79e9;          % Carrier frequency (79 GHz)
% Parameters
tSim = 0.05e-6;      % Total simulation time (0.3 us)
fs = 10*fc;         % Sampling frequency (samples per second)
PRI = 0.1e-9;       % Pulse Repetition Interval (0.1 ns)

% Simulated delay and attenuation for the received signal
delay_time = 400e-6;      % Round-trip delay (400 us)
attenuation = 0.1;        % Attenuation factor
snr = 10;                 % Signal-to-noise ratio for AWGN

% Initialize figure
figure('Position', [100, 100, 900, 600]);

% Filename for the GIF
gif_filename = 'cw_animation.gif';

% Loop through each time step to animate the signal
for i = 1:round(tSim/PRI)
    % Time vector for the current window
    t = linspace((i-1)*PRI, i*PRI, round(PRI * fs)); 
    
    % Transmitted signal (sine wave)
    signalTx = sin(2*pi*fc*t); 

    % Received signal (delayed, attenuated, and with noise)
    signalRx = attenuation * sin(2*pi*fc*(t - delay_time)); 
    signalRx = awgn(signalRx, snr, "measured");

    % Clear previous plot and plot the current signals
    cla
    plot(t*1e6, real(signalTx), 'r', 'LineWidth', 2, 'DisplayName', 'Transmit Signal'); hold on;
    plot(t*1e6, real(signalRx), 'b', 'LineWidth', 2, 'DisplayName', 'Received Signal');
    
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
