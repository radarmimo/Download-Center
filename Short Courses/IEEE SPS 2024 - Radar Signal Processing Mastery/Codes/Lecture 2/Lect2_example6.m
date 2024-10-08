% SPS Short Course: Radar Signal Processing Mastery
% Theory and Hands-On Applications with mmWave MIMO Radar Sensors
% Date: 7-11 October 2024
% Time: 9:00AM-11:00AM ET (New York Time)
% Presenter: Mohammad Alaee-Kerahroodi
close all;
clear;
clc;

Nt = 24;
Nr = 24;

txAntpos = zeros(Nt, Nt);
txAntpos(:,1) = ones(Nt,1);

rxAntpos = zeros(Nr,Nr);
rxAntpos(1,:) = 1;

VAantpos = conv2(txAntpos,rxAntpos);

% Define the shapes
shapeSize = 0.5; % Size of the shapes

% Plotting
figure('Position', [100, 100, 800, 600]);
hold on;

% Plot transmit antennas as rectangles
for i = 1:Nt
    for j = 1:Nt
        if txAntpos(i, j) == 1
            rectangle('Position', [j - shapeSize/2, i - shapeSize/2, shapeSize, shapeSize], ...
                      'FaceColor', 'b', 'EdgeColor', 'k'); % Blue rectangles
        end
    end
end

% Plot receive antennas as circles
for i = 1:Nr
    for j = 1:Nr
        if rxAntpos(i, j) == 1
            viscircles([j+1, i], shapeSize/2, 'Color', 'r', 'LineWidth', 1); % Red circles
        end
    end
end

% Plot virtual antennas as triangles
for i = 1:size(VAantpos, 1)
    for j = 1:size(VAantpos, 2)
        if VAantpos(i, j) == 1
            triangle_x = [j+1 - shapeSize/2, j+1, j+1 + shapeSize/2];
            triangle_y = [i+1, i + shapeSize+1, i+1];
            fill(triangle_x, triangle_y, 'g', 'EdgeColor', 'k'); % Green triangles
        end
    end
end

% Setting axes and labels
axis equal;
box on
grid on;
hold off;
xlabel('Distance (integer multiples of \lambda/2)', 'FontWeight', 'bold');
ylabel('Distance (integer multiples of \lambda/2)', 'FontWeight', 'bold');
