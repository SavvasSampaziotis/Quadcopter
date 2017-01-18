function [ Zd ] = sys( t, Z, Am, Bm, P, alpha, beta, rf, motorModel )
%SYS Summary of this function goes here
%   Detailed explanation goes here
% x = [ xm1, xm2, x1, x2, K1, K2, Kr1, f1..fn];

%% Parse state vector Z
xm = Z(1:2);
x = Z(3:4);
Ki = Z(5:6)';
Kir = Z(7);
f = Z(8:length(Z));

r = rf(t);
y = [0,1]*P*(xm-x);

%% Adapt Gain

Kp = beta*y*x';
Kid = alpha*y*x';

kpr = beta*y*r;
Kird = alpha*y*r;

K = Ki+ Kp;
kr = Kir + kpr;

%% Update Model

% Reference Model
xm_dot = Am*xm + Bm*r;

% Output Controller
u = K*x + kr*r;
if u > 100
    u = 100;
elseif u < 0
    u = 0;
end
% Uknown Motor System
df = motorModel(f,u);

% Pendulum
x1d = x(2);
x2d = -23*sin(x(1)) + 2.8*f(1);

%% Build X_dot
Zd = [xm_dot; x1d; x2d; Kid'; Kird; df];

end
