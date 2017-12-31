#include <iostream>
#include <unistd.h>
#include <time.h>
#include <ev3dev.h> 


using namespace std;

int main(void) {
  timespec tv;  
 
  	ev3Setup();
  	ev3MotorReset(MOTOR_A);
  	ev3MotorReset(MOTOR_B);
  	setInputMode();
  	ev3ColorSetMode(SENSOR_1,0);
	int Isp = 50;
	int Osp = -40;
	int error1, Derror;
	int error2 = 0;
	int Pid = 0;
	int KP = 2;
	float KI = .015;
	float KD = .05;
	int Terror = 0;	
	
while (!escapeButton.isPressed()) {
	
	ev3MotorRun(MOTOR_A);
	ev3MotorRun(MOTOR_B);
		
	error1 = ev3ColorReadReflected(SENSOR_1) - 50;
	error2 = ev3ColorReadReflected(SENSOR_1) - 50;
	Derror = error1 - error2;
	Terror = Terror + error1;
	error2 = error1;
	
	Pid = (error1 * KP) + (Terror * KI) + (Derror * KD);

	ev3MotorSetPower(MOTOR_A, (Osp + Pid));
  	ev3MotorSetPower(MOTOR_B, (Osp - Pid));
		
	
}

 ev3MotorStop(MOTOR_A,MOTOR_FINISH_COAST);
 ev3MotorStop(MOTOR_B,MOTOR_FINISH_COAST);
resetInputMode();
return 0;
}

