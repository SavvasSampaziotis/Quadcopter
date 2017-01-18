////////////////////////////////////////////////////////////////////////////
//
//  This file is part of MPU9150Lib
//
//  Copyright (c) 2013 Pansenti, LLC
//
//  Permission is hereby granted, free of charge, to any person obtaining a copy of 
//  this software and associated documentation files (the "Software"), to deal in 
//  the Software without restriction, including without limitation the rights to use, 
//  copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the 
//  Software, and to permit persons to whom the Software is furnished to do so, 
//  subject to the following conditions:
//
//  The above copyright notice and this permission notice shall be included in all 
//  copies or substantial portions of the Software.
//
//  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, 
//  INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A 
//  PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT 
//  HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION 
//  OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE 
//  SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

// Έτοιμα
#include Servo.h>
#include <Wire.h>

#include "I2Cdev.h"
#include "MPU9150Lib.h"
#include "CalLib.h"
#include "dmpKey.h"
#include "dmpmap.h"
#include "inv_mpu.h"
#include "inv_mpu_dmp_motion_driver.h"

// Δικά μας
#include <Message.h>
#include <SerialParser.h>
//!! NO EEPROM for Arduino Due!!
//#include <EEPROM.h>


// the MPU object
MPU9150Lib IMU;

//  MPU_UPDATE_RATE defines the rate (in Hz) at which the MPU updates the sensor data and DMP output

#define MPU_UPDATE_RATE  (15)

//  MPU_MAG_MIX defines the influence that the magnetometer has on the yaw output.
//  The magnetometer itself is quite noisy so some mixing with the gyro yaw can help
//  significantly. Some example values are defined below:

#define  MPU_MAG_MIX_GYRO_ONLY          0                   // just use gyro yaw
#define  MPU_MAG_MIX_MAG_ONLY           1                   // just use magnetometer and no gyro yaw
#define  MPU_MAG_MIX_GYRO_AND_MAG       10                  // a good mix value 
#define  MPU_MAG_MIX_GYRO_AND_SOME_MAG  50                  // mainly gyros with a bit of mag correction 

//  SERIAL_PORT_SPEED defines the speed to use for the debug serial port

#define  SERIAL_PORT_SPEED  115200

//Required for converting from Raw values
//SSF = Sensitivity Scale Factor
unsigned short ush_AccelSSF;
short AccelSSF;
float GyroSSF;


//---------------HEADERS

/***** NETWORK HEADERS *****/
#define HANDSHAKE_HEADER "H_SH"
#define DECOUPLE_HEADER "D_CP"

/***** MANUAL CONTROL HEADERS *****/
#define PITCHROLL_HEADER "PR"
#define YAW_HEADER "Y"
#define THROTTLE_HEADER "T"

/***** STATE MACHINE HEADERS *****/
#define REC_STATUS_HEADER "TSTREC"

/***** FUNCTION PARAMS HEADERS *****/
#define NONE_HEADER "TST_NONE"
#define COS_HEADER "TST_COS"
#define STEP_HEADER "TST_STEP"
#define RAMP_HEADER "TST_RAMP"
#define MANUAL_HEADER "TST_MANUAL"

/***** FINCTION IDs *****/
#define NONE 0
#define STEP 1
#define RAMP 2
#define COSINE 3
#define MANUAL 4

/***** FINCTION IDs *****/
#define SERVO_PIN 5
#define JOYSTICK_MIN 0
#define JOYSTICK_MAX 100
#define ESC_MIN 1000//1525
#define ESC_MAX 2500//2500

/***** OBJECTS *****/
SerialParser *serialParser;
Message *handshake, *decouple;
Message *pitchRoll, *yaw, *throttle;
Message *recordStart;
Message *msgNone, *msgCosine, *msgStep, *msgRamp, *msgManual;
Message *getReading;

Servo motorServo;

/***** timing resources *****/
long  delayTime;
long calcTime;
long const samplingTime = 20000; //uSecs
long startTime;

/***** state machine flags  *****/
boolean recording;


/***** funcion params *****/
int functionID;
float motorInput, initialInput;
float cos_A, cos_w, cos_DC;
float step_A;
float rampDuration, rampFinalInput, rampSlope;
float warmUP_slope, warmUP_MAX;



void setup()
{

  delay(2000);

  //-------------SERIAL, I2C SETUP-------------
  sendMessage("setup");
  Serial.begin(SERIAL_PORT_SPEED);
  sendMessage("Motor Recorder Mark 3 setting up...");
  Wire.begin();


  //-----------------IMU SETUP-----------------

  //IMU initialization
  IMU.init(MPU_UPDATE_RATE, MPU_MAG_MIX_GYRO_ONLY);   

  //Get Sensitivity Scale Factors
  mpu_get_accel_sens(&ush_AccelSSF);
  AccelSSF = (short) (ush_AccelSSF << 1);
  mpu_get_gyro_sens(&GyroSSF);
  //DEBUG ONLY:
  /*Serial.print("@ACCEL SSF ASSIGNMENT ");
  Serial.print(AccelSSF);
  Serial.print("|");*/


  //---------------MOTOR SETUP----------------
  motorServo.attach(SERVO_PIN);
  motorInput = JOYSTICK_MIN;
  serialParser = new SerialParser();


  //----------SERIAL MESSAGES SETUP-----------
  serialParser->addMessage(handshake = new Message(HANDSHAKE_HEADER, 0));
  serialParser->addMessage(decouple = new Message(DECOUPLE_HEADER, 0));

  serialParser->addMessage(pitchRoll = new Message(PITCHROLL_HEADER, 2));
  serialParser->addMessage(yaw = new Message(YAW_HEADER, 1));
  serialParser->addMessage(throttle = new Message(THROTTLE_HEADER, 1));

  serialParser->addMessage(recordStart = new Message(REC_STATUS_HEADER, 1)); //TODO: make this 1, 0

  //TODO: δες αν τα αριθμητικά ορίσματα είναι σωστά
  serialParser->addMessage(msgNone = new Message(NONE_HEADER, 0));
  serialParser->addMessage(msgStep = new Message(STEP_HEADER, 2));
  serialParser->addMessage(msgRamp = new Message(RAMP_HEADER, 3));
  serialParser->addMessage(msgCosine = new Message(COS_HEADER, 3));
  serialParser->addMessage(msgManual = new Message(MANUAL_HEADER, 0));
  //For debugging only
  serialParser->addMessage(getReading = new Message("MARCO", 0));


  //------------PARAMETER SETUP-------------
  functionID = NONE;
  
  step_A = 0;
  rampDuration = rampFinalInput = rampSlope = 0; 
  cos_A = cos_w = cos_DC = 0;
  
  recording = false;

  motorInput = initialInput = 0;

}

void loop()
{  

  calcTime = micros();

  //If recording is enabled, check the IMU
  if (recording) {
    //if we successfully read any data from the IMU....
    if (IMU.read()) {

      //sendMessage("Recording");

      //Convert from raw gyro to normal Gyro via SSF(= Sensitivity Scale Factor)
      float GyroX = IMU.m_rawGyro[0] / GyroSSF;
      sendReadings((String)(IMU.m_dmpEulerPose[0] * RAD_TO_DEGREE), (String)GyroX, (String)calcTime, (String)motorInput);
	  //DEBUG ONLY
	  //sendMessage("sss;" + (String)(IMU.m_dmpEulerPose[0] * RAD_TO_DEGREE));

      //Angle Data feed to IMU_Test Console
	  //sendAngleData((String)(IMU.m_dmpEulerPose[0] * RAD_TO_DEGREE), (String)GyroX,"0");

    }
	else{
		//This line inserts errors even when they 're not needed.
		//sendReadings("Read_error","error","error","error");
	}
  }


  
  //Get appropriate motor input depending on selected function
  motorInput = getMotorInput();
  //sendMessage((String)motorInput);
  //delay(1000);
  //Motor feed
  motorServo.writeMicroseconds(map(motorInput, JOYSTICK_MIN, JOYSTICK_MAX, ESC_MIN, ESC_MAX));


  //Check if new messages in Serial
  serialParser->serialEventHandler();
  processEvents();

  //Computational Cycle Synchronization
  delayTime = samplingTime - micros() + calcTime;

  if (delayTime > 0)
    delayMicroseconds(delayTime);
  else {
    sendMessage("WARNING: SAMPLING TIME NOT ENOUGH! " + String(delayTime));
    delayMicroseconds(samplingTime);
  }
  

  ////---------Sensor Data feed to IMU_Test Console---------
  //Serial.print("@SensData;");
  //Serial.print(0);//(double) mpu.getTemperature() / 340.0 + 35);
  //Serial.print(";");

  //Serial.print(IMU.m_rawAccel[0]);
  //Serial.print(";");
  //Serial.print(IMU.m_rawAccel[1]);
  //Serial.print(";");
  //Serial.print(IMU.m_rawAccel[2]);
  //Serial.print(";");

  //Serial.print((float)IMU.m_rawAccel[0] / AccelSSF, 3);
  //Serial.print(";");
  //Serial.print((float) IMU.m_rawAccel[1] / AccelSSF, 3); //������� ��� �� (ush_AccelSSF << 1) ��� ����� ��� �� �� AccelSSF
  //Serial.print(";");
  //Serial.print((float)IMU.m_rawAccel[1] / AccelSSF, 3);
  //Serial.print(";");
  //Serial.print(0, 4);
  //Serial.print(";");

  //Serial.print(IMU.m_rawGyro[0]);
  //Serial.print(";");
  //Serial.print(IMU.m_rawGyro[1]);
  //Serial.print(";");
  //Serial.print(IMU.m_rawGyro[2]);
  //Serial.print(";");
  //float GyroSSF;
  //mpu_get_gyro_sens(&GyroSSF);
  //Serial.print(IMU.m_rawGyro[0] / GyroSSF);
  //Serial.print(";");
  //Serial.print(IMU.m_rawGyro[1] / GyroSSF);
  //Serial.print(";");
  //Serial.print(IMU.m_rawGyro[2] / GyroSSF);
  //Serial.print(";");

  //Serial.print(IMU.m_rawMag[0]); //mx*mx);
  //Serial.print(";");
  //Serial.print(IMU.m_rawMag[1]); //my*my);
  //Serial.print(";");
  //Serial.print(IMU.m_rawMag[2]); //mz*mz);
  //Serial.print("|");

  }
  

/*
* Checks for new Serial input.
*/
void processEvents() {
  
  //Response to "MARCO" header. For Debugging purposes only!
  //  if (getReading->dataUpdated())
  //    sendReadings();

  //------Communication Protocol Packets------
  if (handshake->dataUpdated()){
    sendMessage(HANDSHAKE_HEADER);
    sendMessage("Motor Recorder Mark 3");
  }
  if (decouple->dataUpdated()){
    sendMessage("Motor Recorder decoupled");
    sendMessage(DECOUPLE_HEADER);
  }
    

  //------Pitch Roll Yaw Throttle Packets------
  //Sending back an "acknowledge" packet for every packet received. The Throttle packet's contents will
  //be used by the "getMotorInput" function if the Manual mode is selected.

  if (pitchRoll->dataUpdated())
    sendMessage((String)PITCHROLL_HEADER + ";" + pitchRoll->getDataINT(0) + ";" + pitchRoll->getDataINT(1));

  if (yaw->dataUpdated())
    sendMessage((String)YAW_HEADER + ";" + yaw->getDataINT(0));

  if (throttle->dataUpdated())
    sendMessage((String)THROTTLE_HEADER + ";" + throttle->getDataINT(0));
    

  //------Recording------
  if (recordStart->dataUpdated()) {
    recording = recordStart->getDataINT(0); //0 = false, 1 = true
    if (recording)
      sendMessage("Recording...");
    else
      sendMessage("Recording stopped.");
  }


  //------Function Parameters------
  if (msgNone->dataUpdated()) {
	  functionID = NONE;
	  startTime = micros();
  }

  if (msgStep->dataUpdated()) {
    step_A = msgStep->getDataFLOAT(0);
    functionID = STEP;
    startTime = micros();
  }


	if (msgRamp->dataUpdated()) {
		float* params = msgRamp->getAllDataFLOAT();
    
		initialInput = motorInput;

		rampFinalInput = params[0];
		if (rampFinalInput < JOYSTICK_MIN) rampFinalInput = JOYSTICK_MIN;
		if (rampFinalInput > JOYSTICK_MAX) rampFinalInput = JOYSTICK_MAX;

		rampDuration = params[1]*1000; //μs

		rampSlope = (rampFinalInput - motorInput)/rampDuration;
    
		functionID = RAMP;
		startTime = micros();
		//sendMessage("motorInput " + (String) motorInput + ", rampFinalInput " + (String)rampFinalInput + ", rampSlope " + (String)rampSlope + ", startTime " + (String)startTime + ", rampDuration " + (String)rampDuration);
	}


	if (msgCosine->dataUpdated()) {
		float* params = msgCosine->getAllDataFLOAT();
		cos_A = params[1];
		cos_w = 2 * 3.1415 * params[2] / 1000;
		cos_DC = params[0];
		functionID = COSINE;
		startTime = micros();
	}


	if (msgManual->dataUpdated()) {
		//DEBUG ONLY
		//sendMessage((String)msgManual->getDataINT(0));
		functionID = MANUAL;
		startTime = micros();
	}

}

/*
* Send a message (properly wraped in Stard andEnd characters) over the Serial Interface.
*/
float getMotorInput() {

  //time elapsed since the current function started
  float t_elapsed = (micros() - startTime);  //μs 


  switch (functionID) {

    case NONE:
      return 0;

    case STEP:
  
      return step_A;
      break;

    case RAMP:

      if (t_elapsed <= rampDuration) {
        //sendMessage("sss;" + (String)(initialInput + rampSlope * t_elapsed));
        return initialInput + rampSlope * t_elapsed;
      }
      else{
        //sendMessage("sss;" + (String)(rampFinalInput));
        return rampFinalInput;
      }
      break;

    case COSINE:
      //sendMessage((String)(cos_A * cos(cos_w * t_elapsed) + cos_DC));
      return cos_A * cos(cos_w * t_elapsed) + cos_DC;
      break;

    case MANUAL:
      //sendMessage("sss;" + (String)throttle->getDataINT(0));
      return (float)throttle->getDataINT(0);
      break;

  }

  //Return zero if no Case satisfied the Switch.
  return 0;
}

/*
* Send a test's reading over the Serial Interface.
*/
void sendReadings(String Data0, String Data1, String Data2, String Data3) {
  Serial.print("@TST;");
  Serial.print(Data0);
  Serial.print(",");
  Serial.print(Data1);
  Serial.print(",");
  Serial.print(Data2);
  Serial.print(",");
  Serial.print(Data3);
  Serial.print("|");
}

/*
* Send a message (properly wraped in Stard andEnd characters) over the Serial Interface.
*/
void sendMessage(String msg) {
  Serial.print("@" + msg + "|");
}

/*
* Send send angle data according to the "IMU Test Console" data format.
*/
void sendAngleData(String AngleX, String AngleY, String AngleZ) {
	Serial.print("@Angles;0;0;0;0;0;0;");
	Serial.print(AngleX);
	Serial.print(";");
	Serial.print(AngleY);
	Serial.print(";");
	Serial.print(AngleZ);
	Serial.print("|");
}
