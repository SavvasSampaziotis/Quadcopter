clear
load('C:\Users\Savvas\Google Drive\Quadcopter\MATLAB\MOTOR MODELLING RESULTS\Motor Modelling\motorModel2.mat')

motorModel = nlhw7
clear nlhw7

motorLinear = d2c(motorModel.LinearModel);
motorLinear = ss(motorLinear);

motorInput = motorModel.InputNonlinearity;
clear
