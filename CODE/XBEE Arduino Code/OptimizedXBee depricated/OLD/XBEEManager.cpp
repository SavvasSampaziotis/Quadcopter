#ifndef XBEEMANAGER_CPP
#define XBEEMANAGER_CPP
#include "Arduino.h"
#include "C:\Users\Savvas\Google Drive\Quadcopter\CODE\XBEE Arduino Code\OptimizedXBee\XBEEManager.h"

XBEEManager::XBEEManager() {
  //InputCommand = "";
  startChar  = '@';
  endChar = '#';
  timeLimit = 20; // milliseconds
  //  Serial.write("BITCH\n");

}

/**
	Serial Event Handler:
    Always Call at SerialEvent of the main project
*/
void XBEEManager::serialEventHandler() {
  unsigned long startTime = millis(); // keeping the time. if elapsedTime > maxParsingDuration, we gotta go
  char inChar;
  boolean startCharDetected = false;
  String InputCommand = "";

  while (Serial.available()) {

    if ((millis() - startTime) > 20 ) /// TIME LIMIT
      break;

    inChar = (char) Serial.read();

    if (inChar == '@') {
      startCharDetected = true; 
      //Serial.println("Incoming...");
      InputCommand = "";
    }
    else if (inChar == '#') {
      if ( startCharDetected == true) {
        // DEBUG
        Serial.println(" => " + InputCommand); // DEBUG
        decodeCommand(InputCommand);
        startCharDetected = false;
      } else {
        // TODO: handle incomplete message situation
        Serial.println("ERROR PARSING");
      }
      InputCommand = "";
      Serial.println("\n-------------------------\n");
    } else {
      if ( startCharDetected == true)
        InputCommand  += inChar;
    }
  }
}
/** Decodes the inpuCommand from the Serial Buffer. It extracts the Header and Data and then it
  insert the new Data to the appropriate Command obj with the same header */
void XBEEManager::decodeCommand(String inputCommand) {
  String Value, Header = "";
  int i = 0;
  while (inputCommand.charAt(i) != ';') {
    Header += inputCommand.charAt(i);
    i++;
  }

  // IMPORTANT: number of expected arguments shall be included in command class. USE IT
  Value = inputCommand.substring(i + 1);
  Serial.println(" => Header : " + Header + "\t Arguments :" + Value);
  // Search Command with same Header;
  // command->setValue(value);
}

/** Destructor */
XBEEManager::~XBEEManager() {

}



#endif
