% SPS Short Course: Radar Signal Processing Mastery
% Theory and Hands-On Applications with mmWave MIMO Radar Sensors
% Date: 7-11 October 2024
% Time: 9:00AM-11:00AM ET (New York Time)
% Presenter: Mohammad Alaee-Kerahroodi

close all;
clear;
clc

% Load data file
[filename, pathname] = uigetfile('*.csv', 'Select the data file');
if isequal(filename, 0)
    disp('User canceled the file selection');
    return;
end
data1 = readmatrix(fullfile(pathname, filename));

% Check the size of data
if size(data1, 2) < 4
    error('Data must have at least 4 columns (I1, I2, Q1, Q2)');
end

I = data1(:, 2);
Q = data1(:, 4);

xAxisI = data1(:, 1);
xAxisQ = data1(:, 3);
% Create a plot for I and Q
figure('Position', [100, 100, 900, 600]);
hold all
plot(xAxisI, I, 'LineWidth', 2, 'DisplayName', 'In-phase', 'Color', 'b');
plot(xAxisQ, Q, 'LineWidth', 2, 'DisplayName', 'Quadrature', 'Color', 'r');
xlabel('Sample', 'FontSize', 14);
ylabel('Amplitude', 'FontSize', 14);
% title('In-phase and Quadrature Components', 'FontSize', 16);
legend();
axis tight;
grid on;
box on
% % Save the plot as an image file
% saveas(gcf, 'I_Q_Components.png');
% disp('Plot saved as I_Q_Components.png');
