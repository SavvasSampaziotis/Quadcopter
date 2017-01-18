
%N = [500,1000,2000,3000,4000,7000];
N=[2000,3000,5000];
Fs = F(N)';
us = u(N)';
U = us;
for i=2:1:length(N)
    U = [U,us.^i];
end

a = (U^-1)*Fs

f = 0;
for i=1:1:length(N)
    f = f + a(i)*u.^i;
end

figure(1);
%subplot(2,1,1);
plot(u,F,u,f);grid on

%subplot(2,1,2);
%plot(u,(F-f)); grid on

clear Fs us U i N
grid on