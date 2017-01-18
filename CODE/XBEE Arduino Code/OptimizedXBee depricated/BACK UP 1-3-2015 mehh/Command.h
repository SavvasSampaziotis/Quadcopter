#ifndef COMMAND_H
#define COMMAND_H
#include "Arduino.h"
//#include "C:\Users\Savvas\Google Drive\Quadcopter\CODE\XBEE Arduino Code\OptimizedXBee\Command.cpp"

template <class T> class Command
{
  public:
    String headerStr;
    int hashCode;
    T* dataT;
    int argNumber;
    boolean dataGotUpdated;
  public:
    Command(String header_, int argNumber_);
    T getData();
    void updateData(String newData_);
    //boolean dataGotUpdated();
    boolean sameHeader(String otherHeader);
};





#endif
