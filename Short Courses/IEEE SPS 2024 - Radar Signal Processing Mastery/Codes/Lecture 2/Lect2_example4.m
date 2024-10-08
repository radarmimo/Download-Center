% SPS Short Course: Radar Signal Processing Mastery
% Theory and Hands-On Applications with mmWave MIMO Radar Sensors
% Date: 7-11 October 2024
% Time: 9:00AM-11:00AM ET (New York Time)
% Presenter: Mohammad Alaee-Kerahroodi
close all
clear
clc

N = 20; % Number of antenna elements
k = 1; % 2d/lambda (element spacing factor)
desiredAngle = 25; % Initial desired angle in degrees

theta = linspace(-90, 90, 200); % Angle range for plotting

% Initialize arrays for storing results
AF = zeros(length(theta), 1); % Array factor
AFW = zeros(length(theta), 1); % Array factor with Taylor window

% Steering vector for the desired angle
a = exp(-1i * pi * k * (0:N-1) * sind(desiredAngle));
a = a(:);

for i = 1:length(theta)
    % Calculate response at angle theta(i)
    w = exp(-1i * pi * k * (0:N-1) * sind(theta(i)));
    w = w(:);
    AF(i) = abs(w' * a); % Calculate array factor
    AFW(i) = abs((taylorwin(N, 4, -45) .* w)' * a); % Taylor windowed response
end

% Create a new figure for plotting
figure('Position', [100, 100, 800, 600]);
grid on;
box on;
xlabel('Angle [degrees]', 'FontSize', 12);
ylabel('Amplitude [dB]', 'FontSize', 12);
legend('Uniform Array', 'Taylor Windowed Array', 'Location', 'Best');
set(gca, 'FontSize', 12); % Set font size for axes
ylim([-40, 15]); % Set y-axis limits for clarity
xlim([-90, 90]); % Set x-axis limits for clarity

% Initialize GIF file
gifFileName = 'beamforming_animation.gif';

% Animation loop to show beamforming
for desiredAngle = -90:90 % Update desired angle from -90 to 90 degrees
    % Update steering vector for the current desired angle
    a = exp(-1i * pi * k * (0:N-1) * sind(desiredAngle));
    a = a(:);
    for i = 1:length(theta)
        % Calculate response at angle theta(i)
        w = exp(-1i * pi * k * (0:N-1) * sind(theta(i)));
        w = w(:);
        AF(i) = abs(w' * a); % Calculate array factor
        AFW(i) = abs((taylorwin(N, 4, -45) .* w)' * a); % Taylor windowed response
    end

    % Clear current figure and re-plot
    clf;

    % Plot current state of array factor
    plot(theta, 10*log10(AF), 'b-', 'LineWidth', 2); % Uniform Array
    hold on;
    plot(theta, 10*log10(AFW), 'r--', 'LineWidth', 2); % Taylor Window
    grid on;
    box on;

    % Highlight the current steering angle
    plot(desiredAngle, 10*log10(max(AF)), 'ko', 'MarkerSize', 10, 'MarkerFaceColor', 'k'); % Current point for uniform array

    % Update title to show current steering angle
    title(sprintf('Beamforming towards Angle = %.1f degrees', desiredAngle), 'FontSize', 14);

    % Update axis settings
    xlabel('Angle [degrees]', 'FontSize', 12);
    ylabel('Amplitude [dB]', 'FontSize', 12);
    legend('Uniform Array', 'Taylor Windowed Array', 'Location', 'southeast');
    set(gca, 'FontSize', 12); % Set font size for axes
    ylim([-40, 15]); % Set y-axis limits for clarity
    xlim([-90, 90]); % Set x-axis limits for clarity

    % Capture the current frame as an image
    frame = getframe(gcf);
    im = frame2im(frame);
    [A,map] = rgb2ind(im,256);

    % Write to the GIF file
    if desiredAngle == -90
        imwrite(A,map,gifFileName,'gif','LoopCount',inf,'DelayTime',0.1); % Create GIF file
    else
        imwrite(A,map,gifFileName,'gif','WriteMode','append','DelayTime',0.1); % Append frames
    end

    % Pause for a moment to observe the change
    pause(0.1);
end
