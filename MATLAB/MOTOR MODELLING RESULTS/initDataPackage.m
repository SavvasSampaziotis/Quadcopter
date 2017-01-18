% Initialises a Data Package used in controller workspace

clear;

[a1, ad1, T1, u1, add1, F1] = parse('Pendulum_Ramp_100.csv');

[a2, ad2, T2, u2, add1, F2] = parse('Pendulum_Step_30_70.csv');

[a3, ad3, T3, u3, add1, F3] = parse('Pendulum_AC_4000.csv');

[a4, ad4, T4, u4, add1, F4] = parse('Pendulum_AC_15000.csv');

[a5, ad5, T5, u5, add1, F5] = parse('Pendulum_AC_1000.csv');

clear add1
save('TestData');
'data package saved'
%clear 