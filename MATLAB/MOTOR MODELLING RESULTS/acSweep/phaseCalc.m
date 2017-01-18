function [ phase ] = phaseCalc( u, F, Tu_zc, Tf_zc, T_period)
%PHASECALC Summary of this function goes here
%   Detailed explanation goes here
%Tu_zc = zeroCrossDetector(u, Tspan);
%Tf_zc = zeroCrossDetector(F, Tspan);

Lu = length(Tu_zc);
Lf = length(Tf_zc);
if Lu < Lf
    Tf_zc = Tf_zc(1:Lu);
elseif Lf < Lu
    Tu_zc = Tu_zc(1:Lf);
end
Dt = mean(Tf_zc - Tu_zc);
if(Tf_zc(1) < Tu_zc(1))
    Dt = T_period / 2 - abs(Dt)    
end

%if(Dt < 0);
%    Dt = T_period / 2 + Dt
%end

phase = -Dt*2*pi/T_period;
phase = phase*180/pi;
end

