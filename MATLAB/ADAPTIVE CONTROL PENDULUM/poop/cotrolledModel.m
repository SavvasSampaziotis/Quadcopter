testModel;
A = testSys.A;
B = testSys.B; % [1,0,0]
C = testSys.C;
K = [6,5,0];
    
finalSys = ss(A - B*K, B, C, 0);

r = pi/3*ones(size(T))*150;

[y,t,z] = lsim(finalSys, r, T, Tr*[0,0,0]');

x = 0*z;
for i=1:1:length(T)
   x(i,:) = Tr^-1*z(i,:)';
end
%x(:,3) = x(:,3)*180/pi;

figure(1);
%subplot(2,1,1); 
plot(t,x);
title('Έλεγχος τέλεια μοντελοποιημένου εκκρεμούς');
legend('Thrust','ω(t)', 'θ(t)');

return
figure(2);
subplot(2,1,2); plot(t,z);
title('Μετασχηματισμένες καταστάσεις');