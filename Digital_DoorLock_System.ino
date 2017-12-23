//**** Documentation section *****************
// This program is for DIGITAL DOOR LOCK SYSTEM using Arduino Mega.
// Author : Harshit Srivastava
// Date : 15th January 2017




// Library declaration section.
#include<Keypad.h> // Standard Keypad Library for interfacing   
#include<LiquidCrystal.h> // Standard Library 16 X 2 LCD Module interafacing
#include<Servo.h>// Library for Servo motors

// define the GPIO Connected to the Sensors.
#define Servo_PIN 3 // PIN no for Servo Motor (PWM PIN)  
#define buzzer 36 // PIN no for PIEZO buzzer. 
#define LDR_PIN A1 // PIN no for Detecting the brightness of surrounding
          //to adjust the brightness of the LCD Screen
#define UltraSonic_trigPIN 38 // connected to trig Pin on Ultrasonic Sensor  
#define UltraSonic_echoPIN 39 // connected to echo Pin on Ultrasonic Sensor
#define LCD_Contrast 4 // connected to Contrast PIN of LCD display Module (V0 PIN)
             // sets the Contrast of Background
#define LCD_Anode 5 // connects to Anode PINS of LCD display module (A PIN)

LiquidCrystal lcd(22,23,24,25,26,27); // PINS for LCD Module ( DIGITAL PINS )  

char keys[4][4]={ // Layout for keypad 
 {'1','2','3','A'},
 {'4','5','6', 'B'},
 {'7','8','9', 'C'},
 {'*','0','#', 'D'} };
 


byte rowPin[4]={28,29,30,31}; // row pins for keypad (DIGITAL PINS)
byte colPin[4]={32,33,34,35}; // column pins for keypad (DIGITAL PINS)



Servo servo_Motor; 
#define Password_lenght 4 //Change the password LENGHT 
String password = "XXXX";  // Set your Default password .
int position = 0; // variable for determining the Position.

int wrong = 0; // variable to determine the wrong input.

volatile int Brightness ; // detects brigthness in int 366 - 1018 
int Dist; // stores the distance measured  in cm

int distance;// stores the Distance measured by UltraSonic Sensor
int duration;// stores the time Duration for return ultrasonic Sound pulse

const int redPin = 9; // Define the pin for RED LED
const int greenPin = 8; // Define the pin for GREEN LED

const int ROWS = 4;
const int COLM = 4;
int count;

// Mapping of the layout to the Keypad.


int total = 0; // Variable to determine number of wrong Attempts .
int runn = 0;

Keypad keypad=Keypad(makeKeymap(keys),rowPin,colPin,ROWS,COLM);
// Prototype Declaration Section.

void setLocked(int locked);
void buzzer_beep();
void reset();
int DistanceMeasure();

// SUBROUTINE Section of the Program

void setup()
{

  pinMode( redPin , OUTPUT ); // Switches ON the GPIO & makes it O/P PIN
  pinMode( greenPin , OUTPUT );
  pinMode( LDR_PIN , INPUT ); // Switches ON the GPIO & makes it I/P PIN
  pinMode( UltraSonic_trigPIN , OUTPUT );
  pinMode( UltraSonic_echoPIN , INPUT );

  lcd.begin(16,2);


  servo_Motor.attach(Servo_PIN);
  setLocked(true);

  delay(1000);
  
  pinMode(buzzer, OUTPUT);

}

void loop()
{
 Dist = DistanceMeasure();
 if (Dist < 30 )// if Distance Measured is Less than 30cm then only the only the LCD Screen will be Switched on.
 {
  if ( runn == 0)
  {
    lcd.setCursor(0,0);
    lcd.print("   Welcome to ");
    lcd.setCursor(0,1);
    lcd.print("DOOR LOCK SYSTEM");
    delay(2000);
    lcd.clear();  
    lcd.setCursor(0,0);
    lcd.print("Enter Password:");
    delay(100);
    runn++;  
  } 

   Brightness = analogRead(LDR_PIN);

   analogWrite(LCD_Contrast , Brightness / 13);
   analogWrite(LCD_Anode , 80-Brightness/13 );
   
   lcd.setCursor(0,0);
   lcd.print("Enter Password:");
   delay(100);
    
   char pressed=keypad.getKey();// TAKING THE INPUT FROM KEYPAD
   String key[Password_lenght];
    
   if(pressed) // IF THE KEY IS PRESSED
   {
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Enter Password:");
      lcd.setCursor(0,1);

      for(count = 0 ; count < position ; count++)
      {
          lcd.print("*");// this part converts the character of your password to "*" after few seconds
      }

      lcd.setCursor(position,1);
      lcd.blink();
      lcd.print(pressed);
      delay(500);
        if(pressed == '*' || pressed == '#')
          {
              position = 0;
              setLocked(true);
              lcd.clear();
          }

        else if(pressed == password[position])
          {
              // In case of correct input increment by 1.
              position++;
          }
     
        else if (pressed != password[position] )
          {// In case of worng input increment both wrong and position by 1.
              wrong++;
              position ++;
          }

        if(position == Password_lenght)
          {// WHEN POSITION == Password_lenght Then Checks The Following conditions
              if( wrong >0 ) // If any character of Password is Wrong then increment total by 1.
              // Set wrong & position to 0.
                {
                    total++;
                    wrong = 0;
                    position = 0;
                    lcd.clear();
                    lcd.print("WRONG");
                    lcd.setCursor(5,2);
                    lcd.print("PASSWORD");
                    delay(1000);
                    setLocked(true);
                }

              else if(position == Password_lenght && wrong == 0)
                {// If there is no wrong Character the display  
                  // MOVE THE SERVO MOTOR.
                    position = 0;
                    wrong = 0;
                    lcd.clear();
                    lcd.setCursor(0,0);
                    lcd.print("PASSWORD");
                    lcd.setCursor(0,1);
                    lcd.print("ACCEPTED!");
                    delay(2000);
                    lcd.clear();
                    lcd.print("Door Open");
                    delay(2000);
                    setLocked(false);
                }

              if(total == 3)// IF TOTAL OF 3 ATTEMPTS ARE DONE BY ENTERING WRONG PASS
              //WORD THEN SOUND A BUZZER AND SET TOTAL TO 0.
                {
                    total=0;
                    buzzer_beep();
                    lcd.noDisplay();
                    delay(2*60*1000);// display goes of for 2 mins
                    lcd.display();
                    reset();
                }

            }

     }

     }
  else{
    lcd.noDisplay();
    reset();
  }
}

void setLocked(int locked)// FUNCTION TO CHANGE STATUS OF SERVO MOTOR.
  {
    if (locked)
      {
          digitalWrite(redPin, HIGH);
          digitalWrite(greenPin, LOW);
          delay(1000);
          servo_Motor.attach(Servo_PIN);
          servo_Motor.write(10);
          delay(1000);
          servo_Motor.detach();
      }
    else
      {
          digitalWrite(redPin, LOW);
          digitalWrite(greenPin, HIGH);
          delay(1000);
          servo_Motor.attach(Servo_PIN);
          servo_Motor.write(90);      
          delay(30*1000);// door will remain Open for 2 mins
          servo_Motor.detach(); 
       }
  }

void buzzer_beep()// FUNCTION TO BEEP THE BUZZER.
{
  for (count = 0 ;count < 5 ; count++ )
  {
      digitalWrite(buzzer,HIGH);
      digitalWrite(redPin,HIGH);
      delay(1000);
      digitalWrite(buzzer,LOW);
      digitalWrite(redPin,LOW);
      delay(1000);
    }

   
}

void reset() // Resets the variables back to start 
{
  total = 0;  
  wrong = 0;
  position = 0;
  runn = 0;
  servo_Motor.attach(Servo_PIN);
  servo_Motor.write(0);
  servo_Motor.detach();

}

int DistanceMeasure()
{
  // Clears the trigPin
  digitalWrite(UltraSonic_trigPIN, LOW);
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(UltraSonic_trigPIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(UltraSonic_trigPIN, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(UltraSonic_echoPIN, HIGH);
  // Calculating the distance
  distance= duration*0.034/2;
  return distance;

}
