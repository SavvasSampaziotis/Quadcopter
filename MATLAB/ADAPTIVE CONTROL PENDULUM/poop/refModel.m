
poles = [-12,-15,-10];

Gain = abs(prod(poles));
coeff = -poly(poles);
A = [ 0,1,0; 0,0,1; coeff(4), coeff(3), coeff(2)];
B = [0; 0; Gain];
C = [1,0,0];

sys = ss(A,B,C,0);

figure(1);
step(sys);

figure(2);
bode(sys);