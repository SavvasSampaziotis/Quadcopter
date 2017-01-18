[a1, ad1, T1, u1] = readData('Pendulum_Constant_25.csv');
[a1, ad1, T1, u1] = normalise(a1, ad1, T1, u1);
%a1s = cmddenoise(a1,'sym4',1);
[F1,add1] = calcThrust(a1, ad1, T1);
N1 = length(add1);

[a2, ad2, T2, u2] = readData('Pendulum_Constant_50.csv');
[a2, ad2, T2, u2] = normalise(a2, ad2, T2, u2);
[F2, add2] = calcThrust(a2, ad2, T2);
N2 = length(add2);

[a3, ad3, T3, u3] = readData('Pendulum_Constant_75.csv');
[a3, ad3, T3, u3] = normalise(a3, ad3, T3, u3);
[F3, add3] = calcThrust(a3, ad3, T3);
N3 = length(add3);

[a4, ad4, T4, u4] = readData('Pendulum_Constant_100.csv');
[a4, ad4, T4, u4] = normalise(a4, ad4, T4, u4);
[F4, add4] = calcThrust(a4, ad4, T4);
N4 = length(add4);

plot(a2)
hold on
plot(ad2, 'red')
plot(add2, 'green')
plot(F2, 'black')
hold off