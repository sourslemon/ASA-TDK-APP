// 參考資料 https://www.mathworks.com/help/matlab/serial-port-devices.html?requestedDomain=www.mathworks.com


ASA_PC = serial('COM6');
set(ASA_PC,'BaudRate',38400);
fopen(ASA_PC);
fprintf(ASA_PC,'*IDN?')
out = fscanf(ASA_PC);
fclose(ASA_PC)
delete(ASA_PC)
clear ASA_PC
