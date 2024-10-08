% SPS Short Course: Radar Signal Processing Mastery
% Theory and Hands-On Applications with mmWave MIMO Radar Sensors
% Date: 7-11 October 2024
% Time: 9:00AM-11:00AM ET (New York Time)
% Presenter: Mohammad Alaee-Kerahroodi
function cout = Lect2_example7(c, w, L, P)
    % Define default plot parameters
    MarkerSize = 20;
    LineWidth = 1.5;
    LabelFontSize = 16;   % Font size for labels
    TickFontSize = 14;    % Font size for axis ticks
    LegendFontSize = 14;  % Font size for legend

    % Initialize the sequence c if not provided
    if ~exist('c', 'var') || isempty(c)
        rng(1); % Set random seed for reproducibility
        phi = (2 * rand(128, 1) - 1) * pi; % Generate random phase
        c = exp(1i * phi); % Complex sequence with unit magnitude
    end

    % Initialize weights w if not provided
    if ~exist('w', 'var') || isempty(w)
        w = ones(1, 2 * length(c) - 1); % Uniform weights
    end

    % Set default level L if not provided
    if ~exist('L', 'var') || isempty(L)
        L = inf; % Default to no quantization
    end

    % Set default power P if not provided
    if ~exist('P', 'var') || isempty(P)
        P = 70; % Default power level
    end

    c = c(:).'; % Ensure c is a row vector
    N = length(c); % Length of the sequence

    % Adjust weights, set peak weight to zero for numeric accuracy
    if isequal(w, 0)
        w = ones(1, 2 * length(c) - 1);
    end
    w(N) = 0; % Set peak weight to zero
    w = w(:).'; % Ensure w is a row vector

    cout = c; % Initialize output sequence
    c0 = c; % Store initial sequence

    if P == 0
        P = 2.^(1:6); % Default power values
    end

    % Plot settings
    figure(1);
    hold on;
    box on;
    grid on;
    xlabel('Shift (k)', 'FontSize', LabelFontSize);
    ylabel('Correlation Level (dB)', 'FontSize', LabelFontSize);
    ylim([-N/2, 10]);
    legend('Initial Sequence', 'Obtained Sequence', 'Location', 'southeast', 'FontSize', LegendFontSize);
    set(gca, 'FontSize', TickFontSize); % Set font size for ticks

    % Initial plot of the sequence correlation
    plot(-(N-1):(N-1), 20 * log10(abs(xcorr(c0)) / N), 'b.-', 'MarkerSize', MarkerSize, ...
         'MarkerIndices', 1:5:2 * N - 1, 'LineWidth', LineWidth);

    % Flag for saving as video
    saveAsVideo = false; % Set to true if you want to save the output as a video
    videoFilename = 'gradientDescent.avi';

    % Initialize video writer if needed
    if saveAsVideo
        video = VideoWriter(videoFilename, 'Uncompressed AVI');
        open(video);
    end

    % Compute initial correlation and objective value
    rk = abs(xcorr(c));
    obj(1) = norm(rk(1:N-1), P(1));

    % Main optimization loop
    for np = 1:length(P) % Iterate over power levels P
        p = P(np); % Current power level
        for m = 1:10000 % Gradient descent iterations
            % Compute FFT and gradient
            fa = fft(c, 2 * N - 1);
            x = fftshift(ifft(abs(fa).^2)); % Correlation function
            g = w.^(2 * p) .* x .* abs(x).^(2 * p - 2); % Gradient factor
            gar = fftshift(ifft(fft(g, 2 * N - 1) .* fa)); % Convolve and FFT
            grad = -4 * p * imag(c .* conj([gar(end), gar(1:N-1)])); % Gradient calculation
            grad = grad / max(abs(grad)); % Normalize gradient to avoid numeric instability
            s = -0.05 / sqrt(m); % Learning rate that decreases with iterations

            % Update sequence c using the computed gradient
            c = c .* exp(1i * s * grad);

            % Update plot every 100 iterations
            if mod(m, 100) == 0
                cla; % Clear current plot
                % Plot initial and optimized correlation levels
                plot(-(N-1):(N-1), 20 * log10(abs(xcorr(c0)) / N), 'b.-', ...
                    'MarkerSize', MarkerSize, 'MarkerIndices', 1:5:2 * N - 1, ...
                    'LineWidth', LineWidth, 'DisplayName', 'Initial Sequence');
                plot(-(N-1):(N-1), 20 * log10(abs(xcorr(c)) / N), 'r-', ...
                    'MarkerSize', MarkerSize, 'MarkerIndices', 1:5:2 * N - 1, ...
                    'LineWidth', LineWidth, 'DisplayName', 'Optimized Sequence');
                drawnow;

                % Capture the frame for the video
                if saveAsVideo
                    frame = getframe(gcf);
                    writeVideo(video, frame);
                end
            end
        end

        % Update objective value and check for NaN in sequence
        rk = abs(xcorr(c));
        obj(end + 1) = norm(rk(1:N-1), P(1));    

        if isnan(c(1)) 
            break; % Exit if sequence becomes invalid
        end
        
        cout = c; % Update the output sequence
    end

    % Close video file if saving
    if saveAsVideo
        close(video);
    end

    % Quantize to L levels if applicable
    if L ~= 0 && L ~= inf
        cout = exp(1i * floor(angle(cout(1:N)) / (2 * pi / L)) * (2 * pi / L)); % Quantize phase
    end
end
