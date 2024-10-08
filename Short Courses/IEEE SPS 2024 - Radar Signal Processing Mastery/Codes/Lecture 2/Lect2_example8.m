% SPS Short Course: Radar Signal Processing Mastery
% Theory and Hands-On Applications with mmWave MIMO Radar Sensors
% Date: 7-11 October 2024
% Time: 9:00AM-11:00AM ET (New York Time)
% Presenter: Mohammad Alaee-Kerahroodi
function cout = Lect2_example8(c, w, L)
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
        w = ones(1, length(c)); % Uniform weights
    end

    % Set default level L if not provided
    if ~exist('L', 'var') || isempty(L)
        L = inf; % Default to no quantization
    end

    c = c(:); % Ensure c is a row vector
    N = length(c); % Length of the sequence

    % Set peak weight to zero for numeric accuracy at zero-lag autocorrelation
    w(N) = 0; % Set peak weight to zero
    w = w(:); % Ensure w is a column vector

    c0 = c;   % Store initial sequence for comparison

    % Plot settings for dynamic visualization
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
    videoFilename = 'majorizationMinimization.avi';

    % Initialize video writer if needed
    if saveAsVideo
        video = VideoWriter(videoFilename, 'Uncompressed AVI');
        open(video);
    end

    % Maximum number of iterations
    maxIter = 10000; % Set the maximum number of iterations

    % Calculate parameters for the MM algorithm
    c_tilde = [0; w(N-1:-1:1); 0; w(end-1:-1:1)]; % Symmetric extension for FFT
    v = real(fft(c_tilde));                      % Compute FFT of the extended sequence
    p = ifft(v .* fft(ones(1, N), 2 * N));       % Compute the correction factor
    p = p(1:N);                                  % Truncate to relevant part
    p = p(:);                                    % Ensure p is a column vector
    lambda_B = 0.5 * (min(v(1:2:end)) + min(v(2:2:end))); % Lower bound of the minimum eigenvalue

    % Majorization-Minimization algorithm
    for m = 1:maxIter
        % FFT of the sequence with zero padding
        f = fft([c; zeros(N, 1)]);
        
        % Autocorrelation calculation
        r = 1 / (2 * N) * ifft(abs(f).^2);
        
        % Apply correlation weighting
        corrWeights = [0; w; w(end-1:-1:1)];
        
        % FFT of the weighted correlation
        mu = real(fft(r .* corrWeights));
        
        % Update lambda_mu (approximation of the max eigenvalue)
        lambda_mu = 0.5 * (max(mu(2:2:N)) + max(mu(1:2:N)));
        
        % Compute the correction term for the MM update
        y = ifft(mu .* f);
        
        % Update the sequence using MM step
        c = exp(1j * angle((lambda_mu - lambda_B) * c + p .* c - y(1:N)));

        % Update the plot dynamically
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

    % Close video file if saving
    if saveAsVideo
        close(video);
    end

    % Quantize to L levels if applicable
    if L ~= inf
        cout = exp(1i * floor(angle(c) / (2 * pi / L)) * (2 * pi / L)); % Quantize phase
    else
        cout = c; % Return the optimized sequence without quantization
    end
end
