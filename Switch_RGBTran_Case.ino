/*
NOTE - Common Anode so 255 = "off" and 0 = "on"

HOWEVER -- when incorporating a tip120 -- 255 = "on" and 0 = "off"

1 switch
each button press - new function
  push counter == ??
  
1 - turn solid color (white)
2 - change color -- intense green
3 - change color -- intense purple
4 - fade
  -> fades off -- 2 sec delay + 2 loops?
  
  NOTE -- initial fade jumps between colors before starting actual fade
  
*/

#define REDPIN 9
#define GREENPIN 11
#define BLUEPIN 6
 
#define FADESPEED 10           // make this higher to slow down
int SWITCHPIN = 12;
int buttonPushCounter = 0;   // counter for the number of button presses
int buttonState = 0;         // current state of the button
int lastButtonState = 0;     // previous state of the button

void setup() {
  pinMode(REDPIN, OUTPUT);
  pinMode(GREENPIN, OUTPUT);
  pinMode(BLUEPIN, OUTPUT);
  pinMode(SWITCHPIN, INPUT);
  Serial.begin(9600);
}
 
 
void loop() {
  buttonState = digitalRead(SWITCHPIN);
  if (buttonState != lastButtonState) {
    if (buttonState == HIGH) {
      buttonPushCounter++;
    }
  } 
    else {
    }
  
  lastButtonState = buttonState;
  
  switch (buttonPushCounter) {
    case 0:
//      Serial.println("Off until pressed");
      setColor(0, 0, 0);
      break;
    case 1:
      Serial.println("Turn White");
      setColor(255, 255, 255);
      break;
    case 2:   
      Serial.println("Change Color - red");
      setColor(255, 0, 0);
      break;
    case 3:
      Serial.println("Change Color - green");
      setColor(0, 255, 0);
      break;
    case 4:    
      Serial.println("Fade to off");
      fade();
      break;
    case 5:
      buttonPushCounter = 0;
      Serial.println(buttonPushCounter);
     break;
  }
  
  delay(150);        // delay in between reads for stability

}

void fade(){
    for (int x = 0; x < 2; x++){
      Serial.println(x);
      RGB();
    }
    Serial.println("end fade");
    for (int b = 255; b > 0; b--){
      analogWrite(BLUEPIN, b);
      delay(FADESPEED);
    }
   
    buttonPushCounter = 0;
}

void RGB(){
  
    int r, g, b;
 
  // fade from blue to violet -- red to violet
  Serial.println("blue to violet");
  for (r = 0; r < 256; r++) { 
    analogWrite(REDPIN, r);
    delay(FADESPEED);
  } 
  // fade from violet to red -- violet to green
  Serial.println("violet to red");
  for (b = 255; b > 0; b--) { 
    analogWrite(BLUEPIN, b);
    delay(FADESPEED);
  } 
  // fade from red to yellow
  Serial.println("red to yellow");
  for (g = 0; g < 256; g++) { 
    analogWrite(GREENPIN, g);
    delay(FADESPEED);
  } 
  // fade from yellow to green
  Serial.println("yellow to green");
  for (r = 255; r > 0; r--) { 
    analogWrite(REDPIN, r);
    delay(FADESPEED);
  } 
  // fade from green to teal
  Serial.println("green to teal");
  for (b = 0; b < 256; b++) { 
    analogWrite(BLUEPIN, b);
    delay(FADESPEED);
  } 
  // fade from teal to blue
  Serial.println("teal to blue");
  for (g = 255; g > 0; g--) { 
    analogWrite(GREENPIN, g);
    delay(FADESPEED);
  } 
 
}

void setColor(int red, int green, int blue)
{
  analogWrite(REDPIN, red);
  analogWrite(GREENPIN, green);
  analogWrite(BLUEPIN, blue);  
}

