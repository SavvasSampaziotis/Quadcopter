function [ a, ad, T, u ] = normalise(a, ad, T, u)
%NORMALISE Summary of this function goes here
%   Detailed explanation goes here

a = a - 90;
T = T - T(1);
T(1) = 0;
T = T/1000/1000;


%a = filter(ones(1,10)/10,1,a);
%ad = filter(ones(1,10)/10,1,ad);
%u = filter(ones(1,20)/20,1,u);
[a,~] = denoise(a,T);
[ad,~] = denoise(ad,T);

end

