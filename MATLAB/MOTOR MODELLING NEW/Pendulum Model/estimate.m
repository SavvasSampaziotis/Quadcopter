clear;
%load('C:\Users\Savvas\Google Drive\Quadcopter\MATLAB\MOTOR MODELLING NEW\Data Batches\ac_4000.mat');

[a, ad, T, u, add, F] = parse('Pendulum_Free_from_34.csv');
%
N = length(a);

[add,~] = diffInterp(ad);

n0 = 270;
f0 = 4.5;
F = [f0*ones(1,n0),zeros(1,N-n0)];
plot([F;a]');

%%
%min square method for parameter estimation
%
% �'' = -�*sin(�) + b*F = [a, b]*[-sin�; F]
%

a = a*pi/180;
add = add*pi/180;
PHIPHI = zeros(2,2);
PHITHETA = zeros(2,1);

for i=1:1:N
   phi = [-sin(a(i)); F(i)];
   
   PHIPHI = PHIPHI + phi*phi';
    
   PHITHETA = PHITHETA + phi*add(i);
end

PHIPHI = PHIPHI/N;
PHITHETA = PHITHETA/N;

theta0 = (PHIPHI^-1)*PHITHETA;


%%
%min square method for parameter estimation for FILTERED SYSTEM
%
% �'' = -�*sin(�) + b*F ---> 
% � = [a, b, 1]*[-sin�/�(s); F/�(s); ((�1+�2)�' + �1�2�)/�(s)]
%

a = a*pi/180;
add = add*pi/180;
PHIPHI = zeros(3,3);
PHITHETA = zeros(3,1);

F = 0;
[t,Z] = ode23(@filteredSystem, T, [0,0,0,0,0,0], [], T, a, ad, F);

plot(t,Z);

for i=1:1:N
   phi = [Z(i,1); Z(i,2); Z(i,3)];
   
   PHIPHI = PHIPHI + phi*phi';
    
   PHITHETA = PHITHETA + phi*add(i);
end

PHIPHI = PHIPHI/N
PHITHETA = PHITHETA/N;

theta1 = (PHIPHI^-1)*PHITHETA;
