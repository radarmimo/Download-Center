% SPS Short Course: Radar Signal Processing Mastery
% Theory and Hands-On Applications with mmWave MIMO Radar Sensors
% Date: 7-11 October 2024
% Time: 9:00AM-11:00AM ET (New York Time)
% Presenter: Mohammad Alaee-Kerahroodi

close all;
clear;
clc;

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
sample_rate = 50; % 50Hz
window_size = 20*sample_rate; % 1 second window
nFFT = 4096;

% Extract I and Q components
I = data1(:, 2);
Q = data1(:, 4);

xAxisI = data1(:, 1); % Assuming this is the time axis
xAxisQ = data1(:, 3);

% Compute the envelope of the signal 
signal = I + 1i * Q;
signal = signal - mean(signal);
envelope = abs(filter(sample_rate, 1, signal - mean(signal)) / (sample_rate));

num_samples = length(I); % Total number of samples

angle_data = angle(signal);

% Unwrap the phase
phase_unwrap = unwrap(angle_data);

% Apply low-pass filter to unwrapped phase
[b,a] = butter(8, 2/sample_rate, 'low');
filtered_unwrap = filter(b, a, phase_unwrap);

% Remove the trend from the filtered signal using detrend
detrended_signal = detrend(filtered_unwrap);

% Plotting
figure('Position', [100, 100, 800, 600]);
plot(xAxisI, angle_data, 'LineWidth', 2, 'Color', 'b', 'DisplayName', 'Phase (wrapped)');
xlabel('Time (s)'); % Assuming xAxisI represents time in seconds
ylabel('Phase (radians)');
grid on;
legend();
set(gca, 'FontSize', 12); % Set font size for readability

% Plot unwrapped, filtered, and detrended signals
figure('Position', [100, 100, 800, 600]);
hold all
plot(xAxisI, phase_unwrap, 'LineWidth', 2, 'Color', 'r', 'DisplayName', 'Unwrapped Phase');
plot(xAxisI, filtered_unwrap, 'LineWidth', 2, 'Color', 'g', 'DisplayName', 'Filtered Signal');
plot(xAxisI, detrended_signal, 'LineWidth', 2, 'Color', 'm', 'DisplayName', 'Detrended Signal');

xlabel('Time (s)');
ylabel('Phase (radians)');
grid on;
legend();
set(gca, 'FontSize', 12); % Set font size for readability

% Apply a moving average to estimate the trend
% window_size = sample_rate*20; % Adjust this window size according to your data
trend = movmean(filtered_unwrap, window_size);

% Remove the trend
detrended_signal = filtered_unwrap - trend;

% Plotting
figure('Position', [100, 100, 800, 600]);
hold all
plot(xAxisI, phase_unwrap, 'LineWidth', 2, 'Color', 'r', 'DisplayName', 'Unwrapped Phase');
plot(xAxisI, filtered_unwrap, 'LineWidth', 2, 'Color', 'g', 'DisplayName', 'Filtered Signal');
plot(xAxisI, detrended_signal, 'LineWidth', 2, 'Color', 'm', 'DisplayName', 'Detrended Signal');

xlabel('Time (s)');
ylabel('Phase (radians)');
grid on;
legend();
set(gca, 'FontSize', 12); % Set font size for readability
% xlim([45,140])


% Preallocate figure for plotting
figure('Position', [100, 100, 900, 600]);

% Create a subplot for FFT magnitude
subplot(2, 1, 1);
hold on;
xlabel('Frequency (Hz)', 'FontSize', 14);
ylabel('Magnitude (dB)', 'FontSize', 14);
grid on;
ylim([20, 40])
f = linspace(-sample_rate/2, sample_rate/2, nFFT); % Frequency vector
box on

% Create a subplot for I and Q data
subplot(2, 1, 2);
hold on;
plot(xAxisI, phase_unwrap, 'LineWidth', 2, 'DisplayName', 'Unwrapped Phase', 'Color', 'b');
plot(xAxisQ, filtered_unwrap, 'LineWidth', 2, 'DisplayName', 'Filtered Unwrapped', 'Color', 'r');
% plot(xAxisI, envelope, 'LineWidth', 1.5, 'DisplayName', 'Envelope', 'Color', 'k', 'LineStyle', '--');
xlabel('Sample', 'FontSize', 14);
ylabel('Amplitude', 'FontSize', 14);
grid on;
legend();
box on

% Initialize GIF parameters
gifFilename = 'breathing_processing.gif';
frameDelay = 0.1; % Delay between frames in seconds

% Iterate over the data with a sliding window
for start_index = 1:round(window_size/20):num_samples - window_size + 1
    % Define the current window
    end_index = start_index + window_size - 1;
    current_window_1 = phase_unwrap(start_index:end_index); 
    current_window_1 = current_window_1 - mean(current_window_1);
    % Perform FFT
    Y1 = fft(hann(window_size) .* current_window_1, nFFT);
    magnitude1 = abs(Y1); % Magnitude spectrum

    current_window_2 = filtered_unwrap(start_index:end_index); 
    current_window_2 = current_window_2 - mean(current_window_2);
    % Perform FFT
    Y2 = fft(hann(window_size) .* current_window_2, nFFT);
    magnitude2 = abs(Y2); % Magnitude spectrum    

    current_window_3 = detrended_signal(start_index:end_index); 
    current_window_3 = current_window_3 - mean(current_window_3);
    % Perform FFT
    Y3 = fft(hann(window_size) .* current_window_3, nFFT);
    magnitude3 = abs(Y3); % Magnitude spectrum       

    % Clear the previous plot and redraw for FFT magnitude
    subplot(2, 1, 1);
    cla; % Clear current axes
    hold all
    plot(f, 10*log10(fftshift(magnitude1)), 'LineWidth', 2,'DisplayName','Unwrapped Phase', 'Color', 'b'); % Plot the magnitude spectrum
    plot(f, 10*log10(fftshift(magnitude2)), 'LineWidth', 2,'DisplayName','Filtered Unwrapped', 'Color', 'r'); % Plot the magnitude spectrum
    plot(f, 10*log10(fftshift(magnitude3)), 'LineWidth', 2,'DisplayName','Detrended', 'Color', 'k'); % Plot the magnitude spectrum
    xlim([0,0.7])
    legend();
    
    % Highlight the current window in the I/Q plot
    subplot(2, 1, 2);
    % Clear previous highlight
    cla;
    hold on;
    plot(xAxisI, phase_unwrap, 'LineWidth', 2, 'DisplayName', 'Unwrapped Phase', 'Color', 'b');
    plot(xAxisQ, filtered_unwrap, 'LineWidth', 2, 'DisplayName', 'Filtered Unwrapped', 'Color', 'r');
    plot(xAxisI(1:end_index), detrended_signal(1:end_index), 'LineWidth', 1.5, 'DisplayName', 'Detrended', 'Color', 'k', 'LineStyle', '-');
    
    % Highlight current window
    highlight_x = xAxisI(start_index:end_index);
    highlight_y = phase_unwrap(start_index:end_index);
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
