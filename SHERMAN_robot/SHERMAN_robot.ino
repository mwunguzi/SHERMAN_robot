
uint8_t swtchbutton=8;
uint8_t bttnRead,ENA=6,ENB=5,IN1=48,IN2=46,IN3=52,IN4=50;
double x,y;


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

//this is a function that input the value of the joystick and tell which way it's heading
float convertXYtoAngle(uint16_t a,uint16_t b){

 float x_cord,y_cord,angle;
 
 y_cord = map(a,0,1023,-512,512)-2;
 x_cord = map(b,0,1023,-512,512)+1;
 Serial.print(" x_cordinate= ");
 Serial.println(x_cord);
 Serial.print("Y_cordinate= ");
 Serial.println(y_cord);
 angle=atan2(y_cord,x_cord)*(180/PI);// obtaining the angle in degrees
 return floor(angle);
}

void mainDrive(float input_angle,double input_inte_joystick){

  //checking the the angle of the joystict is in the first or the second Quadrant
  if(input_angle>1){
   
    //setting the motor speed
  analogWrite(ENB,(30-(cos(input_angle)))+input_inte_joystick);
  analogWrite(ENA,30+input_inte_joystick);
  
 Serial.print(" speed A: ");
 Serial.println(30+input_inte_joystick);
 Serial.print("speed B ");
 Serial.println((30-(cos(input_angle)))+input_inte_joystick);
 
  //making initial 1 and initial 4 high to move forward
  digitalWrite(IN1,HIGH);
  digitalWrite(IN2,LOW);
  digitalWrite(IN3,LOW);
  digitalWrite(IN4,HIGH);
  }
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



void loop() {
  // put your main code here, to run repeatedly:
double inte_joystick;
double red_x,red_y;
x=analogRead(A0);
y=analogRead(A1);

//reduced x because the center value is (500,500) and absolute function doesn't like calculation inside abs
red_x = (x-514);
red_y = (y-511);

inte_joystick=pow((red_x*red_x) + (red_y*red_y),0.5); //reading the intensity on the joystock
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
for(int i=90;i>1;i-=12){
mainDrive(i,10);
Serial.println(i);
delay(1000);
}
}
