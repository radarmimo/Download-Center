function add2table( x , code_type ,t,handles )
if isempty(x)
    return;
end
N       = length(x);
if get(handles.checkbox_periodic,'value')
    [ r_tilde]  = pcorr( x );
    psl         = max(abs(r_tilde(1:N-1)));
    isl         = sum(abs(r_tilde(1:N-1)).^2);   
    PSLRdB      = 10*log10(psl^2/N^2);
    ISLRdB      = 10*log10(isl/N^2);
else
    [ psl,isl,PSLRdB,ISLRdB ] = pslisl( x );
end


tbldata = {num2str(N), code_type , num2str(psl) , num2str(isl) , num2str(PSLRdB),num2str(ISLRdB),num2str(t),num2str(x.')};

tmpdt   = get(handles.uitable1,'data');
if isempty(tmpdt)
    set(handles.uitable1,'data',tbldata)
    return
end
if strcmp(tmpdt(1,1) , '') ~= 1
    l            = size(tmpdt,1);
    tmpdt(l+1,:) = tbldata;
else
    tmpdt       = tbldata;
end
set(handles.uitable1,'data',tmpdt)

end

