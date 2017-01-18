function [ a, f, b] = calcParams()

mShaft = 0.100;
mMotor = 0.100;
mWeight = 0.625;

lShaft = 0.48; 
lMotor = 0.385; %0.33;
lWeight = 0.48-0.05;

g = 9.81;
I = mMotor*lMotor*lMotor + mWeight*lWeight*lWeight + mShaft*lShaft*lShaft/3;

msg = ['φ" +a*sin(φ) +f*φ',' = b*F ']
a = (mMotor*lMotor + mWeight*lWeight + mShaft*lShaft/2)*g/I;
b = lMotor/I;

% Εμπειρική διόρθωση απο δοκιμές:
a = a - 0.4;
f = 0.025;

M = (mMotor + mWeight + mShaft);
R = (mMotor*lMotor + mWeight*lWeight + mShaft*lShaft/2)/M;
L = I/M/R;
T = 2*pi*sqrt(L/g)

%%
%{
 I = 0.1381
 R = 0.4015
 L = 0.4168
 M = 0.825
%
%}
end