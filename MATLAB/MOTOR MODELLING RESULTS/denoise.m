function [ y, t2] = denoise( x, t )
%DENOISE Summary of this function goes here
%   Detailed explanation goes here
fc = 8;
p = 2*pi*fc;

filt = zpk([],[-p, -p], [p*p]);

[y, t2] = lsim(filt, x, t);
y = y';
t2 = t2';
end

