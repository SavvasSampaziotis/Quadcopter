#ifndef XBEEMANAGER_H
#define XBEEMANAGER_H
#include "Arduino.h"
#include "Command.h"
#include <list>

/* TODO:
  Make List<Command>
  Make addToList function
  Make search cmd in list function
  Implement List of Commands
  Make command Decoding,
  Test everything
*/

/*
  NOTES:
  class member InputCommand CAN NOT be used in eventHandler: it wrecks the parsing for some reason

*/
class XBEEManager {
  public:
  private:
    String InputCommand;
    boolean startCharDetected;
    //list<*Command> commandList;
    char startChar, endChar;
    short int timeLimit;
  public:
    // Constructor!
    XBEEManager();
    void serialEventHandler();
    ~XBEEManager();
    void decodeCommand(String inputCommand);
    //void addCommandToList(Command *cmd);
};







#endif
