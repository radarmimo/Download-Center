function myboldify(h)
% myboldify: make lines and text bold
%   myboldify boldifies the current figure
%   myboldify(h) applies to the figure with the handle h

if nargin < 1
    h = gcf; 
end

ha = get(h, 'Children'); % the handle of each axis

for i = 1:length(ha)
    
    if strcmp(get(ha(i),'Type'), 'axes') % axis format
        set(ha(i), 'FontSize', 12);      % tick mark and frame format
        set(ha(i), 'LineWidth', 1.5);

        set(get(ha(i),'XLabel'), 'FontSize', 12);
        %set(get(ha(i),'XLabel'), 'VerticalAlignment', 'top');

        set(get(ha(i),'YLabel'), 'FontSize', 12);
        %set(get(ha(i),'YLabel'), 'VerticalAlignment', 'baseline');

        set(get(ha(i),'ZLabel'), 'FontSize', 12);
        %set(get(ha(i),'ZLabel'), 'VerticalAlignment', 'baseline');

        set(get(ha(i),'Title'), 'FontSize', 12);
        %set(get(ha(i),'Title'), 'FontWeight', 'Bold');
    end
    
    hc = get(ha(i), 'Children'); % the objects within an axis
    for j = 1:length(hc)
        chtype = get(hc(j), 'Type');
        if strcmp(chtype(1:4), 'text')
            set(hc(j), 'FontSize', 12); % 12 pt descriptive labels
        elseif strcmp(chtype(1:4), 'line')
            set(hc(j), 'LineWidth', 1.5);
            set(hc(j), 'MarkerSize', 8);
        elseif strcmp(chtype, 'hggroup')
            hcc = get(hc(j), 'Children');
            if strcmp(get(hcc, 'Type'), 'hggroup')
                hcc = get(hcc, 'Children');
            end
            for k = 1:length(hcc) % all elements are 'line'
                set(hcc(k), 'LineWidth', 1.5);
                set(hcc(k), 'MarkerSize', 8);
            end            
        end
    end
    
end
