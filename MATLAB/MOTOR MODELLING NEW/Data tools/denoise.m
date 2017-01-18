function [ y ] = denoise( x, k )
%DENOISE

%{
Fs = 1/Ts;                    % sample rate in Hz
N = length(x);                     % number of signal samples
%rng default;
% Design a 70th order lowpass FIR filter with cutoff frequency of 75 Hz.
Fnorm = 75/(Fs/2);           % Normalized frequency
df = designfilt('lowpassfir','FilterOrder',70,'CutoffFrequency',Fnorm);
%}

N = length(x);
%n = [-k:1:k];
%filt = cos(n/k*pi/4)';
for i=1:1:k
  %  y(i) = sum( x(1:1:i+k).*filt ); % dot product
  y(i) = mean(x(1:1:i+k));
end
for i=k+1:1:N-k
   %y(i) = x(i-k:1:i+k)*filt; 
    y(i) = mean(x(i:1:i+k));
end
for i=N-k+1:1:N
  % y(i) = x(i-k:1:N)*filt; 
   y(i) = mean(x(i:1:N));
end

end

