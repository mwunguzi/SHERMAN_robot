//Include Libraries
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

//create an RF24 object
RF24 radio(7, 8);  // CE, CSN

//declaring and initializing variables for the joy_stick
int swtchbutton=4;
int x,y,bttnRead;

//address through which two modules communicate.
const byte address[6] = "00001";

void setup()
{

  Serial.begin(9600);
  radio.begin();

  //setting pin mode for the joystick switch-button
  pinMode(swtchbutton,INPUT);
 
  //set the address
  radio.openWritingPipe(address);
  radio.setDataRate(RF24_2MBPS);
  //Set module as transmitter
  radio.stopListening();
}
void loop()
{

  char sendcommand;

 if(Serial.available())
 {
    sendcommand=Serial.read();
    if(sendcommand =='f')
    {
        //reading values from the joystick
        x=1023;
        y=514;
        bttnRead=digitalRead(swtchbutton);
        //Send message to receiver
        char joystickPos[10];
        sprintf(joystickPos, "%i,%i", x, y);
        radio.write(&joystickPos, sizeof(joystickPos));
       
  
    }
    if(sendcommand =='s')
    {
         //reading values from the joystick
          x=514;
          y=512;
          bttnRead=digitalRead(swtchbutton);
          //Send message to receiver
          char joystickPos[10];
          sprintf(joystickPos, "%i,%i", x, y);
          radio.write(&joystickPos, sizeof(joystickPos));
         
  
    }
   //Serial.println("Herve Here");
}
else{
  //reading values from the joystick
  x=analogRead(A0);
  y=analogRead(A1);
  bttnRead=digitalRead(swtchbutton);
  
  //Send message to receiver
  char joystickPos[10];
  sprintf(joystickPos, "%i,%i", x, y);
  radio.write(&joystickPos, sizeof(joystickPos));
 
}
}
