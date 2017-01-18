%% Simulate the online reference model calculation
clear;

%% Model
Am =[0     1
    -100   -20];
Bm =[0;100];
x0 = [0;0];
u = @(t) 1+sin(10*t);
f = @(t,x) Am*x + Bm*u(t);

%% Sim parameters
N = 100;
%Ts = 0.020*ones(1,N); % 20 msec sampling rate
Ts = 0.020 + 0.0005*(rand(1,N)-0.5);
t = (0:1:(N-1)).* Ts;
x = zeros(2,N);

%% Solve with R-K
x(:,1) = x0;
for i=1:(N-1);    
    k = Ts(i);
    k1 = k*f(t(i), x(:,i));
    k2 = k*f(t(i)+k/2, x(:,i)+k1/2);
    k3 = k*f(t(i)+k/2, x(:,i)+k2/2);
    k4 = k*f(t(i+1), x(:,i)+k3);
    x(:,i+1) = x(:,i) + (k1+k2+k3+k4)/6;
end

%% Plot results and error signals
[t_hat,x_hat] = ode45(f,(1:N)*mean(Ts),x0);

subplot(2,1,1);
plot(t_hat,x_hat,t,x);
legend('x1hat','x2hat','x1','x2')

subplot(2,1,2);
plot(t_hat,x_hat-x');
legend('e1','e2')



