#ifndef MESSAGE_CPP
#define MESSAGE_CPP
#include "Arduino.h"
#include "Message.h"

BaseMessage::BaseMessage(String header_, int argNumber_)
{
  headerStr = header_;
  argNumber  = argNumber_;
  dataGotUpdated = false;
}

IntegerMessage::IntegerMessage(String header_, int argNumber_): BaseMessage( header_,  argNumber_) {
  data = new int[argNumber_];
}

void IntegerMessage::updateData(String newData) {
  String temp = "";
  dataGotUpdated = true;
  if (argNumber == 1) {
    for (int j = 0; j < newData.length(); j++)
      temp += newData[j];
    data[0] = convertInt(temp);
    //Serial.println(" just decoded : = " + temp);  // DEBUG
  } else {
    int i = 0;
    for (int j = 0; j < newData.length(); j++)
      if (newData[j] != ';')
        temp += newData[j];
      else {
        //Serial.println(" Argument : = " + temp);   // DEBUG
        data[i] = convertInt(temp);   // analogws me to an to T einai int , float klp, tha klh8ei h antistoixh overloaded synarthsh convert;
        temp = "";
        i++;
        //if (i > argNumber) {
        // Serial.println(" Argument Overflow");
        // break; }
      }
    data[i] = convertInt(temp);
    // converting the LAST argument
  }
}

int IntegerMessage::convertInt(String s) {
  int t = s.toInt();
  //Serial.println("Just Converted : " + t);   // DEBUG
  return t;
}

int *IntegerMessage::getData() {
  dataGotUpdated = false;
  return data;
}

EmptyMessage::EmptyMessage(String header_): BaseMessage( header_,  0) {

}

void EmptyMessage::updateData(String newData_) {
  dataGotUpdated = true;
}

#endif
