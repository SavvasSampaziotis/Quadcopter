function [ df ] = motorModelB( f, u )
%MOTORMODELA 1st degree linear model of ESC-MOTOR-PROP system
% Ts = 0.5 sec
% Static Gain: 0.07 Nt/PWM
ts = 0.3;
w = 4/ts;
a1 = w*w;
a2 = 2*w;
b = 7*a1/100;

df1 = f(2);
df2 = -a1*f(1) - a2*f(2) + b*u;

df = [df1;df2];
end

