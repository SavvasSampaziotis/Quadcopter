clear
%[a, ad, T, u] = readData('Pendulum_AC_4000.csv');
[a, ad, T, u] = readData('Pendulum_AC_3500.csv');
[a, ad, T, u] = normalise(a, ad, T, u);
[F, add] = calcThrust(a, ad, T);
N = length(T);

Fm = F - mean(F);
plot(T, u - 55, T, Fm);
grid on;

Gain = max(Fm)/15;
GainDB = 20*log10(Gain)
