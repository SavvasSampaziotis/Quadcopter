sys = tf(1,[1,10]);
T = 0:0.001:3;
u1 = ones(size(T));
%u(1:1:1000) = 0;
[y1,T] = lsim(sys,u1,T);

u2 = 5*u1;
[y2,T] = lsim(sys,u2,T);

u3 = u1;
u3(1:1:1000) = 0;
u3(2000:1:3001) = 0;
[y3,T] = lsim(sys,u3,T);

% εδω κανονικά parse τα data απο τις μετρήσεις