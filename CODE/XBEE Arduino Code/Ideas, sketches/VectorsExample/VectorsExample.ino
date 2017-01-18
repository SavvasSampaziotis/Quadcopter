#include <iostream>
#include <vector>

  std::vector<int> first;                              
  std::vector<int> second;                   
  std::vector<int> third;
  std::vector<int> fourth; 
  std::vector<int> fifth; 
  
void setup() {
  
  delay(2000);
  
  Serial.begin(9600);
  
  // constructors used in the same order as described above:
  //std::vector<int> first;                                // empty vector of ints
  second = std::vector<int> (4,100);                       // four ints with value 100
  third = std::vector<int> (second.begin(),second.end());  // iterating through second
  fourth = std::vector<int> (third);                       // a copy of third

  // the iterator constructor can also be used to construct from arrays:
  int myints[] = {16,2,77,29};
  fifth = std::vector<int> (myints, myints + sizeof(myints) / sizeof(int) );

  
  

}

void loop() {
  // put your main code here, to run repeatedly:
  
  Serial.print("The contents of 2nd are:\n");
  
  
  for (std::vector<int>::iterator it = second.begin(); it != fifth.end(); ++it)
  {
    Serial.print("\n");
    Serial.print(*it);
    Serial.print('\n');
  }
  
  Serial.print("The contents of fifth are:\n");
  
  
  for (std::vector<int>::iterator it = fifth.begin(); it != fifth.end(); ++it)
  {
    Serial.print("\n");
    Serial.print(*it);
    Serial.print('\n');
  }


    delay(3000);


}
