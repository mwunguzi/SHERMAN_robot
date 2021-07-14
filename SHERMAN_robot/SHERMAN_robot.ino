
//Include Libraries
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

//create an RF24 object
RF24 radio(7, 8);  // CE, CSN

//address through which two modules communicate.
const byte address[6] = "00001";

uint8_t swtchbutton = 8;
uint8_t bttnRead, ENA = 6, ENB = 5, IN1 = 48, IN2 = 46, IN3 = 24, IN4 = 22;
double x, y, previousNum = 0;


//function of driving a robot forward
void driveForward(uint8_t speeed) {

  //setting the motor speed
  analogWrite(ENA, speeed);
  analogWrite(ENB, speeed);

  //making initial 1 and initial 4 high to move forward
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}

//function of driving the robot backward
void driveBackward(uint8_t speeed) {

  //setting the motor speed
  analogWrite(ENA, speeed);
  analogWrite(ENB, speeed);

  //making initial 2 and initial 3 high to move backward
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

//function for turning right
void turningRight(uint8_t speedl, uint8_t speedr) {

  //setting the motor speed
  analogWrite(ENA, speedl);
  analogWrite(ENB, speedr);

  //making initial 2 and initial 3 high to move backward
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}

//this is a function that input the value of the joystick and tell which way it's heading
float convertXYtoAngle(uint16_t a, uint16_t b) {

  float x_cord, y_cord, angle;

  y_cord = map(a, 0, 1023, -512, 512) - 13;
  x_cord = map(b, 0, 1023, -512, 512) - 5;
  
  // Serial.print(" x_cordinate= ");
  // Serial.println(x_cord);
  // Serial.print("Y_cordinate= ");
  // Serial.println(y_cord);
  
  angle = atan2(y_cord, x_cord) * (180 / PI); // obtaining the angle in degrees
  return floor(angle);
  
}

//this is a function to control the change of the intensity on the joystick
double change_when_new_number(double num) {

  double returnNum;

  if (previousNum >= num or previousNum < num) {

    returnNum = previousNum - num;
    previousNum = num;
    return returnNum;

  }

}

//this is a function to drive the robot in response to the joystick movement
void mainDrive(float input_angle, double input_inte_joystick) {

  //    Serial.print(" angle ");
  //    Serial.println(input_angle);

  double inputSpeedA, inputSpeedB; //This will be the values for the input to controll how fast the motors are moving
  double changeInJoystick;

  //checking the the angle of the joystick is in the first or the second Quadrant
  if (input_angle > 5) {

    changeInJoystick = change_when_new_number(input_inte_joystick);
    inputSpeedA = 50 + (30 * cos((input_angle * PI / 180)));
    inputSpeedB = (50 + (-30 * cos((input_angle * PI / 180))));


    //setting the motor speed
    analogWrite(ENB, inputSpeedB);
    analogWrite(ENA, inputSpeedA);

    //    Serial.print(" speed A: ");
    //    Serial.println(inputSpeedA);
    //    Serial.print("speed B ");
    //    Serial.println(inputSpeedB);
    //    // Serial.print("joystick: ");
    // Serial.println(change_when_new_number(input_inte_joystick));

    //making initial 1 and initial 4 high to move forward
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, HIGH);
    
  }
  else if (input_angle < -5 ) { // condition to make the robot move backwards

    changeInJoystick = change_when_new_number(input_inte_joystick);
    inputSpeedA = 50 + (30 * cos((input_angle * PI / 180)));
    inputSpeedB = (50 + (-30 * cos((input_angle * PI / 180))));


    //setting the motor speed
    analogWrite(ENB, inputSpeedB);
    analogWrite(ENA, inputSpeedA);

    //    Serial.print(" speed A: ");
    //    Serial.println(inputSpeedA);
    //    Serial.print("speed B ");
    //    Serial.println(inputSpeedB);

    //making initial 2 and initial 3 high to move backward
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, HIGH);
    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, LOW);

  }
  if (input_angle == 0 ) {

    analogWrite(ENB, 0);
    analogWrite(ENA, 0);
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, LOW);
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, LOW);
  }

  if (input_angle == -135) { //this is to stop the robot from moving when the remote is not connected

    analogWrite(ENB, 0);
    analogWrite(ENA, 0);
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, LOW);
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, LOW);
    
  }
  
}


void setup() {
  // put your setup code here, to run once:
  //Serial.begin(9600);
  //pinMode(swtchbutton,INPUT); // INTITIALIZING THE PRESS BUTTON ON THE JOYSTIC AS INPUT

  //Initializing the motor pins as output
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  while (!Serial);

  Serial.begin(9600);

  radio.begin();

  //set the address
  radio.openReadingPipe(0, address);

  radio.setPALevel(RF24_PA_MAX);
  radio.setDataRate(RF24_1MBPS);
  //Set module as receiver
  radio.startListening();

}



void loop() {
  
  // put your main code here, to run repeatedly:
  double inte_joystick;
  double red_x, red_y;
  //radio.startListening();
  //Read the data if available in buffer
  if (radio.available())
  {
    char joystickPos[10];
    
    radio.read(&joystickPos, sizeof(joystickPos));
    
    //    Serial.print("x, y: ");
    //    Serial.println(joystickPos);
    //delay(1000);

    //parsing the joystickPos string to obtain the x and y joystick positions
    const char delimiter[] = ","; //the character to look for when parsing
    
    char parsedStrings[2][5]; //char array to store parsed strings
    
    char *token =  strtok(joystickPos, delimiter); //diving the string at ","
    
    strncpy(parsedStrings[0], token, sizeof(parsedStrings[0]));//first one
    
    for (int i = 1; i < 2; i++) {
      
      token =  strtok(NULL, delimiter);
      
      strncpy(parsedStrings[i], token, sizeof(parsedStrings[i]));
    }

    //for (int i = 0; i < 2; i++){
    //Serial.println(parsedStrings[i]);}//  should have the 2 data strings parsed o
    x = atoi(parsedStrings[0]);
    
    y = atoi(parsedStrings[1]);
    
  }
//  else if (! radio.available()){
//    x=513;
//    y=511;
//  }
      Serial.print(" x_cordinate= ");
      Serial.println(x);
      Serial.print("Y_cordinate= ");
      Serial.println(y);

  //reduced x because the center value is (500,500) and absolute function doesn't like calculation inside abs
  red_x = (x - 513);
  red_y = (y - 511);

  inte_joystick = pow((red_x * red_x) + (red_y * red_y), 0.5); //reading the intensity on the joystock 
  
  bttnRead = digitalRead(swtchbutton);
  
  //  Serial.print("  ");
  //Serial.println(bttnRead);
  Serial.print("angle= ");
  Serial.println(convertXYtoAngle(x,y));
  //Serial.print("intensity on the joystick= ");
  //Serial.println(inte_joystick);

  mainDrive(convertXYtoAngle(x, y), inte_joystick);
  
}
