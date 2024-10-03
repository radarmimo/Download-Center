% SPS Short Course: Radar Signal Processing Mastery
% Theory and Hands-On Applications with mmWave MIMO Radar Sensors
% Date: 7-11 October 2024
% Time: 9:00AM-11:00AM ET (New York Time)
% Presenter: Mohammad Alaee-Kerahroodi

close all
clear
clc

% MATLAB Script to visualize one wavelength of a sine wave

% Parameters
lambda = 1; % Wavelength (arbitrary units)
x = linspace(0, 4*lambda, 1000); % x values from 0 to 4 wavelengths
frequency = 1; % Frequency of the sine wave
omega = 2 * pi * frequency; % Angular frequency

% Sine wave calculation
y = sin(omega * x); % Calculate sine wave values

% Plotting
figure('Position', [100, 100, 900, 600]);
plot(x, y, 'b', 'LineWidth', 2); % Plot the sine wave
hold on;

% Highlight one wavelength
fill([0 lambda lambda 0], [-1 -1 1 1], 'r', 'FaceAlpha', 0.3, 'EdgeColor', 'none'); % Highlight area for one wavelength
text(lambda/2, 1.2, '\lambda', 'FontSize', 14, 'HorizontalAlignment', 'center'); % Label for wavelength

% Indicate the cycle completion
text(0.7, -1.1, 'One full cycle (2\pi radians)', 'FontSize', 14, 'HorizontalAlignment', 'center');

% Final plot adjustments
xlabel('Distance (arbitrary units)', 'FontSize', 14);
ylabel('Amplitude', 'FontSize', 14);
% title('Sine Wave and One Wavelength Visualization', 'FontSize', 16);
grid on;
set(gca, 'FontSize', 12);
box on;

% Set x-axis limits to show 4 wavelengths
xlim([0 4*lambda]);
ylim([-1.5 1.5]);
hold off;
