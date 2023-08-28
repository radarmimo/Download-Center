function varargout = SettingGUI(varargin)
% SETTINGGUI MATLAB code for SettingGUI.fig
%      SETTINGGUI, by itself, creates a new SETTINGGUI or raises the existing
%      singleton*.
%
%      H = SETTINGGUI returns the handle to a new SETTINGGUI or the handle to
%      the existing singleton*.
%
%      SETTINGGUI('CALLBACK',hObject,eventData,handles,...) calls the local
%      function named CALLBACK in SETTINGGUI.M with the given input arguments.
%
%      SETTINGGUI('Property','Value',...) creates a new SETTINGGUI or raises the
%      existing singleton*.  Starting from the left, property value pairs are
%      applied to the GUI before SettingGUI_OpeningFcn gets called.  An
%      unrecognized property name or invalid value makes property application
%      stop.  All inputs are passed to SettingGUI_OpeningFcn via varargin.
%
%      *See GUI Options on GUIDE's Tools menu.  Choose "GUI allows only one
%      instance to run (singleton)".
%
% See also: GUIDE, GUIDATA, GUIHANDLES

% Edit the above text to modify the response to help SettingGUI

% Last Modified by GUIDE v2.5 09-Sep-2018 14:54:25

% Begin initialization code - DO NOT EDIT
gui_Singleton = 1;
gui_State = struct('gui_Name',       mfilename, ...
                   'gui_Singleton',  gui_Singleton, ...
                   'gui_OpeningFcn', @SettingGUI_OpeningFcn, ...
                   'gui_OutputFcn',  @SettingGUI_OutputFcn, ...
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


% --- Executes just before SettingGUI is made visible.
function SettingGUI_OpeningFcn(hObject, eventdata, handles, varargin)
% This function has no output args, see OutputFcn.
% hObject    handle to figure
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
% varargin   command line arguments to SettingGUI (see VARARGIN)

% Choose default command line output for SettingGUI
handles.output = hObject;

% Update handles structure
guidata(hObject, handles);
clc
try
load('Setting.mat');
% set(handles.popupmenu_weight,'Value',w_MWIS_Diag);
set(handles.checkbox_plt,'value',plt);
set(handles.edit_p,'string',num2str(P));
set(handles.checkbox_lp,'value',SweepP);
set(handles.edit_quntize,'string',num2str(Qnt));
set(handles.popupmenu_weigth,'Value',w);
if SweepP == 1
    set(handles.edit_p,'enable','off')
else
    set(handles.edit_p,'enable','on')
end
set(handles.edit_thr,'string',num2str(thr));
set(handles.radiobutton_nfft,'value',depfft);
set(handles.radiobutton_nfftin,'value',1-depfft);
set(handles.popupmenu_nfft,'value',depfftval);
set(handles.edit_nfft,'string',num2str(nfft));
set(handles.popupmenu_varsel,'value',varsel);
set(handles.edit_SweepTheta,'string',num2str(ThetaLevels));

catch
end
% UIWAIT makes SettingGUI wait for user response (see UIRESUME)
% uiwait(handles.figure1);


% --- Outputs from this function are returned to the command line.
function varargout = SettingGUI_OutputFcn(hObject, eventdata, handles) 
% varargout  cell array for returning output args (see VARARGOUT);
% hObject    handle to figure
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Get default command line output from handles structure
varargout{1} = handles.output;


% --- Executes on button press in pushbutton_saveclose.
function pushbutton_saveclose_Callback(hObject, eventdata, handles)
% hObject    handle to pushbutton_saveclose (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
clc
set(handles.text_save,'string',' ');
thr             = str2double(get(handles.edit_thr,'string'));
plt             = get(handles.checkbox_plt,'value');
P               = str2double(get(handles.edit_p,'string'));
SweepP          = get(handles.checkbox_lp,'value');
Qnt             = str2double(get(handles.edit_quntize,'string'));
w               = get(handles.popupmenu_weigth,'Value');
depfft          = get(handles.radiobutton_nfft,'value');
depfftval       = get(handles.popupmenu_nfft,'value');
nfft            = str2double(get(handles.edit_nfft,'string'));
varsel          = get(handles.popupmenu_varsel,'value');

ThetaLevels     = str2double(get(handles.edit_SweepTheta,'string'));


save('Setting.mat','thr','w','plt','P','SweepP',...
    'Qnt','depfft','depfftval','nfft','varsel','ThetaLevels')
set(handles.text_save,'string','Saved Successfully  . . . ');

% --- Executes on button press in pushbutton2.
function pushbutton2_Callback(hObject, eventdata, handles)
% hObject    handle to pushbutton2 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)



function edit_thrMWISL_diag_Callback(hObject, eventdata, handles)
% hObject    handle to edit_thrMWISL_diag (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of edit_thrMWISL_diag as text
%        str2double(get(hObject,'String')) returns contents of edit_thrMWISL_diag as a double


% --- Executes during object creation, after setting all properties.
function edit_thrMWISL_diag_CreateFcn(hObject, eventdata, handles)
% hObject    handle to edit_thrMWISL_diag (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end


% --- Executes on selection change in popupmenu_weight.
function popupmenu_weight_Callback(hObject, eventdata, handles)
% hObject    handle to popupmenu_weight (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: contents = cellstr(get(hObject,'String')) returns popupmenu_weight contents as cell array
%        contents{get(hObject,'Value')} returns selected item from popupmenu_weight


% --- Executes during object creation, after setting all properties.
function popupmenu_weight_CreateFcn(hObject, eventdata, handles)
% hObject    handle to popupmenu_weight (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: popupmenu controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end


% --- Executes on button press in checkbox_plt.
function checkbox_plt_Callback(hObject, eventdata, handles)
% hObject    handle to checkbox_plt (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hint: get(hObject,'Value') returns toggle state of checkbox_plt



function edit_thr_MMPSL_Callback(hObject, eventdata, handles)
% hObject    handle to edit_thr_MMPSL (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of edit_thr_MMPSL as text
%        str2double(get(hObject,'String')) returns contents of edit_thr_MMPSL as a double


% --- Executes during object creation, after setting all properties.
function edit_thr_MMPSL_CreateFcn(hObject, eventdata, handles)
% hObject    handle to edit_thr_MMPSL (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end


% --- Executes on button press in checkbox_pltMMPSL.
function checkbox_pltMMPSL_Callback(hObject, eventdata, handles)
% hObject    handle to checkbox_pltMMPSL (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hint: get(hObject,'Value') returns toggle state of checkbox_pltMMPSL


% --- Executes on button press in checkbox_lp.
function checkbox_lp_Callback(hObject, eventdata, handles)
% hObject    handle to checkbox_lp (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hint: get(hObject,'Value') returns toggle state of checkbox_lp

if get(hObject,'Value') == 1
    set(handles.edit_p,'enable','off')
else
    set(handles.edit_p,'enable','on')
end

function edit_p_Callback(hObject, eventdata, handles)
% hObject    handle to edit_p (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of edit_p as text
%        str2double(get(hObject,'String')) returns contents of edit_p as a double


% --- Executes during object creation, after setting all properties.
function edit_p_CreateFcn(hObject, eventdata, handles)
% hObject    handle to edit_p (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end


% --- Executes on button press in checkbox_see.
function checkbox_see_Callback(hObject, eventdata, handles)
% hObject    handle to checkbox_see (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hint: get(hObject,'Value') returns toggle state of checkbox_see



function edit_CANthr_Callback(hObject, eventdata, handles)
% hObject    handle to edit_CANthr (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of edit_CANthr as text
%        str2double(get(hObject,'String')) returns contents of edit_CANthr as a double


% --- Executes during object creation, after setting all properties.
function edit_CANthr_CreateFcn(hObject, eventdata, handles)
% hObject    handle to edit_CANthr (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end


% --- Executes on selection change in popupmenu_CANweigth.
function popupmenu_CANweigth_Callback(hObject, eventdata, handles)
% hObject    handle to popupmenu_CANweigth (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: contents = cellstr(get(hObject,'String')) returns popupmenu_CANweigth contents as cell array
%        contents{get(hObject,'Value')} returns selected item from popupmenu_CANweigth


% --- Executes during object creation, after setting all properties.
function popupmenu_CANweigth_CreateFcn(hObject, eventdata, handles)
% hObject    handle to popupmenu_CANweigth (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: popupmenu controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end


% --- Executes on button press in checkbox_CANplt.
function checkbox_CANplt_Callback(hObject, eventdata, handles)
% hObject    handle to checkbox_CANplt (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hint: get(hObject,'Value') returns toggle state of checkbox_CANplt



function edit_quntize_Callback(hObject, eventdata, handles)
% hObject    handle to edit_quntize (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of edit_quntize as text
%        str2double(get(hObject,'String')) returns contents of edit_quntize as a double


% --- Executes during object creation, after setting all properties.
function edit_quntize_CreateFcn(hObject, eventdata, handles)
% hObject    handle to edit_quntize (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end



function edit_thrITROX_Callback(hObject, eventdata, handles)
% hObject    handle to edit_thrITROX (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of edit_thrITROX as text
%        str2double(get(hObject,'String')) returns contents of edit_thrITROX as a double


% --- Executes during object creation, after setting all properties.
function edit_thrITROX_CreateFcn(hObject, eventdata, handles)
% hObject    handle to edit_thrITROX (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end


% --- Executes on button press in checkbox_pltITROX.
function checkbox_pltITROX_Callback(hObject, eventdata, handles)
% hObject    handle to checkbox_pltITROX (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hint: get(hObject,'Value') returns toggle state of checkbox_pltITROX



function edit_thr_Callback(hObject, eventdata, handles)
% hObject    handle to edit_thr (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of edit_thr as text
%        str2double(get(hObject,'String')) returns contents of edit_thr as a double


% --- Executes during object creation, after setting all properties.
function edit_thr_CreateFcn(hObject, eventdata, handles)
% hObject    handle to edit_thr (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end


% --- Executes on selection change in popupmenu_varselpol.
function popupmenu_varselpol_Callback(hObject, eventdata, handles)
% hObject    handle to popupmenu_varselpol (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: contents = cellstr(get(hObject,'String')) returns popupmenu_varselpol contents as cell array
%        contents{get(hObject,'Value')} returns selected item from popupmenu_varselpol


% --- Executes during object creation, after setting all properties.
function popupmenu_varselpol_CreateFcn(hObject, eventdata, handles)
% hObject    handle to popupmenu_varselpol (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: popupmenu controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end


% --- Executes on button press in checkbox_IM.
function checkbox_IM_Callback(hObject, eventdata, handles)
% hObject    handle to checkbox_IM (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hint: get(hObject,'Value') returns toggle state of checkbox_IM

set(handles.checkbox_binfft,'value',1)
    set(handles.radiobutton_nfft,'enable','off')
    set(handles.radiobutton_nfftin,'enable','off')
    set(handles.popupmenu_nfft,'enable','off')
    set(handles.edit_nfft,'enable','off')
% --- Executes on selection change in popupmenu_varsel.
function popupmenu_varsel_Callback(hObject, eventdata, handles)
% hObject    handle to popupmenu_varsel (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: contents = cellstr(get(hObject,'String')) returns popupmenu_varsel contents as cell array
%        contents{get(hObject,'Value')} returns selected item from popupmenu_varsel


% --- Executes during object creation, after setting all properties.
function popupmenu_varsel_CreateFcn(hObject, eventdata, handles)
% hObject    handle to popupmenu_varsel (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: popupmenu controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end



function edit_nfft_Callback(hObject, eventdata, handles)
% hObject    handle to edit_nfft (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of edit_nfft as text
%        str2double(get(hObject,'String')) returns contents of edit_nfft as a double


% --- Executes during object creation, after setting all properties.
function edit_nfft_CreateFcn(hObject, eventdata, handles)
% hObject    handle to edit_nfft (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end


% --- Executes on button press in radiobutton_nfftin.
function radiobutton_nfftin_Callback(hObject, eventdata, handles)
% hObject    handle to radiobutton_nfftin (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hint: get(hObject,'Value') returns toggle state of radiobutton_nfftin
if get(hObject,'Value') == 1
    set(handles.radiobutton_nfft,'value',0);
end

% --- Executes on button press in radiobutton_nfft.
function radiobutton_nfft_Callback(hObject, eventdata, handles)
% hObject    handle to radiobutton_nfft (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hint: get(hObject,'Value') returns toggle state of radiobutton_nfft
if get(hObject,'Value') == 1
    set(handles.radiobutton_nfftin,'value',0);
end

% --- Executes on selection change in popupmenu_nfft.
function popupmenu_nfft_Callback(hObject, eventdata, handles)
% hObject    handle to popupmenu_nfft (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: contents = cellstr(get(hObject,'String')) returns popupmenu_nfft contents as cell array
%        contents{get(hObject,'Value')} returns selected item from popupmenu_nfft


% --- Executes during object creation, after setting all properties.
function popupmenu_nfft_CreateFcn(hObject, eventdata, handles)
% hObject    handle to popupmenu_nfft (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: popupmenu controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end


% --- Executes on button press in checkbox_binfft.
function checkbox_binfft_Callback(hObject, eventdata, handles)
% hObject    handle to checkbox_binfft (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hint: get(hObject,'Value') returns toggle state of checkbox_binfft



function edit_SweepTheta_Callback(hObject, eventdata, handles)
% hObject    handle to edit_SweepTheta (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of edit_SweepTheta as text
%        str2double(get(hObject,'String')) returns contents of edit_SweepTheta as a double


% --- Executes during object creation, after setting all properties.
function edit_SweepTheta_CreateFcn(hObject, eventdata, handles)
% hObject    handle to edit_SweepTheta (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end


% --- Executes on selection change in popupmenu_weigth.
function popupmenu_weigth_Callback(hObject, eventdata, handles)
% hObject    handle to popupmenu_weigth (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: contents = cellstr(get(hObject,'String')) returns popupmenu_weigth contents as cell array
%        contents{get(hObject,'Value')} returns selected item from popupmenu_weigth


% --- Executes during object creation, after setting all properties.
function popupmenu_weigth_CreateFcn(hObject, eventdata, handles)
% hObject    handle to popupmenu_weigth (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: popupmenu controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end
