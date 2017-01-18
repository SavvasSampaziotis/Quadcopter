function [a, ad, T, u, add, F] = parse( file )

[a, ad, T, u] = readData(file);

a = a - 90;
T = T/1000/1000;
T = T - T(1);

[a] = denoise(a, 4);
[ad] = denoise(ad, 4);

[F, add] = calcThrust(a, ad, T);

end

