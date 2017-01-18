function [ yd , error ] = diffInterp( y )
%DIFFINTERP Summary of this function goes here
%  Η συνάρτηση επαληθεύτηκε, bitch!

N = length(y);
error(1) = 0;
k = 1;
yd = y*0;
y_hat = y*0;
for n=1+k:1:N-k
    
    M(1,:) = [(n-k)^2, n-k, 1];
    M(2,:) = [n^2, n, 1];
    M(3,:) = [(n+k)^2, n+k, 1];
    
    a = (M^-1)*[y(n-k); y(n); y(n+k)]; % συντελεστές πολυωνύμου
    
    y_hat(n) = [n^2, n, 1]*a;
    
    yd(n) = (2*a(1)*n + a(2))*100;
end

for n=1:k
    y_hat(n) = y(n);
    yd(n) = yd(k+1);
end
for n=N-k:N
    y_hat(n) = y(n);
    yd(n) = yd(N-k);
end

%plot(1:N, y, 1:N, y_hat);
for n=1:1:N
    error(n) = abs(y(n) - y_hat(n));
end

if mean(error) > 0.01
    'WARINING. ERROR IS SHIT'
end

end

