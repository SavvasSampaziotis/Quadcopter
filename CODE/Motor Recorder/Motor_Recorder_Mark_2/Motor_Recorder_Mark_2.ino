#include <Servo.h>
#include <Message.h>
#include <SerialParser.h>

// @SESSION_START_HEADER;1|
// @MOTORSTART;1;80;1000|
/***** STATE MACHINE HEADERS *****/
#define MOTOR_START_HEADER "TSTMS"
#define FUNCTION_START_HEADER "TSTFS"
#define REC_START_HEADER "TSTREC"
#define SESSION_START_HEADER "TSTACTIVE"

/***** FUNCTION PARAMS HEADERS *****/
#define COSFUNPARAMS "TSTCOS"
#define STEPFUNPARAMS "TSTSTEP"
#define RAMPFUNPARAMS "TSTRAMP"

#define STEP 0
#define RAMP 1
#define COSINE 2

#define SERVO_PIN 5
#define JOYSTICK_MIN 0
#define JOYSTICK_MAX 100
#define ESC_MIN 1000
#define ESC_MAX 2000

/***** OBJECTS  *****/
SerialParser *serialParser;
Message *sessionStart, *motorStart, *recordStart, *functionStart;
Message *cosFunParams, *stepFunParams, *rampFunParams;
Message *getReading;

Servo motorServo;

/***** timing resources *****/
long delayTime;
long calcTime;
long const samplingTime = 20; //milliSecs /// ΔΙΟΡΘΩΣΗ

/***** state machine flags  *****/
boolean sessionStarted, functionStarted, motorRunning, recording;

int motorInput;
int functionCode;
/***** funcion params *****/
float cos_A, cos_w, cos_DC;
float step_A, step_t0;
float ramp_slope, ramp_t0, ramp_tf;
float warmUP_slope, warmUP_MAX;

void setup() {
  Serial.begin(9600);
  motorServo.attach(SERVO_PIN);
  serialParser = new SerialParser();

  serialParser->addMessage( sessionStart = new Message(SESSION_START_HEADER, 1));
  serialParser->addMessage( motorStart = new Message(MOTOR_START_HEADER, 3));   // TODO: 3 args
  serialParser->addMessage( functionStart = new Message(FUNCTION_START_HEADER, 2));
  serialParser->addMessage( recordStart = new Message(REC_START_HEADER, 1));

  serialParser->addMessage( cosFunParams = new Message(COSFUNPARAMS, 3));
  serialParser->addMessage( stepFunParams = new Message(STEPFUNPARAMS, 2));
  serialParser->addMessage( rampFunParams = new Message(RAMPFUNPARAMS, 2));

  serialParser->addMessage( getReading = new Message("MARCO", 0 ) );

  cos_A =  cos_w = cos_DC = 0;
  step_A = step_t0 = 0;
  ramp_slope = ramp_t0 = ramp_tf = 0;;

  functionCode = 100;

  functionStarted = motorRunning = recording = false;
  sessionStarted = false;
}
int warmUpIndex = 0;
int functionIndex = 0;

void loop() {
  calcTime = micros();

  if (sessionStarted ) {
    if ( motorRunning ) {
      //  Serial.println( "motor running");
      motorInput = warmUpMotor(warmUpIndex);
      warmUpIndex++;
    }
    if ( functionStarted ) {
      // Serial.println( "function started");
      motorInput = function(functionIndex);
      functionIndex++;
    }
    if ( recording ) {
      //   Serial.println( "recording");
    }
    // Serial.println(motorInput);

    //motorServo.writeMicroseconds(motorInput * 20);
  } //else
  // Serial.println( "nothing");

  motorServo.writeMicroseconds(map(motorInput, JOYSTICK_MIN, JOYSTICK_MAX , ESC_MIN, ESC_MAX ));

  serialParser->serialEventHandler();
  processEvents();

  calcTime = (micros() - calcTime) / 1000;
  delayTime = samplingTime - calcTime;  //
  if (delayTime > 0)
    delay(delayTime);
  else {
    Serial.print("@WARNING: SAMPLING TIME NOT ENOUGH! " + String(delayTime) + "|");
    delay(samplingTime);
  }
}

void processEvents() {
  int temp;

  if (getReading->dataUpdated())
    sendReadings();

  if (sessionStart->dataUpdated()) {
    temp = sessionStart->getDataINT(0);
    sessionStarted = (temp == 1);
    warmUpIndex = functionIndex = 0;
    if (sessionStarted ==  false) {
      functionStarted = motorRunning = recording = false;
      motorInput = JOYSTICK_MIN;
      sendMessage("@RECORDING IS STOPED| @MOTOR WARM UP STOPED| @ESC'S INPUT FUNCTION STOPED|");
    }
  }
  if (motorStart->dataUpdated()) {
    temp = motorStart->getDataINT(0);
    warmUpIndex = 0;
    motorRunning = (temp == 1);
    if (motorRunning == true ) {
      sendMessage("@MOTOR STARTS WARMING UP|");
      warmUP_MAX = motorStart->getDataINT(1);
      temp = motorStart->getDataINT(2);
      if (temp != 0)
        warmUP_slope = warmUP_MAX / motorStart->getDataINT(2);
      else
        warmUP_slope = 0;
    } else {
      sendMessage("MOTOR WARM UP IS STOPED|");
      motorInput = JOYSTICK_MIN;
    }
  }
  if (functionStart->dataUpdated()) {
    temp = functionStart->getDataINT(0);
    functionStarted = (temp == 1);
    if (functionStarted == true ) {
      functionCode = functionStart->getDataINT(1);
      sendMessage("@ESC'S INPUT FUNCTION STARTED|");
      sendMessage("MOTOR WARM UP IS STOPED|");
      motorRunning  = false;
    } else
      sendMessage("@ESC'S INPUT IS STOPED|");
  }
  if (recordStart->dataUpdated()) {
    temp = recordStart->getDataINT(0);
    recording = (temp == 1);
    if (recording == true )
      sendMessage("@THRUST AND INPUT ARE BEING RECORDED|");
    else
      sendMessage("@RECORDING IS STOPED|");
  }
  if (cosFunParams->dataUpdated()) {
    float* params = cosFunParams->getAllDataFLOAT();
    cos_A = params[1];
    cos_w = 2 * 3.1415 * params[2] / 1000;
    cos_DC = params[0];
  }
  if (stepFunParams->dataUpdated()) {
    float* params = stepFunParams->getAllDataFLOAT();
    step_A = params[0];
    step_t0 = params[1];
  }
  if ( rampFunParams->dataUpdated()) {
    float* params = stepFunParams->getAllDataFLOAT();
    ramp_slope = params[0];
    ramp_t0 = params[1];
    ramp_tf = ramp_t0 + params[2];
  }
}

int warmUpMotor(int k) {
  if (warmUP_slope == 0)
    return warmUP_MAX;
  int r = warmUP_slope * k * samplingTime;
  if (r > warmUP_MAX)
    return warmUP_MAX;
  else
    return r;
}


int function(int k) {
  int t = k * samplingTime;
  switch (functionCode) {
    case COSINE:
      return cos_A * cos( cos_w * t) + cos_DC;
    case STEP:
      if (t > step_t0)
        return step_A;
      else
        return 0;
      break;
    case RAMP:
      if ((t <= ramp_tf) && (t >= ramp_t0))
        return ramp_slope * t;
      else
        return 0;
      break;
  }
  return 0;
}

void sendReadings() {
  Serial.print("@TST" + String( motorInput )  + ";" + ";" + "|");
}

void sendMessage(String msg) {
  Serial.print("@" + msg + "|");
}
