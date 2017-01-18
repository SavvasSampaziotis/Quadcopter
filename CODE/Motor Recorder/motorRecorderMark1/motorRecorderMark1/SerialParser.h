#ifndef SERIALPARSER_H
#define SERIALPARSER_H

#include "Arduino.h"
#include "Message.h"
//#include "SerialParser.cpp"
//#include "Message.cpp"
#include <vector>

/* TODO:
  1) More Testing;
  2) Implement erratical message reckognition and etc
  3) Implement message class for long, float and bool arguments
*/

class SerialParser {
  private:
    std::vector< BaseMessage* > messagesVector;

    String InputMessage;
    boolean startCharDetected;
    char startChar, endChar;
    short int timeLimit;
  public:
    // Constructor!
    SerialParser();
    void serialEventHandler();
    void decodeMessage(String inputMessage);

    BaseMessage* searchMessage(String header, boolean *headerFound);
    void addMessage(BaseMessage *message);

    ~SerialParser();
};

#endif
