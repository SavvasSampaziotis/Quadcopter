void setup() {
  
  //xbeeIsReady =  initialize_XBEE(); //(boolean)
  // initialize_IMU(); //(boolean)
  // initialize_ESC(); //(boolean)

// ARE YA READY?
  allisReady = true; // xBeeisRady && IMUisREady && 

}


void loop() {
  
  if(allisReady == true){
    
    // 1) Assemble Inputs
          //Xbee inputs
          //IMU inouts etc
    
    // 2) Control Unit: calc PIDRoll PID_pitch PID_yaw .....
    
    // 3) calc_rpms(W_pitch, W_roll, .....);
    
    // 4) update motors()
      
      //ToCK
    //wait( DelayTime - CPUTIME)

    //TICK
  }
    // SEND FEED BACK
    
  
}
