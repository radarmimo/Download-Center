function figSelector()
mainFig = uifigure('Name','Figure Selector','Units','normalized',...
    'Position',[0.42 0.27 .16 .46],'Resize','on','HandleVisibility','on',...
    'CloseRequestFcn',@closeFig);

figT = 20;
parameters.figT = figT;
parameters.disableFigs = [1 2 16];

parameters.Flags = zeros(figT,1);
setappdata(mainFig,'Parameter', parameters)

layout0 = uigridlayout(mainFig,[1,1]);
FigurePanel = uipanel('Parent',layout0, 'Title','Figure Numbers','Tag','Figure Panel');

layout1 = uigridlayout(FigurePanel,[ceil((figT+1)/2)+1,2]);

idx = 1:figT;

for i = idx
    checkboxFig = uicheckbox(layout1,'Text',['Figure ', num2str(i)],...
        'ValueChangedFcn',@(cbx,event) checkboxFigFunc(cbx),'Value',0,'Tag',['fig', num2str(i)]);

    [column, row] = ind2sub([2 ceil((figT+1)/2)],i);
    checkboxFig.Layout.Row = row;
    checkboxFig.Layout.Column = column;

    if any(i == parameters.disableFigs)
        checkboxFig.Enable = 'off';
        checkboxFig.FontColor = 'r';
    end

end

checkboxAll = uicheckbox(layout1,'Text','All Figures',...
    'ValueChangedFcn',@(cbx,event) checkboxAllFunc(cbx),'Value',0);

[columnAll, rowAll] = ind2sub([2 ceil((figT+1)/2)],figT+1);

checkboxAll.Layout.Row = rowAll;
checkboxAll.Layout.Column = columnAll;

genButton = uibutton(layout1,'push','Text','Run Simulation','HorizontalAlignment','center',...
    'FontSize',15,'Tag','RoadGenButton','ButtonPushedFcn',@(src,event)runSimulation);
genButton.Layout.Row = ceil((figT+1)/2) + 1;
genButton.Layout.Column = [1,2];
end

function checkboxFigFunc(cbx)
mainFig = findobj(groot,'Name','Figure Selector');
parameters = getappdata(mainFig,'Parameter');

idx = str2double(cbx.Tag(4:end));
parameters.Flags(idx) = cbx.Value;

setappdata(mainFig,'Parameter', parameters)
end

function checkboxAllFunc(cbx)
mainFig = findobj(groot,'Name','Figure Selector');
parameters = getappdata(mainFig,'Parameter');

idx = 1:parameters.figT;
idx(parameters.disableFigs) = [];
parameters.Flags(idx) = cbx.Value;
for i = idx

    cb = findobj(groot,'Tag',['fig', num2str(i)]);
    cb.Value = cbx.Value;

end

setappdata(mainFig,'Parameter', parameters)

end

function runSimulation

mainFig = findobj(groot,'Name','Figure Selector');

parameters = getappdata(mainFig,'Parameter');

figureNum = find(parameters.Flags);

assignin('base', 'figureNum', figureNum);
close(mainFig)

end

function closeFig(~, ~)

mainFig = findobj(groot,'Name','Figure Selector');
uiresume()
delete(mainFig);

end