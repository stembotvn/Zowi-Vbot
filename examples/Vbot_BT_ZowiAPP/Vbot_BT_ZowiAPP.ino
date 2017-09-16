//----------------------------------------------------------------
//
//Zowi_Vbot Default Firmware 
//Modified from Zowi Vbot Firmware 
//Comatible with Zowi APP, a very fun Smartphone app for programming Zowi Vbot
//Link Android APP: https://play.google.com/store/apps/details?id=com.bq.
// This Firmware also compatible with Mblock SoftWare in Scratch Mode (using online programming in Scratch Language, must always connect to PC to programming and run)
//Suitable for kids from 5-15 years old - Enjoy 
//Created and Modified by Hien Phan - Aug,6,2017
// Visit http://stembot.vn for more detail
//-----------------------------------------------------------------

//-- Vbot Library
#include <ZowiVbot.h>
#include "SoftSerialCommand.h"
ZowiVbot Vbot;  //my name is Vbot! Hello World!

SoftwareSerial BT = SoftwareSerial(BT_Rx,BT_Tx); 
SoftSerialCommand SCmd(BT); //The SerialCommand object

//---------------------------------------------------------



///////////////////////////////////////////////////////////////////
//-- Global Variables -------------------------------------------//
///////////////////////////////////////////////////////////////////
const char programID[]="ZOWI_BASE_v2";

const char name_fac='$'; //Factory name
const char name_fir='#'; 

//-- Movement parameters
int T=1000;              //Initial duration of movement -> show the speed of movement
int moveId=0;            //type of movement
int moveSize=30;         //Size of movement (amplitude of movement)

unsigned long previousMillis=0;

int randomDance=0;
int randomSteps=0;

bool obstacleDetected = false;


///////////////////////////////////////////////////////////////////
//-- Setup ------------------------------------------------------//
///////////////////////////////////////////////////////////////////
void setup(){

  //Serial communication initialization
  BT.begin(9600);  //init for Bluetooth HC-06 interface via Software Serial 
  Serial.begin(9600); //init for Serial interface for Debug data in PC 
  
    Vbot.init(HIP_L, HIP_R, FOOT_L, FOOT_R, false, PIN_NoiseSensor, PIN_Buzzer,PIN_Trigger, PIN_Echo);

  randomSeed(analogRead(A6));

  //Setup callbacks for SerialCommand commands 
  SCmd.addCommand("S", receiveStop);      //  sendAck & sendFinalAck
  SCmd.addCommand("L", receiveLED);       //  sendAck & sendFinalAck
  SCmd.addCommand("T", recieveBuzzer);    //  sendAck & sendFinalAck
  SCmd.addCommand("M", receiveMovement);  //  sendAck & sendFinalAck
  SCmd.addCommand("H", receiveGesture);   //  sendAck & sendFinalAck
  SCmd.addCommand("K", receiveSing);      //  sendAck & sendFinalAck
  SCmd.addCommand("C", receiveTrims);     //  sendAck & sendFinalAck
  SCmd.addCommand("G", receiveServo);     //  sendAck & sendFinalAck
  SCmd.addCommand("R", receiveName);      //  sendAck & sendFinalAck
  SCmd.addCommand("E", requestName);
  SCmd.addCommand("D", requestDistance);
  SCmd.addCommand("N", requestNoise);
  SCmd.addCommand("B", requestBattery);
  SCmd.addCommand("I", requestProgramId);
  SCmd.addDefaultHandler(receiveStop);

  //Vbot wake up!
  Vbot.sing(S_connection);
  Vbot.home();
  delay(50);
  Serial.println("Zowi Started");
 
  //Send Vbot name, programID & battery level.
  requestName();
  delay(50);
  requestProgramId();
  delay(50);
  requestBattery();
  Serial.println("Sent Name");
  
  //Checking battery
  LowBatteryAlarm();
   Vbot.sing(S_happy);
    delay(200);
 

 previousMillis = millis();

}

///////////////////////////////////////////////////////////////////
//-- Principal Loop ---------------------------------------------//
///////////////////////////////////////////////////////////////////
void loop() {

  if (BT.available() > 0) {
   // Vbot.putMouth(happyOpen);
  //  Serial.print(BT.read());
    SCmd.readSerial();
  
    //If Vbot is moving yet
    if (Vbot.getRestState()==false) {
      move(moveId);
    }
  } 
}

///////////////////////////////////////////////////////////////////
//-- Functions --------------------------------------------------//
///////////////////////////////////////////////////////////////////

//-- Function to read distance sensor & to actualize obstacleDetected variable
void obstacleDetector(){

   int distance = Vbot.getDistance();

        if(distance<15){
          obstacleDetected = true;
        }else{
          obstacleDetected = false;
        }
}


//-- Function to receive Stop command.
void receiveStop(){

    sendAck();
    Vbot.home();
    sendFinalAck();

}


//-- Function to receive LED commands
void receiveLED(){  

    //sendAck & stop if necessary
    sendAck();
    Vbot.home();
     //put some code for deny (not available)
   
    sendFinalAck();

}


//-- Function to receive buzzer commands
void recieveBuzzer(){
  
    //sendAck & stop if necessary
    sendAck();
    Vbot.home(); 

    bool error = false; 
    int frec;
    int duration; 
    char *arg; 
    
    arg = SCmd.next(); 
    if (arg != NULL) { frec=atoi(arg); }    // Converts a char string to an integer   
    else {error=true;}
    
    arg = SCmd.next(); 
    if (arg != NULL) { duration=atoi(arg); } // Converts a char string to an integer  
    else {error=true;}

    if(error==true){


      delay(2000);
 

    }else{ 

      Vbot._tone(frec, duration, 1);   
    }

    sendFinalAck();

}


//-- Function to receive TRims commands
void receiveTrims(){  

    //sendAck & stop if necessary
    sendAck();
    Vbot.home(); 
    Vbot.sing(S_confused);
    //Vbot.playGesture(RobotConfused);// Indicate that Function not availabe for this version
    

}
 

//-- Function to receive Servo commands
void receiveServo(){  

    sendAck(); 
    moveId = 30;

    //Definition of Servo Bluetooth command
    //G  servo_YL servo_YR servo_RL servo_RR 
    //Example of receiveServo Bluetooth commands
    //G 90 85 96 78 
    bool error = false;
    char *arg;
    int servo_YL,servo_YR,servo_RL,servo_RR;

    arg=SCmd.next();
    if (arg != NULL) { servo_YL=atoi(arg); }    // Converts a char string to an integer   
    else {error=true;}

    arg = SCmd.next(); 
    if (arg != NULL) { servo_YR=atoi(arg); }    // Converts a char string to an integer  
    else {error=true;}

    arg = SCmd.next(); 
    if (arg != NULL) { servo_RL=atoi(arg); }    // Converts a char string to an integer  
    else {error=true;}

    arg = SCmd.next(); 
    if (arg != NULL) { servo_RR=atoi(arg); }    // Converts a char string to an integer  
    else {error=true;}
    
    if(error==true){

      delay(2000);

    }else{ //Update Servo:

      int servoPos[4]={servo_YL, servo_YR, servo_RL, servo_RR}; 
      Vbot._moveServos(200, servoPos);   //Move 200ms
      
    }

    sendFinalAck();

}


//-- Function to receive movement commands
void receiveMovement(){

    sendAck();
    Serial.print("Move Command: ");
    if (Vbot.getRestState()==true){
        Vbot.setRestState(false);
    }

    //Definition of Movement Bluetooth commands
    //M  MoveID  T   MoveSize  
    char *arg; 
    arg = SCmd.next(); 
    if (arg != NULL) {moveId=atoi(arg); Serial.println(moveId); Serial.print(" ");}
    else{
//      Vbot.putMouth(xMouth);
      delay(2000);
  //    Vbot.clearMouth();
      moveId=0; //stop
    }
    
    arg = SCmd.next(); 
    if (arg != NULL) {T=atoi(arg); Serial.println(T); Serial.print(" ");}
    else{
      T=1000;
    }

    arg = SCmd.next(); 
    if (arg != NULL) {moveSize=atoi(arg); Serial.println(moveSize); Serial.print(" ");}
    else{
      moveSize =30;
    }
}


//-- Function to execute the right movement according the movement command received.
void move(int moveId){

  bool manualMode = false;

  switch (moveId) {
    case 0:
      Vbot.home();
      break;
    case 1: //M 1 1000 
      Vbot.walk(1,T,1);
      break;
    case 2: //M 2 1000 
      Vbot.walk(1,T,-1);
      break;
    case 3: //M 3 1000 
      Vbot.turn(1,T,1);
      break;
    case 4: //M 4 1000 
      Vbot.turn(1,T,-1);
      break;
    case 5: //M 5 1000 30 
      Vbot.updown(1,T,30);
      break;
    case 6: //M 6 1000 30
	  moveSize =30;
      Vbot.moonwalker(1,T,moveSize,1);
      break;
    case 7: //M 7 1000 30
      moveSize =30;
      Vbot.moonwalker(1,T,moveSize,-1);
      break;
    case 8: //M 8 1000 30
	  moveSize =30;
      Vbot.swing(1,T,moveSize);
      break;
    case 9: //M 9 1000 30 
	  moveSize =30;
      Vbot.crusaito(1,T,moveSize,1);
      break;
    case 10: //M 10 1000 30
      moveSize =30;	
      Vbot.crusaito(1,T,moveSize,-1);
      break;
    case 11: //M 11 1000 
      Vbot.jump(1,T);
      break;
    case 12: //M 12 1000 30
	  moveSize =30;
      Vbot.flapping(1,T,moveSize,1);
      break;
    case 13: //M 13 1000 30
	  moveSize =30;
      Vbot.flapping(1,T,moveSize,-1);
      break;
    case 14: //M 14 1000 20
	  moveSize = 20;
      Vbot.tiptoeSwing(1,T,moveSize);
      break;
    case 15: //M 15 500 
      Vbot.bend(1,T,1);
      break;
    case 16: //M 16 500 
      Vbot.bend(1,T,-1);
      break;
    case 17: //M 17 500 
      Vbot.shakeLeg(1,T,1);
      break;
    case 18: //M 18 500 
      Vbot.shakeLeg(1,T,-1);
      break;
    case 19: //M 19 500 20
	  moveSize =30;
      Vbot.jitter(1,T,moveSize);
      break;
    case 20: //M 20 500 15
	  moveSize =30;
      Vbot.ascendingTurn(1,T,moveSize);
      break;
    default:
        manualMode = true;
      break;
  }

  if(!manualMode){
    sendFinalAck();
  }
       
}


//-- Function to receive gesture commands
void receiveGesture(){

    //sendAck & stop if necessary
    sendAck();
    Vbot.home(); 

    //Definition of Gesture Bluetooth commands
    //H  GestureID  
    int gesture = 0;
    char *arg; 
    arg = SCmd.next(); 
    if (arg != NULL) {gesture=atoi(arg);}
    else 
    {
      //Vbot.putMouth(xMouth);
      delay(2000);
      //Vbot.clearMouth();
    }

    switch (gesture) {
      case 1: //H 1 
        Vbot.playGesture(RobotHappy);
        break;
      case 2: //H 2 
        Vbot.playGesture(RobotSuperHappy);
        break;
      case 3: //H 3 
        Vbot.playGesture(RobotSad);
        break;
      case 4: //H 4 
        Vbot.playGesture(RobotSleeping);
        break;
      case 5: //H 5  
        Vbot.playGesture(RobotFart);
        break;
      case 6: //H 6 
        Vbot.playGesture(RobotConfused);
        break;
      case 7: //H 7 
        Vbot.playGesture(RobotLove);
        break;
      case 8: //H 8 
        Vbot.playGesture(RobotAngry);
        break;
      case 9: //H 9  
        Vbot.playGesture(RobotFretful);
        break;
      case 10: //H 10
        Vbot.playGesture(RobotMagic);
        break;  
      case 11: //H 11
        Vbot.playGesture(RobotWave);
        break;   
      case 12: //H 12
        Vbot.playGesture(RobotVictory);
        break; 
      case 13: //H 13
        Vbot.playGesture(RobotFail);
        break;         
      default:
        break;
    }

    sendFinalAck();
}

//-- Function to receive sing commands
void receiveSing(){

    //sendAck & stop if necessary
    sendAck();
    Vbot.home(); 

    //Definition of Sing Bluetooth commands
    //K  SingID    
    int sing = 0;
    char *arg; 
    arg = SCmd.next(); 
    if (arg != NULL) {sing=atoi(arg);}
    else 
    {
      delay(2000);

    }

    switch (sing) {
      case 1: //K 1 
        Vbot.sing(S_connection);
        break;
      case 2: //K 2 
        Vbot.sing(S_disconnection);
        break;
      case 3: //K 3 
        Vbot.sing(S_surprise);
        break;
      case 4: //K 4 
        Vbot.sing(S_OhOoh);
        break;
      case 5: //K 5  
        Vbot.sing(S_OhOoh2);
        break;
      case 6: //K 6 
        Vbot.sing(S_cuddly);
        break;
      case 7: //K 7 
        Vbot.sing(S_sleeping);
        break;
      case 8: //K 8 
        Vbot.sing(S_happy);
        break;
      case 9: //K 9  
        Vbot.sing(S_superHappy);
        break;
      case 10: //K 10
        Vbot.sing(S_happy_short);
        break;  
      case 11: //K 11
        Vbot.sing(S_sad);
        break;   
      case 12: //K 12
        Vbot.sing(S_confused);
        break; 
      case 13: //K 13
        Vbot.sing(S_fart1);
        break;
      case 14: //K 14
        Vbot.sing(S_fart2);
        break;
      case 15: //K 15
        Vbot.sing(S_fart3);
        break;    
      case 16: //K 16
        Vbot.sing(S_mode1);
        break; 
      case 17: //K 17
        Vbot.sing(S_mode2);
        break; 
      case 18: //K 18
        Vbot.sing(S_mode3);
        break;   
      case 19: //K 19
        Vbot.sing(S_buttonPushed);
        break;                      
      default:
        break;
    }

    sendFinalAck();
}


//-- Function to receive Name command
void receiveName(){

    //sendAck & stop if necessary
    sendAck();
    Vbot.home(); 
    Vbot.sing(S_confused); //deny to receive command changing the name. 
    /*
    char newVbotName[11] = "";  //Variable to store data read from Serial.
    int eeAddress = 5;          //Location we want the data to be in EEPROM.
    char *arg; 
    arg = SCmd.next(); 
    
    if (arg != NULL) {

      //Complete newVbotName char string
      int k = 0;
      while((*arg) && (k<11)){ 
          newVbotName[k]=*arg++;
          k++;
      }
      
      EEPROM.put(eeAddress, newVbotName); 
    }
    else 
    {
      //Vbot.putMouth(xMouth);
      delay(2000);
     // Vbot.clearMouth();
    }
      */
  //  sendFinalAck();

}


//-- Function to send Vbot's name
void requestName(){

    Vbot.home(); //stop if necessary

    char actualVbotName[11]= "Zowi";  //Variable to store data read from EEPROM.
 //   int eeAddress = 5;            //EEPROM address to start reading from

    //Get the float data from the EEPROM at position 'eeAddress'
  //  EEPROM.get(eeAddress, actualVbotName);

    BT.print(F("&&"));
    BT.print(F("E "));
    BT.print(actualVbotName);
    BT.println(F("%%"));
    BT.flush();
}


//-- Function to send ultrasonic sensor measure (distance in "cm")
void requestDistance(){

    Vbot.home();  //stop if necessary  

    int distance = Vbot.getDistance();
    BT.print(F("&&"));
    BT.print(F("D "));
    BT.print(distance);
    BT.println(F("%%"));
    BT.flush();
}


//-- Function to send noise sensor measure
void requestNoise(){

    Vbot.home();  //stop if necessary

    int microphone= Vbot.getNoise(); //analogRead(PIN_NoiseSensor);
    BT.print(F("&&"));
    BT.print(F("N "));
    BT.print(microphone);
    BT.println(F("%%"));
    BT.flush();
}


//-- Function to send battery voltage percent
void requestBattery(){

    Vbot.home();  //stop if necessary

    //The first read of the batery is often a wrong reading, so we will discard this value. 
    double batteryLevel = Vbot.getBatteryLevel();

    BT.print(F("&&"));
    BT.print(F("B "));
    BT.print(batteryLevel);
    BT.println(F("%%"));
    BT.flush();
}


//-- Function to send program ID
void requestProgramId(){

    Vbot.home();   //stop if necessary

    BT.print(F("&&"));
    BT.print(F("I "));
    BT.print(programID);
    BT.println(F("%%"));
    BT.flush();
}


//-- Function to send Ack comand (A)
void sendAck(){

  delay(30);

  BT.print(F("&&"));
  BT.print(F("A"));
  BT.println(F("%%"));
  BT.flush();
}


//-- Function to send final Ack comand (F)
void sendFinalAck(){

  delay(30);

  BT.print(F("&&"));
  BT.print(F("F"));
  BT.println(F("%%"));
  BT.flush();
}

//-- Functions with animatics
void LowBatteryAlarm(){

    double batteryLevel = Vbot.getBatteryLevel();

    if(batteryLevel<45){
      Vbot.bendTones (880, 2000, 1.04, 8, 3);  //A5 = 880
      
      delay(30);
      
      Vbot.bendTones (2000, 880, 1.02, 8, 3);  //A5 = 880

      delay(500);     
    }
}