function [ Angle, AngularVelocity, Time, Input] = readData( filename )
%READDATA Summary of this function goes here
%   Detailed explanation goes here

FID = fopen(filename,'r');
if FID == -1
    'ERROR OPENING FILE'
    Angle = 0;
    AngularVelocity = 0;
    Input = 0;
    return;
end
[A] = fscanf(FID,'%f,%f,%f,%f,');
fclose(FID);

N=length(A);
j = 0;
for i=1:4:N;
    j = j + 1;
    Angle(j) = A(i,:);
    AngularVelocity(j) = A(i+1,:);
    Time(j) = A(i+2,:);
    Input(j) = A(i+3,:);
end

%Time = Time - Time(1);
%Time = Time/1000;
end
