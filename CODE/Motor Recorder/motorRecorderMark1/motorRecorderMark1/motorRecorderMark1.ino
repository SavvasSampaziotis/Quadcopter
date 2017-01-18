//fsdfsd
#include "SerialParser.h"
#include <Servo.h>

//#include "SerialParser.cpp"
#include "Message.h"
//#include "Message.cpp"


SerialParser *serialParser;
BaseMessage * throttleMsg;
BaseMessage * PingMsg;
BaseMessage * DeCoupleMsg;

Servo throttleSrv;
int throttle = 0;

void setup() {

  Serial.begin(9600);
  serialParser = new SerialParser();

  throttleMsg = new IntegerMessage("T", 1);
  serialParser->addMessage(throttleMsg);

  PingMsg = new EmptyMessage("PING");
  serialParser->addMessage(PingMsg);

  Serial.print("@START BITCH|");

  // throttleSrv = new Servo();

  throttleSrv.attach(9);


  delay(1000);
  Serial.print("@H_SH|");
  //serv
}



void loop() {

  //if (throttleMsg->dataGotUpdated)
  //Serial.print("@T = " + String(*throttleMsg->getData()) + "|");


  //throttleSrv.writeMicroseconds(throttle);
  //Serial.print("@T = " + String(throttle) + "|");
  //Serial.print("@H_SH|");
  delay(100);

}

void serialEvent() {
  serialParser->serialEventHandler();

  // ayto mporei na grafei kai sthn loop
  if (throttleMsg->dataUpdated()) {
    //Τα παρακάτω θελουν λιγο συμαζεμα κ να μπουν με τη σωστη σειρα. τα αφησα οπως ήταν για να φαινονται οι αλλαγές απο το προηγούμενο
    //που σου έστειλα.

    //Acknowledge για throttle
    Serial.print("@T;" + String(*throttleMsg->getData()) + "|");

    //εκχωριση στη throttle. ΓΙΑΤΙ ΤΟ ΕΙΧΑΜΕ ΞΕΧΑΣΕΙ ΑΥΤΟ?????? :p :p
    throttle = *throttleMsg->getData();

    //στέλνουμε το αποτέλεσμα της συνάρτησης
    //Serial.print("@T_ByFunc = " + String(*throttleMsg->getData()) + "|");
    //στέλνουμε κ το περιεχόμενο μετά την εκχώριση για να ειμαστε σιγουροι.
    //  Serial.print("@T_ByVariable = " + String(throttle) + "|");
    //mapping
    throttle = map(throttle, 0, 100, 1000, 2000 );
    Serial.print("@T_Mapped = " + String(throttle) + "|");

    //Serial.print("@NewThrottle|");
    throttleSrv.writeMicroseconds(throttle);

  }

  if (PingMsg->dataUpdated()) {
    Serial.print("@Ping|");
  }
  //Serial.print();
  // check event-messages for event driven stuff
}
