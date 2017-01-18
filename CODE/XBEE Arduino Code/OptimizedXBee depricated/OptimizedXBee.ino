#include "C:\Users\Savvas\Google Drive\Quadcopter\CODE\XBEE Arduino Code\OptimizedXBee\SerialParser.h"

#define SERIAL_BAUD 9400
/**
*    Global Variables  and Objects
*/
SerialParser *serialParser;

/**
*    Setup
*/
boolean found;
BaseMessage * intMes;
BaseMessage * intMes2;

void setup() {
  Serial.begin(SERIAL_BAUD);

  serialParser = new SerialParser(); // make parser
  Serial.println("Arduino Serial ready");
  // add expected messages to parser
  serialParser->addMessage(new IntegerMessage("INT", 1));
  serialParser->addMessage(new IntegerMessage("INT2", 2));


  // through these pointers you get what you need from the messages. the resources of the system
  //  will have to 'subscribe' to these the parser only ONCE.
  intMes = serialParser->searchMessage("INT", found);
  intMes2 = serialParser->searchMessage("INT2", found);
  

  //   SerialUSB.write("@PR;4;6|");
  //baseMes = SerialParser->searchMessage("INT", found);
}

/**
*    Main Loop
*/
void loop() {

  // this way you get what you need from the messages
  if (intMes->dataGotUpdated)
    Serial.println(" \n\n\n%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%\n\n\nNEW DATA!!!!! = " + String(*intMes->getData()) );
  if (intMes2->dataGotUpdated) {
    int * data = intMes2->getData();
    Serial.println(" \n\n\n%%%%%%%%\n\n\nNEW DATA!!!!! = " + String(data[0]) + " , " + String(data[1]) );
  }

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

