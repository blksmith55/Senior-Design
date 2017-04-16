const int upbutton = 2;
const int upled = 3;
const int downbutton = 4;
const int downled = 5;
const int startbutton = 6;
const int startled = 7;
const int stopbutton = 8;
const int stopled = 9;
const int pot = A0;
const int pwmout1 = 10;
const int pwmout2 = 11;
const int pwmdir1 = 12;
const int pwmdir2 = 13;
int potval = 0;
boolean startflag = false;
boolean stopflag = false;
boolean upflag = false;
boolean downflag = false;

void setup() {
 pinMode(upbutton, INPUT);
 pinMode(upled, OUTPUT);
 pinMode(downbutton, INPUT);
 pinMode(downled, OUTPUT);
 pinMode(startbutton, INPUT);
 pinMode(startled, OUTPUT);
 pinMode(stopbutton, INPUT);
 pinMode(stopled, OUTPUT);
 pinMode(pwmdir1, OUTPUT);
 pinMode(pwmdir2, OUTPUT);
}
void loop() {
  //==================================Reading Up and Down Buttons============================================
 if (digitalRead(upbutton) == LOW){ //if up button is pressed
    if (downflag){ //if down is already on, turn off motors and delay
      analogWrite(pwmout1, 0);
      analogWrite(pwmout2, 0);
      delay(500);
    }//end if 
    if (downflag && startflag){
      digitalWrite(startled, LOW);
      startflag = false;
    }//end if
    upflag = true;  //update flags
    downflag = false;
    digitalWrite(upled, HIGH); //turn on and off LEDs
    digitalWrite(downled, LOW);
    digitalWrite(startled, LOW);
    digitalWrite(stopled, LOW);
  }//end if 
  if (digitalRead(downbutton) == LOW){ //if down button is pressed
    if (upflag){  //if up is already on, turn off motors and delay
      analogWrite(pwmout1, 0);
      analogWrite(pwmout2, 0);
      delay(500);
    }
    if (upflag && startflag){
      digitalWrite(startled, LOW);
      startflag = false;
    }//end if
    downflag = true; //update flags
    upflag = false;
    digitalWrite(downled, HIGH); //turn on and off LEDs
    digitalWrite(upled, LOW);
    digitalWrite(startled, LOW);
    digitalWrite(stopled, LOW); 
  }//end if 
//========================================Reading Start Button========================================
  if (digitalRead(startbutton) == LOW){ //if start button is held down
    if (downflag || upflag){ //if either up or down flag is on
      startflag = true; //turn startflag on
      digitalWrite(startled, HIGH); //turn start LED on
    }//end if 
  }//end if 
  else if (digitalRead(startbutton) == HIGH){ //if start button is not being pressed
    startflag = false;  //startflag off
    digitalWrite(startled, LOW); //start LED off
    analogWrite(pwmout1, 0);
    analogWrite(pwmout2, 0);
  }//end else if 
//========================================Reading Stop Button==========================================
  if (digitalRead(stopbutton) == LOW){ //if stop button is pressed
    stopflag = true; //turn stopflag on
    startflag = false; //turn all flags off
    downflag = false;
    upflag = false;
    digitalWrite(downled, LOW); //turn all other LEDs off
    digitalWrite(upled, LOW);
    digitalWrite(startled, LOW);
    digitalWrite(stopled, HIGH); //turn stop LED on
  }//end if 
  else if (digitalRead(stopbutton) == HIGH){ //if stop button isn't pressed
    digitalWrite(stopled, LOW); //turn stop led off
    if (stopflag){ //if stopflag is true, delay 2 seconds then reset stopflag 
      delay(2000);
      stopflag = false;
    }//end if 
  }//end else if 
//==============================Reading Potentiometer========================================
potval = analogRead(pot); //read pot
potval = potval*255/1023;
if (potval > 875){ //capping max value
  potval = 220;
}
//=============================Setting PWM Direction=========================================
  if (upflag){ //if up mode is on
    digitalWrite(pwmdir1, HIGH);
    digitalWrite(pwmdir2, LOW);
  }//end if 
  else if (downflag) { //if down mode is on
    digitalWrite(pwmdir1, LOW);
    digitalWrite(pwmdir2, HIGH);
  }//end else if 
//===============================Outputting PWM==============================================
  if (startflag){ //if startflag is on
    analogWrite(pwmout1, potval);
    analogWrite(pwmout2, potval);
  }//end if 
  if (stopflag){ //if stopflag is hit
    analogWrite(pwmout1, 0);
    analogWrite(pwmout2, 0);
  }
}//end main loop
