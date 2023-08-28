function varargout = mSISO(varargin)
% MSISO MATLAB code for mSISO.fig
%      MSISO, by itself, creates a new MSISO or raises the existing
%      singleton*.
%
%      H = MSISO returns the handle to a new MSISO or the handle to
%      the existing singleton*.
%
%      MSISO('CALLBACK',hObject,eventData,handles,...) calls the local
%      function named CALLBACK in MSISO.M with the given input arguments.
%
%      MSISO('Property','Value',...) creates a new MSISO or raises the
%      existing singleton*.  Starting from the left, property value pairs are
%      applied to the GUI before mSISO_OpeningFcn gets called.  An
%      unrecognized property name or invalid value makes property application
%      stop.  All inputs are passed to mSISO_OpeningFcn via varargin.
%
%      *See GUI Options on GUIDE's Tools menu.  Choose "GUI allows only one
%      instance to run (singleton)".
%
% See also: GUIDE, GUIDATA, GUIHANDLES

% Edit the above text to modify the response to help mSISO

% Last Modified by GUIDE v2.5 09-Sep-2018 14:40:34

% Begin initialization code - DO NOT EDIT
gui_Singleton = 1;
gui_State = struct('gui_Name',       mfilename, ...
    'gui_Singleton',  gui_Singleton, ...
    'gui_OpeningFcn', @mSISO_OpeningFcn, ...
    'gui_OutputFcn',  @mSISO_OutputFcn, ...
    'gui_LayoutFcn',  [] , ...
    'gui_Callback',   []);
if nargin && ischar(varargin{1})
    gui_State.gui_Callback = str2func(varargin{1});
end

if nargout
    [varargout{1:nargout}] = gui_mainfcn(gui_State, varargin{:});
else
    gui_mainfcn(gui_State, varargin{:});
end
% End initialization code - DO NOT EDIT


% --- Executes just before mSISO is made visible.
function mSISO_OpeningFcn(hObject, eventdata, handles, varargin)
% This function has no output args, see OutputFcn.
% hObject    handle to figure
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
% varargin   command line arguments to mSISO (see VARARGIN)

% Choose default command line output for mSISO
handles.output = hObject;
strFrank    = {'4' ,'9', '16', '25', '36', '49' ,'64' ,'81', '100' ,'121',...
    '144','169' ,'196' ,'225' '256', '289' ,'324' ,'361' ,'400' ,'441' ,...
    '484' ,'529' ,'576' ,'625', '676' ,'729' ,'784' ,'841' ,'900',...
    '961' ,'1024'};
set(handles.popupmenu_codes,'value',8);
% set(handles.popupmenu_length,'string',strFrank)
set(handles.popupmenu_length,'visible','off')
set(handles.edit_length,'visible','on')
% edit_length
% Update handles structure
guidata(hObject, handles);
[ x ,code_type] = gui_inicod( handles );
axes(handles.axes4);
text(0,0,'min \{(\theta) PSL + (1 - \theta) ISL\}')
axes(handles.axes5);
cla
text(0,0,['\theta = ',num2str(get(handles.slider_theta,'Value'))])

% UIWAIT makes mSISO wait for user response (see UIRESUME)
% uiwait(handles.figure1);
set(handles.uipanel7,'visible','on');
set(handles.slider_theta,'visible','on');
set(handles.popupmenu_pil,'visible','on');
set(handles.pushbutton_runour,'visible','on');
% set(handles.pushbutton_setting,'visible','on');

set(handles.uipanel6,'visible','off');
% set(handles.popupmenu_islmini,'visible','off')
set(handles.pushbutton_runother,'visible','off')
% set(handles.pushbutton_settingother,'visible','off')


% --- Outputs from this function are returned to the command line.
function varargout = mSISO_OutputFcn(hObject, eventdata, handles)
% varargout  cell array for returning output args (see VARARGOUT);
% hObject    handle to figure
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Get default command line output from handles structure
varargout{1} = handles.output;


% --- Executes on selection change in popupmenu_wavtype.
function popupmenu_wavtype_Callback(hObject, eventdata, handles)
% hObject    handle to popupmenu_wavtype (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: contents = cellstr(get(hObject,'String')) returns popupmenu_wavtype contents as cell array
%        contents{get(hObject,'Value')} returns selected item from popupmenu_wavtype
% contents    = cellstr(get(hObject,'String'));
strpoly     = {'Frank','Golomb','P1','P2','P3','P4','Chu','Random'};
strbin      = {'Barker','m-sequence','Gold','Kasami','Random','All One'};
set(handles.edit_length,'visible','off');
set(handles.popupmenu_length,'visible','on');
set(handles.popupmenu_length,'value',4)
strFrank    = {'4' ,'9', '16', '25', '36', '49' ,'64' ,'81', '100' ,'121',...
    '144','169' ,'196' ,'225' '256', '289' ,'324' ,'361' ,'400' ,'441' ,...
    '484' ,'529' ,'576' ,'625', '676' ,'729' ,'784' ,'841' ,'900',...
    '961' ,'1024'};
strBarker   = {'2' ,'3', '4', '5', '7', '11' ,'13'};
switch get(hObject,'Value')
    case 1
        % poly phase
        set(handles.popupmenu_codes,'String',strpoly);
        set(handles.popupmenu_codes,'value',1);
        set(handles.popupmenu_length,'string',strFrank)
        
        
    case 2
        % binary
        set(handles.popupmenu_codes,'String',strbin);
        set(handles.popupmenu_codes,'value',1);
        set(handles.popupmenu_length,'string',strBarker)
end
% --- Executes during object creation, after tools all properties.
function popupmenu_wavtype_CreateFcn(hObject, eventdata, handles)
% hObject    handle to popupmenu_wavtype (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: popupmenu controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end


% --- Executes on selection change in popupmenu_codes.
function popupmenu_codes_Callback(hObject, eventdata, handles)
% hObject    handle to popupmenu_codes (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: contents = cellstr(get(hObject,'String')) returns popupmenu_codes contents as cell array
%        contents{get(hObject,'Value')} returns selected item from popupmenu_codes
strFrank    = {'4' ,'9', '16', '25', '36', '49' ,'64' ,'81', '100' ,'121',...
    '144','169' ,'196' ,'225' ,'256', '289' ,'324' ,'361' ,'400' ,'441' ,...
    '484' ,'529' ,'576' ,'625', '676' ,'729' ,'784' ,'841' ,'900',...
    '961' ,'1024'};
strP2    = {'4' , '16', '36', '64' , '100' ,...
    '144','196' , '256', '324' ,'400' ,...
    '484' ,'576' , '676'  ,'784' ,'900','1024'};
strBarker   = {'2' ,'3', '4', '5', '7', '11' ,'13'};
strmseq     = {'3','7','15','31','63','127','255','511','1023'};
strgold     = {'3','7','31','63','127','511','1023'};
strkasami   = {'3','15','63','255','1023'};
if get(handles.popupmenu_wavtype,'value') == 1
    if get(hObject,'Value') == 1 || get(hObject,'Value') == 3 || get(hObject,'Value') == 5
        set(handles.edit_length,'visible','off');
        set(handles.popupmenu_length,'visible','on');
        set(handles.popupmenu_length,'string',strFrank)
        set(handles.popupmenu_length,'value',4)
    elseif get(hObject,'Value') == 4
        set(handles.edit_length,'visible','off');
        set(handles.popupmenu_length,'visible','on');
        set(handles.popupmenu_length,'string',strP2)
        set(handles.popupmenu_length,'value',4)
    else
        set(handles.popupmenu_length,'visible','off');
        set(handles.edit_length,'visible','on');
    end
else
    switch get(hObject,'Value')
        case 1
            set(handles.edit_length,'visible','off');
            set(handles.popupmenu_length,'visible','on');
            set(handles.popupmenu_length,'string',strBarker)
            set(handles.popupmenu_length,'value',4)
        case 2
            set(handles.edit_length,'visible','off');
            set(handles.popupmenu_length,'visible','on');
            set(handles.popupmenu_length,'string',strmseq)
            set(handles.popupmenu_length,'value',4)
        case 3
            set(handles.edit_length,'visible','off');
            set(handles.popupmenu_length,'visible','on');
            set(handles.popupmenu_length,'string',strgold)
            set(handles.popupmenu_length,'value',4)
        case 4
            set(handles.edit_length,'visible','off');
            set(handles.popupmenu_length,'visible','on');
            set(handles.popupmenu_length,'string',strkasami)
            set(handles.popupmenu_length,'value',4)
        case 5
            set(handles.popupmenu_length,'visible','off');
            set(handles.edit_length,'visible','on');
        case 6
            set(handles.popupmenu_length,'visible','off');
            set(handles.edit_length,'visible','on');
    end
end


% --- Executes during object creation, after tools all properties.
function popupmenu_codes_CreateFcn(hObject, eventdata, handles)
% hObject    handle to popupmenu_codes (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: popupmenu controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end


% --- Executes on selection change in popupmenu_length.
function popupmenu_length_Callback(hObject, eventdata, handles)
% hObject    handle to popupmenu_length (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: contents = cellstr(get(hObject,'String')) returns popupmenu_length contents as cell array
%        contents{get(hObject,'Value')} returns selected item from popupmenu_length


% --- Executes during object creation, after tools all properties.
function popupmenu_length_CreateFcn(hObject, eventdata, handles)
% hObject    handle to popupmenu_length (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: popupmenu controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end



function edit_length_Callback(hObject, eventdata, handles)
% hObject    handle to edit_length (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of edit_length as text
%        str2double(get(hObject,'String')) returns contents of edit_length as a double


% --- Executes during object creation, after tools all properties.
function edit_length_CreateFcn(hObject, eventdata, handles)
% hObject    handle to edit_length (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end


% --- Executes on selection change in popupmenu_view.
function popupmenu_view_Callback(hObject, eventdata, handles)
% hObject    handle to popupmenu_view (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: contents = cellstr(get(hObject,'String')) returns popupmenu_view contents as cell array
%        contents{get(hObject,'Value')} returns selected item from popupmenu_view
tmpdt   = get(handles.uitable1,'data');
if isempty(tmpdt)
    return
end
if strcmp(tmpdt(1,1) , '') == 1
    return
end
Indices     = hObject.UserData;
if isempty(Indices)
    row = 1;
else
    row         = Indices(1);
end
x       = str2num(cell2mat(tmpdt(row,end)));
guiplt( x, handles )

% --- Executes during object creation, after tools all properties.
function popupmenu_view_CreateFcn(hObject, eventdata, handles)
% hObject    handle to popupmenu_view (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: popupmenu controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end


% --- Executes on button press in pushbutton_apply.
function pushbutton_apply_Callback(hObject, eventdata, handles)
% hObject    handle to pushbutton_apply (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
tic;
[ x ,str] = gui_inicod( handles );
t = toc;
%  str2    = [str, ' initial code row = ', num2str(CodeIndex)];
add2table( x , str ,t,handles );

% --- Executes when entered data in editable cell(s) in uitable1.
function uitable1_CellEditCallback(hObject, eventdata, handles)
% hObject    handle to uitable1 (see GCBO)
% eventdata  structure with the following fields (see MATLAB.UI.CONTROL.TABLE)
%	Indices: row and column indices of the cell(s) edited
%	PreviousData: previous data for the cell(s) edited
%	EditData: string(s) entered by the user
%	NewData: EditData or its converted form set on the Data property. Empty if Data was not changed
%	Error: error string when failed to convert EditData to appropriate value for Data
% handles    structure with handles and user data (see GUIDATA)


% --- Executes on button press in pushbutton_save.
function pushbutton_save_Callback(hObject, eventdata, handles)
% hObject    handle to pushbutton_save (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
[filename, pathname, filterindex] = uiputfile( {'*.txt;'},'Save as');
if filename ~= 0
    tmpdt   = get(handles.uitable1,'data');
    T       = table(tmpdt);
    writetable(T,[pathname,filename],'Delimiter',',');
    msgbox('saved successfully')
end
% --- Executes on button press in pushbutton_load.
function pushbutton_load_Callback(hObject, eventdata, handles)
% hObject    handle to pushbutton_load (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
[filename, pathname, filterindex] = uigetfile ({'*.txt;'});
if filename ~= 0
    T       = readtable([pathname,filename]);
    tmpdt   = table2cell(T);
    set(handles.uitable1,'data',tmpdt);
end
% --- Executes on button press in pushbutton_del.
function pushbutton_del_Callback(hObject, eventdata, handles)
% hObject    handle to pushbutton_del (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
Indices     = hObject.UserData;
if isempty(Indices)
    answer = questdlg('Do you want to delete all data in the table ? ');
    if strcmp(answer,'Yes')
        set(handles.uitable1,'data',[]);
    end
else
    if size(Indices,1) == 1
        answer = questdlg(['Do you want to delete data of row ',num2str(Indices(1)),' in the table ? ']);
    else
        answer = questdlg('Do you want to delete selected data ? ');
    end
    if strcmp(answer,'Yes')
        tmpdt   = get(handles.uitable1,'data');
        tmpdt(Indices(:,1),:) = [];
        set(handles.uitable1,'data',tmpdt);
    end
    
end
handles.pushbutton_del.UserData = 1;
handles.pushbutton_runother.UserData = 1;
handles.pushbutton_runour.UserData = 1;
handles.popupmenu_view.UserData = 1;

% --- Executes on button press in pushbutton_add.
function pushbutton_add_Callback(hObject, eventdata, handles)
% hObject    handle to pushbutton_add (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
[filename, pathname, filterindex] = uigetfile ({'*.txt;'});
if filename ~= 0
    T       = readtable([pathname,filename]);
    tmpdt2  = table2cell(T);
    l2      = size(tmpdt2,1);
    tmpdt   = get(handles.uitable1,'data');
    if strcmp(tmpdt(1,1) , '') ~= 1
        l1      = size(tmpdt,1);
        tmpdt(l1+1:l1+l2,:) = tmpdt2;
    else
        tmpdt   = tmpdt2;
    end
    set(handles.uitable1,'data',tmpdt);
end


% --- Executes when selected cell(s) is changed in uitable1.
function uitable1_CellSelectionCallback(hObject, eventdata, handles)
% hObject    handle to uitable1 (see GCBO)
% eventdata  structure with the following fields (see MATLAB.UI.CONTROL.TABLE)
%	Indices: row and column indices of the cell(s) currently selecteds
% handles    structure with handles and user data (see GUIDATA)
if isempty(eventdata.Indices)
    return;
end
handles.pushbutton_del.UserData = eventdata.Indices;
handles.pushbutton_runother.UserData = eventdata.Indices;
handles.pushbutton_runour.UserData = eventdata.Indices;
handles.popupmenu_view.UserData = eventdata.Indices;

tmpdt   = get(hObject,'data');
x       = str2num(cell2mat(tmpdt(eventdata.Indices(1),end)));
x       = x(:);
guiplt( x, handles )


% --- Executes on selection change in popupmenu_islmini.
function popupmenu_islmini_Callback(hObject, eventdata, handles)
% hObject    handle to popupmenu_islmini (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: contents = cellstr(get(handles.popupmenu_islmini,'String')) returns popupmenu_islmini contents as cell array
%        contents{get(handles.popupmenu_islmini,'Value')} returns selected item from popupmenu_islmini


% --- Executes during object creation, after tools all properties.
function popupmenu_islmini_CreateFcn(hObject, eventdata, handles)
% hObject    handle to popupmenu_islmini (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: popupmenu controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end


% --- Executes on selection change in popupmenu_pslmini.
function popupmenu_pslmini_Callback(hObject, eventdata, handles)
% hObject    handle to popupmenu_pslmini (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: contents = cellstr(get(hObject,'String')) returns popupmenu_pslmini contents as cell array
%        contents{get(hObject,'Value')} returns selected item from popupmenu_pslmini


% --- Executes during object creation, after tools all properties.
function popupmenu_pslmini_CreateFcn(hObject, eventdata, handles)
% hObject    handle to popupmenu_pslmini (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: popupmenu controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end


% --- Executes on slider movement.
function slider1_Callback(hObject, eventdata, handles)
% hObject    handle to slider1 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'Value') returns position of slider
%        get(hObject,'Min') and get(hObject,'Max') to determine range of slider


% --- Executes during object creation, after tools all properties.
function slider1_CreateFcn(hObject, eventdata, handles)
% hObject    handle to slider1 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: slider controls usually have a light gray background.
if isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor',[.9 .9 .9]);
end


% --- Executes on selection change in popupmenu_pil.
function popupmenu_pil_Callback(hObject, eventdata, handles)
% hObject    handle to popupmenu_pil (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: contents = cellstr(get(hObject,'String')) returns popupmenu_pil contents as cell array
%        contents{get(hObject,'Value')} returns selected item from popupmenu_pil
contents = cellstr(get(hObject,'String')) ;


% --- Executes during object creation, after tools all properties.
function popupmenu_pil_CreateFcn(hObject, eventdata, handles)
% hObject    handle to popupmenu_pil (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: popupmenu controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end


% --- Executes on slider movement.
function slider_theta_Callback(hObject, eventdata, handles)
% hObject    handle to slider_theta (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'Value') returns position of slider
%        get(hObject,'Min') and get(hObject,'Max') to determine range of slider
axes(handles.axes5);
cla
text(0,0,['\theta = ',num2str(get(hObject,'Value'))])


% --- Executes during object creation, after tools all properties.
function slider_theta_CreateFcn(hObject, eventdata, handles)
% hObject    handle to slider_theta (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: slider controls usually have a light gray background.
if isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor',[.9 .9 .9]);
end


% --- Executes on button press in pushbutton_setting.
function pushbutton_setting_Callback(hObject, eventdata, handles)
% hObject    handle to pushbutton_setting (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
guisettingour

% --- Executes on button press in pushbutton_settingother.
function pushbutton_settingother_Callback(hObject, eventdata, handles)
% hObject    handle to pushbutton_settingother (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
guisettingother

% --- Executes on button press in pushbutton_runour.
function pushbutton_runour_Callback(hObject, eventdata, handles)
% hObject    handle to pushbutton_runour (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
tmpdt   = get(handles.uitable1,'data');
if isempty(tmpdt)
    errordlg('You should add at least one initial sequence to the table')
    return
end
if strcmp(tmpdt(1,1) , '') == 1
    errordlg('You should add at least one initial sequence to the table')
    return
end
load('Setting.mat');
guidiskeys( handles )
theta       = get(handles.slider_theta,'value');
tmpdt       = get(handles.uitable1,'data');
Indices     = hObject.UserData;
if isempty(Indices)
    row     = 1;
else
    row     = Indices(1);
end
x0          = str2num(cell2mat(tmpdt(row,end)));
N           = length(x0);
if depfft == 1
    switch depfftval
        case 1
            nfft = N;
        case 2
            nfft = 2*N;
        case 3
            nfft = 10*N;
        case 4
            nfft = 100*N;
        case 5
            nfft = 500*N;
        case 6
            nfft = 1000*N;
    end
end
set(handles.axes1,'visible','off')
set(handles.axes2,'visible','off')
set(handles.axes3,'visible','on')
axes(handles.axes3);
switch get(handles.popupmenu_pil,'Value')
    case 1 % CPM
        str     = ['CPM, \theta = ', num2str(theta)];
        [ x0 , CodeIndex]      = guiques( str, hObject, handles);
        if ~isempty(x0)
            tic;
            if get(handles.checkbox2,'value') == 1
                theta = linspace(0,1,ThetaLevels);
            end
            for i = 1 : length(theta)
                if get(handles.checkbox_periodic,'value')
                    str     = [str, ', Priodic, '];
                    x       = cpm( x0,thr,theta(i),1);
                else
                    tic;
                    x       = cpm( x0,thr,theta(i),0);
                end
                x0 = x;
            end
            t       = toc;
        end
    case 2 % DPM
        str     = ['DPM, \theta = ', num2str(theta)];
        [x0,CodeIndex]      = guiques( str, hObject, handles);
        if ~isempty(x0)
            tic;
            
            if get(handles.checkbox2,'value') == 1
                theta = linspace(0,1,ThetaLevels);
            end
            for i = 1 : length(theta)
                if get(handles.checkbox_periodic,'value')
                    str     = [str, ', Priodic, '];
                    x       = dpm( x0, nfft,thr,theta(i), 1);
                else
                    tic;
                    x       = dpm( x0, nfft,thr,theta(i), 0);
                end
                x0 = x;
            end
            t       = toc;
        end
    case 3 % DPM-Binary
        str     = ['DPM, \theta = ', num2str(theta)];
        [x0,CodeIndex]      = guiques( str, hObject, handles);
        if ~isempty(x0)
            if get(handles.checkbox2,'value') == 1
                theta = linspace(0,1,ThetaLevels);
            end
            for i = 1 : length(theta)
                if get(handles.checkbox_periodic,'value')
                    str     = [str, ', Priodic, '];
                    x       = dpm( x0, 2,thr,theta(i), 1);
                else
                    tic;
                    x       = dpm( x0, 2,thr,theta(i), 0);
                end
                x0 = x;
            end

            t       = toc;
        end
end

if ~isempty(x0)
    
    str2    = [str, ' initial sequence = ', num2str(CodeIndex)];
    
    add2table( x , str2 ,t,handles );
    guiplt( x, handles );
    
end
guienbkeys( handles )
% --- Executes on button press in pushbutton_runother.
function pushbutton_runother_Callback(hObject, eventdata, handles)
% hObject    handle to pushbutton_runother (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
tmpdt       = get(handles.uitable1,'data');
Indices     = hObject.UserData;
if isempty(Indices)
    row     = 1;
else
    row     = Indices(1);
end
x0          = str2num(cell2mat(tmpdt(row,end)));
x0          = x0(:);
N           = length(x0);
if isempty(tmpdt)
    errordlg('You should add at least one initial sequence to the table')
    return
end
if strcmp(tmpdt(1,1) , '') == 1
    errordlg('You should add at least one initial sequence to the table')
    return
end
guidiskeys( handles )

load('Setting.mat');
N       = length(x0);
set(handles.axes1,'visible','off')
set(handles.axes2,'visible','off')
set(handles.axes3,'visible','on')
axes(handles.axes3);
if depfft == 1
    switch depfftval
        case 1
            nfft = N;
        case 2
            nfft = 2*N;
        case 3
            nfft = 10*N;
        case 4
            nfft = 100*N;
        case 5
            nfft = 500*N;
        case 6
            nfft = 1000*N;
    end
end
switch w
    case 1
        w       = ones(N-1,1);          % weights
    case 2
        w       = hann(N-1);            % weights
    case 3
        w       = hamming(N-1);         % weights
    case 4
        w       = gausswin(N-1);        % weights
end
if SweepP == 1
    P       = 0;
end
x       = x(:);
str2    = [str, ' initial sequence = ', num2str(CodeIndex)];
add2table( x.' , str2 ,t,handles );

plot(abs(xcorr(x)))
axis('tight')
guiplt( x, handles );
guienbkeys( handles )


% --- Executes on button press in pushbutton_reset.
function pushbutton_reset_Callback(hObject, eventdata, handles)
% hObject    handle to pushbutton_reset (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

guienbkeys(handles)
clc;


% --- Executes on button press in pushbutton_pareto.
function pushbutton_pareto_Callback(hObject, eventdata, handles)
% hObject    handle to pushbutton_pareto (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

tmpdt   = get(handles.uitable1,'data');
if isempty(tmpdt)
    errordlg('You should add at least one initial sequence to the table')
    return
end
if strcmp(tmpdt(1,1) , '') == 1
    errordlg('You should add at least one initial sequence to the table')
    return
end
load('Setting.mat');


% --- Executes during object creation, after tools all properties.
function pushbutton_runour_CreateFcn(hObject, eventdata, handles)
% hObject    handle to pushbutton_runour (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called


% --- Executes on button press in checkbox_periodic.
function checkbox_periodic_Callback(hObject, eventdata, handles)
% hObject    handle to checkbox_periodic (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hint: get(hObject,'Value') returns toggle state of checkbox_periodic


% --- Executes on button press in pushbutton_designed.
function pushbutton_designed_Callback(hObject, eventdata, handles)
% hObject    handle to pushbutton_designed (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
set(handles.uipanel7,'visible','on');
set(handles.slider_theta,'visible','on');
set(handles.popupmenu_pil,'visible','on');
set(handles.pushbutton_runour,'visible','on');
% set(handles.pushbutton_setting,'visible','on');

set(handles.uipanel6,'visible','off');
% set(handles.popupmenu_islmini,'visible','off')
set(handles.pushbutton_runother,'visible','off')
% set(handles.pushbutton_settingother,'visible','off')

% --- Executes on button press in pushbutton_other.
function pushbutton_other_Callback(~, eventdata, handles)
% hObject    handle to pushbutton_other (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
set(handles.uipanel7,'visible','off');
set(handles.slider_theta,'visible','off');
set(handles.popupmenu_pil,'visible','off');
set(handles.pushbutton_runour,'visible','off');
% set(handles.pushbutton_setting,'visible','off');

set(handles.uipanel6,'visible','on');
% set(handles.popupmenu_islmini,'visible','on')
set(handles.pushbutton_runother,'visible','on')
% set(handles.pushbutton_settingother,'visible','on')


% --------------------------------------------------------------------
function Tools_Callback(hObject, ~, handles)
% hObject    handle to Tools (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)


% --------------------------------------------------------------------
function Setting_Callback(hObject, eventdata, handles)
% hObject    handle to Setting (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
SettingGUI


% --- Executes on button press in pushbutton_constellation.
function pushbutton_constellation_Callback(hObject, eventdata, handles)
% hObject    handle to pushbutton_constellation (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
tmpdt   = get(handles.uitable1,'data');
if isempty(tmpdt)
    return
end
if strcmp(tmpdt(1,1) , '') == 1
    return
end
Indices     = handles.popupmenu_view.UserData;
if isempty(Indices)
    row = 1;
else
    row         = Indices(1);
end
x       = str2num(cell2mat(tmpdt(row,end)));
scatterplot(x);
myboldify        


% --- Executes on button press in checkbox2.
function checkbox2_Callback(hObject, eventdata, handles)
% hObject    handle to checkbox2 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hint: get(hObject,'Value') returns toggle state of checkbox2
