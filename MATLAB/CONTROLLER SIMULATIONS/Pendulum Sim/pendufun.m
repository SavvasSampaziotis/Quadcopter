function [ xd ] = pendufun(t, x, T, U)
%PENDUFUN Το συνολικό σύστημα για το εκκρεμές.
%   Detailed explanation goes here

v = interp1(T,U,t);

u = [-1.6038e-06, 2.6214e-04, 1.2484e-05, 4.6963e-07 ]*[ v^3; v^2 ; v ; 1];

a1 = 23.5365;
b1 = 2.7885;

a2 = 7.439;
b2 = 8*6.706;

xd1 = x(2);
xd2 = -a1*sin(x(1)) + b1*x(3) - 0.2*x(2);
xd3 = -a2*x(3) + b2*u;


xd = [xd1,xd2,xd3]';
end