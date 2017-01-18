function [ Tzc ] = zeroCrossDetector( signal, T )
%ZEROCROSSDETECTOR returns array T of the zero cross time moments of signal
%   Detailed explanation goes here
signal = signal - mean(signal);
if signal(1) > 0
    sign = 1;
else
    sign = 0;
end
k = 0;
for i=1:1:length(signal)
    if (signal(i) > 0)
        if sign == 0 % zero crossed!!!
            k = k + 1;
            Tzc(k) = T(i);
            sign = 1;
        end
    elseif signal(i) < 0
        if sign == 1
            k = k + 1;
            Tzc(k) = T(i);
            sign = 0;
        end
    end
end
end

