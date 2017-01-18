clear
%[a, ad, T, u] = readData('Pendulum_AC_4000.csv');
Files = {
    %'Pendulum_AC_30000.csv';
   % 'Pendulum_AC_25000.csv';
    'Pendulum_AC_20000.csv';
    'Pendulum_AC_15000.csv';
    'Pendulum_AC_10000.csv';
    'Pendulum_AC_9500.csv';
    'Pendulum_AC_9000.csv';
    'Pendulum_AC_8500.csv';
    'Pendulum_AC_8000.csv';
    'Pendulum_AC_7500.csv';
    'Pendulum_AC_7000.csv';
    'Pendulum_AC_6500.csv';
    'Pendulum_AC_6000.csv';
    'Pendulum_AC_5000.csv';
    'Pendulum_AC_4500.csv';
    'Pendulum_AC_4000.csv';
    'Pendulum_AC_3500.csv';
    'Pendulum_AC_3000.csv';
    'Pendulum_AC_2500.csv';
    'Pendulum_AC_2000.csv';
    'Pendulum_AC_1000.csv';
    'Pendulum_AC_500.csv';
    }


for i=1:1:length(Files)
    file = char(Files(i));
    [a, ad, T, u, add, F] = parse(file);
     
    N = length(T);
    
    Fm = F - mean(F);
    
    T_temp = file(13:length(file)-4);
    T_period = str2num(T_temp)/1000
    W(i) = 2*pi/T_period;
    
    Tu_zc = zeroCrossDetector(u, T);
    Tf_zc = zeroCrossDetector(Fm, T);
    GainDB(i) = 20*log10(amptCalc(Fm, T, Tf_zc) / 15);
    Phase(i) = phaseCalc(u, Fm, Tu_zc, Tf_zc, T_period);
    
    %figure(2);
    %  hold on
    % plot(T, Fm, T, u-55);
    
    %grid on
end

figure(1);
subplot(2,1,1);
semilogx(W,GainDB);
grid on;
subplot(2,1,2);
semilogx(W, Phase);
grid on;

%clear F N T Fm a ad add u T_temp file i