% https://www.mathworks.com/help/matlab/serial-port-devices.html?requestedDomain=www.mathworks.com

delete(instrfindall);

% If you have Instrument Control Toolbox you can also try >>info =instrhwinfo('serial'), to get all the information about serial ports.
clear;
ASA_PC = serial('com9');
set(ASA_PC,'BaudRate',38400);
set(ASA_PC,'InputBufferSize',5000);

set(ASA_PC, 'FlowControl', 'none');
set(ASA_PC, 'Parity', 'none');
set(ASA_PC, 'DataBits', 8);
set(ASA_PC, 'StopBit', 1);
set(ASA_PC, 'Timeout',1000);

fopen(ASA_PC);
i = 1;
a = 1;
while 1
    if ASA_PC.BytesAvailable > 0
        data = fgets(ASA_PC);
        fprintf('i = %d,BytesAvailable = %d : %s\n',i,ASA_PC.BytesAvailable);
        data


        if mean( data(1:5) == 'Start' ) == 1
            fprintf(ASA_PC,'%d\n',1);
        end

        if mean( data(1:7) == 'RareDeg' ) == 1
            [m,deg] = TEST();
            fprintf(ASA_PC,'%d\n',round(deg*100));
        end

        if mean( data(1:7) == 'FrontDeg' ) == 1
            [m,deg] = TEST();
            fprintf(ASA_PC,'%d\n',round(deg*100));
        end

        if mean( data(1:3) == 'End' ) == 1
            break
        end
    end
    pause(0.2);
    i=i+1;
end

% fprintf(ASA_PC,'*IDN?')
% out = fscanf(ASA_PC);
fclose(ASA_PC)
delete(ASA_PC)
clear ASA_PC

%
