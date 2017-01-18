%parseall;
%load('C:\Users\Savvas\Google Drive\Quadcopter\MATLAB\MOTOR MODELLING NEW\Data Batches\free.mat');
%plot(F);

%[a, ad, T, u] = readData('Pendulum_Step_30_70.csv');
%[a, ad, T, u] = readData('Pendulum_AC_4000.csv');
[a, ad, T, u,] = parse('Pendulum_Free_2.csv');
%
a = a - 90;
%a = a*pi/180;
%ad = ad*pi/180;
T = T/1000/1000;
T = T - T(1);
ad = denoise(ad, 4);
[F, add] = calcThrust(a,ad,T);
plot(F);

return;
n = 1:length(a);

figure(1);
clf;
subplot(2,3,1); plot(a); title('a');
subplot(2,3,2); plot(a); title('a denoised');
subplot(2,3,3); plot(abs(a-a2)); title('a - error');

subplot(2,3,4); plot(ad); title('ad');
subplot(2,3,5); plot(ad2); title('ad denoised');
subplot(2,3,6); plot(abs(ad2-ad)); title('ad - error');

figure(2);  
clf;
subplot(2,2,1); plot(n,add,n,add2); title('add');
subplot(2,2,2); plot(abs(add2-add)); title('add - error');

subplot(2,2,3); plot(n,F,n,F2); title('F');
subplot(2,2,4); plot(abs(F-F2)); title('F - error');






