#ifndef COMMAND_H
#define COMMAND_H
#include "Arduino.h"
//#include "C:\Users\Savvas\Google Drive\Quadcopter\CODE\XBEE Arduino Code\OptimizedXBee\Command.cpp"

class BaseMessage {
  public:
    String headerStr;
    int argNumber;
    boolean dataGotUpdated;
  public:
    BaseMessage(String header_, int argNumber_);
   // template<class T>
    virtual void updateData(String newData_) = 0;
    
    boolean sameHeader(String otherHeader) {
      return headerStr.equals(otherHeader);
    };
};


class IntegerMessage: public BaseMessage
{
  public:
    int* data;
  public:
    IntegerMessage(String header_, int argNumber_);
    void updateData(String newData_);
    int* getData();
    boolean sameHeader(String otherHeader);
};

/*class FloatMessage
{
  public:
    float* data;
  public:
    IntegerMessage(String header_, int argNumber_);
    int* getData();
    boolean sameHeader(String otherHeader);
};*/



#endif
