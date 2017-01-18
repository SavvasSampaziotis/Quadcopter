
%load('TestData');

a = -a2;
ad = -ad2;
T = T2;
u = u2;
F = F2;
Xo = [a(1)*pi/180, ad(1)*pi/180, F(1)];

[t,x] = ode23s(@pendufun, [0,T(length(T))], Xo ,[], T, u);

subplot(3,2,1);
plot(t, x(:,1)*180/pi, T, a);
ylabel('deg');
title('Angle of Pendulum');

subplot(3,2,3); 
plot(t, x(:,2)*180/pi, T, ad);
title('Angular Velocity of Pendulum');
ylabel('[deg / sec]');

subplot(3,2,5);
plot(t ,x(:,3), T, F);
title('Thrust');
ylabel('[Nt]');
xlabel('time [sec]');

clear

load('TestData');

a = -a4;
ad = -ad4;
T = T4;
u = u4;
F = F4;
Xo = [a(1)*pi/180, ad(1)*pi/180, F(1)];

[t,x] = ode23s(@pendufun, [0,T(length(T))], Xo ,[], T, u);

subplot(3,2,2);
plot(t, x(:,1)*180/pi, T, a);
ylabel('deg');
title('Angle of Pendulum');

subplot(3,2,4); 
plot(t, x(:,2)*180/pi, T, ad);
title('Angular Velocity of Pendulum');
ylabel('[deg / sec]');

subplot(3,2,6);
plot(t ,x(:,3), T, F);
title('Thrust');
ylabel('[Nt]');
xlabel('time [sec]');