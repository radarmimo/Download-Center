% SPS Short Course: Radar Signal Processing Mastery
% Theory and Hands-On Applications with mmWave MIMO Radar Sensors
% Date: 7-11 October 2024
% Time: 9:00AM-11:00AM ET (New York Time)
% Presenter: Mohammad Alaee-Kerahroodi

% Radiation Pattern of a Single Antenna Element
close all;
clear;
clc;

% Define the parameters for the antenna
fc = 10e9;           % Frequency (Hz)
c = 3e8;             % Speed of light (m/s)
lambda = c / fc;     % Wavelength (m)

% Define angles for plotting
theta = linspace(0, pi, 100);  % Elevation angles from 0 to 180 degrees
phi = linspace(0, 2*pi, 100);   % Azimuth angles from 0 to 360 degrees
[THETA, PHI] = meshgrid(theta, phi);

% Define the radiation pattern (for a dipole antenna)
% Example radiation pattern for a dipole antenna (normalized)
R = abs(sin(THETA));  % Simple dipole radiation pattern

% Convert spherical coordinates to Cartesian coordinates for 3D plotting
X = R .* sin(THETA) .* cos(PHI);
Y = R .* sin(THETA) .* sin(PHI);
Z = R .* cos(THETA);

% Create the 3D plot
figure('Position', [100, 100, 800, 600]);
surf(X, Y, Z, 'EdgeColor', 'none', 'FaceColor', 'interp');
view(30, 30);  % Set the view angle
axis equal;
grid on;
xlabel('X-axis');
ylabel('Y-axis');
zlabel('Z-axis');
title('Radiation Pattern of a Single Antenna Element');
colorbar;
caxis([0, max(R(:))]);
set(gca, 'Color', 'k');  % Set background to black
set(gcf, 'Color', 'k');   % Set figure background to black
colormap(jet);            % Set color map

% Optionally, set axis limits for better visualization
xlim([-1 1]);
ylim([-1 1]);
zlim([-1 1]);
