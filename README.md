# Digital-Door-Lock
___

## Introduction & Overview

Digital Door lock system using Arduino MEGA.
Automatically Switches on the LCD screen when one goes in front of the door lock system. 
If the correct Password is entered then the lock opens up for 2 minutes, else after three wrong attempts,
the buzzer buzzes for  10 seconds and then the screen is switched off for 2 minutes.

___

## Components Used 

1. Arduino MEGA
2. LCD Sreen Module
3. UltraSonic Sensor Module
4. 4 X 4 Matrix Membrane Keypad
5. LDR
6. Piezo Buzzer
7. Servo Motor
8. Breadboard
9. Resistors ,LEDs ,Jumper Wire

___

## Working 

Digital door lock system is similar to digital Godrej Digital Lock. Some additional features are added to digital door lock system. 
System <b> uses Ultrasonic sensors to activate to Door-lock-System's LCD Screen</b> hence saves power by activating screen only when the person comes in front of the Door Lock system. Further we use <b>LDR to automatically Adjust the Brightness of the Screen and sharpness of characters on the Screen  according to the Lighting Condition</b>, brightness problem is a common issue in various LCD based Embedded devices.

To Unlock the Door system we have to Enter correct PIN from Keypad. If PIN Entered is correct is then Servo motor rotates by 90 degree
and unlockes the door. Digital Door System gives 3 Attempts to Door lock system after the Red LED Flashes along with the Piezo Buzzer
And Screen switches OFF for 2 mins.

___

## Code Burning

Take the Library uploaded and paste them in<b> Libraries</b> folder inside the Arduino Folder. Libararies are provided by<b> Arduino</b> itself, but some Libraries are not present by default some we need to add them, in such case we can add them by putting it into libraries folder. Take the code for Arduino , select Arduino Mega in<b> Tool>Board </b>option , futher select COM port and then burn the code.

___
