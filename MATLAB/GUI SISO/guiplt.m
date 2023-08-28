function guiplt( x, handles )
if isempty(x)
    return;
end
axes(handles.axes1);
cla
axes(handles.axes2);
cla
axes(handles.axes3);
cla
axes(handles.axes4);
cla
axes(handles.axes5);
cla
switch get(handles.popupmenu_view,'value')
    case 1
        
        set(handles.axes1,'visible','on')
        set(handles.axes2,'visible','on')
        set(handles.axes3,'visible','off')
        axes(handles.axes1);
        plot(real(x));
        xlabel('code length (N)')
        ylabel('amplitude (real)');        
        grid on;
        axis('tight');
        myboldify
        axes(handles.axes2);
        plot(imag(x));
        grid on;
        xlabel('code length (N)')
        ylabel('amplitude (imaginary)');        
        axis('tight');
        xlabel('code length (N)')
        myboldify
        
    case 2
        set(handles.axes1,'visible','on')
        set(handles.axes2,'visible','on')
        set(handles.axes3,'visible','off')
        axes(handles.axes1);
        plot(abs(x));
        ylim([0 2* max(abs(x))])
        grid on;
        xlabel('code length (N)')
        ylabel('amplitude');
%         axis('tight');
        myboldify
        
        axes(handles.axes2);
        plot(angle(x));        
        ylim([-pi-0.1 pi+0.1])
        grid on;
        ylabel('phase');
%         axis('tight');
        xlabel('code length (N)')
        myboldify
        
    case 3
        set(handles.axes1,'visible','off')
        set(handles.axes2,'visible','off')
        set(handles.axes3,'visible','on')
        axes(handles.axes3);
        
        if get(handles.checkbox_periodic,'value') == 1
            plot(abs(pcorr(x)));
        else
            plot(abs(xcorr(x)));
        end
        
        xlabel('shift(k)');
        ylabel('correlation level')

        grid on;
        axis('tight');
        myboldify

        
end

axes(handles.axes4);
text(0,0,'min \{(\theta) PSL + (1 - \theta) ISL\}')
axes(handles.axes5);
text(0,0,['\theta = ',num2str(get(handles.slider_theta,'Value'))])


end

