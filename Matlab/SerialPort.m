% https://www.mathworks.com/help/matlab/serial-port-devices.html?requestedDomain=www.mathworks.com

delete(instrfindall);

% If you have Instrument Control Toolbox you can also try >>info =instrhwinfo('serial'), to get all the information about serial ports.
clear;
ASA_PC = serial('com8');
set(ASA_PC,'BaudRate',38400);
set(ASA_PC,'InputBufferSize',5000);

set(ASA_PC, 'FlowControl', 'none');
set(ASA_PC, 'Parity', 'none');
set(ASA_PC, 'DataBits', 8);
set(ASA_PC, 'StopBit', 1);
set(ASA_PC, 'Timeout',100);

fopen(ASA_PC);

while (1) {
    data = fgets(ASA_PC);
    if ( data[1] == 's') {
        % 開始
    }
    if ( data[1] == 'l') {
        % 線 斜率
    }
    if ( data[1] == 'r') {
        % 紅點
    }
    if ( data[1] == 'c') {
        % 水杯
    }
    if ( data[1] == 'k') {
        % 可樂
    }
    if ( data[1] == 'a') {
        % 方糖
    }
}

fprintf(ASA_PC,'*IDN?')
out = fscanf(ASA_PC);
fclose(ASA_PC)
delete(ASA_PC)
clear ASA_PC
