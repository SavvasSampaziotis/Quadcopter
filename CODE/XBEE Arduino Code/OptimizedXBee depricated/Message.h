#ifndef MESSAGE_H
#define MESSAGE_H
#include "Arduino.h"

class BaseMessage {
  public:
    String headerStr;
    int argNumber;
  protected:
    boolean dataGotUpdated;
  public:
    BaseMessage(String header_, int argNumber_);
    // template<class T>
    virtual void updateData(String newData_) = 0;
    virtual  int* getData() = 0;
    boolean sameHeader(String otherHeader) {
      return headerStr.equals(otherHeader);
    };
    boolean dataUpdated() {
      boolean temp = dataGotUpdated;
      dataGotUpdated = false;
      return temp;
    };
};

class IntegerMessage: public virtual BaseMessage
{
  public:
    int* data;
  public:
    IntegerMessage(String header_, int argNumber_);
    void updateData(String newData_);
    int* getData();
    int convertInt(String s);
    //boolean sameHeader(String otherHeader);
};

class EmptyMessage: public virtual BaseMessage
{
  public:
    EmptyMessage(String header_);
    void updateData(String newData_);
    int* getData() { };
};

class FloatMessage
{
  public:
    float* data;
  public:
    FloatMessage(String header_, int argNumber_);
    int* getData();
    boolean sameHeader(String otherHeader);
    float convert(String s);
};

#endif
