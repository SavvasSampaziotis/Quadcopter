[a, ad, T, u, add, F] = parse('Pendulum_Ramp_100.csv');

clear a ad add

figure(1);
subplot(1,2,1);
plot(T,u);
grid on
title('������� u')
ylabel('PWM ������� �� %')
xlabel('������ �� sec')

subplot(1,2,2);
plot(T,F);
grid on
title('������ F lift')
ylabel('Newton')
xlabel('������ �� sec')

figure(2);
plot(u,F);
grid on
title('�������������� F-u')
ylabel('Newton')
xlabel('PWM ������� �� %')