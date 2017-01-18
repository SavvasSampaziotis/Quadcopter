T = 0:0.01:25;

m = 1;
l = 0.5;
I = m*l*l;
g = 10;


a = m*g*l/I;
b = l/I;

clear m l I g

U = 0.7*T(1:1000)/10;
U = [U,0.7*ones(1,1501)];%+ 0.2*sin(10*T);
U = 0*T;

[t, x] = ode45(@odefun, T, [pi/4,0], [], a, b, T, U);
%u = m*g*sin(x(1:length(t)-1,1)) + I/l*diff(x(:,2))./diff(t);

%[t, x2] = ode45(@odefun2, T, [0,0], [], a, b, T, U);
%u2 = m*g*sin(x2(1:length(t)-1,1)) + I/l*diff(x2(:,2))./diff(t);
%dt = t(1:length(t)-1);


%subplot(1,2,1);  
plot(t,x(:,1))
%subplot(1,2,1);  plot(dt,u ,dt, u2)
%subplot(1,2,2);  plot(dt,u-u2)%
%subplot(1,2,2);  plot(t,x(:,1)-x2(:,1))



