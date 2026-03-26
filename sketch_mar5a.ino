/*
  SparkFun Inventor’s Kit
  Circuit 5B - Remote Control Robot

  Control a two wheeled robot by sending direction commands through the serial monitor.
  This sketch was adapted from one of the activities in the SparkFun Guide to Arduino.
  Check out the rest of the book at
  https://www.sparkfun.com/products/14326

  This sketch was written by SparkFun Electronics, with lots of help from the Arduino community.
  This code is completely free for any use.

  View circuit diagram and instructions at: https://learn.sparkfun.com/tutorials/sparkfun-inventors-kit-experiment-guide---v40
  Download drawings and code at: https://github.com/sparkfun/SIK-Guide-Code
*/

//Code for part 1 of lab.

#include <SoftwareSerial.h>

SoftwareSerial mySerial(2, 3); // HC-05 Tx connected to Arduino #2 & HC-05 Rx to Arduino #3

const byte numChars = 16;       
char receivedChars[numChars];  // an array to store the received data
char tempChars[numChars];

char botDir[numChars] = {0};         // char type variable for the direction of the robot
int botSpeed = 0;           //stores the speed of the whole robot
boolean newData = false;
int motorSpeed = 0;

//the right motor will be controlled by the motor A pins on the motor driver
const int AIN1 = 13;           //control pin 1 on the motor driver for the right motor
const int AIN2 = 12;            //control pin 2 on the motor driver for the right motor
const int PWMA = 11;            //speed control pin on the motor driver for the right motor

//the left motor will be controlled by the motor B pins on the motor driver
const int PWMB = 10;           //speed control pin on the motor driver for the left motor
const int BIN2 = 9;           //control pin 2 on the motor driver for the left motor
const int BIN1 = 8;           //control pin 1 on the motor driver for the left motor

int switchPin = 7;             //switch to turn the robot on and off

const int driveTime = 20;      //this is the number of milliseconds that it takes the robot to drive 1 inch
                               //it is set so that if you tell the robot to drive forward 25 units, the robot drives about 25 inches

const int turnTime = 8;        //this is the number of milliseconds that it takes to turn the robot 1 degree
                               //it is set so that if you tell the robot to turn right 90 units, the robot turns about 90 degrees

                               //Note: these numbers will vary a little bit based on how you mount your motors, the friction of the
                               //surface that your driving on, and fluctuations in the power to the motors.
                               //You can change the driveTime and turnTime to make them more accurate

String botDirection;           //the direction that the robot will drive in (this change which direction the two motors spin in)
String speed ; // the speed input 
//Code for part 1 of lab.

const int trigPin = 6; // initilizes the trig pin
const int echoPin = 7;// initilized the echo pin
 

 
void setup() { // set up portion of the code. 
mySerial.begin(9600);
  mySerial.begin(9600);       //Default Baud Rate for software serial communications
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
//set the motor control pins as outputs
  pinMode(AIN1, OUTPUT);
  pinMode(AIN2, OUTPUT);
  pinMode(PWMA, OUTPUT);

  pinMode(BIN1, OUTPUT);
  pinMode(BIN2, OUTPUT);
  pinMode(PWMB, OUTPUT);
  Serial.begin(9600);

  //prompt the user to enter a command
  Serial.println("Enter a direction followed by a speed (23-200 from slow to fast) followed by a space ");
  Serial.println(" L = turn left, R = turn right, B = backward, F = forward, X= stop ");
  Serial.println("Example command: B 50 ");
// INCLUDE THESE LINES AT THE BEGINNING OF THE SKETCH FILE


}
 
void loop() {
int Speed;
  digitalWrite(trigPin, LOW); // trig pin/ set it to a low voltage to turn off the ultrasonic signal allowing for it to reset.
  delayMicroseconds(2); // delays the function of the circuit to let the sensor read/ function. 
  digitalWrite(trigPin, HIGH); // turn on 
  delayMicroseconds(10); // delays the function of the circuit to let the sensor read/ function.
  digitalWrite(trigPin, LOW); // turn off trig pin/ set it to a low voltage to turn off the ultrasonic signal allowing for it to reset.

  float duration, distance;

  duration = pulseIn(echoPin, HIGH); // starts the ultra sonic sound wave
  distance = (duration*.0343)/2; // speed of sound conversion
  Serial.print("Distance: "); // distance measured in cm this line displays the distance in the serial monitor window
  Serial.println(distance); // this prints the distance it is moving after Distance: in our serial monitor.
 delay(100);

  if ( true )
  {                                                     // the code always runs
    if (Serial.available() > 0)                         //if the user has sent a command to the RedBoard
    {
      botDirection = Serial.readStringUntil(' ');       //read the characters in the command until you reach the first space
      speed = Serial.readStringUntil(' ');           //read the characters in the command until you reach the second space



      //print the command that was just received in the serial monitor
      Serial.print(botDirection);
      Serial.print(" ");
      Serial.println(speed);
      Speed = speed.toInt();
    }
    recvWithEndMarker();                    // Calls a function to check the software serial port
  if (newData == true)                    // Any new data from the software serial port?
  {
    strcpy(tempChars, receivedChars);    // Creates a copy of the received data
    parseData();                         // Call to a function that parses the received Data
    botDirection = botDir;               // Assigns the direction received via softweare serial port
    Speed = botSpeed;               // Assigns the speed received via softweare serial port
    newData = false;                     // Reset the new data flag
    Serial.println(botDirection);        // Print new direction and speed
    Serial.println(Speed);
  }
      if (botDirection == "F")                         //if the entered speed is high
      {
        rightMotor(Speed);                                //drive the right wheel forward
        leftMotor(-Speed);                                 //drive the left wheel forward
                                     
      }
       if (botDirection == "B")                         //if the entered speed is medium
      {
        rightMotor(-Speed);                                //drive the right wheel forwar                                //drive the right wheel forward
        leftMotor(Speed);                                 //drive the left wheel forward
                                     
      }
       if (botDirection == "L")                         //if the entered direction is low
      {
        rightMotor(Speed);                                //drive the right wheel forward
        leftMotor(Speed);                                 //drive the left wheel forward
                                     
      }
      if (botDirection == "R")
      {
        rightMotor(-Speed);                                //drive the right wheel forward
        leftMotor(-Speed);                                 //drive the left wheel forward
                                     
      }
      if (botDirection == "X")
      {
        rightMotor(0);                                //drive the right wheel forward
        leftMotor(0);                                 //drive the left wheel forward
                                     
      }
    }
  else
  {
    rightMotor(0);                                  //turn the right motor off
    leftMotor(0);                                   //turn the left motor off
  }
  if (distance < 10.00)
  {
    rightMotor(0);
    leftMotor(0);
  }
}

/********************************************************************************/
void rightMotor(int motorSpeed)                       //function for driving the right motor
{
  if (motorSpeed > 0)                                 //if the motor should drive forward (positive speed)
  {
    digitalWrite(AIN1, HIGH);                         //set pin 1 to high
    digitalWrite(AIN2, LOW);                          //set pin 2 to low
  }
  else if (motorSpeed < 0)                            //if the motor should drive backward (negative speed)
  {
    digitalWrite(AIN1, LOW);                          //set pin 1 to low
    digitalWrite(AIN2, HIGH);                         //set pin 2 to high
  }
  else                                                //if the motor should stop
  {
    digitalWrite(AIN1, LOW);                          //set pin 1 to low
    digitalWrite(AIN2, LOW);                          //set pin 2 to low
  }
  analogWrite(PWMA, abs(motorSpeed));                 //now that the motor direction is set, drive it at the entered speed
}

/********************************************************************************/
void leftMotor(int motorSpeed)                        //function for driving the left motor
{
  if (motorSpeed > 0)                                 //if the motor should drive forward (positive speed)
  {
    digitalWrite(BIN1, HIGH);                         //set pin 1 to high
    digitalWrite(BIN2, LOW);                          //set pin 2 to low
  }
  else if (motorSpeed < 0)                            //if the motor should drive backward (negative speed)
  {
    digitalWrite(BIN1, LOW);                          //set pin 1 to low
    digitalWrite(BIN2, HIGH);                         //set pin 2 to high
  }
  else                                                //if the motor should stop
  {
    digitalWrite(BIN1, LOW);                          //set pin 1 to low
    digitalWrite(BIN2, LOW);                          //set pin 2 to low
  }
  analogWrite(PWMB, abs(motorSpeed));                 //now that the motor direction is set, drive it at the entered speed
}
void recvWithEndMarker() {
    static byte ndx = 0;
    char endMarker = '\n';
    char rc;
    while (mySerial.available() > 0 && newData == false){
      rc = mySerial.read();
      if (rc != endMarker) {
        receivedChars[ndx] = rc;
        ndx++;
        if (ndx >= numChars){
          ndx = numChars - 1;
        }
      }
      else {
        receivedChars[ndx] = '\0'; // terminate the string
        ndx = 0;
        newData = true;
      }
    }
}
/*****************************************************************************************/
void parseData() {      // split the data into its parts

    char * strtokIndx; // this is used by strtok() as an index
    strtokIndx = strtok(tempChars," ");      // get the first part - the string
    strcpy(botDir, strtokIndx); // copy it to messageFromPC
 
    strtokIndx = strtok(NULL, "\l\n"); // this continues where the previous call left off
    //strcpy(botSpeed, strtokIndx); // Use this line for sending speed as text
    botSpeed = atoi(strtokIndx);     // Use this line for sending speed as an integer

}
