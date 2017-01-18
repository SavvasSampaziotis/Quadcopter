
subplot(3,1,1);
plot(a);
title('Γωνία Εκκρεμούς');
ylabel('Μοίρες');

subplot(3,1,2);
plot(u);
title('Είσοδος στον Κινητήρα');
ylabel('PWM %');

subplot(3,1,3);
plot(F);
title('Thrust');
xlabel('Δειγματα');
ylabel('F - Newton');
