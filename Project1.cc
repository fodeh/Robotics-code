#include <iostream>
#include <unistd.h>
#include <time.h>
#include <ev3dev.h> 
#include <sstream>

using namespace std;

int main(void) {
  timespec tv;
  int barA, barB;  
  stringstream code;
  ev3Setup();
  ev3MotorReset(MOTOR_A);
  ev3MotorReset(MOTOR_B);
  setInputMode();
  ev3ColorSetMode(SENSOR_1,0);
	int x = 0;
	int y = 0;

while (x < 10 || !enterButton.isPressed()) {
	tv.tv_sec = 0;
	tv.tv_nsec = 300000000;

	ev3MotorRun(MOTOR_A);
	ev3MotorRun(MOTOR_B);
	ev3MotorSetPower(MOTOR_A,-25);
	ev3MotorSetPower(MOTOR_B,-27);
	
	barA = ev3ColorReadReflected(SENSOR_1);
	nanosleep(&tv,NULL);
	barB = ev3ColorReadReflected(SENSOR_1);
	x++;
	
if (barA > 50 && barB < 50) {	
	y++;	
	cout << "Edge of bar" << endl;
	if (y == 1) { x = 0; } 
	
if (y > 1) { 
	if (x <= 2) { code << 0;
	x = 0; }
	if (x > 2) { code << 1;
	x = 0; }
}
 }	
else if (barA < 50 && barB > 50) {	
	y++;	
	cout << "Edge of bar" << endl;
	if (y == 1) { x = 0; } 
	
if (y > 1) { 
	if (x <= 2) { code << 0;
	x = 0; }
	if (x > 2) { code << 1;
	x = 0; }
}
 }
cout << code.str() << endl;
if (y ==10) { break; }
  }
cout << code.str() << endl; 
 ev3MotorStop(MOTOR_A,MOTOR_FINISH_COAST);
 ev3MotorStop(MOTOR_B,MOTOR_FINISH_COAST);
resetInputMode();
return 0;
}
