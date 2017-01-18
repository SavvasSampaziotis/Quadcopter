String InputCommand = "";
boolean InputComplete = false;
//For MotorFeedback Demo-------------
long iteration = 0;
boolean SendMotorFeedback;
//--------------------------------

void setup() {
   // initialize serial:
   Serial.begin(9600);
   //Μαλακία
   randomSeed(345);
 
}

void loop() {
  
  //MotorFeedback Demo---------------------------------------------------------------------
  //if (SendMotorFeedback) {
    /*
    if (iteration > 50000){
      
      Serial.print("MF;");
       Serial.print(random(0,100));
       Serial.print(";");
       Serial.print(random(0,100));
       Serial.print(";");
       Serial.print(random(0,100));
       Serial.print(";");
       Serial.print(random(0,100));
       Serial.print("|");
       
iteration = 0;

    //}
    
  }
  
  
  //κακή προγραμματιστική πρακτική αυτό εδώ αλλα βαριέμαι για κάτι καλύτερο
  iteration += 1;
  */
  
  //-----------------------------------------------------------------------------------------
  
  
   // print the string when a newline arrives:
   if (InputComplete) {
 
     //String Fields[5];
     //ParseInput(Fields, InputCommand);
     

     
     
     String Header = "";
     int HeaderIndex = InputCommand.indexOf(';');
     
     if (HeaderIndex != -1){
         Header = InputCommand.substring(0,HeaderIndex);
         //Serial.println("HIndex: " + HeaderIndex);
     }
     else{
         Header = InputCommand;
         //Serial.println("HEADER_ALL");
     }

    
       
       //PitchRoll Unified
     if (Header == "PR"){ 
       int Value2Index = InputCommand.indexOf(';',HeaderIndex+1);
       int Pitch = InputCommand.substring(HeaderIndex+1).toInt();
       int Roll = InputCommand.substring(Value2Index+1).toInt();
       delay(100);
       
       //Serial.print("AR;");
       //Serial.print(Value);
       //Serial.print("|");
       //Serial.print(Pitch);
       //Serial.print(Roll);
       Serial.print("PR;");
       Serial.print(Pitch);
       Serial.print(";");
       Serial.print(Roll);
       Serial.print("|");
       
     //Yaw
     } else if (Header == "Y"){ 
       int Value = InputCommand.substring(HeaderIndex+1).toInt();
       delay(100);
       
      
       //Serial.print("AY;");
       //Serial.print(Value);
       //Serial.print("|");
       Serial.print("Y;");
       Serial.print(Value);
       Serial.print("|");
       
     //Throttle
     } else if (Header == "T"){  
       int Value = InputCommand.substring(HeaderIndex+1).toInt();
       delay(100);
       
       
       Serial.print("T;");
       Serial.print(Value);
       Serial.print("|");
       
       
     //Handshake Arduino-PC
     } else if (Header == "H_SH"){  
      
       delay(3000);
      //for (int i=1; i <= 50; i++){
        Serial.print("H_SH|");
      //delay(1);
      //} 

     //Decouple Arduino-PC request
     } else if (Header == "D_CP"){  
      
      delay(3000);
      //for (int i=1; i <= 50; i++){
        Serial.print("D_CP|");
      //delay(1);
      //} 
       
     //PING
     } else if (Header == "PING"){  
      Serial.print("PING|");
  //    Serial.print("|");
   //   Serial.print(iteration);
      
      //Motor Feedback-Active
     } else if (Header == "MFA"){  
      SendMotorFeedback = true;
      
        
         //Motor Feedback-Inactive
     } else if (Header == "MFI"){  
         SendMotorFeedback = false;
        
     } else {
       Serial.print("BAD;");
       Serial.print(InputCommand);
       Serial.print("|");
     }
     
     //Serial.println(Header);
     //Serial.print(InputCommand); 
     // clear the string:
     InputCommand = "";
     InputComplete = false;
   }

}






/*
   SerialEvent occurs whenever a new data comes in the
 hardware serial RX.  This routine is run between each
  time loop() runs, so using delay inside loop can delay
  response.  Multiple bytes of data may be available.
  */
void serialEvent() {

   while (Serial.available()) {
     // get the new byte:
     char inChar = (char)Serial.read(); 
     
     
     if (inChar != '|') {
       // add it to the inputString:
       InputCommand += inChar;
     }
     else{
       // if the incoming character is a newline, set a flag
       // so the main loop can do something about it:
       InputComplete = true;
  
     } 
   }
}





////Unused
//void ParseInput(String Fields[],String Input){
//  
//
//  //-----------------------------------
//  /*Serial.print("IN| (");
//  Serial.print(Input + ") |LEN: (");
//  Serial.print(Input.length());
//  Serial.print(") |"); */
//  //-----------------------------------
//  
//  int Start = -1;
//  int End = 0;
//  //Δείκτης για το Fields
//  int i = 0;
//  
//  //Η εκτέλεση θα πραγματοποιείται μέχρι να έρθει η ώρα να διαβάσουμε μέχρι το τέλος του String
//  //Δηλαδή μέχρι το End να γίνει = με το Input.length
//  while (End < Input.length()) {
//   
//    End = Input.indexOf(';', Start + 1);
//    //---------------------------------
//    /*Serial.print("EndIS (");
//    Serial.print(End);
//    Serial.print(") |");*/
//    //---------------------------------
//    
//    //Αν δεν βρέθηκε άλλο κόμμα από το σημείο που ψάχνουμε και πέρα, αρκεί να διαβάσουμε το
//    //String μέχρι το τέλος του.
//    if (End == -1){
//      End = Input.length();
//      //-------------------------
//      //Serial.print("EOF!");
//      //Serial.print(End);
//      //-------------------------
//    }
//    
//    //Παίρνουμε το Substring
//    Fields[i] = Input.substring(Start + 1,End);
//    //-----------------------------------
//    /*Serial.print("VAL: ("); 
//    Serial.print(Fields[i]); 
//    Serial.print(")|"); */
//    //-----------------------------------
//    
//    //Προετοιμασία για την επόμενη επανάληψη (Άν υπάρξει): Αυξάνουμε το δείκτη για το Fields και το τρέχον
//    // Start θα γίνει = με End για να προχωρήσει η αναζήτηση για κόμμα παραπέρα
//    i++;
//    Start = End;
//   
//  }
//  
//  //-----------------------------------------
//  /*Serial.print(Fields[0]);
//  Serial.print(Fields[1]);
//  Serial.print(Fields[2]);
//  Serial.print(Fields[3]);
//  Serial.print(Fields[4]); */
//  //-----------------------------------------
//
//}




