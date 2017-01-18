[a, ad, T, u, add, F] = parse('Pendulum_Step_30_70.csv');
Ts = mean(diff(T));
zStep = iddata(F(10:length(F))' ,u(10:length(F))'   , Ts);
zStep.InputUnit ={'pwm %'};
zStep.OutputUnit ={'Newton'};
zStep.ExperimentName = 'Step Response 30% to 70%';


[a, ad, T, u, add, F] = parse('Pendulum_Ramp_100.csv');
Ts = mean(diff(T));
zRamp = iddata(F',u', Ts);
zRamp.InputUnit ={'pwm %'};
zRamp.OutputUnit ={'Newton'};
zRamp.ExperimentName = 'Ramp Response 0% to 100%';    
 %{
Προσαρμόζει τα δεδομένα για τον System Identification Toolbox.

----Το μοντέλο έχει προσδιορισθει
        Το session εχει αποθηκευτεί ως HW model - success, 
        και το μοντέλο ως idnlhw object με όνομα motorModel.

θυμήσου να μετατρέψεις το μοντέλο σε Continous Time πριν κάνεις τίποτα
%}

[a, ad, T, u, add, F] = parse('Pendulum_AC_9500.csv');
Ts = mean(diff(T));
zAC9500 = iddata(F(10:length(F))' ,u(10:length(F))'   , Ts);
zAC9500.InputUnit ={'pwm %'};
zAC9500.OutputUnit ={'Newton'};
zAC9500.Period = 9.5;
zAC9500.ExperimentName = 'AC Response at 55% +- 15% T=9.5sec';    


[a, ad, T, u, add, F] = parse('Pendulum_AC_1000.csv');
Ts = mean(diff(T));
zAC1000 = iddata(F(10:length(F))' ,u(10:length(F))'   , Ts);
zAC1000.InputUnit ={'pwm %'};
zAC1000.OutputUnit ={'Newton'};
zAC1000.Period = 1;
zAC1000.ExperimentName = 'AC Response at 55% +- 15% T=1sec';     

clear a ad u add T F Ts;