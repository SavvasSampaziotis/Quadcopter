/*********READ ME*************/
/*
      Οι συναρτησεις ειναι συμβολικες. ορισματα και συμπληρωματικες εντολες θα προστεθουν οταν ερθει η ωρα τους
      Το ιδιο ισχυει και για καποιες τιμες που εχουν προστεθει (πχ Dt)
*/

float Dt;

void   init_params(){
  /* PID parameters*/
  Dt = 100;  //msec   <--- temp
}

void setup() {
  // put your setup code here, to run once:
  
  init_params();
  
  IMU_1 = new IMU()                      //-----μια class διαχειρησεις της ΙΜU
  motorManager = new MotorManager();     //-----μια class διαχειρησεις της ΙΜU
  XBEE_1 = new XBEE();                   //-------// --
  PID_theta = new PID();                 //-----PID class για την γωνια Θ μεταξυ κινητηρων 1 και 3
  PID_phi = new PID();                   //-----PID class για την γωνια Φ μεταξυ κινητηρων 2 και 4
  PID_throttle = new PID;                //-----PID class για την κατακορυφη επιταχυνση
  PID_yaw = new PID;                     //-----PID class για την κινηση YAW
  
  IMU_1.setup_IMU();                     //-----
  motorManager.setup_MOTORS();           //-----ανοιγει τις PWM θυρες κλπ κλπ
  XBEE_1.setup_XBEE();
}

void loop() {
  
  XBEE_1.get_XBEE_signal();    /// ΣΤΗΝ ΧΒΕΕ ΤΟ ΠΡΑΜΑ ΠΕΡΙΠΛΕΚΕΙ ΑΛΛΑ ΔΕΙΤΕ ΛΙΓΟ ΠΟΛΥ ΕΤΣΙ ΜΕΧΡΙ ΣΤΙΓΜΗΣ
  IMU_1.get_shit();            // feedback
  convert_signal_to_PID_var(); // τωρα εχουμε τα TARGETS γωνιων κλπ
  
  PID_theta.update();
  PID_phi.update();
  PID_throttle.update();
  PID_yaw.update();
  
  //isws mesolavhsei kati edw anamesa
  motorManager.set_motor_input(PID_theta.output(), PID_phi.output(), PID_throttle.output(), PID_yaw.output());
  
  delay(Dt);
}

