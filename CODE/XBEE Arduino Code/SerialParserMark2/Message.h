#ifndef MESSAGE_H
#define MESSAGE_H

#include "Arduino.h"

class Message {
  private:
    boolean dataGotUpdated;
    int argNumber;
  public:
    String headerStr;
    String *dataStr;
  public:
    Message(String Header, int argNumber);
    void updateData(String newData_);

    boolean sameHeader(String otherHeader) {
      return headerStr.equals(otherHeader);
    };
    boolean dataUpdated() {
      boolean temp = dataGotUpdated;
      dataGotUpdated = false;
      return temp;
    };

    int* getAllDataINT();
    int getDataINT(int i);

    float getDataFLOAT(int i);
    float* getAllDataFLOAT();

};

#endif
