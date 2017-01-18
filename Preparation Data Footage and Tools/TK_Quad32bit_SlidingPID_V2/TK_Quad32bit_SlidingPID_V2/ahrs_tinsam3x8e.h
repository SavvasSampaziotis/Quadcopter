//An attitude and heading reference system (AHRS)  By tinnakon 26_05_2557(2014)
//project_Quad 32 bit Arduino Due
//1. stabilized quadrotor 
//by: tinnakon kheowree 
//0860540582
//tinnakon_za@hotmail.com
//tinnakonza@gmail.com
#define Kp 0.22 //0.15  //0.2 1.62	// proportional gain governs rate of convergence to accelerometer/magnetometer
#define Ki 0.122 //0.072 0.096 0.05	// integral gain governs rate of convergence of gyroscope biases
#define Kp_mag 0.25  //0.22
#define Ki_mag 0.112 //0.142
float exInt , eyInt , ezInt ;	// scaled integral error
float q0, q1 , q2 , q3 ;	// quaternion elements representing the estimated orientation
float ahrs_p,ahrs_r,ahrs_y;
float Heading = 0.0;
float setHeading = 0.0;
float previousEx = 0.0;
float previousEy = 0.0;
float previousEz = 0.0;

void ahrs_initialize()
{
  exInt=0.0;
  eyInt=0.0;
  ezInt=0.0;
  q0=1.0;
  q1=0.0;
  q2=0.0;
  q3=0.0;
}
boolean isSwitched(float previousError, float currentError) {
  if ((previousError > 0.0 &&  currentError < 0.0) || (previousError < 0.0 &&  currentError > 0.0)) {
    return true;
  }
  return false;
}
void ahrs_updateMARG(float gx, float gy, float gz, float ax, float ay, float az, float mx, float my, float mz, float G_Dt){

  float norm1,halfT;
  float hx, hy, hz, bx, bz;
  float vx, vy, vz, wx, wy, wz;
  float ex, ey, ez, ezMag;
  
  halfT=G_Dt/2.0;        
  // normalise the measurements
  norm1 = sqrt(ax*ax + ay*ay + az*az);       
  ax = ax / norm1;
  ay = ay / norm1;
  az = az / norm1;
  norm1 = sqrt(mx*mx + my*my + mz*mz);          
  mx = mx / norm1;
  my = my / norm1;
  mz = mz / norm1;         
  // compute reference direction of flux, Earth Frame
  hx = mx*DCM00 + my*DCM01 + mz*DCM02;
  hy = mx*DCM10 + my*DCM11 + mz*DCM12;
  hz = mx*DCM20 + my*DCM21 + mz*DCM22;         
  bx = sqrt((hx*hx) + (hy*hy));
  bz = hz; 
  // estimated direction of gravity and flux (v and w)
  vx = DCM20;//2*(q1q3 - q0q2)
  vy = DCM21;//2*(q0q1 + q2q3)
  vz = DCM22;//q0q0 - q1q1 - q2q2 + q3q3
  wx = bx*DCM00 + bz*DCM20;
  wy = bx*DCM01 + bz*DCM21;
  wz = bx*DCM02 + bz*DCM22;  
  // error is sum of cross product between reference direction of fields and direction measured by sensors
  ex = (ay*vz - az*vy);
  ey = (az*vx - ax*vz);
  ez = (ax*vy - ay*vx);
  //ez = (ax*vy - ay*vx);// + (mx*wy - my*wx)
  ezMag = (mx*wy - my*wx);
  // integral error scaled integral gain
  //exInt += ex*Ki*G_Dt;
  //eyInt += ey*Ki*G_Dt;
  //ezInt += (ez*Ki + ezMag*Ki_mag)*G_Dt;
  //*
  exInt += ex*Ki*G_Dt;
    if (isSwitched(previousEx,ex)) {
    exInt = 0.0;
  }
  previousEx = ex;
  eyInt += ey*Ki*G_Dt;
    if (isSwitched(previousEy,ey)) {
    eyInt = 0.0;
  }
  previousEy = ey;
  float ezi = (ez*Ki + ezMag*Ki_mag);
    ezInt += ezi*G_Dt;
    if (isSwitched(previousEz,ezi)) {
    ezInt = 0.0;
  }
  previousEz = ezi;
  //*/
  // adjusted gyroscope measurements
  gx += (Kp*ex + exInt);
  gy += (Kp*ey + eyInt);
  gz += (Kp*ez + ezMag*Kp_mag + ezInt);
  // integrate quaternion rate and normalise
  q0 = q0 + (-q1*gx - q2*gy - q3*gz)*halfT;
  q1 = q1 + (q0*gx + q2*gz - q3*gy)*halfT;
  q2 = q2 + (q0*gy - q1*gz + q3*gx)*halfT;
  q3 = q3 + (q0*gz + q1*gy - q2*gx)*halfT;  
  // normalise quaternion
  norm1 = sqrt(q0*q0 + q1*q1 + q2*q2 + q3*q3);
  q0 = q0 / norm1;
  q1 = q1 / norm1;
  q2 = q2 / norm1;
  q3 = q3 / norm1;
// auxiliary variables to reduce number of repeated operations
  //float q0q0 = q0*q0;
  float q0q1 = q0*q1;
  float q0q2 = q0*q2;
  float q0q3 = q0*q3;
  float q1q1 = q1*q1;
  float q1q2 = q1*q2;
  float q1q3 = q1*q3;
  float q2q2 = q2*q2;   
  float q2q3 = q2*q3;
  float q3q3 = q3*q3;  
  //direction cosine matrix (DCM), Rotation matrix , Rotated Frame to Stationary Frame XYZ
  //Quaternions_and_spatial_rotation
  DCM00 = 2*(0.5 - q2q2 - q3q3);//2*(0.5 - q2q2 - q3q3);//=q0q0 + q1q1 - q2q2 - q3q3
  DCM01 = 2*(q1q2 - q0q3);//2*(q0q1 + q2q3)
  DCM02 = 2*(q1q3 + q0q2);//2*(q1q3 - q0q2); 2*(q0q2 - q1q3)
  DCM10 = 2*(q1q2 + q0q3);
  DCM11 = 2*(0.5 - q1q1 - q3q3);//2*(0.5 - q1q1 - q3q3);//q0q0 - q1q1 + q2q2 - q3q3
  DCM12 = 2*(q2q3 - q0q1);
  DCM20 = 2*(q1q3 - q0q2);//-sin pitch
  DCM21 = 2*(q2q3 + q0q1);
  DCM22 = 2*(0.5 - q1q1 - q2q2);//2*(0.5 - q1q1 - q2q2);//=q0q0 - q1q1 - q2q2 + q3q3
  //DCM23 = q0*q0 - q1*q1 + q2*q2 - q3*q3;
  //ahrs_toEuler();
  ahrs_y=degrees(atan2(DCM10, DCM00));//2*q0*q0+2*q1*q1-1)
  ahrs_p=degrees(-asin(DCM20)); // theta
  //ahrs_p=acos(22);//http://en.wikipedia.org/wiki/Rotation_formalisms_in_three_dimensions
  ahrs_r=degrees(atan2(DCM21, DCM22)); // phi
  
    cos_rollcos_pitch = DCM22;
    if(cos_rollcos_pitch < 0.82)//25 deg = 0.82
    {
      cos_rollcos_pitch = 0.82;
    }
////transition between 0 and 360 or -180 and 180 ,By aeroquad//////////    
     Heading = ahrs_y - setHeading;
    if (ahrs_y <= (setHeading - 180)) {
      Heading += 360;
    }
    if (ahrs_y >= (setHeading + 180)) {
      Heading -= 360;
    } 
/////////////////////////////////////////////////////////
//////Earth Frame///////////////
//accrX_Earth = hx;
//accrY_Earth = hy;
//accrZ_Earth = hz;
accrX_Earth = (AccXf*DCM00 + AccYf*DCM01 + AccZf*DCM02)*-1.0;
accrY_Earth = (AccXf*DCM10 + AccYf*DCM11 + AccZf*DCM12)*-1.0;
accrZ_Earth = (AccXf*DCM20 + AccYf*DCM21 + AccZf*DCM22) - acc_offsetZ;
//accrZ_Earth = accrZ_Earth + (accrZ_Earthf - accrZ_Earth)*G_Dt*42.5;//18.5 Low pass filter ,smoothing factor  α := dt / (RC + dt)
applyDeadband(accrX_Earth, 0.02);//+-0.03 m/s^2
applyDeadband(accrY_Earth, 0.02);//+-0.03 m/s^2
applyDeadband(accrZ_Earth, 0.02);//+-0.03 m/s^2
}
