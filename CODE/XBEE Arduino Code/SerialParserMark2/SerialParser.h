#ifndef SERIALPARSER_H
#define SERIALPARSER_H

#include "Arduino.h"
#include "Message.h"

#include <vector>

/* TODO:
  1) More Testing;
  2) Implement erratical message reckognition and etc
  3) Implement message class for long, float and bool arguments
*/

class SerialParser {
  private:
    std::vector< Message* > messagesVector;

    String InputMessage;
    boolean startCharDetected;
    char startChar, endChar;
    short int timeLimit;
  public:
    // Constructor!
    SerialParser();
    SerialParser(int timeLimit, char starChar, char endChar);

    void serialEventHandler();
    void decodeMessage(String inputMessage);
    Message* searchMessage(String header, boolean *headerFound);
    void addMessage(Message *message);

    ~SerialParser();
};

#endif
