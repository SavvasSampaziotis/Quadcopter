clear;
Ts = 0.02;



% dummy measurements
%x2 = x1 + 0.2*(rand(size(x1))-0.5);

% real meaurements
[Angle, AngularVel, Tm] = readData('Pendulum_Free_2.csv');
Tm = Tm - Tm(1);
Tm = Tm/1000/1000; % σε secs
Angle = Angle - 90;
%Angle = Angle*pi/180;
%AngularVel = AngularVel*pi/180;

n1 = 300;
n2 = length(Angle);
Tm = Tm(n1:n2);
Angle = Angle(n1:1:n2);
AngularVel = AngularVel(n1:1:n2);

% virtual pendulum, based on structure of real pendulum
%T = [0:Ts:Tm(length(Tm))/1000/1000];
ang1 = max(abs(Angle));

[t1, x1] = ode45(@pendulumEst, Tm, [Angle(1)*pi/180, AngularVel(1)*pi/180], 0, 0);
x1 = x1*180/pi;

%plot(t1,x1);

grid on;

subplot(3,1,2); 
%plot(t1,x1);
plot(t1,x1(:,1),Tm, Angle);
title('Γωνία');
grid on;

subplot(3,1,1); 
%plot(Tm,Angle,Tm, AngularVel);
plot(t1,x1(:,2),Tm, AngularVel);
title('Γωνιακή Ταχύτητα');
grid on;

error = Angle - x1(:,1)';
error_dot = AngularVel - x1(:,2)';
subplot(3,1,3); plot(Tm,error, Tm, error_dot);
title('Σφάλμα συστήματος-μοντέλου');
grid on;