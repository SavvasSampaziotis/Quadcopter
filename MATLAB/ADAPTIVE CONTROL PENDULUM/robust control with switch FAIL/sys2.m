function [ Zd ] = sys2( t, Z, Am, Bm, K, delta, rf, motorModel )
%SYS Summary of this function goes here
%   Detailed explanation goes here
% x = [ xm1, xm2, x1, x2, f1..fn];

%% Parse state vector Z
xm = Z(1:2);
x = Z(3:4);
f = Z(5:length(Z));

r = rf(t);

%% Update Model

% Reference Model
xm_dot = Am*xm + Bm*r;

%Error
e = x-xm;

% Controller Output
Be = Bm'*e;
V0 = -sign(Be)*abs(r);
if abs(Be) < delta
    V = V0*abs(Be/delta);
else
    V = V0;
end
u = -K*x + V;
if u > 100
    %u = 100;
elseif u < 0
    % u = 0;
end

% Uknown Motor System
df = motorModel(f,u);

% Pendulum
x1d = x(2);
x2d = -23*sin(x(1)) + 2.8*f(1);

%% Build X_dot
Zd = [xm_dot; x1d; x2d;  df];


end
