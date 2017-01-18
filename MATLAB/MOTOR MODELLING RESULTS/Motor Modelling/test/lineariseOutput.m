% 1 : DCsweep
% 2 : estimateDCmodel
% 3 : this....

for i=1:1:length(F)
    F_linear(i) = F(i) - a(3)*u(i)^3 - a(2)*u(i)^2; % == a(1)*u(i)
end

%plot(u,F_linear,u,a(1)*u);






clear temp;