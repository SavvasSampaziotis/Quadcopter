function [ df ] = motorModelA( f, u )
%MOTORMODELA 1st degree linear model of ESC-MOTOR-PROP system
% Ts = 0.5 sec
% Static Gain: 0.07 Nt/PWM
ts = 0.5;
a = 4/ts;
b = 7*a/100;

df  = -a*f + b*u;
end

