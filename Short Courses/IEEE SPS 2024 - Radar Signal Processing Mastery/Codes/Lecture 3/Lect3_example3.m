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
% Parameters
sample_rate = 2000; % 2 kHz
window_size = sample_rate; % 1 second window
nFFT = 2^nextpow2(sample_rate);

% Extract I and Q components
I = data1(:, 2);
Q = data1(:, 4);

xAxisI = data1(:, 1);
xAxisQ = data1(:, 3);

% Compute the envelope of the signal using Hilbert transform
signal = I + 1i * Q;
envelope = abs(filter(sample_rate,1,signal-mean(signal))/(sample_rate));

num_samples = length(I); % Total number of samples

% Preallocate figure for plotting
figure('Position', [100, 100, 900, 600]);

% Create a subplot for FFT magnitude
subplot(2, 1, 1);
hold on;
xlabel('Frequency (Hz)', 'FontSize', 14);
ylabel('Magnitude (dB)', 'FontSize', 14);
grid on;
ylim([-30, 30])
f = linspace(-sample_rate/2, sample_rate/2, nFFT); % Frequency vector
box on

% Create a subplot for I and Q data
subplot(2, 1, 2);
hold on;
plot(xAxisI, I, 'LineWidth', 2, 'DisplayName', 'In-phase (I)', 'Color', 'b');
plot(xAxisQ, Q, 'LineWidth', 2, 'DisplayName', 'Quadrature (Q)', 'Color', 'r');
% plot(xAxisI, envelope, 'LineWidth', 1.5, 'DisplayName', 'Envelope', 'Color', 'k', 'LineStyle', '--');
xlabel('Sample', 'FontSize', 14);
ylabel('Amplitude', 'FontSize', 14);
grid on;
legend('In-phase (I)', 'Quadrature (Q)', 'Envelope', 'Location', 'best');
box on

% Initialize GIF parameters
gifFilename = 'doppler_processing.gif';
frameDelay = 0.1; % Delay between frames in seconds

% Iterate over the data with a sliding window
for start_index = 1:round(window_size/4):num_samples - window_size + 1
    % Define the current window
    end_index = start_index + window_size - 1;
    current_window = I(start_index:end_index) + 1i * Q(start_index:end_index); 
    
    current_window = current_window - mean(current_window);
    % Perform FFT
    Y = fft(hann(window_size) .* current_window, nFFT);
    
    magnitude = abs(Y); % Magnitude spectrum

    % Clear the previous plot and redraw for FFT magnitude
    subplot(2, 1, 1);
    cla; % Clear current axes
    plot(f, 10*log10(fftshift(magnitude)), 'LineWidth', 2); % Plot the magnitude spectrum
    legend('FFT Magnitude', 'Location', 'northeast');
    
    % Highlight the current window in the I/Q plot
    subplot(2, 1, 2);
    % Clear previous highlight
    cla;
    hold on;
    plot(xAxisI, I, 'LineWidth', 2, 'DisplayName', 'In-phase (I)', 'Color', 'b');
    plot(xAxisQ, Q, 'LineWidth', 2, 'DisplayName', 'Quadrature (Q)', 'Color', 'r');
    plot(xAxisI(1:end_index), envelope(1:end_index), 'LineWidth', 1.5, 'DisplayName', 'Envelope', 'Color', 'k', 'LineStyle', '-');
    
    % Highlight current window
    highlight_x = xAxisI(start_index:end_index);
    highlight_y = I(start_index:end_index);
    fill([highlight_x; flipud(highlight_x)], [highlight_y; zeros(length(highlight_y), 1)], 'g', ...
        'FaceAlpha', 0.3, 'EdgeColor', 'none', 'DisplayName', 'Current Window');
    
    xlabel('Time (s)', 'FontSize', 14);
    ylabel('Amplitude', 'FontSize', 14);
    grid on;
    legend('In-phase (I)', 'Quadrature (Q)', 'Envelope', 'Current Window', 'Location', 'best');
    
    % Capture the current frame
    frame = getframe(gcf);
    im = frame2im(frame);
    [A, map] = rgb2ind(im, 256);
    
    % Write to the GIF file
    if start_index == 1
        imwrite(A, map, gifFilename, 'gif', 'Loopcount', inf, 'DelayTime', frameDelay);
    else
        imwrite(A, map, gifFilename, 'gif', 'WriteMode', 'append', 'DelayTime', frameDelay);
    end
    
    % Update the figure
    drawnow; % Force MATLAB to update the figure window
end

hold off; % Release the figure

