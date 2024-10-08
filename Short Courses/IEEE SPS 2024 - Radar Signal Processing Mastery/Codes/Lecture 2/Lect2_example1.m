% SPS Short Course: Radar Signal Processing Mastery
% Theory and Hands-On Applications with mmWave MIMO Radar Sensors
% Date: 7-11 October 2024
% Time: 9:00AM-11:00AM ET (New York Time)
% Presenter: Mohammad Alaee-Kerahroodi

% 2D Beampattern for a dish antenna 

close all;
clear;
clc;

% Constants
c = 3e8;           % Speed of light (m/s)
fc = 1e9;          % Operating frequency (Hz)
D = 3;             % Dish diameter (m)
lambda = c / fc;   % Wavelength (m)

% Azimuth and Elevation angle grids (in radians)
theta = linspace(-pi, pi, 360);      % Azimuth angle (-180 to 180 degrees)
phi = linspace(-pi/2, pi/2, 180);    % Elevation angle (-90 to 90 degrees)
[Theta, Phi] = meshgrid(theta, phi); % Create a meshgrid

% Approximate directivity gain for a parabolic dish
G = (pi * D / lambda)^2; % Directivity (linear scale)

% Main lobe pattern in azimuth and elevation (assuming Gaussian-like pattern)
beamwidth_az = 70 * lambda / D;     % Approximate beamwidth in azimuth (degrees)
beamwidth_el = 70 * lambda / D;     % Approximate beamwidth in elevation (degrees)
beamwidth_az_rad = deg2rad(beamwidth_az);  % Convert to radians
beamwidth_el_rad = deg2rad(beamwidth_el);  % Convert to radians

% Calculate the antenna gain in dB
antennaGaindB = 10 * log10(4 * pi / (beamwidth_el_rad * beamwidth_el_rad));

% Beam pattern based on Gaussian distribution for main lobe
E_az = exp(-4 * log(2) * (Theta / beamwidth_az_rad).^2);  % Azimuth beampattern
E_el = exp(-4 * log(2) * (Phi / beamwidth_el_rad).^2);    % Elevation beampattern

% Total beampattern (assuming the product of azimuth and elevation patterns)
E_total = E_az .* E_el;

% Normalize the radiation pattern
E_normalized = E_total / max(max(E_total));

% Convert to decibels (dB) and scale by antenna gain
E_dB = 10 * log10(E_normalized) + antennaGaindB;
E_dB(E_dB < -40) = -40;  % Limit dynamic range to -40 dB

% Plot the 2D beampattern in polar coordinates (azimuth)
figure('Position', [100, 100, 800, 600]);
polarplot(theta, E_dB(round(size(E_dB, 1)/2), :), 'LineWidth', 2);
rlim([-40, antennaGaindB]);  % Set radial limits from -40 to antenna gain
ax = gca;
ax.RAxis.Label.String = 'Gain (dB)';
ax.ThetaZeroLocation = 'top';  % Zero degrees at the top
ax.ThetaDir = 'clockwise';     % Clockwise angle direction
grid on;

% 3D Radiation pattern
figure('Position', [100, 100, 800, 600]);
mesh(Theta, Phi, E_dB);
xlabel('Azimuth Angle (rad)');
ylabel('Elevation Angle (rad)');
zlabel('Gain (dB)');
colorbar;
caxis([-40 antennaGaindB]);  % Set color limits from -40 to antenna gain
grid on;
