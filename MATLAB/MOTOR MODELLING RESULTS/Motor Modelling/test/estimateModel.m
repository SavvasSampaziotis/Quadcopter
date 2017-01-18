%{
 φτιάχνουμε σειρά μοντέλων και αξιολογούμε. 
%}
% για zStep:  np = 3, nz = 0
% για AC1000: np = 3, nz = 0


sysEst1 = tfest(zAC1000, 3, 0);

sysEst = sysEst1*1.1;

figure(1)
grid on

subplot(2,2,1); 
Ts = zStep.Ts;
u = zStep.u;
T = Ts*(0:1:length(u)-1);
[y,~] = lsim( sysEst, u , T );
plot( T, zStep.y, T, y);
grid on

subplot(2,2,2);
Ts = zRamp.Ts;
u = zRamp.u;
T = Ts*(0:1:length(u)-1);
[y, ~] = lsim( sysEst, u , T );
plot( T, zRamp.y, T, y);

grid on
subplot(2,2,3);
Ts = zAC9500.Ts;
u = zAC9500.u;
T = Ts*(0:1:length(u)-1);
[y, ~] = lsim( sysEst, u , T );
plot( T, zAC9500.y, T, y);
grid on

subplot(2,2,4);
Ts = zAC1000.Ts;
u = zAC1000.u;
T = Ts*(0:1:length(u)-1);
[y, ~] = lsim( sysEst, u , T );
plot( T, zAC1000.y, T, y);
grid on



