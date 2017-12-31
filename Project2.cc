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
	//int y = -70;
	//int a = 100;
	
  	ev3MotorSetPower(MOTOR_A, y);
  	ev3MotorSetPower(MOTOR_B, y);
	
	
/*
cout << "Arrow Keys Increment or decrement power by 10. Use Up and down buttons to change normal speed, and use left and right to determine turning power. Hit enter when ready to start." << endl;

while (!enterButton.isPressed()) {	
	
	if (upButton.isPressed()) {
		y = y - 10;
		ev3MotorSetPower(MOTOR_A, y);
		ev3MotorSetPower(MOTOR_B, y);
		cout << "Motor A = " << y << endl; 
		cout << "MOTOR B = " << y << endl;
			
			if (y < -100) {
				y == -100;}
}

	if (downButton.isPressed()) {
		y = y + 10;
		ev3MotorSetPower(MOTOR_A, y);
		ev3MotorSetPower(MOTOR_B, y);
		cout << "Motor A = " << y << endl;
		cout << "Motor A = " << y << endl;
			if (y > 100) {
				y == 100;}
 }
	

	if (rightButton.isPressed()) {
		a = a - 10;		
 
		cout << "Turn = " << a << endl;
			if (y < -100) {
				y == -100;}
		}

	if (leftButton.isPressed()) {
		a = a + 10;
		 
		cout << "Turn = " << a << endl;
			if (y > 100) {
				y == 100;}
		}

}
*/
while (!escapeButton.isPressed()) {
	
	ev3MotorRun(MOTOR_A);
	ev3MotorRun(MOTOR_B);

	
	if (ev3ColorReadReflected(SENSOR_1) < 45 || ev3olorReadReflected(SENSOR_1) > 55) {
		ev3MotorSetPower(MOTOR_A, -90);
		ev3MotorSetPower(MOTOR_B, -90);

}
	
	else { 
		ev3MotorSetPower(MOTOR_A, -90);
		ev3MotorSetPower(MOTOR_B, -90);	}
 
}

 
 ev3MotorStop(MOTOR_A,MOTOR_FINISH_COAST);
 ev3MotorStop(MOTOR_B,MOTOR_FINISH_COAST);
resetInputMode();
return 0;
}

