function [ DT ] = freqZC(Angle, T)
%FREQZC ανίχνευση συχνότητας με zero-crossing detection
%   H DC συνιστώσα πρέπει να έχει αφαιρεθεί απο το σήμα
if Angle(1) > 0
    sign = 1;
else
    sign = 0;
end
k = 0;
for i=1:1:length(Angle)
    if (Angle(i) > 0)
        if sign == 0 % zero crossed!!!
            k = k + 1;
            Tzc(k) = T(i);
            sign = 1;
        end
    elseif Angle(i) < 0
        if sign == 1
            k = k + 1;
            Tzc(k) = T(i);
            sign = 0;
        end
    end
end

if k == 0
    'WARNING: No zeros crossed. Subtract DC component'
else
    DT = diff(Tzc);
end


end

