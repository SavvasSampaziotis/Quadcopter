#ifndef COMMAND_CPP
#define COMMAND_CPP
#include "Arduino.h"
#include "C:\Users\Savvas\Google Drive\Quadcopter\CODE\XBEE Arduino Code\OptimizedXBee\Command.h"

template <class T>
Command<T>::Command(String header_, int argNumber_)
{
  headerStr = header_;

  argNumber  = argNumber_;
  dataT = new T[argNumber];
  dataGotUpdated = false;
}

template <class T>void Command<T>::updateData(String newData) {
  String temp = "";
  dataGotUpdated = true;

  for (int i = 0; i < this.argNumber; i++)
    for (int j = 0; j < newData.length(); j++)
      if (newData[j] != ';')
        temp += newData[j];
      else
        convert(temp, dataT[i]);   // analogws me to an to T einai int , float klp, tha klh8ei h antistoixh overloaded synarthsh convert;

  temp = "";
}


template <class T> T Command<T>::getData() {
  dataGotUpdated = false;
  return dataT;
}

template <class T> boolean Command<T>::sameHeader(String otherHeader) {
  return headerStr.equals(otherHeader);
}

void convert(String s, int &t) {
  t = s.toInt();
}

void convert(String s, float &f) {
  f = s.toFloat();
}
#endif
