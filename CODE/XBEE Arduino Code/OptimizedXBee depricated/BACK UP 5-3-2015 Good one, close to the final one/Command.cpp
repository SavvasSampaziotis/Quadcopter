#ifndef COMMAND_CPP
#define COMMAND_CPP
#include "Arduino.h"
#include "C:\Users\Savvas\Google Drive\Quadcopter\CODE\XBEE Arduino Code\OptimizedXBee\Command.h"

void convert(String s, int &t) {
  t = s.toInt();
  Serial.println("Just Converted : " + t);
}

void convert(String s, float &f) {
  f = s.toFloat();
}

BaseMessage::BaseMessage(String header_, int argNumber_)
{
  headerStr = header_;

  argNumber  = argNumber_;
  dataGotUpdated = false;
}

IntegerMessage::IntegerMessage(String header_, int argNumber_): BaseMessage( header_,  argNumber_) {
  data = new int[argNumber];
}

void IntegerMessage::updateData(String newData) {
  String temp;
  dataGotUpdated = true;
  for (int i = 0; i < argNumber; i++) {
    temp = "";
    for (int j = 0; j < newData.length(); j++)
      if (newData[j] != ';')
        temp += newData[j];
      else {
        Serial.println(" Argument : = " + temp);
        convert(temp, data[i]);   // analogws me to an to T einai int , float klp, tha klh8ei h antistoixh overloaded synarthsh convert;
      }
  }
}

int *IntegerMessage::getData() {
  dataGotUpdated = false;
  return data;
}


#endif
