

%a0 = 71.86 + a1*a1/4;
a1 = 8/3;
a0 = 5;

b = 5.3*a0/70;

G = tf([b],[1,a1,a0])
Gss = ss(G);

n = 120:1:2192;
Tsim = T(n) - T(n(1));
U = 70*ones(size(Tsim));

Fsim = lsim(Gss, U, Tsim, [0,1.36]);

plot(Tsim, Fsim, Tsim, F(n), Tsim, 5.3*1.05,Tsim, 5.3*0.95)
grid on