/********
* Arduino code for Wireless Surveilance Rover made using Mediatek Cloud Sandbox and LinkIt Smart 7688 Dev board
* This will be the core controller of the rover.
* It will received the command from mcs and parse it to perform tasks
*
* Author : Jeff Paredes
* Version : 1.0
*/

const int motorIn1 = 2;
const int motorIn2 = 3;
const int motorIn3 = 4;      
const int motorIn4 = 5;       

String dpadLeft_press = "left|1";
String dpadLeft_release = "left|0";
String dpadUp_press = "up|1";
String dpadUp_release = "up|0";
String dpadRight_press = "right|1";
String dpadRight_release = "right|0";
String dpadDown_press = "down|1";
String dpadDown_release = "down|0";

const int DELAY = 1000;

void setup()  
{
	// Listen to nodejs application
  Serial1.begin(57600);
  	// Listen to default serial
  Serial.begin(9600);
  pinMode(motorIn1, OUTPUT);
  pinMode(motorIn2, OUTPUT);
  pinMode(motorIn3, OUTPUT);
  pinMode(motorIn4, OUTPUT);    
}

void loop()
{
  String command="";
  while (Serial1.available()) {
   int v = Serial1.read(); 
   Serial.println(v, DEC);
    if ( v != -1) {
      command += (char)v;
      Serial.println(command);
      if (command.equals(dpadLeft_press)) {
        left();
        delay(DELAY);
        command = "";
      } else if (command.equals(dpadLeft_release)) {
        motorstop();
        command = "";
        delay(500);
      } else if (command.equals(dpadUp_press)) {
        forward();
        command = "";
        delay(DELAY);
      } else if (command.equals(dpadUp_release)) {
        motorstop();
        command = "";
        delay(500);
      } else if (command.equals(dpadRight_press)) {
        right();
        command = "";
        delay(DELAY);
      } else if (command.equals(dpadRight_release)) {
        motorstop();
        command = "";
        delay(500);
      } else if (command.equals(dpadDown_press)) {
        backward();
        command = "";
        delay(DELAY);
      } else if (command.equals(dpadDown_release)) {
        motorstop();
        command = "";
        delay(500);
      }
    }
  }
}

void motorstop()
{
  digitalWrite(motorIn1, LOW);
  digitalWrite(motorIn2, LOW);
  digitalWrite(motorIn3, LOW);
  digitalWrite(motorIn4, LOW);
}

void forward()
{
  digitalWrite(motorIn1, HIGH);
  digitalWrite(motorIn2, LOW);
  digitalWrite(motorIn3, HIGH);
  digitalWrite(motorIn4, LOW);
}

void backward()
{
  digitalWrite(motorIn1, LOW);
  digitalWrite(motorIn2, HIGH);
  digitalWrite(motorIn3, LOW);
  digitalWrite(motorIn4, HIGH);
}

// Let right motor keep running, but stop left motor
void right()
{
  digitalWrite(motorIn1, HIGH);
  digitalWrite(motorIn2, LOW);
  digitalWrite(motorIn3, LOW);
  digitalWrite(motorIn4, LOW);
}

// Let left motor keep running, but stop right motor
void left()
{
  digitalWrite(motorIn1, LOW);
  digitalWrite(motorIn2, LOW);
  digitalWrite(motorIn3, HIGH);
  digitalWrite(motorIn4, LOW);
}

void showMessageDisplay(String msg){

}