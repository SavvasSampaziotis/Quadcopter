#include "Arduino.h"
#include "Message.h"

Message::Message(String header, int argNumber_) {
  headerStr = header;
  argNumber = argNumber_;
  dataGotUpdated = false;
  if (argNumber > 0)
    dataStr = new String[argNumber];
}
/**
  an leipoun args, oi kenes theseis tha meinoun 0. MHDEN. M-H-D-E-N
*/
void Message::updateData(String newData) {
  dataGotUpdated = true;
  if (argNumber <= 0) //
    return;
  int  i ;
  i = 0;
  dataStr[0] = "";
  for (int j = 0; j < newData.length(); j++)
    if (newData[j] != ';')
      dataStr[i] += newData[j];
    else {
      i++;
      if (i == argNumber)
        break; // Serial.println(" argument overflow for header: "+headerStr);
      dataStr[i] = "";
    }
}

int* Message::getAllDataINT() {
  dataGotUpdated = false;
  if (argNumber <= 0)
    return NULL;
  int* temp = new int[argNumber];
  for (int i = 0; i < argNumber; i++)
    temp[i] = dataStr[i].toInt();
  return temp;
}
int Message::getDataINT(int i) {
  dataGotUpdated = false;
  if (argNumber <= 0)
    return 0;
  if (i < argNumber)
    return dataStr[i].toInt();
}

float Message::getDataFLOAT(int i) {
  dataGotUpdated = false;
  if (argNumber <= 0)
    return 0;
  if (i < argNumber)
    return dataStr[i].toFloat();
}

float* Message::getAllDataFLOAT() {
  dataGotUpdated = false;
  if (argNumber <= 0)
    return NULL;
  float* temp = new float[argNumber];
  for (int i = 0; i < argNumber; i++)
    temp[i] = dataStr[i].toFloat();
  return temp;
}


