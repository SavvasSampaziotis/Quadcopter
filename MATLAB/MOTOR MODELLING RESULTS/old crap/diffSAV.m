function [ Ad, T ] = diffSAV( A, T )
%DIFFSAV Summary of this function goes here
%   Detailed explanation goes here
for i=2:1:30
    P = polyfit(T,A,i);
    A_bar = calcPoly(P,T);
    err = A - A_bar;
    if max(abs(err)) < 0.01
        break;
    end
end
n = length(P)

for i=1:1:length(P)-1
    Pdiff(i) = P(i)*(n-i+1)
end

Ad = calcPoly(Pdiff,T)

end

function [Y]=calcPoly(P,T)
n = length(P);
for i=1:1:length(T)
    Y(i) = 0;
    for j=1:1:length(P)
        Y(i) = Y(i) + P(j)*T(i)^(n-j+1);
    end
end

end

