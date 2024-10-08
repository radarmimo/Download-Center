% SPS Short Course: Radar Signal Processing Mastery
% Theory and Hands-On Applications with mmWave MIMO Radar Sensors
% Date: 7-11 October 2024
% Time: 9:00AM-11:00AM ET (New York Time)
% Presenter: Mohammad Alaee-Kerahroodi
function Lect2_example9(x0)
    % Define default plot parameters
    MarkerSize = 20;
    LineWidth = 1.5;
    LabelFontSize = 16;   % Font size for labels
    TickFontSize = 14;    % Font size for axis ticks
    LegendFontSize = 14;  % Font size for legend

    % If initial sequence x0 is not provided, generate a random one
    if ~exist('x0', 'var') || isempty(x0)
        rng(1);  % Set random seed for reproducibility
        N = 128; % Sequence length
        phi = (2 * rand(N, 1) - 1) * pi; % Random initial phase
        x0 = exp(1i * phi); % Initial complex sequence with unit magnitude
    end

    % Initialize variables
    x = x0;                  % Starting sequence
    N = length(x);           % Length of the sequence
    MaxIter = 1000;           % Maximum number of iterations

    % Plot settings
    figure(1);
    hold on;
    box on;
    grid on;
    xlabel('Shift (k)', 'FontSize', LabelFontSize);
    ylabel('Correlation Level (dB)', 'FontSize', LabelFontSize);
    ylim([-N/2, 10]);
    legend('Initial Sequence', 'Optimized Sequence', 'Location', 'southeast', 'FontSize', LegendFontSize);
    set(gca, 'FontSize', TickFontSize); % Set font size for ticks

    % Plot the initial correlation
    plot(-(N-1):(N-1), 20 * log10(abs(xcorr(x0)) / N), 'b.-', 'MarkerSize', MarkerSize, ...
         'MarkerIndices', 1:5:2 * N - 1, 'LineWidth', LineWidth, 'DisplayName', 'Initial Sequence');

    % Flag for saving as video
    saveAsVideo = false; % Set to true if you want to save the output as a video
    videoFilename = 'cdAlgorithm.avi';

    % Initialize video writer if needed
    if saveAsVideo
        video = VideoWriter(videoFilename, 'Uncompressed AVI');
        open(video);
    end

    % Main optimization loop
    for cnt = 1:MaxIter
        for d = 1:N
            % Compute a_dk, b_dk, and c_dk based on the current sequence x
            [a_dk, b_dk, c_dk] = mabc(x, d);

            % Calculate the coefficients mu, kappa, xi, eta, and rho
            [mu, kappa, xi, eta, rho] = coef(a_dk, b_dk, c_dk);

            % Sum of coefficients for polynomial construction
            mu_tilde = sum(mu);
            kappa_tilde = sum(kappa);
            xi_tilde = sum(xi);
            eta_tilde = sum(eta);
            rho_tilde = sum(rho);

            % Polynomial coefficients
            a1 = -kappa_tilde;
            a2 = (4 * mu_tilde - 2 * xi_tilde);
            a3 = (2 * kappa_tilde - 3 * eta_tilde);
            a4 = (4 * mu_tilde - 4 * rho_tilde);
            a5 = (3 * kappa_tilde - 2 * eta_tilde);
            a6 = (2 * xi_tilde - 4 * rho_tilde);
            a7 = eta_tilde;

            % Polynomial roots
            p = [a1, a2, a3, a4, a5, a6, a7];
            root_tmp = roots(p);

            % Filter real roots only
            roots1 = real(root_tmp(abs(imag(root_tmp)) < 1e-10));

            % Compute the value of the objective function at the roots
            betaVec = (mu_tilde * roots1.^4 + kappa_tilde * roots1.^3 + ...
                       xi_tilde * roots1.^2 + eta_tilde * roots1 + rho_tilde) ./ (1 + roots1.^2).^2;

            % Find the root that minimizes the objective function
            [~, indx] = min(betaVec);
            beta_d = roots1(indx);

            % Update the sequence element if a valid beta_d is found
            if ~isempty(beta_d)
                phi_d = 2 * atan(beta_d);
                x(d) = exp(1i * phi_d);
            end
        end

        % Update the plot dynamically every few iterations
        if mod(cnt, 10) == 0
            cla; % Clear current plot
            % Plot initial and optimized correlation levels
            plot(-(N-1):(N-1), 20 * log10(abs(xcorr(x0)) / N), 'b.-', ...
                'MarkerSize', MarkerSize, 'MarkerIndices', 1:5:2 * N - 1, ...
                'LineWidth', LineWidth, 'DisplayName', 'Initial Sequence');
            plot(-(N-1):(N-1), 20 * log10(abs(xcorr(x)) / N), 'r-', ...
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

    % Display the final optimized sequence
    disp('Optimized Sequence:');
    disp(x);
end

% Helper function to compute mabc values
function [a_dk, b_dk, c_dk] = mabc(x, d)
    % Computes vectors a_dk, b_dk, and c_dk for a given sequence and index d

    x = x(:);       % Ensure x is a column vector
    N = length(x);  % Length of the sequence

    % Remove the d-th element and compute autocorrelation
    x(d) = 0; % Set d-th element to zero temporarily
    c_dk = xcorr(conj(x)); % Compute cross-correlation
    c_dk(1:N) = [];        % Remove the first half

    % Calculate b_dk by circularly shifting and setting elements to zero
    b_dk = circshift(x(end:-1:1), d - 1);
    b_dk(d:end) = 0;
    b_dk(end) = [];

    % Calculate a_dk by circularly shifting and setting elements to zero
    a_dk = conj(circshift(x, -d));
    a_dk(end-d+1:end) = 0;
    a_dk(end) = [];
end

% Helper function to compute coefficients
function [mu, kappa, xi, eta, rho] = coef(ak, bk, ck)
    % Computes coefficients mu, kappa, xi, eta, and rho from a_dk, b_dk, c_dk

    % Real and imaginary parts
    akr = real(ak);
    aki = imag(ak);
    bkr = real(bk);
    bki = imag(bk);
    ckr = real(ck);
    cki = imag(ck);

    % Calculate coefficients for both real and imaginary parts
    mu1 = (akr + bkr).^2 - 2 * ckr .* (akr + bkr) + ckr.^2;
    kappa1 = -4 * (akr + bkr) .* (bki - aki) + 4 * ckr .* (bki - aki);
    xi1 = -2 * (akr + bkr).^2 + 2 * ckr.^2 + 4 * (bki - aki).^2;
    eta1 = 4 * (akr + bkr) .* (bki - aki) + 4 * ckr .* (bki - aki);
    rho1 = (akr + bkr).^2 + 2 * (akr + bkr) .* ckr + ckr.^2;

    mu2 = (aki + bki).^2 - 2 * cki .* (aki + bki) + cki.^2;
    kappa2 = -4 * (aki + bki) .* (akr - bkr) + 4 * cki .* (akr - bkr);
    xi2 = -2 * (aki + bki).^2 + 2 * cki.^2 + 4 * (akr - bkr).^2;
    eta2 = 4 * (aki + bki) .* (akr - bkr) + 4 * cki .* (akr - bkr);
    rho2 = (aki + bki).^2 + 2 * (aki + bki) .* cki + cki.^2;

    % Sum up the components for the final coefficients
    mu = mu1 + mu2;
    kappa = kappa1 + kappa2;
    xi = xi1 + xi2;
    eta = eta1 + eta2;
    rho = rho1 + rho2;
end
