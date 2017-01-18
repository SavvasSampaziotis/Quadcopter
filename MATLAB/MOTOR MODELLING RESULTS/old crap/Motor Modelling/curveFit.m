file = 'Pendulum_AC_5000.csv';

% calc thrust and stuff
[a, ad, T, u] = readData(file);
[a, ad, T, u] = normalise(a, ad, T, u);
[f,~] = calcThrust(a,ad,T);
N = length(T);

% Η F(t) για προσεγγίζεται με την F = 3.68 + 1.75*sin(0.2*pi*t);
% με u(t) = 55 + 15*sin(0.2*pi*t + 0.0242*pi);

% fdd +a1*fd + a0*f = a0*b *u + a0*c;
% με f = b*u + c την dc χαρακτηριστική F-u;

f = 3.68 + 1.75*sin(0.2*pi*T);
fd  = +1.75*cos(0.2*pi*T)*(0.2*pi);
fdd = -1.75*sin(0.2*pi*T)*(0.2*pi)^2;
fddd = -1.75*cos(0.2*pi*T)*(0.2*pi)^3;

u = 55 + 15*sin(0.2*pi*T + 0.0242*pi);

b = 0.1018;
c = -1.862;

a2 = zeros(size(T));
a1 = zeros(size(T));
a0 = zeros(size(T));

for i=3:1:N
        
A = [fdd(i-2), fd(i-2), f(i-2)- b*u(i-2) - c; 
    fdd(i-1),fdd(i-1), f(i-1)- b*u(i-1) - c;
    fdd(i),fdd(i), f(i)- b*u(i) - c];    
%D(i-1) = det(A);
temp = -(A^-1)*[fddd(i-2);fddd(i-1);fddd(i);];
a2(i-2) = temp(1);
a1(i-2) = temp(2);
a0(i-2) = temp(3);

end
%plot(D)
%n = 1:1:N-2;
plot([a0,a1,a2]);
a0 = mean(a0)
a1 = mean(a1)
a2 = mean(a2)












