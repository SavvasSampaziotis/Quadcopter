#ifndef XBEEMANAGER_H
#define XBEEMANAGER_H
#include "Arduino.h"
//#include "C:\Users\Savvas\Google Drive\Quadcopter\CODE\XBEE Arduino Code\OptimizedXBee\Command.h"
#include "Command.h"
#include <vector>
/* TODO:
  Make List<Command>
  Make addToList function
  Make search cmd in list function
  Implement List of Commands
  Make command Decoding - DONE
  Test everything
*/

/*
  NOTES:
  class member InputCommand CAN NOT be used in eventHandler: it wrecks the parsing for some reason

*/
class XBEEManager {
  private:
     std::vector< Command<int>* > intCommands;

    String InputCommand;
    boolean startCharDetected;
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
