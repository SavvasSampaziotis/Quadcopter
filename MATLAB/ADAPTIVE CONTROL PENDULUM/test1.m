% This script tests the adaptive controller for various motor-propeller models
clear;
%% Reference Model
Am = [0,1;
    -100, -20];
Bm = [0; 100];

P = lyap(Am', diag([1,1]));

r = @(t) (45 + 15*sign(sin(t/3)))*pi/180;
%r = @(t) 0;

%% Adaptation Coefficients and ODE
alpha = 1500;
beta =  1000;
motorModel = @motorModelA;
X0 = [1,0, 1,0, 0,0,0, zeros(1,1)];
[t,x] = ode45(@sys1, [0,60], X0, [], Am, Bm, P, alpha, beta, r, motorModel );

%% Plot Results
subplot(2,2,1);
plot(t, x(:,[1,3]));
legend('xm1','x1','location', 'northwest');
title('Απόκριση εκκρεμούς');
xlabel('sec')
ylabel('rad');

subplot(2,2,2);
plot(t, x(:,5:7));
legend('k1 [rad/pwm]','k2 [rad/sec/pwm]','kr [rad/rad]', 'location', 'northwest');
title('Απόκριση Προσαρμοζόμενων Κερδών');
xlabel('sec')
ylabel('gain');

subplot(2,2,3);
u = x(:,5).*x(:,3) + x(:,6).*x(:,4) + x(:,7).*r(t);
for i=1:length(u)
    if u(i) > 100
        u(i) = 100;
    elseif u(i) < 0
        u(i) = 0;
    end
end
plot(t, u);
title('Είσοδος ESC');
xlabel('sec')
ylabel('PWM [%]');

subplot(2,2,4);
plot(t, x(:,8:length(X0)));
title('Thrust');
xlabel('sec')
ylabel('Nt');

% min = 1000;
% for alpha=100:100:10000
%     for beta=100:100:10000
%         [t,x] = ode45(@sys1, [0,60], X0, [], Am, Bm, P, alpha, beta, r, motorModel );
%         if(min > norm(x(:,1)-x(:,3)))
%            min = norm(x(:,1)-x(:,3))
%            alphaOpt = alpha
%            betaOpt = beta
%         end
%     end
% end
%[t,x] = ode45(@sys1, [0,60], X0, [], Am, Bm, P, alphaOpt, betaOpt, r, motorModel );