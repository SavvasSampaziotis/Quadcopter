#ifndef XBEEMANAGER_CPP
#define XBEEMANAGER_CPP
#include "Arduino.h"
#include "XBEEManager.h"


XBEEManager::XBEEManager() {
  //input command declaration, όχι εδω!
  startChar  = '@';
  endChar = '#';
  timeLimit = 20; // milliseconds
  InputCommand = "";
  startCharDetected = false;
  // intCommands();
  // messagesVector = new std::vector();
  //messagesVector();
  messagesVector.push_back( new IntegerMessage("INT", 1)); //Command("TWO_INT", 2) };
  
  //  Serial.write("BITCH\n");
  //commandArray = {new Command("INT", 1), new Command("FLOAT", 1), new Command("TWO_INT", 2), new Command("TWO_FLOAT", 2) };
}
/* TEST COMMANDS

@INT;100#
@INT;10#

@FLOAT;100#
@FLOAT;100.2#
@FLOAT;0.0255#

@TWO_INT;10;40#
@TWO_INT;100;400#

*/
/**
	Serial Event Handler:
    Always Call at SerialEvent of the main project
*/
void XBEEManager::serialEventHandler() {
  unsigned long startTime = millis(); // keeping the time. if elapsedTime > maxParsingDuration, we gotta go
  char inChar;
  while (Serial.available()) {

    Serial.print("\nSerial Available"); // DEBUG

    if ((millis() - startTime) > 20 ) {  /// TIME LIMIT
   //   Serial.print("\nTIME CONSUMPTION CONTROL!"); // DEBUG
      break;
    }

    inChar = (char) Serial.read();
//    Serial.print("\n<inChar>"); // DEBUG
 //   Serial.print(inChar); // DEBUG
 //   Serial.print("</inChar>\n"); // DEBUG

    if (inChar == startChar) {
      startCharDetected = true;
      Serial.print("\nIncoming...");
      InputCommand = "";
    }
    else if (inChar == endChar) {

      if ( startCharDetected ) {

        Serial.print("\n >FinishedCommand:"); // DEBUG
        Serial.print(InputCommand); // DEBUG

        decodeCommand(InputCommand);
        startCharDetected = false;
      } else {
        // TODO: handle incomplete message situation
        Serial.print("\n End Char W/O Start Char!");
      }
      InputCommand = "";

      Serial.println("\n-------------------------\n");

    } else {
      if ( startCharDetected ) {
        Serial.print("\n>RECORDING! Current InputCommand:"); // DEBUG
        Serial.print(InputCommand); // DEBUG
        InputCommand += inChar;
        Serial.print("\n>Appended InputCommand:"); // DEBUG
        Serial.print(InputCommand); // DEBUG
        Serial.print("\n"); // DEBUG
      }
      else {
        Serial.print("\n>Junk:"); // DEBUG
        Serial.print(inChar); // DEBUG
        Serial.print("\n"); // DEBUG
      }

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
  // if i == inputCommand.length -> EXIT;
  Value = inputCommand.substring(i + 1);
  Serial.println(" => Header : " + Header + "\t Arguments :" + Value);

  boolean headerFound;
  BaseMessage* message = searchMessage(Header, headerFound);
  if (headerFound == true) {
    Serial.println(" Header : " + Header + " Found");
    message->updateData(Value);
  } else
    Serial.println(" Header : " + Header + " Not Found");
}

BaseMessage* XBEEManager::searchMessage(String header, boolean &headerFound) {
  //int it;
  headerFound = false;
  for (int i = 0; i < messagesVector.size(); i++)
    if (messagesVector[i]->sameHeader(header)) {
      headerFound = true;
      return messagesVector[i];
    }
}

/** Destructor */
XBEEManager::~XBEEManager() {

}



#endif
