#include "C:\Users\Savvas\Google Drive\Quadcopter\CODE\XBEE Arduino Code\OptimizedXBee\XBEEManager.h"

#define SERIAL_BAUD 9400
/**
*    Global Variables  and Objects
*/
XBEEManager *xBeeManager;

/**
*    Setup
*/
void setup() {
  Serial.begin(SERIAL_BAUD);
  //SerialUSB.begin(SERIAL_USB_BAUD);
  xBeeManager = new XBEEManager();
  Serial.println("Arduino Serial ready");
  //   SerialUSB.write("@PR;4;6|");
}

/**
*    Main Loop
*/
void loop() {

}

/**
  SerialEvent occurs whenever a new data comes in the
  hardware serial RX.  This routine is run between each
  time loop() runs, so using delay inside loop can delay
  response.  Multiple bytes of data may be available.
  */
void serialEvent() {
  xBeeManager->serialEventHandler();
}
