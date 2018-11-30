BUFFER_SIZE = 34;
X_RANGE = 0.5;
PAUSE_TIME = 0.0001;

maxValue = 0;
minValue = 0;
time = 0;

system('./start-demo.sh &');
%pause(1);

fid=fopen('data_final.txt');
while(1)
    f = -1;
    pause(PAUSE_TIME);
    while(f == -1)
        f=fgets(fid);
        if(length(f) ~= BUFFER_SIZE)
            f = -1;
        end
    end
    s = sscanf(f, '%f %f %f %f');
    x = s(1);
    time = x;
    if(x < time), x = x + time, end
    if(x == 0) 
        hold off
        title('\bfECG Reading')
        xlabel('Time (s)')
        ylabel('Voltage (mV)')
        grid on
    end
    v1 = s(2);
    if v1 > maxValue, maxValue = v1, end
    if v1 < minValue, minValue = v1, end 
    v2 = s(3);
    if v2 > maxValue, maxValue = v2, end
    if v2 < minValue, minValue = v2, end
    v3 = s(4);
    if v3 > maxValue, maxValue = v3, end
    if v3 < minValue, minValue = v3, end
   
    plot(x, v1, 'r.')
    hold on
    plot(x, v2, 'g.')
    hold on
    plot(x, v3, 'b.')
    hold on
    axis([(x-X_RANGE) (x+X_RANGE) minValue maxValue])
end

hold off
fclose(fid);
