%% Motor Model
load('C:\Users\Savvas\Google Drive\Quadcopter\MATLAB\MOTOR MODELLING RESULTS\Motor Modelling\motorModel2.mat')

motorModel = nlhw7;
clear nlhw7

motorLinear = d2c(motorModel.LinearModel);
motorLinear = ss(motorLinear);
motorInput = motorModel.InputNonlinearity;

%% Pendulum Parameters
mShaft = 0.100;
mMotor = 0.100;
mWeight = 0.625;

lShaft = 0.48; 
lMotor = 0.385; %0.33;
lWeight = 0.48-0.05;

g = 9.81;
I = mMotor*lMotor*lMotor + mWeight*lWeight*lWeight + mShaft*lShaft*lShaft/3;

msg = 'φ" +a*sin(φ) = b*F '
a = (mMotor*lMotor + mWeight*lWeight + mShaft*lShaft/2)*g/I;
b = lMotor/I;

M = (mMotor + mWeight + mShaft);
R = (mMotor*lMotor + mWeight*lWeight + mShaft*lShaft/2)/M;
L = I/M/R; % equal pendulum
%T = 2*pi*sqrt(L/g)
% Για την κατασκευή του μοντέλου στο robotics toolbox :)
clear lShaft lMotor lWeight mMotor mShaft mWeight M R L g I
%%