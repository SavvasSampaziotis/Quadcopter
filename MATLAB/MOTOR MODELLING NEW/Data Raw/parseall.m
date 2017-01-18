%% 
clear;
batchName = 'Free Response';
%
[a, ad, T, u, add, F] = parse('Pendulum_Free_2.csv');
iMin = 310;
iMax = 0;
[a, ad, T, u, add, F] = window(a, ad, T, u, add, F, iMin, iMax);
Ts = mean(diff(T));
clear iMin iMax;
save('Data Batches\free');
clear;

%%
batchName = 'Step Response 30% -> 70%';
%
[a, ad, T, u, add, F] = parse('Pendulum_Step_30_70.csv');
iMin = 120;
iMax = 0;
[a, ad, T, u, add, F] = window(a, ad, T, u, add, F, iMin, iMax);
Ts = mean(diff(T));
clear iMin iMax;
save('Data Batches\step_30_70');
clear;

%%
batchName = 'Ramp Response 0% -> 100%';
%
[a, ad, T, u, add, F] = parse('Pendulum_Ramp_100.csv');
iMin = 0;
iMax = 0;
[a, ad, T, u, add, F] = window(a, ad, T, u, add, F, iMin, iMax);
Ts = mean(diff(T));
clear iMin iMax;
save('Data Batches\ramp_100');
clear;

%%
batchName = 'AC Response T=500ms';
%
[a, ad, T, u, add, F] = parse('Pendulum_AC_500.csv');
iMin = 40;
iMax = 0;
[a, ad, T, u, add, F] = window(a, ad, T, u, add, F, iMin, iMax);
Ts = mean(diff(T));
clear iMin iMax;
save('Data Batches\ac_500');
clear;

%%
batchName = 'AC Response T=1000ms';
%
[a, ad, T, u, add, F] = parse('Pendulum_AC_1000.csv');
iMin = 60;
iMax = 0;
[a, ad, T, u, add, F] = window(a, ad, T, u, add, F, iMin, iMax);
clear iMin iMax;
Ts = mean(diff(T));
save('Data Batches\ac_1000');
clear;

%%
batchName = 'AC Response T=2000ms';
%
[a, ad, T, u, add, F] = parse('Pendulum_AC_2000.csv');
iMin = 44;
iMax = 0;
[a, ad, T, u, add, F] = window(a, ad, T, u, add, F, iMin, iMax);
clear iMin iMax;
Ts = mean(diff(T));
save('Data Batches\ac_2000');
clear;

%%
batchName = 'AC Response T=3000ms';
%
[a, ad, T, u, add, F] = parse('Pendulum_AC_3000.csv');
iMin = 136;
iMax = 0;
[a, ad, T, u, add, F] = window(a, ad, T, u, add, F, iMin, iMax);
clear iMin iMax;
Ts = mean(diff(T));
save('Data Batches\ac_3000');
clear;

%%
batchName = 'AC Response T=4000ms';
%
[a, ad, T, u, add, F] = parse('Pendulum_AC_4000.csv');
iMin = 10;
iMax = 0;
[a, ad, T, u, add, F] = window(a, ad, T, u, add, F, iMin, iMax);
clear iMin iMax;
Ts = mean(diff(T));
save('Data Batches\ac_4000');
clear;

%%
batchName = 'AC Response T=5000ms';
%
[a, ad, T, u, add, F] = parse('Pendulum_AC_5000.csv');
iMin = 6;
iMax = 0;
[a, ad, T, u, add, F] = window(a, ad, T, u, add, F, iMin, iMax);
clear iMin iMax;
save('Data Batches\ac_5000');

%%
batchName = 'AC Response T=6000ms';
%
[a, ad, T, u, add, F] = parse('Pendulum_AC_6000.csv');
iMin = 10;
iMax = 0;
[a, ad, T, u, add, F] = window(a, ad, T, u, add, F, iMin, iMax);
clear iMin iMax;
Ts = mean(diff(T));
save('Data Batches\ac_6000');
clear;
%%
batchName = 'AC Response T=7000ms';
%
[a, ad, T, u, add, F] = parse('Pendulum_AC_7000.csv');
iMin = 5;
iMax = 0;
[a, ad, T, u, add, F] = window(a, ad, T, u, add, F, iMin, iMax);
clear iMin iMax;
Ts = mean(diff(T));
save('Data Batches\ac_7000');
clear;

%%
batchName = 'AC Response T=8000ms';
[a, ad, T, u, add, F] = parse('Pendulum_AC_8000.csv');
iMin = 10;
iMax = 0;
[a, ad, T, u, add, F] = window(a, ad, T, u, add, F, iMin, iMax);
clear iMin iMax;
Ts = mean(diff(T));
save('Data Batches\ac_8000');
clear;

%%
batchName = 'AC Response T=10000ms';
%
[a, ad, T, u, add, F] = parse('Pendulum_AC_10000.csv');
iMin = 5;
iMax = 0;
[a, ad, T, u, add, F] = window(a, ad, T, u, add, F, iMin, iMax);
clear iMin iMax;
Ts = mean(diff(T));
save('Data Batches\ac_10000');
clear;
