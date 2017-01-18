#include "Message.h"
#include "SerialParser.h"

#define SERIAL_BAUD 9400
/**
*    Global Variables  and Objects
*/
SerialParser *serialParser;

/**
*    Setup
*/
boolean found;
Message * intMes, *intMes2, *emptyMes;

void setup() {
  Serial.begin(SERIAL_BAUD);

  serialParser = new SerialParser(); // make parser
  Serial.println("Arduino Serial ready");
  // add expected messages to parser
  serialParser->addMessage(new Message("INT", 1));
  serialParser->addMessage(new Message("FLOAT2", 2));
  serialParser->addMessage(new Message("HELLO", 0));

  // through these pointers you get what you need from the messages. the resources of the system
  //  will have to 'subscribe' to these the parser only ONCE.
  intMes = serialParser->searchMessage("INT", &found);
  intMes2 = serialParser->searchMessage("FLOAT2", &found);
  emptyMes = serialParser->searchMessage("HELLO", &found);
  //   SerialUSB.write("@PR;4;6|");
  //baseMes = SerialParser->searchMessage("INT", found);
}

/**
*    Main Loop
*/
void loop() {

  // this way you get what you need from the messages
  if (intMes->dataUpdated())
    Serial.println(" \n\n\n%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%\n\n\nNEW DATA!!!!! = " + String(intMes->getDataINT(0)) );
  if (intMes2->dataUpdated()) {
    float * data = intMes2->getAllDataFLOAT();
    Serial.println(" \n\n\n%%%%%%%%\n\n\nNEW DATA!!!!! = " + String(data[0]) + " , " + String(data[1]) );
  }
  if (emptyMes->dataUpdated())
    Serial.println(" \n\n\n%%%%%%%%\n\n\nNEW DATA!!!!! from HELLOOO" );

  delay(2000);
  Serial.println("ping");
}

/**
  SerialEvent occurs whenever a new data comes in the
  hardware serial RX.  This routine is run between each
  time loop() runs, so using delay inside loop can delay
  response.  Multiple bytes of data may be available.
  */
void serialEvent() {
  serialParser->serialEventHandler();
  // check event-messages for event driven stuff
}

