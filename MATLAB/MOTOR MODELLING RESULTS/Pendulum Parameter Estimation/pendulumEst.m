function [ dx ] = pendulumEst(t, x, F, T )

%F = interp1(T,input,t,'cubic');
F = 0;
dx = [x(2); -23.5365*sin(x(1)) + 2.7885*F];

end

