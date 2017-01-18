% προσεγγιστικές παράμετροι του μοντέλου
a = 23;
b = 2.7;
c = 8;
d = c*0.750/100;

A = [0, 1, 0; -a, 0, b; 0, 0, -c];
B = [0;0;d];
C = [1,0,0];

% Controllability Matrix
M = [B, A*B, A*A*B];

% Controllability Matrix of Model in Canonical Controllable Form
p = -poly(diag(eigs(A)));
A_bar=[p(2:4); 1, 0, 0; 0, 1, 0];
B_bar = [1;0;0];
M_bar = [B_bar, A_bar*B_bar, A_bar*A_bar*B_bar];

% Transformation
Tr = M_bar*(M^-1);

% Model in Canonical Controllable Form
testSys = ss(Tr*A*Tr^-1, Tr*B, C*Tr^-1, 0);

T = 0:0.001:10;
u = 55*ones(size(T));

return
T = 0:0.001:10;
u = 100*ones(size(T));
% 
% [y,t,x] = lsim(testSys, 0*u, T, Tr*[pi/4,0,0]');
% z = 0*x;
% for i=1:1:length(T)
%    z(i,:) = Tr^-1*x(i,:)';
% end
% 
% subplot(2,1,1); plot(t,x);
% 
% %z(:,1) = z(:,1)*180/pi;
% subplot(2,1,2); plot(t,z);



