//----------------------------------------------------------------
//-- Zowi-Vbot - An Wooden Bipedal Robot
//-- Design by STEMbot.vn (http://stembot.vn/zowivbot) mixed from OttoDIY project with some modify in library
//-- Example: Avoid obstacles, using SRF04 Sonar Sensor for measure Range in front, if there is obstacle with distance < 15 cm, stop and turn then keep going

//-----------------------------------------------------------------
//Chương trình mẫu thực hiện yêu cầu tránh vật cản, khi robot đang đi tiến về trước và phát hiện vật cản ở khoảng cách nhỏ hơn 15 Cm thì dừng lại và rẽ hướng khác. 
//-----------------------------------------------------------------

#include <ZowiVbot.h>

ZowiVbot Vbot;  //my name is Vbot! Hello World!
//---------------------------------------------------------

///////////////////////////////////////////////////////////////////
//-- Global Variables -------------------------------------------//
///////////////////////////////////////////////////////////////////

//---------------------------------------------------------
///////////////////////////////////////////////////////////////////
//-- Setup ------------------------------------------------------//
///////////////////////////////////////////////////////////////////
void setup(){
  //Set the servo pins
  Vbot.init(HIP_L, HIP_R, FOOT_L, FOOT_R, false, PIN_NoiseSensor, PIN_Buzzer,PIN_Trigger, PIN_Echo);

  Vbot.sing(S_connection); //Vbot wake up!
  Vbot.home();
  delay(50);
  Vbot.sing(S_happy); // a happy Vbot :)
}
///////////////////////////////////////////////////////////////////
//-- Principal Loop ---------------------------------------------//
///////////////////////////////////////////////////////////////////
void loop() {
  if (Vbot.getDistance()<15) { 
               Vbot.sing(S_surprise); 
               Vbot.playGesture(VbotFretful); 
               Vbot.sing(S_fart3); 
               Vbot.walk(2,1300,-1); 
               Vbot.turn(2,1000,-1);                
             delay(50); 
           
             }        
         else{ 
            Vbot.walk(1,1000,1); 
           
        }           
  }  
///////////////////////////////////////////////////////////////////
