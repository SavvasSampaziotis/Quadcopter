clear;
%% Reference Model
Am = [0,1;
    -100, -20];
Bm = [0; 2.8];

K = [100-23, 20]/2.8;
Kr = 100/2.8;
r = @(t) pi/4 + pi/6*sign(sin(t/3));
r = @(t) 1*Kr;

%% Adaptation Coefficients and ODE
tic
delta = 0.0001;
X0 = [0,0, 0.1,0,0];
[t,x] = ode15s(@sys2, [0,6], X0, [], Am, Bm, K, delta, r, @motorModelA );
toc


%% Plot Results
subplot(2,1,1);
plot(t, x(:,[1,3]));
legend('xm1','x1','location', 'northwest');
title('Απόκριση εκκρεμούς');
xlabel('sec')
ylabel('rad');

subplot(2,1,2);
for i=1:length(t)
    e = x(i,[3,4])'-x(i,[1,2])';
    Be = Bm'*e;
    V0 = -sign(Be)*abs(r(t(i)));
    if abs(Be) < delta
        V = V0*abs(Be/delta);
    else
        V = V0;
    end
    u(i) = -K(1)*x(i,3)-K(2)*x(i,4) + V;
    if u(i) > 100
        u(i) = 100;
    elseif u(i) < 0
        u(i) = 0;
    end
    s(i) = Be;
end
plot(t, u); %, t, s);
title('Είσοδος ESC');
xlabel('sec')
ylabel('PWM [%]');
