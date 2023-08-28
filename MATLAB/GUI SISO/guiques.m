function [ x0 , CodeIndex] = guiques( str, hObject, handles)
x0          = [];
Indices     = hObject.UserData;
if isempty(Indices)
    row = 1;
else
    row         = Indices(1);
end

status = questdlg(['You will run the algorithm ',str,' intialized by sequence #',num2str(row),' of the table, right? (Run-time dependens on the algorithm and code length)']);
if strcmp(status,'Yes')
    tmpdt   = get(handles.uitable1,'data');
    x0      = str2num(cell2mat(tmpdt(row,end)));
    x0      = x0(:);
end
CodeIndex = row;
end

