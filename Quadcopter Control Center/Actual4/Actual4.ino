String InputCommand = "";
boolean InputComplete = false;
boolean startCharDetected = false;
//For MotorFeedback Demo-------------
long iteration = 0;
boolean SendMotorFeedback;
//--------------------------------
boolean TestDemo = false;
long Counter = 0;
void setup() {
  
  
 
   // initialize serial:
   Serial.begin(9600);
    InputCommand = "" ;
   //Για το Motorfeedback
   //randomSeed(345);

}

void loop() {
       //Serial.print("))");
       //Serial.print(InputCommand);
       //delay (10);
  //MotorFeedback Demo---------------------------------------------------------------------
  //if (SendMotorFeedback) {
   /*
    if (iteration > 500000){
      
      Serial.print("F;");
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
  
  
  //-------------------TEST Demo--------------------------
  
  if (TestDemo) {
    
    if (iteration > 5000){
      
      Serial.print("@TEST;");
      Counter++;
      Serial.print(Counter);
      Serial.print("|");
      iteration = 0;
      
    }

iteration++;
    
  }
  
  
  
  
  
  
  
  
  
  
  //------------------------------------------------------
  
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
       Serial.print("@PR;");
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
       Serial.print("@Y;");
       Serial.print(Value);
       Serial.print("|");
       
     //Throttle
     } else if (Header == "T"){  
       int Value = InputCommand.substring(HeaderIndex+1).toInt();
       delay(100);
       
       
       Serial.print("@T;");
       Serial.print(Value);
       Serial.print("|");
       
       
     //Handshake Arduino-PC
     } else if (Header == "H_SH"){  
      
       //delay(3000);
      //for (int i=1; i <= 50; i++){
        Serial.print("@H_SH|");
      //delay(1);
      //} 

     //Decouple Arduino-PC request
     } else if (Header == "D_CP"){  
      
      //delay(3000);
      //for (int i=1; i <= 50; i++){
        Serial.print("@D_CP|");
      //delay(1);
      //} 
       
     //PING
     } else if (Header == "PING"){  
      Serial.print("@PING|");
  //    Serial.print("|");
   //   Serial.print(iteration);
      
      //Motor Feedback-Active
     } else if (Header == "MFA"){  
      SendMotorFeedback = true;
      
        
         //Motor Feedback-Inactive
     } else if (Header == "MFI"){  
         SendMotorFeedback = false;
         
     } else if (Header == "TEST"){ 
         Serial.print("@testing...|");
         TestDemo = true;
         
     } else if (Header == "TESTOFF"){ 
         Serial.print("@done testing|");
         TestDemo = false;
 
        
     } else {
       Serial.print("@BAD;");
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

  

   unsigned long startTime = millis(); // keeping the time. if elapsedTime > maxParsingDuration, we gotta go
  char inChar;


  while (Serial.available()) {

    //Serial.print("@Serial Available|"); // DEBUG
    
    if ((millis() - startTime) > 20 ) {  /// TIME LIMIT
      //Serial.print("\nTIME CONSUMPTION CONTROL!"); // DEBUG
      break;
    }
     
     

    inChar = (char) Serial.read();
    //Serial.print("\n<inChar>"); // DEBUG
    //Serial.print(inChar); // DEBUG
    //Serial.print("</inChar>\n"); // DEBUG

    if (inChar == '@') {
      startCharDetected = true; 
      //Serial.print("\nIncoming...");
      InputCommand = "";
    }
    else if (inChar == '|') {
      
      if ( startCharDetected ) {

        //Serial.print("@>FinishedCommand:"); // DEBUG
        //Serial.print(InputCommand); // DEBUG
        //Serial.print("|"); // DEBUG
        
        //decodeCommand(InputCommand);
        startCharDetected = false;
        InputComplete= true;
      } else {
        // TODO: handle incomplete message situation
        //Serial.print("\n End Char W/O Start Char!");
      }
     //InputCommand = "";
      
      //Serial.println("\n-------------------------\n");
      
    } else {
      if ( startCharDetected ) {
        //Serial.print("\n>RECORDING! Current InputCommand:"); // DEBUG
        //Serial.print(InputCommand); // DEBUG
        InputCommand += inChar;
        //Serial.print("\n>Appended InputCommand:"); // DEBUG
        //Serial.print(InputCommand); // DEBUG
        //Serial.print("\n"); // DEBUG
      }
      else {
        //Serial.print("\n>Junk:"); // DEBUG
        //Serial.print(inChar); // DEBUG
        //Serial.print("\n"); // DEBUG
      }
        
    }
  }
}


/* old parser
void serialEvent() {

  
  
   while (Serial.available()) {
     
     Serial.print("@");
     Serial.print(Serial.available());
     Serial.print("|");
     
     // get the new byte:
     char inChar = (char)Serial.read(); 
     //Serial.print("**");
     //Serial.print(inChar);
     //Serial.print("|");
     
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
*/




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




