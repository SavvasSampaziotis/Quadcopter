function [ a, b ] = calcParams()

mShaft = 0.100;
mMotor = 0.100;
mWeight = 0.625;

lShaft = 0.48; 
lMotor = 0.385; %0.33;
lWeight = 0.48-0.05;

g = 9.81;
I = mMotor*lMotor*lMotor + mWeight*lWeight*lWeight + mShaft*lShaft*lShaft/3;

msg = 'ö" +a*sin(ö) = b*F '
a = (mMotor*lMotor + mWeight*lWeight + mShaft*lShaft/2)*g/I;
b = lMotor/I;


M = (mMotor + mWeight + mShaft);
R = (mMotor*lMotor + mWeight*lWeight + mShaft*lShaft/2)/M;
L = I/M/R;
T = 2*pi*sqrt(L/g)


%clear mShaft mWeight mMotor lShaft lMotor lWeight R msg
end