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
}
void loop() {
  if (digitalRead(upbutton) == HIGH){
    upflag = true;
    downflag = false;
    digitalWrite(upled, HIGH);
    digitalWrite(downled, LOW);
    digitalWrite(startled, LOW);
    digitalWrite(stopled, LOW);
  }//end if 
  if (digitalRead(downbutton) == HIGH){
    downflag = true;
    upflag = false;
    digitalWrite(downled, HIGH);
    digitalWrite(upled, LOW);
    digitalWrite(startled, LOW);
    digitalWrite(stopled, LOW); 
  }//end if 
  if (digitalRead(startbutton) == HIGH){
    if (downflag || upflag){
      startflag = true;
      digitalWrite(startled, HIGH);
    }//end if 
  }//end if 
  else if (digitalRead(startbutton) == LOW){
    startflag = false;
    digitalWrite(startled, LOW);
  }//end else if 
  if (digitalRead(stopbutton) == HIGH){
    startflag = false;
    downflag = false;
    upflag = false;
    digitalWrite(downled, LOW);
    digitalWrite(upled, LOW);
    digitalWrite(startled, LOW);
    digitalWrite(stopled, HIGH); 
  }//end if 
  else if (digitalRead(stopbutton) == LOW){
    digitalWrite(stopled, LOW);
  }//end else if 
  if (startflag){
    
  }




}
