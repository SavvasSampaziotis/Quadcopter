function [a, ad, T, u, add, F] = window(a, ad, T, u, add, F, iMin, iMax)
%WINDOW Summary of this function goes here
%   Detailed explanation goes here

if(iMax == 0)
    iMax = length(T);
end

if(iMin == 0)
    iMin = 1;
end

v = iMin:1:iMax;

a = a(v);
ad = ad(v);
T = T(v); 
T = T - T(1);
u = u(v);
add = add(v);
F = F(v);

end

