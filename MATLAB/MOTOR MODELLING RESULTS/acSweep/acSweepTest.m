clear

sys = zpk([],[-10,-20],[10]);

W = 2*pi*[0.1:0.1:1, 2:1:50];


for i=1:1:length(W)
    
    Tspan = [0:2*pi/W(i)/30:2*pi/W(i)*10];
    u = 5*sin(W(i)*Tspan);
    F = lsim(sys,u,Tspan);
    N = length(Tspan);
    Fm = F - mean(F);
    
    
    Fm = Fm(50:length(Tspan));
    u = u(50:length(Tspan));
    Tspan = Tspan(50:length(Tspan));
    
    Tu_zc = zeroCrossDetector(u, Tspan);
    Tf_zc = zeroCrossDetector(Fm, Tspan);
    
    GainDB(i) = 20*log10(amptCalc(Fm, Tspan, Tf_zc)/5);
    
    %μορφοποιώ τα σήματα έτσι ώστε το πρώτο zero cross να το κάνει το u
    if(Tf_zc(1) < Tu_zc(1))
        startIndex = 1
        for j=1:1:length(Tspan)
            if Tspan(j)==Tu_zc(1) % πρώτο zerocross
                startIndex = j;
            end
        end
        Fm = Fm(startIndex:N);
        u = u(startIndex:N);
        Tf_zc = Tf_zc(2:length(Tf_zc));
        Tspan = Tspan(startIndex:N);
    end
    Phase(i) = phaseCalc(u, Fm, Tu_zc, Tf_zc, 2*pi/W(i));
    
    i;
end

figure(1);
subplot(2,1,1);
semilogx(W,GainDB);
title('Gain');
grid on;
subplot(2,1,2);
semilogx(W, Phase);
grid on;

figure(2);
bode(sys);
grid on;

clear F N T Fm a ad add u T_temp file i