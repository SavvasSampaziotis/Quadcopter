#include "Arduino.h"
#include "SerialParser.h"

SerialParser::SerialParser(int timeLimit_, char startChar_, char endChar_) {
  //input Message declaration, όχι εδω!
  startChar  = startChar_;
  endChar = endChar_;
  timeLimit = timeLimit_; // milliseconds
  InputMessage = "";
  startCharDetected = false;
}

SerialParser::SerialParser() {
  //input Message declaration, όχι εδω!
  startChar  = '@';
  endChar = '|';
  timeLimit = 20; // milliseconds
  InputMessage = "";
  startCharDetected = false;
}
/**
	Serial Event Handler:
    Always Call at SerialEvent of the main project
*/

void SerialParser::serialEventHandler() {
  unsigned long startTime = millis(); // keeping the time. if elapsedTime > maxParsingDuration, we gotta go
  char inChar;
  while (Serial.available()) {
    //Serial.print("\nSerial Available"); // DEBUG

    if ((millis() - startTime) > 20 ) {  /// TIME LIMIT
      break;
    }

    inChar = (char) Serial.read();

    if (inChar == startChar)
    {
      startCharDetected = true;
      InputMessage = "";
    }
    else if (inChar == endChar)
    {
      if ( startCharDetected ) {

        //   Serial.print("\n >FinishedMessage:"); // DEBUG
        //  Serial.print(InputMessage); // DEBUG
        decodeMessage(InputMessage);
        startCharDetected = false;
      }
      else
      {
        // TODO: handle incomplete message situation
        //     Serial.print("\n End Char W/O Start Char!");
      }
      InputMessage = "";
      //Serial.println("\n-------------------------\n");
    } else {
      if ( startCharDetected ) {
        //Serial.print("\n>RECORDING! Current InputMessage:"); // DEBUG
        //Serial.print(InputMessage); // DEBUG
        InputMessage += inChar;
        //Serial.print("\n>Appended InputMessage:"); // DEBUG
        //Serial.print(InputMessage); // DEBUG
        //Serial.print("\n"); // DEBUG
      }
      else {
        // Serial.print("\n>Junk:"); // DEBUG
        //Serial.print(inChar); // DEBUG
        //Serial.print("\n"); // DEBUG
      }
    }
  }
}

/** Decodes the inputMessage from the Serial Buffer. It extracts the Header and Data and then it
  insert the new Data to the appropriate Message obj with the same header */
void SerialParser::decodeMessage(String inputMessage) {

  String Value, Header = "";
  int i = 0;
  while ((inputMessage.charAt(i) != ';') && (i < inputMessage.length())) {
    Header += inputMessage.charAt(i);
    i++;
  }
  // if i == inputMessage.length -> EXIT;
  Value = inputMessage.substring(i + 1);
  //Serial.println(" => Header : " + Header + "\t Arguments :" + Value);

  boolean headerFound;
  Message* message = searchMessage(Header, &headerFound);
  if (headerFound == true) {
    //Serial.println(" Header : " + Header + " Found");
    message->updateData(Value);
  }
  //else
  //Serial.println(" Header : " + Header + " Not Found");
}

Message* SerialParser::searchMessage(String header, boolean *headerFound) {
  //int it;
  *headerFound = false;
  for (int i = 0; i < messagesVector.size(); i++)
    if (messagesVector[i]->sameHeader(header)) {
      *headerFound = true;
      return messagesVector[i];
    }
}

void SerialParser::addMessage(Message *message) {
  messagesVector.push_back(message);
}

/** Destructor */
SerialParser::~SerialParser() {
  //TODO: messageVector->~messageVector();
}
