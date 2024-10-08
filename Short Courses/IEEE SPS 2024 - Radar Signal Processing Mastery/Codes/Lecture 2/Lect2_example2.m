% SPS Short Course: Radar Signal Processing Mastery
% Theory and Hands-On Applications with mmWave MIMO Radar Sensors
% Date: 7-11 October 2024
% Time: 9:00AM-11:00AM ET (New York Time)
% Presenter: Mohammad Alaee-Kerahroodi

% Mechanical Scanning of Radar Antenna (Clockwise Rotation in PPI Display)
close all;
clear;
clc;

% Constants
fc = 10e9;           % Frequency (Hz)
c = 3e8;             % Speed of light (m/s)
lambda = c / fc;     % Wavelength (m)

D = 3;               % Dish antenna diameter (m)
beamwidth = 70 * lambda / D;  % Beamwidth in degrees

% Time and scanning parameters
scan_speed = 10;     % Degrees per second (scanning rate)
scan_range = 360;    % Total scan range in degrees
time_step = 0.1;     % Time step for simulation (seconds)
total_time = scan_range / scan_speed;  % Total time for a full rotation

theta = linspace(-pi, pi, 360);  % Azimuth angle grid (-180 to 180 degrees)

% Setup PPI Plot with black background
figure('Position', [100, 100, 800, 600]);
hold on;
axis equal;
grid on;

% Radar position (center of the scan)
radar_pos = [0, 0];

% Set the black background and white grid
set(gca, 'Color', 'k');                 % Black background
set(gca, 'XColor', 'w', 'YColor', 'w'); % White axis lines
grid minor;
ax = gca;
ax.GridColor = [1, 1, 1];               % White grid
ax.MinorGridColor = [0.5 0.5 0.5];      % Light gray minor grid

% Set black axis labels
xlabel('X-axis', 'Color', 'k');
ylabel('Y-axis', 'Color', 'k');

% Set the x-ticks and y-ticks to black
set(gca, 'XColor', 'k', 'YColor', 'k'); % Black ticks

% Draw concentric range rings for PPI (Plan Position Indicator)
max_range = 1.5;  % Maximum range for the plot
num_rings = 5;    % Number of range rings
for i = 1:num_rings
    radius = i * (max_range / num_rings);
    rectangle('Position', [-radius -radius 2*radius 2*radius], 'Curvature', [1 1], ...
              'EdgeColor', [0.7 0.7 0.7], 'LineStyle', '--');
end

% Create text object for current angle display (before the loop)
angle_text = text(-1.3, 1.3, '', 'Color', 'w', 'FontSize', 14, 'FontWeight', 'bold');

% Initialize GIF file
gif_filename = 'mechanical_scanning_animation.gif';

% Loop through time steps to simulate scanning
for t = 0:time_step:total_time
    % Current azimuth angle (clockwise rotation, starting from 0 degrees)
    current_angle = mod(-scan_speed * t, scan_range);  % Clockwise rotation

    % Define beam coverage based on current_angle
    beam_left = current_angle - beamwidth / 2;
    beam_right = current_angle + beamwidth / 2;

    % Convert angles to radians for calculations
    beam_left_rad = deg2rad(beam_left);
    beam_right_rad = deg2rad(beam_right);

    % Calculate x and y positions for the beam edges
    x_left = cos(beam_left_rad);
    y_left = sin(beam_left_rad);
    x_right = cos(beam_right_rad);
    y_right = sin(beam_right_rad);
    
    % Clear previous radar beam plot, but keep the text object
    delete(findall(gca, 'Type', 'patch'));  % Delete only the beam (patch)
    
    % Plot the radar beam in the PPI display with better visibility (bright green)
    fill([0, x_left, x_right], [0, y_left, y_right], 'g', 'FaceAlpha', 0.85, 'EdgeAlpha', 0);

    % Plot radar position (center)
    plot(radar_pos(1), radar_pos(2), 'ro', 'MarkerSize', 8, 'LineWidth', 2);
    
    % Plot the range rings (replot after clearing the figure)
    for i = 1:num_rings
        radius = i * (max_range / num_rings);
        rectangle('Position', [-radius -radius 2*radius 2*radius], 'Curvature', [1 1], ...
                  'EdgeColor', [0.7 0.7 0.7], 'LineStyle', '--');
    end

    % Update the current angle in degrees
    set(angle_text, 'String', ['Current Angle: ' num2str(mod(current_angle, 360), '%.1f') '°']);

    % Keep the axis fixed
    axis equal;
    xlim([-1.5, 1.5]);
    ylim([-1.5, 1.5]);
    
    % Capture the current frame
    frame = getframe(gcf);  % Capture the figure as a frame
    [A, map] = frame2im(frame);  % Convert to image
    % Convert to indexed image
    [A_ind, map] = rgb2ind(A, 256);  % Convert to indexed color format

    % Write the frame to the GIF file
    if t == 0
        imwrite(A_ind, map, gif_filename, 'gif', 'LoopCount', inf, 'DelayTime', time_step);
    else
        imwrite(A_ind, map, gif_filename, 'gif', 'WriteMode', 'append', 'DelayTime', time_step);
    end

    % Pause to simulate real-time scanning
    pause(0.05);
end

disp(['GIF saved to: ' gif_filename]);
