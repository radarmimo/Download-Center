% SPS Short Course: Radar Signal Processing Mastery
% Theory and Hands-On Applications with mmWave MIMO Radar Sensors
% Date: 7-11 October 2024
% Time: 9:00AM-11:00AM ET (New York Time)
% Presenter: Mohammad Alaee-Kerahroodi
close all;
clear;
clc;

Nt = 3;
Nr = 4;

txAntpos = zeros(Nt*Nr, Nt*Nr);
txAntpos(1, Nt + Nr + 1) = 1;
txAntpos(1, Nt + Nr + 5) = 1;
txAntpos(2, Nt + Nr + 3) = 1;

rxAntpos = zeros(Nt*Nr, Nr*Nt);
rxAntpos(1, 1:Nr) = 1;

VAantpos = conv2(txAntpos, rxAntpos);

% Define the shapes
shapeSize = 0.75; % Size of the shapes
fontSize = 18;

% Plotting transmit and receive antennas
figure('Position', [100, 100, 800, 600]);
hold on;

% Plot transmit antennas as rectangles
for i = 1:Nt*Nr
    for j = 1:Nt*Nr
        if txAntpos(i, j) == 1
            rectangle('Position', [j - shapeSize/2, i - shapeSize/2, shapeSize, shapeSize], ...
                      'FaceColor', 'r', 'EdgeColor', 'k'); % Blue rectangles
        end
        if rxAntpos(i, j) == 1
            rectangle('Position', [j + 1 - shapeSize/2, i - shapeSize/2, shapeSize, shapeSize], ...
                      'Curvature', [1, 1], 'FaceColor', 'b', 'EdgeColor', 'k'); % Filled red circles
        end
    end
end

% Adding labels for Tx and Rx arrays
text(Nt*Nr - 2, 0.0, 'Tx Array', 'FontWeight', 'bold', 'Color', 'r', 'HorizontalAlignment', 'center','FontSize',fontSize);
text(Nr - 0.5, 0.0, 'Rx Array', 'FontWeight', 'bold', 'Color', 'b', 'HorizontalAlignment', 'center','FontSize',fontSize);

% Setting axes and labels
axis equal;
box on;
grid on;
hold off;
xlabel('Distance (integer multiples of \lambda/2)', 'FontWeight', 'bold','FontSize',fontSize);
ylabel('Distance (integer multiples of \lambda/2)', 'FontWeight', 'bold','FontSize',fontSize);
xlim([0, Nt*Nr + 1])

% Plotting virtual antennas
figure('Position', [100, 100, 800, 600]);
hold on;

% Plot virtual antennas as triangles
for i = 1:size(VAantpos, 1)
    for j = 1:size(VAantpos, 2)
        if VAantpos(i, j) == 1
            triangle_x = [j + 1 - shapeSize/2, j + 1, j + 1 + shapeSize/2];
            triangle_y = [i + 1, i + shapeSize + 1, i + 1];
            fill(triangle_x, triangle_y, 'g', 'EdgeColor', 'k'); % Green triangles
        end
    end
end

% Adding label for virtual antennas
text(Nt*Nr + 0.5, 1.5, 'Virtual Antennas', 'FontWeight', 'bold', 'Color', 'g', 'HorizontalAlignment', 'center','FontSize',fontSize);

% Setting axes and labels
axis equal;
box on;
grid on;
hold off;
xlabel('Distance (integer multiples of \lambda/2)', 'FontWeight', 'bold','FontSize',fontSize);
ylabel('Distance (integer multiples of \lambda/2)', 'FontWeight', 'bold','FontSize',fontSize);
xlim([Nt*Nr/2 + 1, Nt*Nr + Nt*Nr/2])
