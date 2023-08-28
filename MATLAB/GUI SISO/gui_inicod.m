function [ x , code_type] = gui_inicod( handles )
strcd   = get(handles.popupmenu_codes,'value');
if get(handles.popupmenu_wavtype,'value') == 1 % polyphase
    
    switch strcd
        case 1
            contents    = cellstr(get(handles.popupmenu_length,'String'));
            N           = str2double(contents{get(handles.popupmenu_length,'Value')});
            code_type   = 'frank';
        case 2
            code_type   = 'golomb';
            N           = str2double(get(handles.edit_length,'string'));
        case 3
            code_type   = 'p1';
            contents    = cellstr(get(handles.popupmenu_length,'String'));
            N           = str2double(contents{get(handles.popupmenu_length,'Value')});
        case 4
            code_type   = 'p2';
            contents    = cellstr(get(handles.popupmenu_length,'String'));
            N           = str2double(contents{get(handles.popupmenu_length,'Value')});
        case 5
            code_type   = 'px';
            contents    = cellstr(get(handles.popupmenu_length,'String'));
            N           = str2double(contents{get(handles.popupmenu_length,'Value')});
        case 6
            code_type   = 'p4';
            N           = str2double(get(handles.edit_length,'string'));
        case 7
            code_type   = 'chu';
            N           = str2double(get(handles.edit_length,'string'));
        case 8
            code_type   = 'random polyphase ';
            N           = str2double(get(handles.edit_length,'string'));
    end
    
else % binary
    strcd   = strcd + 10;
    switch strcd
        case 11 % barker
            contents    = cellstr(get(handles.popupmenu_length,'String'));
            N           = str2double(contents{get(handles.popupmenu_length,'Value')});            
            code_type   = 'barker';
        case 12 % m-seq
            contents    = cellstr(get(handles.popupmenu_length,'String'));
            N           = str2double(contents{get(handles.popupmenu_length,'Value')});            
            code_type   = 'm-seq';
        case 13 % gold
            contents    = cellstr(get(handles.popupmenu_length,'String'));
            N           = str2double(contents{get(handles.popupmenu_length,'Value')});            
            code_type   = 'gold';
        case 14 % kasami
            contents    = cellstr(get(handles.popupmenu_length,'String'));
            N           = str2double(contents{get(handles.popupmenu_length,'Value')});            
            code_type   = 'kasami';
        case 15 % random
            N           = str2double(get(handles.edit_length,'string'));
            code_type   = 'random binary';
        case 16 % all one
            N           = str2double(get(handles.edit_length,'string'));
            code_type   = 'all one';
    end

end

[ x ] = mcode( strcd , N  );

guiplt( x, handles );