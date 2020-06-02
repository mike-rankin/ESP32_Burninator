//ESP32 Dev Board

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define MOT_EN 4    //Enable Power to Top motor power supply 
#define LASER_EN 12 //Enable Power to laser
#define RIGHT_PUSHBUTTON 10   
#define LEFT_PUSHBUTTON 32 

int RIGHT_BUTTON = 0;  //Right PushButton
int LEFT_BUTTON = 0;   //Left PushButton

int i=0;

int TOP_LIMIT = 0;
int BOTTOM_LIMIT = 0;

Adafruit_SSD1306 display(96, 16, &Wire, 22);

//Top Motor
#define EN_1 33           //Motor Enable
#define STCK_1 26         //Motor Clock
#define DIR_1 15          //Motor Direction
#define LIMIT_SWITCH_1 34 //Top Limit Switch

//Bottom Motor
#define EN_2 25           //Motor Enable
#define STCK_2 27         //Motor Clock
#define DIR_2 2           //Motor Direction
#define LIMIT_SWITCH_2 35 //Bottom Limit Switch


void setup() 
{
 Serial.begin(9600);
 Wire.begin(13, 14); 
 display.setRotation(2);
 display.begin(SSD1306_SWITCHCAPVCC, 0x3C);

 display.display();
 delay(500); 
 display.clearDisplay();
 display.setTextSize(1);             // Normal 1:1 pixel scale
 display.setTextColor(WHITE);        // Draw white text
 display.setCursor(0,0);             // Start at top-left corner
 display.println(F("ESP32 Burninator"));
 display.display();
 delay(2000);

 pinMode(RIGHT_PUSHBUTTON, INPUT);
 pinMode(LEFT_PUSHBUTTON, INPUT); 
 
 pinMode(LIMIT_SWITCH_2, INPUT); //Bottom 
 pinMode(LIMIT_SWITCH_1, INPUT); //Top
 
 pinMode(MOT_EN,     OUTPUT);
 pinMode(LASER_EN,   OUTPUT);
 pinMode(EN_1,       OUTPUT);   
 pinMode(EN_2,       OUTPUT);
 pinMode(STCK_1,     OUTPUT); 
 pinMode(STCK_2,     OUTPUT);
 pinMode(DIR_1,      OUTPUT); 
 pinMode(DIR_2,      OUTPUT); 

 digitalWrite(MOT_EN, HIGH); //Power up Motors
 delay(100);
 
 digitalWrite(EN_1, HIGH); //Enable Motor
 digitalWrite(EN_2, HIGH); //Enable Motor

  Go_To_Center();
  Burn_Square();

}


void loop() 
{
 digitalWrite(EN_1, HIGH); //Enable Motor
 digitalWrite(EN_2, HIGH); //Enable Motor
  
 RIGHT_BUTTON = digitalRead(RIGHT_PUSHBUTTON); //read the right button
 LEFT_BUTTON = digitalRead(LEFT_PUSHBUTTON);   //read the left button

 digitalWrite(LASER_EN, LOW); //Power off Laser
}

void Move_Top_Motor_Right()
{
 digitalWrite(DIR_1, HIGH); //Direction: LOW=Left, HIGH=Right 

 for (int i=0; i <= 10; i++)  //Move left
  {
   digitalWrite(STCK_1, HIGH);
   delay(1);
   digitalWrite(STCK_1, LOW);
   delay(1);
  }
}

void Move_Top_Motor_Left()
{
 digitalWrite(DIR_1, LOW); //Direction: LOW=Left, HIGH=Right  

 for (int i=0; i <= 10; i++)  //Move left
  {
   digitalWrite(STCK_1, HIGH);
   delay(1);
   digitalWrite(STCK_1, LOW);
   delay(1);
  }
}

void Move_Bottom_Motor_Out()
{
 digitalWrite(EN_2, HIGH);  //Enable Bottom Motor
 digitalWrite(DIR_2, HIGH); //Direction: LOW=Out, HIGH=In 

 for (int i=0; i <= 10; i++)  //Move left
  {
   digitalWrite(STCK_2, HIGH);
   delay(1);
   digitalWrite(STCK_2, LOW);
   delay(1);
  }
}

void Move_Bottom_Motor_In()
{
 digitalWrite(EN_2, HIGH);  //Enable Bottom Motor
 digitalWrite(DIR_2, LOW); //Direction: LOW=Out, HIGH=In 

 for (int i=0; i <= 10; i++)  //Move left
  {
   digitalWrite(STCK_2, HIGH);
   delay(1);
   digitalWrite(STCK_2, LOW);
   delay(1);
  }
}


void Go_To_Center()
{  
 for (int j=0; j<=150; j++)
 {
  Move_Top_Motor_Right();
  j=j+1;
  display.clearDisplay();
  display.setCursor(10,0);
  display.print("X: ");            
  display.print(j);
  display.display();
 }
 
 for (int j=0; j<=150; j++)
 {
  Move_Top_Motor_Left();
  j=j+1;
  display.clearDisplay();
  display.setCursor(10,0); 
  display.print("-X: ");          
  display.print(j);
  display.display();
 }

 for (int j=0; j<=60; j++)
 {
  Move_Top_Motor_Right();
  j=j+1;
  display.clearDisplay();
  display.setCursor(10,0); 
  display.print("X: ");          
  display.print(j);
  display.display();
 }

 for (int k=0; k<=150; k++)
 {
  Move_Bottom_Motor_In();
  k=k+1;
  display.clearDisplay();
  display.setCursor(30,0);
  display.print("-Y: ");           
  display.print(k);
  display.display();
 }

 for (int k=0; k<=150; k++)
 {
  Move_Bottom_Motor_Out();
  k=k+1;
  display.clearDisplay();
  display.setCursor(30,0);
  display.print("Y: ");           
  display.print(k);
  display.display();
 }

 for (int k=0; k<=200; k++)
 {
  Move_Bottom_Motor_In();
  k=k+1;
  display.clearDisplay();
  display.setCursor(30,0); 
  display.print("-Y: ");          
  display.print(k);
  display.display();
 }
}

void Burn_Square()
{ 
 Laser_Enable();
 display.clearDisplay();
 display.setCursor(0,0);           
 display.print("Burninating!");
 display.display();
 
 for (int j=0; j<=20; j++)
 {
  Move_Top_Motor_Right();
  delay(100);
 }

 for (int j=0; j<=20; j++)
 {
  Move_Bottom_Motor_Out();
  delay(100);
 }

 for (int j=0; j<=20; j++)
 {
  Move_Top_Motor_Left();
  delay(100);
 }

 for (int j=0; j<=20; j++)
 {
  Move_Bottom_Motor_In();
  delay(100);

  display.clearDisplay();
  display.setCursor(0,0);           
  display.print("Done...");
  display.display();
 }

 digitalWrite(LASER_EN, LOW);
 
 for (int k=0; k<=150; k++)
 {
  Move_Bottom_Motor_Out();
 }
    
}

void Laser_Enable()
{
 digitalWrite(LASER_EN, HIGH); //Power up Laser
}
