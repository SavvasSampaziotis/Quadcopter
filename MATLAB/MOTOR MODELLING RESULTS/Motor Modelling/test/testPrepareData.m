%{

 ετοιμάζουμε τα data. Θυμήσου να βάλεις ονοματάκια, μονάδες μέτρησεις,
και το ΣΗΜΑΝΤΙΚΟΤΕΡΟ, απαρίθμηση πειράματος
z.ExperimentName = 'myExp 1'

%}

z1 = iddata(y1,u1',0.001);
z1.InputUnit ={'pwm %'};
z1.OutputUnit ={'N'};
z1.ExperimentName = 'Dummy System 1';    

z2 = iddata(y2,u2',0.001);
z2.InputUnit ={'pwm %'};
z2.OutputUnit ={'N'};
z2.ExperimentName = 'Dummy System 2';    

z3 = iddata(y3,u3',0.001);
z3.InputUnit ={'pwm %'};
z3.OutputUnit ={'N'};
z3.ExperimentName = 'Dummy System 3';    

plot(z3(:,1));



