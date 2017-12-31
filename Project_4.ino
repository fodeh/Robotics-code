#include <SPI.h>

#include <Wire.h>

#include <EVs_UIModule.h>

#include <EVShield.h>

#include <EVs_EV3Ultrasonic.h>

EVShield evs(0x34,0x36);

EVs_EV3Ultrasonic us;
EVs_UIModule uim = EVs_UIModule(7,8,9);

//Program setup
void setup() {
  evs.init(SH_HardwareI2C);
  us.init(&evs,SH_BBS1);
  us.setMode(MODE_Sonar_CM);
  uim.begin();
  uim.clearScreen();
}

//Start of loop
void loop() {
  float d = us.getDist();
  char s[16];
  int EyePower;
  int EyeDegree;
  int TotalAngle;

//Interface to only start program once "GO" is pushed
  if (evs.getButtonState(BTN_GO) == true) {

 //enter loop to detect distance and move motors   
  while (us.getDist() != 0) {

    sprintf(s,"%d.%02d",(int)d,(int)(d*100)%100);
    uim.writeLine(0,1,s,true,EVs_UIM_GREEN);
    delay(1000);

    evs.bank_a.motorRunUnlimited(SH_Motor_Both, SH_Direction_Forward, 50);

    //Enters commands to search for new distance if object is detected within 15cm          
    if (us.getDist() <= 15) {
       evs.bank_a.motorStop(SH_Motor_Both, SH_Next_Action_Float);
       
       sprintf(s,"%d.%02d",(int)d,(int)(d*100)%100);
       uim.writeLine(0,1,s,true,EVs_UIM_GREEN);
       delay(1000);

       EyePower = 100;
       EyeDegree = 40;
       TotalAngle = 0;

      //Loop to move sensor left searching for valid distances 
      while (us.getDist() <= 15 && TotalAngle < 200) {  
       evs.bank_b.motorRunDegrees(SH_Motor_1, SH_Direction_Forward, EyePower, EyeDegree, SH_Completion_Wait_For,SH_Next_Action_BrakeHold); 
       TotalAngle = TotalAngle + EyeDegree;

       sprintf(s,"%d.%02d",(int)d,(int)(d*100)%100);
       uim.writeLine(0,1,s,true,EVs_UIM_GREEN);
       delay(1000);

       //Once distance is found, matches angle moved with appropriate turning distance to center robot to new direction
       if (us.getDist() > 15 && TotalAngle <= 200) {
          sprintf(s,"%d.%02d",(int)d,(int)(d*100)%100);
             uim.writeLine(0,1,s,true,EVs_UIM_GREEN);
              delay(1000);
              
          if (TotalAngle == 40) {
           evs.bank_a.motorRunRotations(SH_Motor_2, SH_Direction_Forward, SH_Speed_Slow,2/6, SH_Completion_Wait_For, SH_Next_Action_BrakeHold);
           evs.bank_a.motorRunRotations(SH_Motor_1, SH_Direction_Reverse, SH_Speed_Slow,2/6, SH_Completion_Wait_For, SH_Next_Action_BrakeHold);
           evs.bank_b.motorRunDegrees(SH_Motor_1, SH_Direction_Reverse, EyePower, TotalAngle, SH_Completion_Wait_For, SH_Next_Action_BrakeHold);
           
          
          }
          if (TotalAngle == 80) {
           evs.bank_a.motorRunRotations(SH_Motor_2, SH_Direction_Forward, SH_Speed_Slow,4/6, SH_Completion_Wait_For, SH_Next_Action_BrakeHold);
           evs.bank_a.motorRunRotations(SH_Motor_1, SH_Direction_Reverse, SH_Speed_Slow,4/6, SH_Completion_Wait_For, SH_Next_Action_BrakeHold);
           evs.bank_b.motorRunDegrees(SH_Motor_1, SH_Direction_Reverse, EyePower, TotalAngle, SH_Completion_Wait_For, SH_Next_Action_BrakeHold);
           
          
          }
          if (TotalAngle == 120) {
           evs.bank_a.motorRunRotations(SH_Motor_2, SH_Direction_Forward, SH_Speed_Slow,1, SH_Completion_Wait_For, SH_Next_Action_BrakeHold);
           evs.bank_a.motorRunRotations(SH_Motor_1, SH_Direction_Reverse, SH_Speed_Slow,1, SH_Completion_Wait_For, SH_Next_Action_BrakeHold);
           evs.bank_b.motorRunDegrees(SH_Motor_1, SH_Direction_Reverse, EyePower, TotalAngle, SH_Completion_Wait_For, SH_Next_Action_BrakeHold);
           
         
          }
          if (TotalAngle == 160) {
           evs.bank_a.motorRunRotations(SH_Motor_2, SH_Direction_Forward, SH_Speed_Slow,8/6, SH_Completion_Wait_For, SH_Next_Action_BrakeHold);
           evs.bank_a.motorRunRotations(SH_Motor_1, SH_Direction_Reverse, SH_Speed_Slow,8/6, SH_Completion_Wait_For, SH_Next_Action_BrakeHold);
           evs.bank_b.motorRunDegrees(SH_Motor_1, SH_Direction_Reverse, EyePower, TotalAngle, SH_Completion_Wait_For, SH_Next_Action_BrakeHold);
           
          
          }
          if (TotalAngle == 200) {
           evs.bank_a.motorRunRotations(SH_Motor_2, SH_Direction_Forward, SH_Speed_Slow,10/6, SH_Completion_Wait_For, SH_Next_Action_BrakeHold);
           evs.bank_a.motorRunRotations(SH_Motor_1, SH_Direction_Reverse, SH_Speed_Slow,10/6, SH_Completion_Wait_For, SH_Next_Action_BrakeHold);
           evs.bank_b.motorRunDegrees(SH_Motor_1, SH_Direction_Reverse, EyePower, TotalAngle, SH_Completion_Wait_For, SH_Next_Action_BrakeHold);
           
}
}       
}
          //Centers sensor if no valid distances on left side
          if (TotalAngle >= 200 && us.getDist() <= 15) {
           evs.bank_b.motorRunDegrees(SH_Motor_1, SH_Direction_Reverse, EyePower, TotalAngle, SH_Completion_Wait_For,SH_Next_Action_BrakeHold); 
          }
          
            TotalAngle = 0;

            sprintf(s,"%d.%02d",(int)d,(int)(d*100)%100);
            uim.writeLine(0,1,s,true,EVs_UIM_GREEN);
            delay(1000);

           //Loops sensor to the right searching for a valid distance   
           while (us.getDist() <= 15 && TotalAngle < 200) {
                     
           evs.bank_b.motorRunDegrees(SH_Motor_1, SH_Direction_Reverse, EyePower, EyeDegree, SH_Completion_Wait_For,SH_Next_Action_BrakeHold); 
           TotalAngle = TotalAngle + EyeDegree;

           
             sprintf(s,"%d.%02d",(int)d,(int)(d*100)%100);
             uim.writeLine(0,1,s,true,EVs_UIM_GREEN);
              delay(1000);

       //Matches valid distances with appropriate rotations to center the robot to the new direction       
       if (us.getDist() > 15 && TotalAngle <= 200) {
          sprintf(s,"%d.%02d",(int)d,(int)(d*100)%100);
          uim.writeLine(0,1,s,true,EVs_UIM_GREEN);
          delay(1000);
          
          if (TotalAngle == 40) {
           evs.bank_a.motorRunRotations(SH_Motor_1, SH_Direction_Forward, SH_Speed_Slow,2/6, SH_Completion_Wait_For, SH_Next_Action_BrakeHold);
           evs.bank_a.motorRunRotations(SH_Motor_2, SH_Direction_Reverse, SH_Speed_Slow,2/6, SH_Completion_Wait_For, SH_Next_Action_BrakeHold);
           evs.bank_b.motorRunDegrees(SH_Motor_1, SH_Direction_Forward, EyePower, TotalAngle, SH_Completion_Wait_For, SH_Next_Action_BrakeHold);
            
          
          }
          if (TotalAngle == 80) {
           evs.bank_a.motorRunRotations(SH_Motor_1, SH_Direction_Forward, SH_Speed_Slow,4/6, SH_Completion_Wait_For, SH_Next_Action_BrakeHold);
           evs.bank_a.motorRunRotations(SH_Motor_2, SH_Direction_Reverse, SH_Speed_Slow,4/6, SH_Completion_Wait_For, SH_Next_Action_BrakeHold);
           evs.bank_b.motorRunDegrees(SH_Motor_1, SH_Direction_Forward, EyePower, TotalAngle, SH_Completion_Wait_For, SH_Next_Action_BrakeHold);
             
          
          }
          if (TotalAngle == 120) {
           evs.bank_a.motorRunRotations(SH_Motor_1, SH_Direction_Forward, SH_Speed_Slow,6/6, SH_Completion_Wait_For, SH_Next_Action_BrakeHold);
           evs.bank_a.motorRunRotations(SH_Motor_2, SH_Direction_Reverse, SH_Speed_Slow,6/6, SH_Completion_Wait_For, SH_Next_Action_BrakeHold);
           evs.bank_b.motorRunDegrees(SH_Motor_1, SH_Direction_Forward, EyePower, TotalAngle, SH_Completion_Wait_For, SH_Next_Action_BrakeHold);
            
          
          }
          if (TotalAngle == 160) {
           evs.bank_a.motorRunRotations(SH_Motor_1, SH_Direction_Forward, SH_Speed_Slow,8/6, SH_Completion_Wait_For, SH_Next_Action_BrakeHold);
           evs.bank_a.motorRunRotations(SH_Motor_2, SH_Direction_Reverse, SH_Speed_Slow,8/6, SH_Completion_Wait_For, SH_Next_Action_BrakeHold);
           evs.bank_b.motorRunDegrees(SH_Motor_1, SH_Direction_Forward, EyePower, TotalAngle, SH_Completion_Wait_For, SH_Next_Action_BrakeHold);
            
          
          }
          if (TotalAngle == 200) {
           evs.bank_a.motorRunRotations(SH_Motor_1, SH_Direction_Forward, SH_Speed_Slow,10/6, SH_Completion_Wait_For, SH_Next_Action_BrakeHold);
           evs.bank_a.motorRunRotations(SH_Motor_2, SH_Direction_Reverse, SH_Speed_Slow,10/6, SH_Completion_Wait_For, SH_Next_Action_BrakeHold);
           evs.bank_b.motorRunDegrees(SH_Motor_1, SH_Direction_Forward, EyePower, TotalAngle, SH_Completion_Wait_For, SH_Next_Action_BrakeHold);
              
          
}        
}   
}
          //Centers sensor and turns the robot around if no valid distances detected
          if (us.getDist() <= 15) {
           evs.bank_b.motorRunDegrees(SH_Motor_1, SH_Direction_Forward, EyePower, TotalAngle, SH_Completion_Wait_For,SH_Next_Action_BrakeHold);

           evs.bank_a.motorRunRotations(SH_Motor_1, SH_Direction_Reverse, SH_Speed_Medium,4, SH_Completion_Wait_For, SH_Next_Action_BrakeHold);
           evs.bank_a.motorRunRotations(SH_Motor_2, SH_Direction_Forward, SH_Speed_Medium,4, SH_Completion_Wait_For, SH_Next_Action_BrakeHold); }
}
}
}    
}
  

