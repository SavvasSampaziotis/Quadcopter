function [ mag, phase ] = magCalc(y, u, t, t1, t2)
%MAGCALC Summary of this function goes here
%   Detailed explanation goes here


% calc indeces
k1 = -1;
k2= -1;
for i=1:1:length(t)
    if (k1 < 0)&&(t(i) >= t1)
        k1 = i;
    end
    
    if (k2 < 0)&&(t(i) >= t2)
        k2 = i;
        break;
    end
end

y = y(k1:k2);
t = t(k1:k2);

DC = mean(y);
y = y - DC;
plot(t,y);

mag = max(y) - min(y);
phase = 0;

end

