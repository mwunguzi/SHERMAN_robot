uint8_t swtchbutton=8;
volatile uint8_t bttnRead,ENA=6,ENB=5,IN1=48,IN2=46,IN3=52,IN4=50;
volatile uint16_t x,y;


//function of driving a robot forward
void driveForward(uint8_t speeed){

  //setting the motor speed
  analogWrite(ENA,speeed);
  analogWrite(ENB,speeed);
  
  //making initial 1 and initial 4 high to move forward
  digitalWrite(IN1,HIGH);
  digitalWrite(IN2,LOW);
  digitalWrite(IN3,LOW);
  digitalWrite(IN4,HIGH);
}

//function of driving the robot backward
void driveBackward(uint8_t speeed){

  //setting the motor speed
  analogWrite(ENA,speeed);
  analogWrite(ENB,speeed);
  
  //making initial 2 and initial 3 high to move backward
  digitalWrite(IN1,LOW);
  digitalWrite(IN2,HIGH);
  digitalWrite(IN3,HIGH);
  digitalWrite(IN4,LOW);
}

//function for turning right
void turningRight(uint8_t speedl,uint8_t speedr){

  //setting the motor speed
  analogWrite(ENA,speedl);
  analogWrite(ENB,speedr);
  
  //making initial 2 and initial 3 high to move backward
  digitalWrite(IN1,HIGH);
  digitalWrite(IN2,LOW);
  digitalWrite(IN3,LOW);
  digitalWrite(IN4,HIGH);
}


void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
pinMode(swtchbutton,INPUT); // INTITIALIZING THE PRESS BUTTON ON THE JOYSTIC AS INPUT

//Initializing the motor pins as output
pinMode(ENA,OUTPUT);
pinMode(ENB,OUTPUT);
pinMode(IN1,OUTPUT);
pinMode(IN2,OUTPUT);
pinMode(IN3,OUTPUT);
pinMode(IN4,OUTPUT);

}

//this is a function that input the value of the joystick and tell which way it's heading
float convertXYtoAngle(uint16_t a,uint16_t b){

 float x_cord,y_cord,angle;
 
 y_cord = map(a,0,1023,-512,512);
 x_cord = map(b,0,1023,-512,512);
 angle=atan2(y_cord,x_cord)*(180/PI);// obtaining the angle in degrees
 return angle;
}

void loop() {
  // put your main code here, to run repeatedly:
float inte_joystick;
x=analogRead(A0);
y=analogRead(A1);
inte_joystick=sqrt(pow(abs(x-512),2),pow(abs(y-512),2)); //reading the intensity on the joystock
bttnRead=digitalRead(swtchbutton);
Serial.println("X:  Y:  Button:");
Serial.print(x);
Serial.print("  ");
Serial.print(y);
Serial.print("  ");
Serial.println(bttnRead);
Serial.print("angle= ");
Serial.println(convertXYtoAngle(x,y));
Serial.print("intensity on the joystick= ");
Serial.println(inte_joystick);

}
