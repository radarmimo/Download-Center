% SPS Short Course: Radar Signal Processing Mastery
% Theory and Hands-On Applications with mmWave MIMO Radar Sensors
% Date: 7-11 October 2024
% Time: 9:00AM-11:00AM ET (New York Time)
% Presenter: Mohammad Alaee-Kerahroodi
close all;
clear;
clc;

% Define lambda value (wavelength) and half-wavelength value
lambda = 1; % Example value; adjust based on your radar context
half_lambda = lambda / 2;

% First virtual array example
Nt1 = 1;
Nr1 = 8;
txarray1 = ones(Nt1, 1);
rxarray1 = ones(Nr1, 1);
varray1 = conv(txarray1, rxarray1);

% Create figure for the first virtual array example
figure;
plotva(Nt1, Nr1, txarray1, rxarray1, varray1, 1, half_lambda);
title('Virtual Array - Example 1', 'FontWeight', 'bold');
xlabel('Distance (integer multiples of \lambda/2)', 'FontWeight', 'bold');
ylabel('Amplitude (integer multiples of \lambda/2)', 'FontWeight', 'bold');
legend('Tx', 'Rx', 'VA', 'Location', 'Best');
grid on;

% Second virtual array example
Nt2 = 2;
Nr2 = 4;
txarray2 = [1; 0; 0; 0; 1];
rxarray2 = ones(Nr2, 1);
varray2 = conv(txarray2, rxarray2);

% Create figure for the second virtual array example
figure;
plotva(Nt2, Nr2, txarray2, rxarray2, varray2, 2, half_lambda);
title('Virtual Array - Example 2', 'FontWeight', 'bold');
xlabel('Distance (integer multiples of \lambda/2)', 'FontWeight', 'bold');
ylabel('Amplitude (integer multiples of \lambda/2)', 'FontWeight', 'bold');
legend('Tx', 'Rx', 'VA', 'Location', 'Best');
grid on;

% Third virtual array example with multiple transmitters
Nt3a = 2; % Number of transmitters
Nt3e = 2; % Effective transmitters
Nr3 = 4;  % Number of receivers
txarray3 = [1, 0, 0, 0, 1; 0, 0, 1, 0, 0];
rxarray3 = ones(1, Nr3);
varray3 = zeros(Nt3e, Nt3a * Nr3);

% Create figure for the third example
figure;

for i = 1:Nt3e
    varray3(i, :) = conv(txarray3(i, :), rxarray3);
    plotva(Nt3a, Nr3, txarray3(i, :), rxarray3, varray3(i, :), i, half_lambda);

end
title(['Virtual Array - Example 3: Tx ' num2str(i)], 'FontWeight', 'bold');
xlabel('Distance (integer multiples of \lambda/2)', 'FontWeight', 'bold');
ylabel('Amplitude (integer multiples of \lambda/2)', 'FontWeight', 'bold');
legend('Tx', 'Rx', 'VA', 'Location', 'Best');
grid on;



% ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
function plotva(Nt, Nr, txarray, rxarray, varray, i, half_lambda)
    hold on;
    varray(1:end) = varray(1:end) * i; % Scale virtual array for clarity
    
    % Calculate x-axis values for plotting
    x_tx = -length(txarray):-1; % Transmitter x-axis
    x_rx = 1:Nr; % Receiver x-axis
    x_varray = 1:length(varray); % Virtual array x-axis
    
    % Convert x values to integer multiples of lambda/2
    x_tx = x_tx * half_lambda; % Scale tx values
    x_rx = x_rx * half_lambda; % Scale rx values
    x_varray = x_varray * half_lambda; % Scale virtual array values

    % Define y values for amplitude in terms of lambda/2
    y_tx = txarray * i; % Scale transmitted array
    y_rx = rxarray;      % Received array
    y_varray = varray;   % Virtual array
    
    % Plot transmitted array
    plot(x_tx, y_tx, 'bs', 'MarkerSize', 10, 'DisplayName', 'Tx');
    % Plot received array
    plot(x_rx, y_rx, 'ro', 'MarkerSize', 10, 'DisplayName', 'Rx');
    % Plot virtual array
    plot(x_varray, y_varray, 'g^', 'MarkerSize', 20, 'DisplayName', 'VA');
    
    % Set x and y limits
    xlim([min(x_tx) - half_lambda, max(x_varray) + half_lambda]);
    if i == 1
        % Annotations
        text(mean(x_tx), mean(y_tx)+0.3, 'Tx', 'color', 'blue', 'HorizontalAlignment', 'center', 'FontWeight', 'bold');
        text(mean(x_rx), max(y_rx)-0.3, 'Rx', 'color', 'red', 'HorizontalAlignment', 'center', 'FontWeight', 'bold');
        text(mean(x_varray), max(y_varray)+0.4, 'Virtual Array', 'color', 'green', 'HorizontalAlignment', 'center', 'FontWeight', 'bold');
    end
    % Enhance plot visibility
    box on; % Add a box around the plot
    grid on; % Add grid for better visualization
    set(gca, 'FontWeight', 'bold'); % Bold axis labels

    % Set x and y ticks for better visibility
    set(gca, 'YTick', 0:0.5:1.5*i); % Set y ticks
    axis('equal')
    ylim([0.5, 1.5 * i]);
end
