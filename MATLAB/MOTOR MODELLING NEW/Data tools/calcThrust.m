function [Thrust, Add] = calcThrust(a, ad, T)
% Angle Angular σε μοίρες
%
%Add1 = diff(ad)./diff(T);
N = length(a);
n = (1:N);
%Add = denoise(Add1, 4);

A = 23.5365; % - 0.4;
b = 2.7885;
f = 0.0025;

A = 23.2458;
b = -2.6768;

[Add, error] = diffInterp(ad);
Add = denoise(Add, 4);

%%Thrust = Add(n) + f*ad(n)*pi/180 + A*sin(a(n)*pi/180) + 0.0000001*pi/180*sign(ad(n)).*ad(n).^2;
Thrust = Add*pi/180 + A*sin(a*pi/180);
Thrust = Thrust/b;

Thrust = denoise(Thrust, 4);
end