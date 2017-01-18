% Simulation Parameters
%file = 'Pendulum_Step_30_70.csv';
file = 'Pendulum_AC_10.csv';
start = 21;

% calc thrust and stuff
[a, ad, T, u] = readData(file);
[a, ad, T, u] = normalise(a, ad, T, u);
[f,~] = calcThrust(a,ad,T);
N = length(T);
clear a ad add file

% Initial State
f = f(start:N);
T = T(start:N) - T(start);
u = u(start:N);

%model = tf([ 0.3786 ],[ 1, 8/3, 5 ]);
a2 = 1.4469;
a1 = +0;
a0 = 4,4;
A = [0,0,1;0,1,0;-a0,-a1,-a2];
B = [0;0;a0];
C = [1,0,0];
D = 0;
model= ss(A,B,C,D);
b = 0.1018;
c = -1.862;


X0 = [f(start); 0;0];
[ fs, t ] = lsim(model, b*u+c, T, X0);
t = t';
fs = fs';

plot( T, fs, T, f );
%plot(T,f,T,u,T,3.68 + 1.75*sin(0.2*pi*T),T, 55+ 15*sin(0.2*pi*T+0.0242*pi));
%plot(T,f,T,u);
grid on;
