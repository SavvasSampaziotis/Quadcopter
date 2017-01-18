function [Thrust, Add2] = calcThrust(Angle, AngularVel, T)
% Angle Angular σε μοίρες
%
Add = diff(AngularVel)./diff(T);
%Add = cmddenoise(Add,'sym4',1);
%Add1 = filter(ones(1,10)/10,1,Add);
Add2 = denoise(Add, T(1:length(T)-1));

a = 23.5365;
b = 2.7885;

Thrust = -(Add2*pi/180 + a*sin(Angle(1:length(Angle)-1  )*pi/180))/ b;

Add2 = [Add2,Add2(length(Add2))];
Thrust = [Thrust,Thrust(length(Thrust))];

end