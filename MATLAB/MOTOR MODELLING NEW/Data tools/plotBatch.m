
subplot(3,1,1);
plot(a);
title('����� ���������');
ylabel('������');

subplot(3,1,2);
plot(u);
title('������� ���� ��������');
ylabel('PWM %');

subplot(3,1,3);
plot(F);
title('Thrust');
xlabel('��������');
ylabel('F - Newton');
