function [ dx ] = pendulumEst(t, x, F, T )

%F = interp1(T,input,t,'cubic');
F = 0;
a = 23.5365;
a = a - 0.4;
dx = [x(2); -a*sin(x(1)) - 0.025*x(2) + 2.7885*F];

end

