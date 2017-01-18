function [a, ad, T, u, add, F] = parse( file )
%PARSE Summary of this function goes here
%   Detailed explanation goes here

[a, ad, T, u] = readData(file);
[a, ad, T, u] = normalise(a, ad, T, u);
[F, add] = calcThrust(a, ad, T);

end

