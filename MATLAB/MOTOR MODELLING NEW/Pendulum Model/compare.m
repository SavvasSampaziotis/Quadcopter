clear; 
load('C:\Users\Savvas\Google Drive\Quadcopter\MATLAB\MOTOR MODELLING NEW\Data Batches\free.mat')

% virtual pendulum, based on structure of real pendulum
[t1, x] = ode45(@pendulumEst, T, [a(1)*pi/180, ad(1)*pi/180],[], 0, 0);
x1 = x(:,1)*180/pi;
x2 = x(:,2)*180/pi;
clear t1 x
grid on;

subplot(2,1,1); 
plot(T ,x1 , T, a);
title('Γωνία');
grid on;

subplot(2,1,2); 
plot(T,x2, T, ad);
title('Γωνιακή Ταχύτητα');
grid on;

%{
error = a - x1(:,1)';
error_dot = ad - x1(:,2)';
subplot(3,1,3); plot(T, ad, T(1:779), diff(a)./diff(T));
title('Σφάλμα ad x2');
grid on;
%}